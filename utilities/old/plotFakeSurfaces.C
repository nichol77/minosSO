#include <iostream>
#include <fstream>
#include "TFile.h"
#include "TF1.h"
#include "TH1.h"
#include "TMath.h"
#include "TRandom.h"
#include "TCanvas.h"
#include "TH2.h"
#include "TGraph.h"
#include "TStyle.h"
#include "TMarker.h"
#include "TLegend.h"


#include "src/paramFuncs.h"

void subtractMinimum(TH2D*histCombi);
TH2D *convertToSin2Theta23(TH2D *histInput, char *histName) ;
Double_t th2dEval(TH2D *histInput, Double_t xValue, Double_t yValue);

int getNiceColour(int index)
{
  if(index>10) return index;
  Int_t niceColours[11]={kAzure+2,kRed+1,kGreen+1,kMagenta+1,kCyan+1,kOrange+2,kGreen-2,12,40,20,41};
  return niceColours[index];
}



Double_t simpleInterploate(Double_t x1, Double_t y1, Double_t x2, Double_t y2, Double_t x)
{
  return ((y2 - y1)* ((x - x1) / (x2-x1)) + y1);
}

Double_t simpleBilinearInterpolate(Double_t x[2], Double_t y[2], Double_t z[4], Double_t xp, Double_t yp) 
{
  //Here we have four points x[0],y[0] = z[0]
  //Here we have four points x[0],y[1] = z[1]
  //Here we have four points x[1],y[0] = z[2]
  //Here we have four points x[1],y[1] = z[3]


  Double_t a=z[0]*(x[1]-xp)*(y[1]-yp);
  Double_t b=z[2]*(xp-x[0])*(y[1]-yp);
  Double_t c=z[1]*(x[1]-xp)*(yp-y[0]);
  Double_t d=z[3]*(xp-x[0])*(yp-y[0]);

  return (a+b+c+d)/((x[1]-x[0])*(y[1]-y[0]));  
}




void plotFakeSurfaces(int fakeDmBin, int fakeT23bin)
{


  Double_t trueDm=1e3*getDeltaM2(fakeDmBin);
  Double_t trueT23=getT23(fakeT23bin);


  gStyle->SetOptStat(0);
  //   gStyle->SetOptTitle(0);
  char histName[180];
  char fileName[180];
  char canName[180];
  
  //  const char *fileTag[10]={"runi","runii","runiii","runiv","runv","runvi","runvii","runviii","runix","runx"};
  const char *histNameArray[6]={"histEnergyNQ","histEnergyPQ","histEnergyNC","histEnergyNCTrack","histEnergyNQRHC","histEnergyPQRHC"};
  //  const char *predHistNameArray[4]={"histPredNQ","histPredPQ","histPredNC","histPredNCTrack"};
  //  const char *fileTypeTag[3]={"main","nue","tau"};
  //  const char *potFileTypeTag[3]={"","Nue","Tau"};
  //  Int_t doRun[10]={1,1,1,1,1,1,1,0,1,1};
  Int_t doRun[10]={1,1,0,0,0,0,0,0,0,0};
  Int_t isRHC[10]={0,0,0,1,0,0,1,0,1,0};


  Double_t t23Array[4][1000]={0};
  Double_t dm2Array[4][1000]={0};
  Double_t t23ArrayTot[1000]={0};
  Double_t dm2ArrayTot[1000]={0};
  Double_t t23ArrayPQNQ[1000]={0};
  Double_t dm2ArrayPQNQ[1000]={0};
  TH2D *histSum[10][6]={{0}};
  TH2D *histAll[10]={0};
  TH2D *histRunNQPQ[10]={0};

  //  TH2D *histRun
  TH2D *histRunJustFHC[10]={0};
  TH2D *histRunJustRHC[10]={0};
  
  Int_t numExps=1000;
  
  sprintf(histName,"histTotal");
  TH2D *histTotal = new TH2D(histName,histName,MAX_T23_INDEX,MIN_T23-0.5*T23_STEP_SIZE,MIN_T23+(MAX_T23_INDEX-0.5)*T23_STEP_SIZE,MAX_DMI_INDEX,1e3*(MIN_DM2-0.5*DM2_STEP_SIZE),1e3*(MIN_DM2+(MAX_DMI_INDEX-0.5)*DM2_STEP_SIZE));

  sprintf(histName,"histNQPQ");
  TH2D *histNQPQ = new TH2D(histName,histName,MAX_T23_INDEX,MIN_T23-0.5*T23_STEP_SIZE,MIN_T23+(MAX_T23_INDEX-0.5)*T23_STEP_SIZE,MAX_DMI_INDEX,1e3*(MIN_DM2-0.5*DM2_STEP_SIZE),1e3*(MIN_DM2+(MAX_DMI_INDEX-0.5)*DM2_STEP_SIZE));

  sprintf(histName,"histJustFHC");
  TH2D *histJustFHC = new TH2D(histName,histName,MAX_T23_INDEX,MIN_T23-0.5*T23_STEP_SIZE,MIN_T23+(MAX_T23_INDEX-0.5)*T23_STEP_SIZE,MAX_DMI_INDEX,1e3*(MIN_DM2-0.5*DM2_STEP_SIZE),1e3*(MIN_DM2+(MAX_DMI_INDEX-0.5)*DM2_STEP_SIZE));

  sprintf(histName,"histJustRHC");
  TH2D *histJustRHC = new TH2D(histName,histName,MAX_T23_INDEX,MIN_T23-0.5*T23_STEP_SIZE,MIN_T23+(MAX_T23_INDEX-0.5)*T23_STEP_SIZE,MAX_DMI_INDEX,1e3*(MIN_DM2-0.5*DM2_STEP_SIZE),1e3*(MIN_DM2+(MAX_DMI_INDEX-0.5)*DM2_STEP_SIZE));

  TH2D *histSix[6];
  for(int histType=0;histType<6;histType++) {
    sprintf(histName,"histSix_%s",histNameArray[histType]);
    histSix[histType] = new TH2D(histName,histName,MAX_T23_INDEX,MIN_T23-0.5*T23_STEP_SIZE,MIN_T23+(MAX_T23_INDEX-0.5)*T23_STEP_SIZE,MAX_DMI_INDEX,1e3*(MIN_DM2-0.5*DM2_STEP_SIZE),1e3*(MIN_DM2+(MAX_DMI_INDEX-0.5)*DM2_STEP_SIZE));
           
  }

  TFile *fpInRun[10]={0};

  //Loop over runs
  for(int runInd=0;runInd<10;runInd++) {
    if(!doRun[runInd]) continue;
    std::cerr << "*";

    sprintf(fileName,"fakeSurfaces/fakeSurface_run%d_%d_%d.root",runInd+1,fakeDmBin,fakeT23bin);
    fpInRun[runInd] = new TFile(fileName,"OLD");
    if(!fpInRun[runInd]) {
      std::cerr << "Can not open " << fileName << "\n";
      continue;
    }

    sprintf(histName,"histAllRun%d",runInd+1);
    histAll[runInd] = new TH2D(histName,histName,MAX_T23_INDEX,MIN_T23-0.5*T23_STEP_SIZE,MIN_T23+(MAX_T23_INDEX-0.5)*T23_STEP_SIZE,MAX_DMI_INDEX,1e3*(MIN_DM2-0.5*DM2_STEP_SIZE),1e3*(MIN_DM2+(MAX_DMI_INDEX-0.5)*DM2_STEP_SIZE));

    sprintf(histName,"histNQPQRun%d",runInd+1);
    histRunNQPQ[runInd] = new TH2D(histName,histName,MAX_T23_INDEX,MIN_T23-0.5*T23_STEP_SIZE,MIN_T23+(MAX_T23_INDEX-0.5)*T23_STEP_SIZE,MAX_DMI_INDEX,1e3*(MIN_DM2-0.5*DM2_STEP_SIZE),1e3*(MIN_DM2+(MAX_DMI_INDEX-0.5)*DM2_STEP_SIZE));

    sprintf(histName,"histJustFHCRun%d",runInd+1);
    histRunJustFHC[runInd] = new TH2D(histName,histName,MAX_T23_INDEX,MIN_T23-0.5*T23_STEP_SIZE,MIN_T23+(MAX_T23_INDEX-0.5)*T23_STEP_SIZE,MAX_DMI_INDEX,1e3*(MIN_DM2-0.5*DM2_STEP_SIZE),1e3*(MIN_DM2+(MAX_DMI_INDEX-0.5)*DM2_STEP_SIZE));


    sprintf(histName,"histJustRHCRun%d",runInd+1);
    histRunJustRHC[runInd] = new TH2D(histName,histName,MAX_T23_INDEX,MIN_T23-0.5*T23_STEP_SIZE,MIN_T23+(MAX_T23_INDEX-0.5)*T23_STEP_SIZE,MAX_DMI_INDEX,1e3*(MIN_DM2-0.5*DM2_STEP_SIZE),1e3*(MIN_DM2+(MAX_DMI_INDEX-0.5)*DM2_STEP_SIZE));
  
        
    for(int histType=0;histType<6;histType++) {	  	
      
      sprintf(histName,"histSumRun%d_%s",runInd+1,histNameArray[histType]);
      histSum[runInd][histType] = new TH2D(histName,histName,MAX_T23_INDEX,MIN_T23-0.5*T23_STEP_SIZE,MIN_T23+(MAX_T23_INDEX-0.5)*T23_STEP_SIZE,MAX_DMI_INDEX,1e3*(MIN_DM2-0.5*DM2_STEP_SIZE),1e3*(MIN_DM2+(MAX_DMI_INDEX-0.5)*DM2_STEP_SIZE));
              
    }
  }
  std::cerr << "\n";

  for(int exp=0;exp<numExps;exp++) {
    std::cerr << "#";
    TH2D histOneExp("histOneExp","histOneExp",MAX_T23_INDEX,MIN_T23-0.5*T23_STEP_SIZE,MIN_T23+(MAX_T23_INDEX-0.5)*T23_STEP_SIZE,MAX_DMI_INDEX,1e3*(MIN_DM2-0.5*DM2_STEP_SIZE),1e3*(MIN_DM2+(MAX_DMI_INDEX-0.5)*DM2_STEP_SIZE));
    TH2D histOneExpPQNQ("histOneExpPQNQ","histOneExpPQNQ",MAX_T23_INDEX,MIN_T23-0.5*T23_STEP_SIZE,MIN_T23+(MAX_T23_INDEX-0.5)*T23_STEP_SIZE,MAX_DMI_INDEX,1e3*(MIN_DM2-0.5*DM2_STEP_SIZE),1e3*(MIN_DM2+(MAX_DMI_INDEX-0.5)*DM2_STEP_SIZE));
    for(int runInd=0;runInd<10;runInd++) {
      if(!doRun[runInd]) continue;
      for(int histType=0;histType<4;histType++) {
	sprintf(histName,"histSurface_%s_%d",histNameArray[histType],exp);
	TH2D *histSurface = (TH2D*) fpInRun[runInd]->Get(histName);
	histOneExp.Add(histSurface);
	//	 Double_t minLL=histSurface->GetMinimum();
	Int_t minGlobBin=histSurface->GetMinimumBin();
	Int_t minBinX,minBinY,minBinZ;
	histSurface->GetBinXYZ(minGlobBin,minBinX,minBinY,minBinZ);
	Double_t minT23=histSurface->GetXaxis()->GetBinCenter(minBinX);
	Double_t minDm2=histSurface->GetYaxis()->GetBinCenter(minBinY);
	 	 
	//	 std::cout <<  minT23 << "\t" << minDm2 << "\n";
	t23Array[histType][exp]=minT23;
	dm2Array[histType][exp]=minDm2;
	 
	if(histType==0) {
	  if(isRHC[runInd]) 
	    histSum[runInd][4]->Add(histSurface);
	  else 
	    histSum[runInd][histType]->Add(histSurface);
	}
	else if(histType==1) {
	  if(isRHC[runInd]) 
	    histSum[runInd][5]->Add(histSurface);
	  else 
	    histSum[runInd][histType]->Add(histSurface);
	}
	else {
	  histSum[runInd][histType]->Add(histSurface);
	}





	histAll[runInd]->Add(histSurface);

	if(isRHC[runInd]) histRunJustRHC[runInd]->Add(histSurface);
	else histRunJustFHC[runInd]->Add(histSurface);

	if(histType<2) {
	  histRunNQPQ[runInd]->Add(histSurface);
	  histOneExpPQNQ.Add(histSurface);
	}

	delete histSurface;
      }
    }
    Int_t minGlobBin=histOneExp.GetMinimumBin();
    Int_t minBinX,minBinY,minBinZ;
    histOneExp.GetBinXYZ(minGlobBin,minBinX,minBinY,minBinZ);
    Double_t minT23=histOneExp.GetXaxis()->GetBinCenter(minBinX);
    Double_t minDm2=histOneExp.GetYaxis()->GetBinCenter(minBinY);
    
    //	 std::cout <<  minT23 << "\t" << minDm2 << "\n";
    t23ArrayTot[exp]=minT23;
    dm2ArrayTot[exp]=minDm2;
    {
      Int_t minGlobBin=histOneExpPQNQ.GetMinimumBin();
      Int_t minBinX,minBinY,minBinZ;
      histOneExpPQNQ.GetBinXYZ(minGlobBin,minBinX,minBinY,minBinZ);
      Double_t minT23=histOneExpPQNQ.GetXaxis()->GetBinCenter(minBinX);
      Double_t minDm2=histOneExpPQNQ.GetYaxis()->GetBinCenter(minBinY);
      
      //	 std::cout <<  minT23 << "\t" << minDm2 << "\n";
      t23ArrayPQNQ[exp]=minT23;
      dm2ArrayPQNQ[exp]=minDm2;
    }
  }
  std::cerr << "\n";

  for(int runInd=0;runInd<10;runInd++) {
    if(!doRun[runInd]) continue;
    histTotal->Add(histAll[runInd]);
    histNQPQ->Add(histRunNQPQ[runInd]);
    histJustFHC->Add(histRunJustFHC[runInd]);
    histJustRHC->Add(histRunJustFHC[runInd]);
    for(int histType=0;histType<6;histType++) {
      histSix[histType]->Add(histSum[runInd][histType]);
    }
  }
      
  

  histTotal->Scale(1./(numExps));
  subtractMinimum(histTotal);
  histNQPQ->Scale(1./numExps);
  histJustFHC->Scale(1./numExps);
  histJustRHC->Scale(1./numExps);
  subtractMinimum(histNQPQ);
  subtractMinimum(histJustRHC);
  subtractMinimum(histJustFHC);
  for(int histType=0;histType<6;histType++) {	 
    histSix[histType]->Scale(1./numExps);
    subtractMinimum(histSix[histType]);
  }




  Int_t quadCountBest[4]={0};
  Int_t quadCountSecond[4]={0};
  for(int exp=0;exp<numExps;exp++) {
    int baseTot=0;
    if(t23ArrayTot[exp]>TMath::PiOver4()) {
      baseTot=2;  
    }
    if(dm2ArrayTot[exp]<0) {
      baseTot++;
    }
    quadCountBest[baseTot]++;

    int basePQNQ=0;
    if(t23ArrayPQNQ[exp]>TMath::PiOver4()) {
      basePQNQ=2;  
    }
    if(dm2ArrayPQNQ[exp]<0) {
      basePQNQ++;
    }
    quadCountSecond[basePQNQ]++;
  }
  
  char *quadLabel[4]={"Normal theta23<=pi/4","Inverted theta23<=pi/4",
		      "Normal theta23>pi/4","Inverted theta23>pi/4"};
  
  std::cout << trueT23 << "\t" << trueDm << "\n";
  std::cout << "Best\n";
  for(int i=0;i<4;i++) {
    std::cout << quadLabel[i] << "\t" << quadCountBest[i] << "\n";
  }
  std::cout << "Second\n";
  for(int i=0;i<4;i++) {
    std::cout << quadLabel[i] << "\t" << quadCountSecond[i] << "\n";
  }

  char textName[180];
  sprintf(textName,"countSuccess_%d_%d.txt",fakeDmBin,fakeT23bin);
  ofstream OutText(textName);

  OutText << trueT23 << "\t" << trueDm << "\n";
  OutText << "Best\n";
  for(int i=0;i<4;i++) {
    OutText << quadLabel[i] << "\t" << quadCountBest[i] << "\n";
  }
  OutText << "Second\n";
  for(int i=0;i<4;i++) {
    OutText << quadLabel[i] << "\t" << quadCountSecond[i] << "\n";
  }
  OutText.close();







  char *plotTitle[6]={"FHC CC-Selected (q<0)",
		      "FHC CC-Selected (q>0)",
		      "RHC CC-Selected (q<0)",
		      "RHC CC-Selected (q>0)",
		      "NC-Selected (w/o track)",
		      "NC-Selected (w/ track)"};
  int plotInd[6]={0,1,4,5,2,3};

  // sprintf(canName,"canSurface");
  // TCanvas *canSurface  = new TCanvas(canName,canName,1200,1200);
  // canSurface->Divide(2,3);
  // for(int canInd=0;canInd<6;canInd++) {	 
  //   canSurface->cd(canInd+1); 
  //   Int_t histInd=plotInd[canInd];
  //   std::cout << canInd << "\t" << histInd << "\n";
  //   Double_t minLL=histSix[histInd]->GetMinimum();
  //   histSix[histInd]->SetMaximum(minLL+10);
  //   histSix[histInd]->GetXaxis()->SetTitle("#theta_{23} (radians)");
  //   histSix[histInd]->GetYaxis()->SetTitle("#Delta m^{2}_{23} (eV^{2})");
  //   histSix[histInd]->GetZaxis()->SetTitle("-2 #Delta LL");
  //   histSix[histInd]->SetTitle(plotTitle[canInd]);
  //   histSix[histInd]->Draw("colz");     
  //   //      TGraph 
  // }   


  
  //   sprintf(canName,"canAll");
  //   TCanvas *canAll  = new TCanvas(canName,canName,800,800);
  //   canAll->Divide(1,2);
  //   canAll->cd(1);
  //   histTotal->SetMaximum(10);
  //   histTotal->SetTitle("All Events");
  //   histTotal->Draw("colz");    
  //   canAll->cd(2);
  //   histNQPQ->SetMaximum(10);
  //   histNQPQ->SetTitle("Just CC Selected Events");
  //   histNQPQ->Draw("colz");
  
  
  sprintf(canName,"canCont");
  TCanvas *canCont  = new TCanvas(canName,canName,800,800);
  canCont->Divide(1,2,0.01,0.01);
  canCont->cd(1);
  //  gPad->SetLeftMargin(0.15);  
  TH2D *histContAll90 = (TH2D*) histTotal->Clone("histContAll90");
  histContAll90->SetTitle("");
  Double_t val90All=histContAll90->GetMinimum()+4.61;
  histContAll90->SetContour(1,&val90All);
  histContAll90->SetLineColor(1);
  histContAll90->SetLineWidth(3);   
  histContAll90->GetXaxis()->SetTitle("#theta_{23} (radians)");
  histContAll90->GetYaxis()->SetTitle("#Delta m^{2}_{23} (eV^{2})");
  //    histContAll90->GetYaxis()->SetTitleOffset(1.7);
  histContAll90->GetYaxis()->SetRangeUser(2,3);
  histContAll90->DrawClone("cont3");
  //   TH2D *histContNQ90 = (TH2D*) histSix[0]->Clone("histContNQ90");
  //   Double_t val90NQ=histContNQ90->GetMinimum()+4.61;
  //   histContNQ90->SetContour(1,&val90NQ);
  //   histContNQ90->SetLineColor(getNiceColour(0));
  //   histContNQ90->SetLineWidth(3);
  //   histContNQ90->Draw("cont3 same");

  TH2D *histContNQPQ90 = (TH2D*) histNQPQ->Clone("histContNQPQ90");
  Double_t val90NQPQ=histContNQPQ90->GetMinimum()+4.61;
  histContNQPQ90->SetContour(1,&val90NQPQ);
  histContNQPQ90->SetLineColor(getNiceColour(0));
  histContNQPQ90->SetLineWidth(3);
  histContNQPQ90->DrawClone("cont3 same");


  TH2D *histContJustFHC90 = (TH2D*) histJustFHC->Clone("histContJustFHC90");
  Double_t val90JustFHC=histContJustFHC90->GetMinimum()+4.61;
  histContJustFHC90->SetContour(1,&val90JustFHC);
  histContJustFHC90->SetLineColor(getNiceColour(1));
  histContJustFHC90->SetLineWidth(3);
  //  histContJustFHC90->DrawClone("cont3 same");
  

  TGraph *grBest = new TGraph(numExps,t23ArrayTot,dm2ArrayTot);
  grBest->SetMarkerStyle(29);
  grBest->DrawClone("p");

  TGraph *grSecondBest = new TGraph(numExps,t23ArrayPQNQ,dm2ArrayPQNQ);
  grSecondBest->SetMarkerStyle(22);
  grSecondBest->SetMarkerColor(getNiceColour(0));
  grSecondBest->DrawClone("p");
  

  canCont->cd(2);
  histContAll90->GetYaxis()->SetRangeUser(-3,-2);
  histContAll90->Draw("cont3");
  histContNQPQ90->Draw("cont3 same");
  grBest->DrawClone("p");
  //  grSecondBest->DrawClone("p");
  //  histContJustFHC90->Draw("cont3 same");
  


  TMarker *marky = new TMarker(trueT23,trueDm,29);
  marky->SetMarkerColor(kRed+2);
  marky->SetMarkerSize(2);
  if(trueDm>0)
    canCont->cd(1);
  marky->Draw("same");

  
  canCont->cd(1);
  TLegend *leggy = new TLegend(0.6,0.6,0.9,0.9);
  leggy->SetFillColor(0);
  leggy->SetFillStyle(0);
  leggy->SetBorderSize(0);
  //  leggy->AddEntry("blank","90% C.L.","l");
  leggy->AddEntry(histContNQPQ90,"CC Selected (90%)","l");
  leggy->AddEntry(histContAll90,"CC+NC Selected (90%)","l");
  leggy->AddEntry(marky,"Input Values","p");
  leggy->AddEntry(grBest,"Fake Best Fits","p");

  //  leggy->AddEntry(histContJustFHC90,"No RHC","l");
  leggy->Draw("same");

  canCont->Update();
  canCont->Modified();
  sprintf(canName,"plots/canContAll_1000_%d_%d.pdf",fakeDmBin,fakeT23bin);
  canCont->Print(canName);
  
  
  //  TH2D *histOldAll=convertToSin2Theta23(histTotal,"oldHistoAll");
  //     TCanvas *canOld = new TCanvas("canOld","canOld",800,800);  
  //     TH2D *histContOldAll = (TH2D*) histOldAll->Clone("histContOldAll");
  //     Double_t val90OldAll=histContOldAll->GetMinimum()+4.61;
  //     histContOldAll->SetContour(1,&val90OldAll);
  //     histContOldAll->SetLineColor(1);
  //     histContOldAll->SetLineWidth(3);
  //     histContOldAll->Draw("cont3");

  //     TH2D *histOldSum=convertToSin2Theta23(histSix[0],"oldHistoSum");
  //     canOld->cd();
  //     TH2D *histContOldSum = (TH2D*) histOldSum->Clone("histContOldSum");
  //     Double_t val90OldSum=histContOldSum->GetMinimum()+4.61;
  //     histContOldSum->SetContour(1,&val90OldSum);
  //     histContOldSum->SetLineColor(getNiceColour(0));
  //     histContOldSum->SetLineWidth(3);
  //     histContOldSum->Draw("cont3 same");
            


    
}



TH2D *convertToSin2Theta23(TH2D *histInput, char *histName) 
{
  
  static Double_t lookupFirstTheta23[MAX_SIN2_INDEX]={0};
  static Double_t lookupSecondTheta23[MAX_SIN2_INDEX]={0};
  static int firstTime=1;

  TH2D *histOut = new TH2D(histName,histName,
			   MAX_SIN2_INDEX,MIN_SIN2-0.5*SIN2_STEP_SIZE,MIN_SIN2+(MAX_SIN2_INDEX-0.5)*SIN2_STEP_SIZE,
			   MAX_DMI_INDEX,1e3*(MIN_DM2-0.5*DM2_STEP_SIZE),1e3*(MIN_DM2+(MAX_DMI_INDEX-0.5)*DM2_STEP_SIZE));
  TAxis *histXaxis = histOut->GetXaxis();
  //  TAxis *histYaxis = histOut->GetYaxis();
  

  //   Double_t aSliceBin[1000];
  //   Double_t aSliceValue[1000];
  //   Int_t testDmBin=77;
  //   for(int sinBin=1;sinBin<=histInput->GetNbinsX();sinBin++) {    
  //     aSliceBin[sinBin-1]=histXaxis->GetBinCenter(sinBin);
  //     aSliceValue[sinBin-1]=histInput->GetBinContent(sinBin,testDmBin);

  //   }
  //   TCanvas *can = new TCanvas();
  //   TGraph *grTest = new TGraph(histInput->GetNbinsX(),aSliceBin,aSliceValue);
  //   grTest->Draw("alp");

  //  std::cout << histOut << "\n";
  for(int sinBin=1;sinBin<=histOut->GetNbinsX();sinBin++) {    
    if(firstTime) {
      lookupFirstTheta23[sinBin-1]=getFirstT23(histXaxis->GetBinCenter(sinBin));
      lookupSecondTheta23[sinBin-1]=getSecondT23(histXaxis->GetBinCenter(sinBin));      
      //        std::cout << histXaxis->GetBinCenter(sinBin) << "\t" << lookupFirstTheta23[sinBin-1] << "\t" << lookupSecondTheta23[sinBin-1] << "\t" << histInput->GetXaxis()->GetBinCenter(getT23IFromT23(lookupFirstTheta23[sinBin-1])+1) << "\n" ;
    }

    //    Int_t firstBin=getT23IFromT23(lookupFirstTheta23[sinBin-1])+1;
    //    Int_t secondBin=getT23IFromT23(lookupSecondTheta23[sinBin-1])+1;

    for(int dmBin=1;dmBin<=histOut->GetNbinsY();dmBin++) {
      //       Double_t value1=histInput->GetBinContent(firstBin,dmBin);
      //       Double_t value2=histInput->GetBinContent(secondBin,dmBin);
      Double_t value1=th2dEval(histInput,lookupFirstTheta23[sinBin-1],histOut->GetYaxis()->GetBinCenter(dmBin));
      Double_t value2=th2dEval(histInput,lookupSecondTheta23[sinBin-1],histOut->GetYaxis()->GetBinCenter(dmBin));

      if(value2<value1) value1=value2;
      histOut->SetBinContent(sinBin,dmBin,value1);
       
      //      std::cout << sinBin << "\t" << dmBin << "\t" << histXaxis->GetBinCenter(sinBin) << "\t" << histYaxis->GetBinCenter(dmBin) << "\n";
    }
  }
  
  firstTime=0;
  return histOut;


}


Double_t th2dEval(TH2D *histInput, Double_t xValue, Double_t yValue) {
  Int_t xBin=histInput->GetXaxis()->FindBin(xValue);
  Double_t xCentre=histInput->GetXaxis()->GetBinCenter(xBin);
  Int_t xBin2=xBin+1;
  if(xBin>=histInput->GetNbinsX() || xValue<xCentre) 
    xBin2=xBin-1;
  Double_t xCentre2=histInput->GetXaxis()->GetBinCenter(xBin2);
  

  Int_t yBin=histInput->GetYaxis()->FindBin(yValue);
  Double_t yCentre=histInput->GetYaxis()->GetBinCenter(yBin);
  Int_t yBin2=yBin+1;
  if(yBin>=histInput->GetNbinsY() || yValue<yCentre) 
    yBin2=yBin-1;
  Double_t yCentre2=histInput->GetYaxis()->GetBinCenter(yBin2);

  Double_t xInt[2]={xCentre,xCentre2};
  Double_t yInt[2]={yCentre,yCentre2};
  Double_t zVals[4]={histInput->GetBinContent(xBin,yBin),
		     histInput->GetBinContent(xBin,yBin2),
		     histInput->GetBinContent(xBin2,yBin),
		     histInput->GetBinContent(xBin2,yBin2)};


  return simpleBilinearInterpolate(xInt,yInt,zVals,xValue,yValue);

}



void subtractMinimum(TH2D*histCombi)
{

  Double_t minValue=1e9;
  for(int binx=1;binx<histCombi->GetNbinsX();binx++) {
    for(int biny=1;biny<=histCombi->GetNbinsY();biny++) {
      if(histCombi->GetBinContent(binx,biny)<minValue)
	minValue=histCombi->GetBinContent(binx,biny);
    }    
  }     
  
  for(int binx=1;binx<histCombi->GetNbinsX();binx++) {
    for(int biny=1;biny<=histCombi->GetNbinsY();biny++) {
      histCombi->SetBinContent(binx,biny,histCombi->GetBinContent(binx,biny)-minValue);
    }
  }
}
