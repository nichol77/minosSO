#include <iostream>
#include <fstream>
#include "TFile.h"
#include "TF1.h"
#include "TH1.h"
#include "TTree.h"
#include "TH2.h"
#include "TSystem.h"
#include "TMath.h"
#include "TCanvas.h"
#include "TDirectory.h"
#include "TGraphAsymmErrors.h"
#include "TGraphErrors.h"
#include "TString.h"
#include "TKey.h"
#include "TLegend.h"
#include "TROOT.h"
#include "src/paramFuncs.h"


void plotAlexErrorBand() {
   int run=11;

   TH1::AddDirectory(kFALSE);
   
   char histName[180];
   char fileName[180];
   char dirName[180];
   char mcPotName[180];
   char dataPotName[180];
   char inFile[180];

   Double_t binEdge[]={0,0.5,0.75,1,1.25,1.5,1.75,2,2.25,2.5,2.75,3,3.25,3.5,3.75,4,4.25,4.5,4.75,5,5.25,5.5,5.75,6,6.25,6.5,6.75,7,7.25,7.5,7.75,8,8.25,8.5,8.75,9,9.25,9.5,9.75,10,10.25,10.5,10.75,11,11.25,11.5,11.75,12,12.25,12.5,12.75,13,13.25,13.5,13.75,14,14.25,14.5,14.75,15,15.25,15.5,15.75,16,16.25,16.5,16.75,17,17.25,17.5,17.75,18,18.25,18.5,18.75,19,19.25,19.5,19.75,20,21,22,23,24,25,26,27,28,29,30,32,34,36,38,40,42,44,46,48,50,200};

   TFile *fpError = TFile::Open("farFiles/alexErrorBand.root","RECREATE");
   TH1D *histLowRatio[2]={0};
   TH1D *histHighRatio[2]={0};
   
   const char *alexHistNameArray[2]={"RecoEnergy_FD","RecoEnergyPQ_FD"};
   const char *histNameArray[4]={"histEnergyNQ","histEnergyPQ","histEnergyNC","histEnergyNCTrack"};
   const char *predHistNameArray[4]={"histPredNQ","histPredPQ","histPredNC","histPredNCTrack"};
   const char *fileTypeTag[3]={"main","nue","tau"};
   const char *potFileTypeTag[3]={"","Nue","Tau"};
   
   
   const char *runNameArray[11]={"run1","run2","run3","run4","run5","run6","run7","run8","run9","run10","run11"};
   const char *histNameTagArray[11]={"run1","run2","run3","run4","run5","run6","run7","run8","run9","run10","minosplus"};
   


  sprintf(dataPotName,"pot/%sFDDataPOT.txt",runNameArray[run-1]);
  std::ifstream DataPotFile(dataPotName);
  if(!DataPotFile) {
    std::cerr << "Can not open " << dataPotName << "\n";
    return;
  }
  Double_t dataPOT=0;
  DataPotFile >> dataPOT;

 

  Double_t mcPOT[3]; //main, nue and tau
  Double_t scaleFactor[3]; //main, nue and tau
  
  //Loop over main, nue , tau
  for(int fileType=0;fileType<3;fileType++) { 

    sprintf(mcPotName,"pot/%sFD%sMCPOT.txt",runNameArray[run-1],potFileTypeTag[fileType]);
    std::ifstream McPotFile(mcPotName);
    if(!McPotFile) {
      std::cerr << "Can not open " << mcPotName << "\n";
      continue;
    }
    McPotFile >> mcPOT[fileType];     
     
    scaleFactor[fileType]=dataPOT/mcPOT[fileType];
    std::cout << "Run " << runNameArray[run-1] << " " << fileTypeTag[fileType] << "\t" << dataPOT << "\t" << mcPOT[fileType] << "\t" << scaleFactor[fileType] << "\n";
  }


  
  Int_t dmi=68;
  Int_t t23i=44;
  Int_t t13i=0;
  Int_t deltai=0;

  TFile *fpPreds[3];
  for(int fileType=0;fileType<3;fileType++) {
     sprintf(fileName,"/unix/minos1/rjn/ccPlusNc/farPreds/%s/%s%d.root",runNameArray[run-1],fileTypeTag[fileType],dmi);
     fpPreds[fileType] = TFile::Open(fileName);
  }
     
  TDirectory *fpDirs[3];      
  for(int fileType=0;fileType<3;fileType++) {
     if(!fpPreds[fileType]) continue;
     sprintf(dirName,"/dmi%d/t23i%d",dmi,t23i);
     fpPreds[fileType]->cd(dirName);
     fpDirs[fileType]=gDirectory;
  }


  TH1D *histPred[2];

  //Loop over the two types of fake data
  for(int histType=0;histType<2;histType++) {		 
     histPred[histType] = new TH1D(predHistNameArray[histType],"histPred",100,binEdge);
     for(int fileType=0;fileType<3;fileType++) {		 
	if(!fpPreds[fileType]) continue;
	sprintf(histName,"%s_%d_%d_%d_%d",predHistNameArray[histType],dmi,t23i,t13i,deltai);
	TH1D *histTemp = (TH1D*) fpDirs[fileType]->Get(histName);
	
	if(!histTemp) {
	   std::cout << "Can't find " << histName << "\n";
	   break;
	}
	histTemp->Scale(scaleFactor[fileType]);
	histPred[histType]->Add(histTemp);
	delete histTemp;
     }
     
     
  }

  TH1D *histNumEvents = new TH1D("histNumEvents","histNumEvents",400,1000,1400);
  TH1D *histNumEventsPred = new TH1D("histNumEventsPred","histNumEventsPred",400,1000,1400);
  TH1D *histPredDiff = new TH1D("histPredDiff","histPredDiff",200,-100,100);


  int firstTime=1;

  
  Double_t energyVals[1000]={0};
  Double_t ratioVals[1000]={0};
  Double_t rmsVals[1000]={0};
  Double_t ratioSqVals[1000]={0};
  Int_t numRatios=0;

   for(int alexRun=0;alexRun<1000;alexRun++) {
      sprintf(inFile,"/unix/minos1/rjn/altHornCurr/farHornCurrNorm_%d.root",alexRun);
      
      char ratioFile[180];
      sprintf(ratioFile,"/unix/minos1/rjn/altHornCurr/ratios/nearHornCurrNorm_rat_%d.root",alexRun);
      
      TFile *fpRatio = TFile::Open(ratioFile);
      if(!fpRatio) {
	 std::cerr << "Can not open " << ratioFile << "\n";
	 continue;
      }
      
      TH1D *ratioHists[2];
      ratioHists[0]=(TH1D*) fpRatio->Get("ratioNQ");
      ratioHists[1]=(TH1D*) fpRatio->Get("ratioPQ");

      TH1D *histNewPred[2];
      for(int histType=0;histType<2;histType++) {
	 histNewPred[histType] = (TH1D*) histPred[histType]->Clone();
	 //This is the line that "corrects" the FD predcition by the (ND Fake)/(ND Real) ratio
	 histNewPred[histType]->Multiply(ratioHists[histType]); 
      }


      
      //Next step is to open the Alex FD data files
      TFile *fpData = TFile::Open(inFile,"OLD");      
      if(!fpData) {
	 std::cerr << "Can not open " << inFile << "\n";
	 //      continue;
	 return;
      }
      
      //Read in the  data files
      TH1D *histData[2]={0};
      
      //Loop over the two types of data
      TH1D *hTotalPotData = (TH1D*)fpData->Get("hTotalPot");
      
      for(int histType=0;histType<2;histType++) {
	 sprintf(histName,"%s",alexHistNameArray[histType]);
	 histData[histType] = (TH1D*) fpData->Get(histName);
	 if(!histData[histType]) {
	    std::cerr << "Couldn't get " << histName << "\n";
	    break;
	 }
	 
	 //RJN -- Need to think if this is the correct thing to do, or if we should just hcange the data POT to match the Fake Data
	 histData[histType]->Scale(dataPOT/hTotalPotData->Integral()); 

	 
	 if(histType==0) {
	   histNumEvents->Fill(histData[histType]->Integral());
	   histNumEventsPred->Fill(histNewPred[histType]->Integral());
	   histPredDiff->Fill(histData[histType]->Integral()-histNewPred[histType]->Integral());
	 }


	 //Now we take the ratio of data to my scaled prediction
	 TH1D *ratio = (TH1D*) histData[histType]->Clone();
	 ratio->Divide(histNewPred[histType]);
// 	 if(firstTime) {
// 	   ratio->DrawClone();
// 	   firstTime=0;
// 	 }
// 	 else
// 	   ratio->DrawClone("same");


	 for(int bin=1;bin<=ratio->GetNbinsX();bin++) {
	   Double_t val=ratio->GetBinContent(bin);
	   energyVals[bin-1]=ratio->GetBinCenter(bin);
	   ratioVals[bin-1]+=val;
	   ratioSqVals[bin-1]+=val*val;
	 }
	 numRatios++;


	 fpError->cd();
	 if(!histLowRatio[histType]) {
	    sprintf(histName,"histLowRatio_%s",histNameArray[histType]);
	    histLowRatio[histType]=(TH1D*)ratio->Clone(histName);
	    histLowRatio[histType]->SetName(histName);
	 }
	 else {
	    for(int bin=1;bin<=histLowRatio[histType]->GetNbinsX();bin++) {
	       double val=ratio->GetBinContent(bin);
	       if(val<histLowRatio[histType]->GetBinContent(bin)) {
		  histLowRatio[histType]->SetBinContent(bin,val);
	       }
	    }
	 }


	 if(!histHighRatio[histType]) {
	    sprintf(histName,"histHighRatio_%s",histNameArray[histType]);
	    histHighRatio[histType] =(TH1D*)ratio->Clone(histName);
	    histHighRatio[histType]->SetName(histName);
	 } 
	 else {
	    for(int bin=1;bin<=histHighRatio[histType]->GetNbinsX();bin++) {
	       double val=ratio->GetBinContent(bin);
	       if(val>histHighRatio[histType]->GetBinContent(bin)) {
		  histHighRatio[histType]->SetBinContent(bin,val);
	       }
	    }
	 }
      }
      fpRatio->Close();
      fpData->Close();

   }
   TCanvas *can2  = new TCanvas("can2","can2",800,800);
   can2->Divide(1,2);
   can2->cd(1);
   histNumEvents->SetXTitle("Number of Events");
   histNumEvents->Draw();
   histNumEventsPred->SetLineColor(kRed+2);
   histNumEventsPred->Draw("sames");
   TLegend *leggy = new TLegend(0.7,0.7,0.9,0.9);
   leggy->SetFillColor(0);
   leggy->SetFillStyle(0);
   leggy->SetBorderSize(0);
   leggy->AddEntry(histNumEvents,"Fake Data","l");
   leggy->AddEntry(histNumEventsPred,"Prediction","l");
   leggy->Draw("same");
   
   can2->cd(2);
   histPredDiff->SetXTitle("Num Events (Fake Data - Prediction)");
   histPredDiff->Draw();
   
   

   Double_t xVals[1000];
   Double_t exLowVals[1000];
   Double_t exHighVals[1000];
   Double_t yVals[1000];
   Double_t eyLowVals[1000];
   Double_t eyHighVals[1000];

   for(int i=0;i<histHighRatio[0]->GetNbinsX();i++) {
     ratioVals[i]/=numRatios;
     ratioSqVals[i]/=numRatios;
     rmsVals[i]=TMath::Sqrt(ratioSqVals[i]-ratioVals[i]*ratioVals[i]);

      int bin=i+1;
      xVals[i]=histHighRatio[0]->GetBinCenter(bin);
      exLowVals[i]=0.5*histHighRatio[0]->GetBinWidth(bin);
      exHighVals[i]=0.5*histHighRatio[0]->GetBinWidth(bin);

      Double_t high=histHighRatio[0]->GetBinContent(bin);
      Double_t low=histLowRatio[0]->GetBinContent(bin);
      yVals[i]=0.5*(high+low);
      eyLowVals[i]=yVals[i]-low;
      eyHighVals[i]=high-yVals[i];

//      std::cout << xVals[i] << "\t" << yVals[i] << "\t"
//		<< exLowVals[i] << "\t" << exHighVals[i] << "\t"
//		<< eyLowVals[i] << "\t" << eyHighVals[i] << "\n";

   }
   
   
   fpError->cd();
   TCanvas *can = new TCanvas();
   TGraphAsymmErrors *gr= new TGraphAsymmErrors(histHighRatio[0]->GetNbinsX(),
						xVals,yVals,
						exLowVals,exHighVals,
						eyLowVals,eyHighVals);
   gr->Draw("a3");
   gr->GetXaxis()->SetTitle("Neutrino Energy (GeV)");
   gr->GetYaxis()->SetTitle("Error Band");
   gr->GetXaxis()->SetRangeUser(0,20);
   gr->GetYaxis()->SetRangeUser(0.8,1.2);

   gr->SetName("grAlexError");
   gr->Write();



   TCanvas *can3 = new TCanvas();
   TGraphErrors *gr2= new TGraphErrors(histHighRatio[0]->GetNbinsX(),
				       xVals,ratioVals,0,rmsVals);
   gr2->Draw("al3");
   gr2->GetXaxis()->SetTitle("Neutrino Energy (GeV)");
   gr2->GetYaxis()->SetTitle("Error Band");
   gr2->GetXaxis()->SetRangeUser(0,20);
   gr2->GetYaxis()->SetRangeUser(0.8,1.2);
   
   gr2->SetName("grAlexMeanRMS");
   gr2->Write();

   fpError->Write();

}
