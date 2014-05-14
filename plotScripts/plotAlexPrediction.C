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
#include "TString.h"
#include "TKey.h"
#include "TROOT.h"
#include "src/paramFuncs.h"

void plotAlexPrediction(int alexRun);

void plotAlexPrediction() {
   plotAlexPrediction(10);
}

void plotAlexPrediction(int alexRun) {
   int run=11;

  TH1::AddDirectory(kFALSE);

   char histName[180];
   char fileName[180];
   char dirName[180];
   char mcPotName[180];
   char inFile[180];
   sprintf(inFile,"/unix/minos1/rjn/altHornCurr/farHornCurrNorm_%d.root",alexRun);

   char ratioFile[180];
   sprintf(ratioFile,"/unix/minos1/rjn/altHornCurr/ratios/nearHornCurrNorm_rat_%d.root",alexRun);

   TFile *fpRatio = TFile::Open(ratioFile);
   if(!fpRatio) {
      std::cerr << "Can not open " << ratioFile << "\n";
      return;
   }

   TH1D *ratioHists[2];
   ratioHists[0]=(TH1D*) fpRatio->Get("ratioNQ");
   ratioHists[1]=(TH1D*) fpRatio->Get("ratioPQ");




   sprintf(fileName,"fakeSurfaces/altHornCurr/fakeSurface_%d.root",alexRun);
   TFile *fpSurface = TFile::Open(fileName);
   if(!fpSurface) continue;
   
   TH2D *histNQ = (TH2D*) fpSurface->Get("histNormal_histEnergyNQ_0_0");
   Int_t minBinx=0,minBiny=0,minBinz=0;
   histNQ->GetMinimumBin(minBinx,minBiny,minBinz);
   std::cout << "Minimum bin: " << minBinx << "\t" << minBiny << "\n";
   std::cout << "Minimum theta23: " << histNQ->GetXaxis()->GetBinCenter(minBinx) << "\t" << getT23IFromT23(histNQ->GetXaxis()->GetBinCenter(minBinx)) << "\n";
   std::cout << "Minimum dm2: " << histNQ->GetYaxis()->GetBinCenter(minBiny) << "\t" << getDmiFromDm(1e-3*histNQ->GetYaxis()->GetBinCenter(minBiny)) << "\n";
   new TCanvas();
   histNQ->Draw("COLZ");


  Double_t binEdge[]={0,0.5,0.75,1,1.25,1.5,1.75,2,2.25,2.5,2.75,3,3.25,3.5,3.75,4,4.25,4.5,4.75,5,5.25,5.5,5.75,6,6.25,6.5,6.75,7,7.25,7.5,7.75,8,8.25,8.5,8.75,9,9.25,9.5,9.75,10,10.25,10.5,10.75,11,11.25,11.5,11.75,12,12.25,12.5,12.75,13,13.25,13.5,13.75,14,14.25,14.5,14.75,15,15.25,15.5,15.75,16,16.25,16.5,16.75,17,17.25,17.5,17.75,18,18.25,18.5,18.75,19,19.25,19.5,19.75,20,21,22,23,24,25,26,27,28,29,30,32,34,36,38,40,42,44,46,48,50,200};

  const char *alexHistNameArray[2]={"RecoEnergy_FD","RecoEnergyPQ_FD"};
  const char *histNameArray[4]={"histEnergyNQ","histEnergyPQ","histEnergyNC","histEnergyNCTrack"};
  const char *predHistNameArray[4]={"histPredNQ","histPredPQ","histPredNC","histPredNCTrack"};
  const char *fileTypeTag[3]={"main","nue","tau"};
  const char *potFileTypeTag[3]={"","Nue","Tau"};
  
 
  const char *runNameArray[11]={"run1","run2","run3","run4","run5","run6","run7","run8","run9","run10","run11"};
  const char *histNameTagArray[11]={"run1","run2","run3","run4","run5","run6","run7","run8","run9","run10","minosplus"};

 //Next step is to open the Alex FD data files
  TFile *fpData = TFile::Open(inFile,"OLD");      
  if(!fpData) {
    std::cerr << "Can not open " << inFile << "\n";
    //      continue;
    return;
  }
  
  //Read in the  data files
  TH1D *histData[2]={0};
  Double_t numEventsTot[2]={0};
  
  //Loop over the two types of data
  TH1D *hTotalPotData = (TH1D*)fpData->Get("hTotalPot");
  Double_t dataPOT=hTotalPotData->Integral();

  for(int histType=0;histType<2;histType++) {
     sprintf(histName,"%s",alexHistNameArray[histType]);
     histData[histType] = (TH1D*) fpData->Get(histName);
     if(!histData[histType]) {
	std::cerr << "Couldn't get " << histName << "\n";
	break;
     }

     //RJN -- Need to think if this is the correct thing to do, or if we should just hcange the data POT to match the Fake Data
     //     histData[histType]->Scale(dataPOT/hTotalPotData->Integral());     
     numEventsTot[histType]=histData[histType]->Integral();
  }




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


  
  for(int histType=0;histType<2;histType++) {	  	
    std::cout << "Integral " << histNameArray[histType] << "\t" << numEventsTot[histType] << "\n";
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
     
     if(!histData[histType]) {
	std::cerr << "No data\n";
	break;
     }
     
     //This is the line that "corrects" the FD predcition by the (ND Fake)/(ND Real) ratio
     histPred[histType]->Multiply(ratioHists[histType]);          
  }
  
  TCanvas *can = new TCanvas("can","can",800,800);
  can->Divide(1,2);
  can->cd(1);
  histData[0]->Draw();
  histPred[0]->SetLineColor(kRed+2);
  histPred[0]->Draw("same");
  can->cd(2);
  TH1D *ratio = (TH1D*) histData[0]->Clone();
  ratio->Divide(histPred[0]);
  ratio->Draw();
  ratioHists[0]->SetLineColor(kBlue+2);
  ratioHists[0]->Draw("same");



}
