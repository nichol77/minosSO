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


#include "src/paramFuncs.h"


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
  char histName[180];
  char fileName[180];
  char canName[180];
  
  //  const char *fileTag[10]={"runi","runii","runiii","runiv","runv","runvi","runvii","runviii","runix","runx"};
  const char *histNameArray[4]={"histEnergyNQ","histEnergyPQ","histEnergyNC","histEnergyNCTrack"};
  //  const char *predHistNameArray[4]={"histPredNQ","histPredPQ","histPredNC","histPredNCTrack"};
  //  const char *fileTypeTag[3]={"main","nue","tau"};
  //  const char *potFileTypeTag[3]={"","Nue","Tau"};
  Int_t doRun[10]={1,0,0,0,0,0,0,0,0,0};


  Double_t t23Array[4][1000]={0};
  Double_t dm2Array[4][1000]={0};
  TH2D *histSum[10][4]={{0}};
  TH2D *histAll[10]={0};
  
  Int_t numExps=100;

  //Loop over runs
  for(int runInd=0;runInd<10;runInd++) {
    if(!doRun[runInd]) continue;


    sprintf(fileName,"fakeSurfaces/fakeSurface_run%d_%d_%d.root",runInd+1,fakeDmBin,fakeT23bin);
    TFile *fpIn = new TFile(fileName,"OLD");
    if(!fpIn) {
      std::cerr << "Can not open " << fileName << "\n";
      continue;
    }


    sprintf(histName,"histAllRun%d",runInd+1);
    histAll[runInd] = new TH2D(histName,histName,MAX_T23_INDEX,MIN_T23-0.5*T23_STEP_SIZE,MIN_T23+(MAX_T23_INDEX-0.5)*T23_STEP_SIZE,MAX_DMI_INDEX,1e3*(MIN_DM2-0.5*DM2_STEP_SIZE),1e3*(MIN_DM2+(MAX_DMI_INDEX-0.5)*DM2_STEP_SIZE));

        
    for(int histType=0;histType<4;histType++) {	  	
      
       sprintf(histName,"histSumRun%d_%s",runInd+1,histNameArray[histType]);
       histSum[runInd][histType] = new TH2D(histName,histName,MAX_T23_INDEX,MIN_T23-0.5*T23_STEP_SIZE,MIN_T23+(MAX_T23_INDEX-0.5)*T23_STEP_SIZE,MAX_DMI_INDEX,1e3*(MIN_DM2-0.5*DM2_STEP_SIZE),1e3*(MIN_DM2+(MAX_DMI_INDEX-0.5)*DM2_STEP_SIZE));
              
       for(int exp=0;exp<numExps;exp++) {
	 sprintf(histName,"histSurface_%s_%d",histNameArray[histType],exp);
	 TH2D *histSurface = (TH2D*) fpIn->Get(histName);
	 
	 //	 Double_t minLL=histSurface->GetMinimum();
	 Int_t minGlobBin=histSurface->GetMinimumBin();
	 Int_t minBinX,minBinY,minBinZ;
	 histSurface->GetBinXYZ(minGlobBin,minBinX,minBinY,minBinZ);
	 Double_t minT23=histSurface->GetXaxis()->GetBinCenter(minBinX);
	 Double_t minDm2=histSurface->GetYaxis()->GetBinCenter(minBinY);
	 	 
	 //	 std::cout <<  minT23 << "\t" << minDm2 << "\n";
	 t23Array[histType][exp]=minT23;
	 dm2Array[histType][exp]=minDm2;
	 

	 histSum[runInd][histType]->Add(histSurface);
	 histAll[runInd]->Add(histSurface);
       }
    }

    sprintf(canName,"canSurface%d",runInd+1);
    TCanvas *canSurface  = new TCanvas(canName,canName,1200,800);
    canSurface->Divide(2,2);
    for(int histType=0;histType<4;histType++) {	 
      canSurface->cd(histType+1);
      histSum[runInd][histType]->Scale(1./numExps);
      Double_t minLL=histSum[runInd][histType]->GetMinimum();
      histSum[runInd][histType]->SetMaximum(minLL+4.6);
      histSum[runInd][histType]->Draw("colz");

      //      TGraph 
    }        
    
    sprintf(canName,"canAll%d",runInd+1);
    TCanvas *canAll  = new TCanvas(canName,canName,800,800);
    canAll->Divide(1,2);
    canAll->cd(1);
    histAll[runInd]->Scale(1./(numExps));
    Double_t minLL=histAll[runInd]->GetMinimum();
    histAll[runInd]->SetMaximum(minLL+4.6);
    histAll[runInd]->Draw("colz");
    
    canAll->cd(2);
    histSum[runInd][0]->Draw("colz");


    sprintf(canName,"canCont%d",runInd+1);
    TCanvas *canCont  = new TCanvas(canName,canName,800,800);
    canCont->SetLeftMargin(0.15);
    TH2D *histContAll = (TH2D*) histAll[runInd]->Clone("histContAll");
    Double_t val90All=histContAll->GetMinimum()+4.61;
    histContAll->SetContour(1,&val90All);
    histContAll->SetLineColor(1);
    histContAll->SetLineWidth(3);   
    histContAll->GetXaxis()->SetTitle("#theta_{23} (radians)");
    histContAll->GetYaxis()->SetTitle("#Delta m^{2}_{23} (eV^{2})");
    //    histContAll->GetYaxis()->SetTitleOffset(1.7);
    histContAll->Draw("cont3");
    TH2D *histContSum = (TH2D*) histSum[runInd][0]->Clone("histContSum");
    Double_t val90Sum=histContSum->GetMinimum()+4.61;
    histContSum->SetContour(1,&val90Sum);
    histContSum->SetLineColor(getNiceColour(0));
    histContSum->SetLineWidth(3);
    histContSum->Draw("cont3 same");
   
    TMarker *marky = new TMarker(trueT23,trueDm,29);
    marky->SetMarkerColor(kRed+2);
    marky->SetMarkerSize(2);
    marky->Draw("same");

    canCont->Update();
    canCont->Modified();
    sprintf(canName,"plots/canContRun%d_%d_%d.pdf",runInd+1,fakeDmBin,fakeT23bin);
    canCont->Print(canName);

  
   //  TH2D *histOldAll=convertToSin2Theta23(histAll[runInd],"oldHistoAll");
//     TCanvas *canOld = new TCanvas("canOld","canOld",800,800);  
//     TH2D *histContOldAll = (TH2D*) histOldAll->Clone("histContOldAll");
//     Double_t val90OldAll=histContOldAll->GetMinimum()+4.61;
//     histContOldAll->SetContour(1,&val90OldAll);
//     histContOldAll->SetLineColor(1);
//     histContOldAll->SetLineWidth(3);
//     histContOldAll->Draw("cont3");

//     TH2D *histOldSum=convertToSin2Theta23(histSum[runInd][0],"oldHistoSum");
//     canOld->cd();
//     TH2D *histContOldSum = (TH2D*) histOldSum->Clone("histContOldSum");
//     Double_t val90OldSum=histContOldSum->GetMinimum()+4.61;
//     histContOldSum->SetContour(1,&val90OldSum);
//     histContOldSum->SetLineColor(getNiceColour(0));
//     histContOldSum->SetLineWidth(3);
//     histContOldSum->Draw("cont3 same");
  }
            


    
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
