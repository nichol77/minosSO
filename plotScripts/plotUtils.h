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

TH2D *getContours(TH2D *histSurface, int c68909599, double absVal=0);
void subtractMinimum(TH2D*histCombi);
TH2D *convertToSin2Theta23(TH2D *histInput, char *histName) ;
TH2D *convertToAndy(TH2D *histInput, char *histName) ;
TH2D *convertToSin2Theta23Andy(TH2D *histInput, const char *histName, Int_t normalOrInverted) ;
Double_t th2dEval(TH2D *histInput, Double_t xValue, Double_t yValue);
TMarker *drawBestFit(TH2D *histCont);
void getMinPoint(TH2D *histCont, Double_t &minX, Double_t &minY);


TH2D *getContours(TH2D *histSurface, int c68909599, double absVal)
{
   double upValue[4]={2.30,4.61,5.99,9.21};  //upValues from PDG statistics 2013
   double minVal=histSurface->GetMinimum();

   double contVal=absVal;
   if(c68909599>0 && c68909599<5) {
      contVal=minVal+upValue[c68909599-1];
   }
   TH2D *histCont = (TH2D*) histSurface->Clone("histCont"); 

   histCont->SetContour(1,&contVal);
   histCont->SetLineColor(1);
   histCont->SetLineWidth(3);
   return histCont;
}

void getMinPoint(TH2D *histCont, Double_t &minX, Double_t &minY) {

   int minBin=0,minBinX=0,minBinY=0,minBinZ=0;
   minBin=histCont->GetMinimumBin();
   histCont->GetBinXYZ(minBin,minBinX,minBinY,minBinZ);
   minX=histCont->GetXaxis()->GetBinCenter(minBinX);
   minY=histCont->GetYaxis()->GetBinCenter(minBinY);


}

TMarker *drawBestFit(TH2D *histCont) {
   //   std::cout << histCont->GetMinimumBin() << "\n";
   Double_t minX=0,minY=0;
   getMinPoint(histCont,minX,minY);
   std::cout << minX << "\t" << minY << "\n";
   TMarker *marky = new TMarker(minX,minY,29);
   marky->SetMarkerColor(histCont->GetLineColor());
   marky->SetMarkerSize(2);
   marky->Draw("same");
   return marky;
}

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


TH2D *convertToAndy(TH2D *histInput, char *histName) {

  static Double_t inputTheta23[MAX_T23_INDEX]={0};
  static Double_t lookupTheta23[100]={0};
  static Int_t leftBin[100]={0};
  static Int_t rightBin[100]={0};
  static int firstTime=1;
  
  
  for(int i=0;i<MAX_T23_INDEX;i++) {
    inputTheta23[i]=histInput->GetXaxis()->GetBinCenter(i+1);
  }
  

  TH2D *histOut = new TH2D(histName,histName,
			   100,0.1,0.9,
			   histInput->GetNbinsY(),histInput->GetYaxis()->GetBinLowEdge(1),histInput->GetYaxis()->GetBinUpEdge(histInput->GetNbinsY()));
  TAxis *histXaxis = histOut->GetXaxis();
  for(int sinBin=1;sinBin<=histOut->GetNbinsX();sinBin++) {
     if(firstTime) {
	lookupTheta23[sinBin-1]=TMath::ASin(TMath::Sqrt(histXaxis->GetBinCenter(sinBin)));
	for(int i=0;i<MAX_T23_INDEX;i++) {
	   if(inputTheta23[i]<lookupTheta23[sinBin-1]) {
	      leftBin[sinBin-1]=i;
	   }
	   else if(inputTheta23[i]>lookupTheta23[sinBin-1]) {
	      rightBin[sinBin-1]=i;
	      break;
	   }
	}
	//	std::cout << sinBin << "\t" << leftBin[sinBin-1] << "\t" <<rightBin[sinBin-1] << "\n";
     }
  }
  


  for(int sinBin=1;sinBin<=histOut->GetNbinsX();sinBin++) {
     for(int dmBin=1;dmBin<=histOut->GetNbinsY();dmBin++) {
	
	Double_t value1=histInput->GetBinContent(leftBin[sinBin-1]+1,dmBin);
	Double_t value2=histInput->GetBinContent(rightBin[sinBin-1]+1,dmBin);
	Double_t value=simpleInterploate(inputTheta23[leftBin[sinBin-1]],value1,inputTheta23[rightBin[sinBin-1]],value2,lookupTheta23[sinBin-1]);
	std::cout << sinBin << "\t" << dmBin << "\t" << value1 << "\t" << value2 << "\t"
		  << value << "\n";
	histOut->SetBinContent(sinBin,dmBin,value);
     }
  }
  
  firstTime=0;
  return histOut;



}



TH2D *convertToSin2Theta23(TH2D *histInput, char *histName) 
{
   static Double_t inputTheta23[MAX_T23_INDEX]={0};
   static Double_t lookupTheta23[100]={0};
   static Int_t leftBin[100]={0};
   static Int_t rightBin[100]={0};
   static int firstTime=1;
   
   
   for(int i=0;i<MAX_T23_INDEX;i++) {
      inputTheta23[i]=histInput->GetXaxis()->GetBinCenter(i+1);
   }


  TH2D *histOut = new TH2D(histName,histName,
			   100,0.1,0.9,
			   histInput->GetNbinsY(),histInput->GetYaxis()->GetBinLowEdge(1),histInput->GetYaxis()->GetBinUpEdge(histInput->GetNbinsY()));
  TAxis *histXaxis = histOut->GetXaxis();
  for(int sinBin=1;sinBin<=histOut->GetNbinsX();sinBin++) {
     if(firstTime) {
	lookupTheta23[sinBin-1]=TMath::ASin(TMath::Sqrt(histXaxis->GetBinCenter(sinBin)));
	for(int i=0;i<MAX_T23_INDEX;i++) {
	   if(inputTheta23[i]<lookupTheta23[sinBin-1]) {
	      leftBin[sinBin-1]=i;
	   }
	   else if(inputTheta23[i]>lookupTheta23[sinBin-1]) {
	      rightBin[sinBin-1]=i;
	      break;
	   }
	}
	//	std::cout << sinBin << "\t" << leftBin[sinBin-1] << "\t" <<rightBin[sinBin-1] << "\n";
     }
  }
  


  for(int sinBin=1;sinBin<=histOut->GetNbinsX();sinBin++) {
     for(int dmBin=1;dmBin<=histOut->GetNbinsY();dmBin++) {
	
	Double_t value1=histInput->GetBinContent(leftBin[sinBin-1]+1,dmBin);
	Double_t value2=histInput->GetBinContent(rightBin[sinBin-1]+1,dmBin);
	Double_t value=simpleInterploate(inputTheta23[leftBin[sinBin-1]],value1,inputTheta23[rightBin[sinBin-1]],value2,lookupTheta23[sinBin-1]);
	std::cout << sinBin << "\t" << dmBin << "\t" << value1 << "\t" << value2 << "\t"
		  << value << "\n";
	histOut->SetBinContent(sinBin,dmBin,value);
     }
  }
  
  firstTime=0;
  return histOut;

}



TH2D *convertToSin2Theta23Andy(TH2D *histInput, const char *histName, Int_t normalOrInverted) 
{
   Double_t lookupTheta23[81]={0};
   Double_t lookupDm[61]={0};
   
   TH2D *histOut = new TH2D(histName,histName,
			    81, 0.2975, 0.7025,
			    61, 2.095e-3, 2.705e-3);
   for(int sinBin=1;sinBin<=histOut->GetNbinsX();sinBin++) {
     Double_t sin2theta23=histOut->GetXaxis()->GetBinCenter(sinBin);
     Double_t theta23=TMath::ASin(TMath::Sqrt(sin2theta23));
     lookupTheta23[sinBin-1]=theta23;     
   }
   for(int dmBin=1;dmBin<=histOut->GetNbinsY();dmBin++) {
     Double_t fogliDm=histOut->GetYaxis()->GetBinCenter(dmBin);
     //Normal hierarchy
     Double_t dm32=fogliDm;
     if(normalOrInverted==1) {
       //Inverted  hierarchy
       dm32=-1*(fogliDm+0.5*DM_12);
     }     
     lookupDm[dmBin-1]=dm32*1e3;
   }

  for(int sinBin=1;sinBin<=histOut->GetNbinsX();sinBin++) {
     for(int dmBin=1;dmBin<=histOut->GetNbinsY();dmBin++) {
	
       Double_t value=th2dEval(histInput,lookupTheta23[sinBin-1],lookupDm[dmBin-1]);


       //	std::cout << sinBin << "\t" << dmBin << "\t" << lookupTheta23[sinBin-1] << "\t" << lookupDm[dmBin-1] << "\t"
       //		  << value << "\n";
	histOut->SetBinContent(sinBin,dmBin,value);
     }
  }
  
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
  for(int binx=1;binx<=histCombi->GetNbinsX();binx++) {
    for(int biny=1;biny<=histCombi->GetNbinsY();biny++) {
      if(histCombi->GetBinContent(binx,biny)<minValue)
	minValue=histCombi->GetBinContent(binx,biny);
    }    
  }     
  
  for(int binx=1;binx<=histCombi->GetNbinsX();binx++) {
    for(int biny=1;biny<=histCombi->GetNbinsY();biny++) {
      histCombi->SetBinContent(binx,biny,histCombi->GetBinContent(binx,biny)-minValue);
    }
  }
}
