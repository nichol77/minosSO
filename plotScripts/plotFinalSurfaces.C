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

#define NUM_EXPS 1000

#include "src/paramFuncs.h"
TH2D *marginaliseOtherWay(TH2D *inHistsNorm[MAX_T13_INDEX][MAX_DELTA_INDEX],TH2D *inHistsInv[MAX_T13_INDEX][MAX_DELTA_INDEX]);
TH2D *marginaliseOverHists(TH2D *inHists[], Double_t penaltyTerms[], Int_t numHists, char *histName);
void subtractMinimum(TH2D*histCombi);
TH2D *convertToSin2Theta23(TH2D *histInput, char *histName) ;
TH2D *convertToAndy(TH2D *histInput, char *histName) ;
Double_t th2dEval(TH2D *histInput, Double_t xValue, Double_t yValue);
void plotFinalSurfaces(int fakeDmBin, int fakeT23Bin,int fakeT13Bin, int fakeDeltaBin, int doMinosPlus);
TCanvas *getCanCont(TH2D *histTotalNormal, TH2D *histTotalInverted, TH2D *histNQPQNormal, TH2D *histNQPQInverted) ;
Double_t getT13PenaltyTerm(Double_t t13);
TCanvas *getCanContSin2(TH2D *histTotalNormalIn, TH2D *histTotalInvertedIn, TH2D *histNQPQNormalIn, TH2D *histNQPQInvertedIn);

Double_t trueDm;
Double_t trueT23;
Double_t trueSin2T23;

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

void plotFinalSurfaces()
{

  plotFinalSurfaces(69,39,6,0,1000);
}


void plotFinalSurfaces(int fakeDmBin, int fakeT23Bin,int fakeT13Bin, int fakeDeltaBin, int doMinosPlus)
{
   
   trueDm=1e3*getDeltaM2(fakeDmBin);
  trueT23=getT23(fakeT23Bin);
  trueSin2T23=TMath::Power(TMath::Sin(trueT23),2);
  
  gStyle->SetOptStat(0);
  //   gStyle->SetOptTitle(0);
  char histName[180];
  char fileName[180];
  
  if(doMinosPlus)
     sprintf(fileName,"finalSurfaces/finalPlots_%d_%d_%d_%d.root",fakeDmBin,fakeT23Bin,fakeT13Bin,fakeDeltaBin);
  else {
     sprintf(fileName,"finalSurfaces/finalPlotsMinosOnly_%d_%d_%d_%d.root",fakeDmBin,fakeT23Bin,fakeT13Bin,fakeDeltaBin);
  }
  TFile *fp = TFile::Open(fileName);
  

  TH2D *histTotalNormal = (TH2D*) fp->Get("histTotalNormal");
  TH2D *histTotalInverted = (TH2D*) fp->Get("histTotalInverted");
  TH2D *histNQPQNormal = (TH2D*) fp->Get("histNQPQNormal");
  TH2D *histNQPQInverted = (TH2D*) fp->Get("histNQPQInverted");

  sprintf(histName,"histTotalNormalSub_%d_%d",fakeT13Bin,fakeDeltaBin);
  TH2D *histTotalNormalCheat = (TH2D*) fp->Get(histName);
  if(!histTotalNormalCheat) {
    std::cerr << "Couldn't get " << histName << "\n";
    return;
  }

  sprintf(histName,"histTotalInvertedSub_%d_%d",fakeT13Bin,fakeDeltaBin);
  TH2D *histTotalInvertedCheat = (TH2D*) fp->Get(histName);
  if(!histTotalInvertedCheat) {
    std::cerr << "Couldn't get " << histName << "\n";
    return;
  }
  
  sprintf(histName,"histNQPQNormalSub_%d_%d",fakeT13Bin,fakeDeltaBin);
  TH2D *histNQPQNormalCheat = (TH2D*) fp->Get(histName);
  if(!histNQPQNormalCheat) {
    std::cerr << "Couldn't get " << histName << "\n";
    return;
  }

  sprintf(histName,"histNQPQInvertedSub_%d_%d",fakeT13Bin,fakeDeltaBin);
  TH2D *histNQPQInvertedCheat = (TH2D*) fp->Get(histName);
  if(!histNQPQInvertedCheat) {
    std::cerr << "Couldn't get " << histName << "\n";
    return;
  }

  Double_t penaltyTerms[MAX_T13_INDEX][MAX_DELTA_INDEX]={{0}};
  TH2D *histTotalNormalSub[MAX_T13_INDEX][MAX_DELTA_INDEX]={{0}};
  TH2D *histTotalInvertedSub[MAX_T13_INDEX][MAX_DELTA_INDEX]={{0}};
  TH2D *histNQPQNormalSub[MAX_T13_INDEX][MAX_DELTA_INDEX]={{0}};
  TH2D *histNQPQInvertedSub[MAX_T13_INDEX][MAX_DELTA_INDEX]={{0}};
  for(int t13i=0;t13i<MAX_T13_INDEX;t13i++) {
    for(int deltai=0;deltai<MAX_DELTA_INDEX;deltai++) {
      penaltyTerms[t13i][deltai]=getT13PenaltyTerm(getT13(t13i));
      sprintf(histName,"histTotalNormalSub_%d_%d",t13i,deltai);
      histTotalNormalSub[t13i][deltai] = (TH2D*) fp->Get(histName);
      if(!histTotalNormalSub[t13i][deltai]) {
      std::cerr << "Couldn't get " << histName << "\n";
      return;
      }
      
      sprintf(histName,"histTotalInvertedSub_%d_%d",t13i,deltai);
      histTotalInvertedSub[t13i][deltai] = (TH2D*) fp->Get(histName);
      if(!histTotalInvertedSub[t13i][deltai]) {
	std::cerr << "Couldn't get " << histName << "\n";
	return;
      }
      sprintf(histName,"histNQPQNormalSub_%d_%d",t13i,deltai);
      histNQPQNormalSub[t13i][deltai] = (TH2D*) fp->Get(histName);
      if(!histNQPQNormalSub[t13i][deltai]) {
	std::cerr << "Couldn't get " << histName << "\n";
	return;
      }
      
      sprintf(histName,"histNQPQInvertedSub_%d_%d",t13i,deltai);
      histNQPQInvertedSub[t13i][deltai] = (TH2D*) fp->Get(histName);
      if(!histNQPQInvertedSub[t13i][deltai]) {
	std::cerr << "Couldn't get " << histName << "\n";
	return;
      }
      
    }
  }

  //Now marginalise over delta
  //  TH2D *histTotalNormalBest = marginaliseOverHists(histTotalNormalSub[fakeT13Bin],MAX_DELTA_INDEX,"histTotalNormalBest");
  //  TH2D *histTotalInvertedBest = marginaliseOverHists(histTotalInvertedSub[fakeT13Bin],MAX_DELTA_INDEX,"histTotalInvertedBest");
  //  TH2D *histNQPQNormalBest = marginaliseOverHists(histNQPQNormalSub[fakeT13Bin],MAX_DELTA_INDEX,"histNQPQNormalBest");
  //  TH2D *histNQPQInvertedBest = marginaliseOverHists(histNQPQInvertedSub[fakeT13Bin],MAX_DELTA_INDEX,"histNQPQInvertedBest");

  //Now marginalise over delta
  TH2D *histTotalNormalBest = marginaliseOverHists(histTotalNormalSub[0],penaltyTerms[0],MAX_T13_INDEX*MAX_DELTA_INDEX,"histTotalNormalBest");
  TH2D *histTotalInvertedBest = marginaliseOverHists(histTotalInvertedSub[0],penaltyTerms[0],MAX_T13_INDEX*MAX_DELTA_INDEX,"histTotalInvertedBest");
  TH2D *histNQPQNormalBest = marginaliseOverHists(histNQPQNormalSub[0],penaltyTerms[0],MAX_T13_INDEX*MAX_DELTA_INDEX,"histNQPQNormalBest");
  TH2D *histNQPQInvertedBest = marginaliseOverHists(histNQPQInvertedSub[0],penaltyTerms[0],MAX_T13_INDEX*MAX_DELTA_INDEX,"histNQPQInvertedBest");

 
  // This one just gets the best one
  //  TCanvas *canCont = getCanContSin2(histTotalNormal,histTotalInverted,histNQPQNormal,histNQPQInverted);
  TCanvas *canContCheat = getCanContSin2(histTotalNormalCheat,histTotalInvertedCheat,histNQPQNormalCheat,histNQPQInvertedCheat);
  canContCheat->SetName("canContCheat");
  canContCheat->SetTitle("canContCheat");
  TCanvas *canCont = getCanContSin2(histTotalNormalBest,histTotalInvertedBest,histNQPQNormalBest,histNQPQInvertedBest);
    
  canCont->Update();
  canCont->Modified();
  //  sprintf(fileName,"plots/canContAll_%d_%d_%d_%d.pdf",fakeDmBin,fakeT23Bin,fakeT13Bin,fakeDeltaBin);//,plotT13Bin,plotDeltaBin);

  TGraph *grBest = (TGraph*) fp->Get("bestFitTotal");
  TGraph *grNQPQ = (TGraph*) fp->Get("bestFitNQPQ");
  
  Double_t countQuad[4]={0};
  Double_t countQuad2[4]={0};

  std::cout << trueDm << "\t" << trueT23 << "\n";

  if(grBest) {
     Double_t *bestT23 = grBest->GetX();
     Double_t *bestDm2 = grBest->GetY();
     for(int i=0;i<grBest->GetN();i++) {
	int bin=0;
	if(bestT23[i]>TMath::PiOver4()) 
	   bin+=1;
	if(bestDm2[i]<0)
	   bin+=2;
	countQuad[bin]++;
     }

     std::cout << "True: ";
     if(trueDm<0) {
	std::cout << "Inverted, ";
     }
     else {
	std::cout << "Normal, ";
     }
     if(trueT23>TMath::PiOver4())
	std::cout << "Higher\n";
     else
	std::cout << "Lower\n";
     std::cout << "Normal, Lower " << countQuad[0] << "\n";
     std::cout << "Normal, Higher " << countQuad[1] << "\n";
     std::cout << "Inverted, Lower " << countQuad[2] << "\n";
     std::cout << "Inverted, Higher " << countQuad[3] << "\n";
  }

  if(grNQPQ) {
     Double_t *bestT23 = grNQPQ->GetX();
     Double_t *bestDm2 = grNQPQ->GetY();
     for(int i=0;i<grNQPQ->GetN();i++) {
	int bin=0;
	if(bestT23[i]>TMath::PiOver4()) 
	   bin+=1;
	if(bestDm2[i]<0)
	   bin+=2;
	countQuad2[bin]++;
     }

     std::cout << "\n\nJust CC\n";
     std::cout << "True: ";
     if(trueDm<0) {
	std::cout << "Inverted, ";
     }
     else {
	std::cout << "Normal, ";
     }
     if(trueT23>TMath::PiOver4())
	std::cout << "Higher\n";
     else
	std::cout << "Lower\n";
     std::cout << "Normal, Lower " << countQuad2[0] << "\n";
     std::cout << "Normal, Higher " << countQuad2[1] << "\n";
     std::cout << "Inverted, Lower " << countQuad2[2] << "\n";
     std::cout << "Inverted, Higher " << countQuad2[3] << "\n";
  }

  TCanvas *can = new TCanvas();
  can->SetRightMargin(0.2);
  TH2D *histDeltaT13 = marginaliseOtherWay(histTotalNormalSub,histTotalInvertedSub);
  //  TH2D *histDeltaT13 = marginaliseOtherWay(histNQPQNormalSub,histNQPQInvertedSub);
  subtractMinimum(histDeltaT13);
  histDeltaT13->SetTitle("");
  histDeltaT13->Draw("colz");
  histDeltaT13->GetXaxis()->SetTitle("#theta_{13} (radians)");
  histDeltaT13->GetYaxis()->SetTitle("#delta (radians)");
  histDeltaT13->GetZaxis()->SetTitle("#Delta #chi^{2}");
  histDeltaT13->GetYaxis()->SetTitleOffset(0.7);
  histDeltaT13->GetZaxis()->SetTitleOffset(0.7);
  //  canCont->Print(fileName);
}


TH2D *marginaliseOtherWay(TH2D *inHistsNorm[MAX_T13_INDEX][MAX_DELTA_INDEX], TH2D *inHistsInv[MAX_T13_INDEX][MAX_DELTA_INDEX])
{
   TH2D *deltaT13Hist = new TH2D("deltaT13Hist","deltaT13Hist",
				 MAX_T13_INDEX,MIN_T13-0.5*T13_STEP_SIZE,MIN_T13+(MAX_T13_INDEX-0.5)*T13_STEP_SIZE,
				 MAX_DELTA_INDEX,MIN_DELTA-0.5*DELTA_STEP_SIZE,MIN_DELTA+(MAX_DELTA_INDEX-0.5)*DELTA_STEP_SIZE);
   for(int t13i=0;t13i<MAX_T13_INDEX;t13i++) {
      for(int deltai=0;deltai<MAX_DELTA_INDEX;deltai++) {
	 Int_t normx,normy,normz;
	 Int_t invx,invy,invz;
	 
	 Int_t binNorm=inHistsNorm[t13i][deltai]->GetMinimumBin(normx,normy,normz);
	 Double_t normValue=inHistsNorm[t13i][deltai]->GetBinContent(normx,normy);
	 

	 Int_t binInv=inHistsInv[t13i][deltai]->GetMinimumBin(invx,invy,invz);
	 Double_t invValue=inHistsInv[t13i][deltai]->GetBinContent(invx,invy);
	 
	 if(normValue<invValue) {
	   //  std::cout << inHistsNorm[t13i][deltai]->GetXaxis()->GetBinCenter(normx) << "\t"
// 		      << inHistsNorm[t13i][deltai]->GetYaxis()->GetBinCenter(normy) << "\t"
// 		      << normValue << "\n";
	    deltaT13Hist->SetBinContent(t13i+1,deltai+1,normValue);
	 }
	 else {	    
// 	    std::cout << inHistsInv[t13i][deltai]->GetXaxis()->GetBinCenter(invx) << "\t"
// 		      << inHistsInv[t13i][deltai]->GetYaxis()->GetBinCenter(invy) << "\t"
// 		      << invValue << "\n";
	    deltaT13Hist->SetBinContent(t13i+1,deltai+1,invValue);
	 }
      }
   }
   
   return deltaT13Hist;

}



TH2D *marginaliseOverHists(TH2D *inHists[], Double_t penaltyTerms[],Int_t numHists, char *histName)
{  
  if(numHists==0) return NULL;
  TH2D *outHist=(TH2D*)inHists[0]->Clone(histName);
  Int_t numXbins=outHist->GetNbinsX();
  Int_t numYbins=outHist->GetNbinsY();


  for(int binx=1;binx<=numXbins;binx++) {
    for(int biny=1;biny<=numYbins;biny++) {
      Double_t value=outHist->GetBinContent(binx,biny)+penaltyTerms[0];
      outHist->SetBinContent(binx,biny,value);
    }
  }
      
  
  if(numHists>1) {
    for(int binx=1;binx<=numXbins;binx++) {
      for(int biny=1;biny<=numYbins;biny++) {
	Double_t value=outHist->GetBinContent(binx,biny);
	for(int i=1;i<numHists;i++) {
	  Double_t other=inHists[i]->GetBinContent(binx,biny)+penaltyTerms[i];
	  if(other<value) {
	    value=other;
	  }
	}
	outHist->SetBinContent(binx,biny,value);
	
      }
    }
  }
  return outHist;
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

TH2D *getNewHistogram(int normalOrInverted, char *histName) {
  if(normalOrInverted==0) return getNewNormalHistogram(histName);
  else return getNewInvertedHistogram(histName);
}


TCanvas *getCanCont(TH2D *histTotalNormal, TH2D *histTotalInverted, TH2D *histNQPQNormal, TH2D *histNQPQInverted) 
{

  char canName[180];
   
  sprintf(canName,"canCont");
  TCanvas *canCont  = new TCanvas(canName,canName,800,800);
  canCont->Divide(1,2,0.01,0.01);
  canCont->cd(1); 
  //  gPad->SetLeftMargin(0.15);  
  TH2D *histContNormalAll90 = (TH2D*) histTotalNormal->Clone("histContNormalAll90");
  TH2D *histContInvertedAll90 = (TH2D*) histTotalInverted->Clone("histContInvertedAll90");
  histContNormalAll90->SetTitle("");
  histContInvertedAll90->SetTitle("");
  Double_t val90All=histContNormalAll90->GetMinimum()+4.61;
  if(histContInvertedAll90->GetMinimum()<histContNormalAll90->GetMinimum())
     val90All=histContInvertedAll90->GetMinimum()+4.61;
  
  histContNormalAll90->SetContour(1,&val90All);
  histContNormalAll90->SetLineColor(1);
  histContNormalAll90->SetLineWidth(3);

  histContInvertedAll90->SetContour(1,&val90All);
  histContInvertedAll90->SetLineColor(1);
  histContInvertedAll90->SetLineWidth(3);   


  TH2D *histContNormalAll68 = (TH2D*) histTotalNormal->Clone("histContNormalAll68");
  TH2D *histContInvertedAll68 = (TH2D*) histTotalInverted->Clone("histContInvertedAll68");
  histContNormalAll68->SetTitle("");
  histContInvertedAll68->SetTitle("");
  Double_t val68All=histContNormalAll68->GetMinimum()+2.71;
  if(histContInvertedAll68->GetMinimum()<histContNormalAll68->GetMinimum())
     val68All=histContInvertedAll68->GetMinimum()+2.71;
  
  histContNormalAll68->SetContour(1,&val68All);
  histContNormalAll68->SetLineColor(1);
  histContNormalAll68->SetLineStyle(3);
  histContNormalAll68->SetLineWidth(3);

  histContInvertedAll68->SetContour(1,&val68All);
  histContInvertedAll68->SetLineColor(1);
  histContInvertedAll68->SetLineStyle(2);
  histContInvertedAll68->SetLineWidth(3);   

   
  histContNormalAll90->GetXaxis()->SetTitle("#theta_{23} (radians)");
  histContNormalAll90->GetXaxis()->SetRangeUser(0.5,1.1);
  histContNormalAll90->GetYaxis()->SetRangeUser(2.1,2.8);
  histContNormalAll90->GetYaxis()->SetTitle("#Delta m^{2}_{23} (eV^{2})");

  histContInvertedAll90->GetXaxis()->SetRangeUser(0.5,1.1);
  histContInvertedAll90->GetYaxis()->SetRangeUser(-2.8,-2.1);
  histContInvertedAll90->GetXaxis()->SetTitle("#theta_{23} (radians)");
  histContInvertedAll90->GetYaxis()->SetTitle("#Delta m^{2}_{23} (eV^{2})");


  TH2D *histContNormalNQPQ90 = (TH2D*) histNQPQNormal->Clone("histContNormalNQPQ90");
  TH2D *histContInvertedNQPQ90 = (TH2D*) histNQPQInverted->Clone("histContInvertedNQPQ90");
  Double_t val90NQPQ=histContNormalNQPQ90->GetMinimum()+4.61;
  if(histContInvertedNQPQ90->GetMinimum()<histContNormalNQPQ90->GetMinimum()) 
     val90NQPQ=histContInvertedNQPQ90->GetMinimum()+4.61;

  histContNormalNQPQ90->SetContour(1,&val90NQPQ);
  histContNormalNQPQ90->SetLineColor(getNiceColour(0));
  histContNormalNQPQ90->SetLineWidth(3);


  histContInvertedNQPQ90->SetContour(1,&val90NQPQ);
  histContInvertedNQPQ90->SetLineColor(getNiceColour(0));
  histContInvertedNQPQ90->SetLineWidth(3);
  


  TH2D *histContNormalNQPQ68 = (TH2D*) histNQPQNormal->Clone("histContNormalNQPQ68");
  TH2D *histContInvertedNQPQ68 = (TH2D*) histNQPQInverted->Clone("histContInvertedNQPQ68");
  Double_t val68NQPQ=histContNormalNQPQ68->GetMinimum()+2.71;
  if(histContInvertedNQPQ68->GetMinimum()<histContNormalNQPQ68->GetMinimum()) 
     val68NQPQ=histContInvertedNQPQ68->GetMinimum()+2.71;

  histContNormalNQPQ68->SetContour(1,&val68NQPQ);
  histContNormalNQPQ68->SetLineColor(getNiceColour(0));
  histContNormalNQPQ68->SetLineStyle(3);
  histContNormalNQPQ68->SetLineWidth(3);


  histContInvertedNQPQ68->SetContour(1,&val68NQPQ);
  histContInvertedNQPQ68->SetLineColor(getNiceColour(0));
  histContInvertedNQPQ68->SetLineStyle(3);
  histContInvertedNQPQ68->SetLineWidth(3);

  canCont->cd(1);

  histContNormalAll90->Draw("cont3");
  histContNormalAll68->Draw("cont3 same");
  histContNormalNQPQ90->Draw("cont3 same");
  histContNormalNQPQ68->Draw("cont3 same");
  
  

//   TGraph *grBest = new TGraph(numExps,t23ArrayTot,dm2ArrayTot);
//   grBest->SetMarkerStyle(29);
//   grBest->SetMarkerColor(kGreen+2);
//   grBest->DrawClone("p");

//   TGraph *grSecondBest = new TGraph(numExps,t23ArrayPQNQ,dm2ArrayPQNQ);
//   grSecondBest->SetMarkerStyle(22);
//   grSecondBest->SetMarkerColor(getNiceColour(0));
//   // grSecondBest->DrawClone("p");
  

  canCont->cd(2);

  histContInvertedAll90->Draw("cont3");
  histContInvertedNQPQ90->Draw("cont3 same");
  histContInvertedAll68->Draw("cont3 same");
  histContInvertedNQPQ68->Draw("cont3 same");
  //  grBest->DrawClone("p");
  //  grSecondBest->DrawClone("p");
  

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
  leggy->AddEntry(histContNormalNQPQ90,"CC Selected (90%)","l");
  leggy->AddEntry(histContNormalAll90,"CC+NC Selected (90%)","l");
  leggy->AddEntry(marky,"Input Values","p");
  //  leggy->AddEntry(grBest,"Fake Best Fits","p");

  //  leggy->AddEntry(histContNormalJustFHC90,"No RHC","l");
  leggy->Draw("same");

  return canCont;
}




TCanvas *getCanContSin2(TH2D *histTotalNormalIn, TH2D *histTotalInvertedIn, TH2D *histNQPQNormalIn, TH2D *histNQPQInvertedIn) 
{
   char histName[180];
   sprintf(histName,"%sSin2",histTotalNormalIn->GetName());
   TH2D *histTotalNormal=convertToSin2Theta23(histTotalNormalIn,histName);
   sprintf(histName,"%sSin2",histTotalInvertedIn->GetName());
   TH2D *histTotalInverted=convertToSin2Theta23(histTotalInvertedIn,histName);
   sprintf(histName,"%sSin2",histNQPQNormalIn->GetName());
   TH2D *histNQPQNormal=convertToSin2Theta23(histNQPQNormalIn,histName);
   sprintf(histName,"%sSin2",histNQPQInvertedIn->GetName());
   TH2D *histNQPQInverted=convertToSin2Theta23(histNQPQInvertedIn,histName);


  char canName[180];
   
  sprintf(canName,"canCont");
  TCanvas *canCont  = new TCanvas(canName,canName,800,800);
  canCont->Divide(1,2,0.01,0.01);
  canCont->cd(1); 
  //  gPad->SetLeftMargin(0.15);  
  TH2D *histContNormalAll90 = (TH2D*) histTotalNormal->Clone("histContNormalAll90");
  TH2D *histContInvertedAll90 = (TH2D*) histTotalInverted->Clone("histContInvertedAll90");
  histContNormalAll90->SetTitle("");
  histContInvertedAll90->SetTitle("");
  Double_t val90All=histContNormalAll90->GetMinimum()+4.61;
  if(histContInvertedAll90->GetMinimum()<histContNormalAll90->GetMinimum())
     val90All=histContInvertedAll90->GetMinimum()+4.61;
  
  histContNormalAll90->SetContour(1,&val90All);
  histContNormalAll90->SetLineColor(1);
  histContNormalAll90->SetLineWidth(3);

  histContInvertedAll90->SetContour(1,&val90All);
  histContInvertedAll90->SetLineColor(1);
  histContInvertedAll90->SetLineWidth(3);   


  TH2D *histContNormalAll68 = (TH2D*) histTotalNormal->Clone("histContNormalAll68");
  TH2D *histContInvertedAll68 = (TH2D*) histTotalInverted->Clone("histContInvertedAll68");
  histContNormalAll68->SetTitle("");
  histContInvertedAll68->SetTitle("");
  Double_t val68All=histContNormalAll68->GetMinimum()+2.71;
  if(histContInvertedAll68->GetMinimum()<histContNormalAll68->GetMinimum())
     val68All=histContInvertedAll68->GetMinimum()+2.71;
  
  histContNormalAll68->SetContour(1,&val68All);
  histContNormalAll68->SetLineColor(1);
  histContNormalAll68->SetLineStyle(3);
  histContNormalAll68->SetLineWidth(3);

  histContInvertedAll68->SetContour(1,&val68All);
  histContInvertedAll68->SetLineColor(1);
  histContInvertedAll68->SetLineStyle(2);
  histContInvertedAll68->SetLineWidth(3);   

   
  histContNormalAll90->GetXaxis()->SetTitle("sin^{2}(#theta_{23})");
  histContNormalAll90->GetXaxis()->SetRangeUser(0.3,0.7);
  histContNormalAll90->GetYaxis()->SetRangeUser(2.1,2.7);
  histContNormalAll90->GetYaxis()->SetTitle("#Delta m^{2}_{23} (eV^{2})");

  histContInvertedAll90->GetXaxis()->SetRangeUser(0.3,0.7);
  histContInvertedAll90->GetYaxis()->SetRangeUser(-2.7,-2.1);
  histContInvertedAll90->GetXaxis()->SetTitle("sin^{2}(#theta_{23})");
  histContInvertedAll90->GetYaxis()->SetTitle("#Delta m^{2}_{23} (eV^{2})");


  TH2D *histContNormalNQPQ90 = (TH2D*) histNQPQNormal->Clone("histContNormalNQPQ90");
  TH2D *histContInvertedNQPQ90 = (TH2D*) histNQPQInverted->Clone("histContInvertedNQPQ90");
  Double_t val90NQPQ=histContNormalNQPQ90->GetMinimum()+4.61;
  if(histContInvertedNQPQ90->GetMinimum()<histContNormalNQPQ90->GetMinimum()) 
     val90NQPQ=histContInvertedNQPQ90->GetMinimum()+4.61;

  histContNormalNQPQ90->SetContour(1,&val90NQPQ);
  histContNormalNQPQ90->SetLineColor(getNiceColour(0));
  histContNormalNQPQ90->SetLineWidth(3);


  histContInvertedNQPQ90->SetContour(1,&val90NQPQ);
  histContInvertedNQPQ90->SetLineColor(getNiceColour(0));
  histContInvertedNQPQ90->SetLineWidth(3);
  


  TH2D *histContNormalNQPQ68 = (TH2D*) histNQPQNormal->Clone("histContNormalNQPQ68");
  TH2D *histContInvertedNQPQ68 = (TH2D*) histNQPQInverted->Clone("histContInvertedNQPQ68");
  Double_t val68NQPQ=histContNormalNQPQ68->GetMinimum()+2.71;
  if(histContInvertedNQPQ68->GetMinimum()<histContNormalNQPQ68->GetMinimum()) 
     val68NQPQ=histContInvertedNQPQ68->GetMinimum()+2.71;

  histContNormalNQPQ68->SetContour(1,&val68NQPQ);
  histContNormalNQPQ68->SetLineColor(getNiceColour(0));
  histContNormalNQPQ68->SetLineStyle(3);
  histContNormalNQPQ68->SetLineWidth(3);


  histContInvertedNQPQ68->SetContour(1,&val68NQPQ);
  histContInvertedNQPQ68->SetLineColor(getNiceColour(0));
  histContInvertedNQPQ68->SetLineStyle(3);
  histContInvertedNQPQ68->SetLineWidth(3);

  canCont->cd(1);

  histContNormalAll90->Draw("cont3");
  histContNormalAll68->Draw("cont3 same");
  histContNormalNQPQ90->Draw("cont3 same");
  histContNormalNQPQ68->Draw("cont3 same");
  
  

//   TGraph *grBest = new TGraph(numExps,t23ArrayTot,dm2ArrayTot);
//   grBest->SetMarkerStyle(29);
//   grBest->SetMarkerColor(kGreen+2);
//   grBest->DrawClone("p");

//   TGraph *grSecondBest = new TGraph(numExps,t23ArrayPQNQ,dm2ArrayPQNQ);
//   grSecondBest->SetMarkerStyle(22);
//   grSecondBest->SetMarkerColor(getNiceColour(0));
//   // grSecondBest->DrawClone("p");
  

  canCont->cd(2);

  histContInvertedAll90->Draw("cont3");
  histContInvertedNQPQ90->Draw("cont3 same");
  histContInvertedAll68->Draw("cont3 same");
  histContInvertedNQPQ68->Draw("cont3 same");
  //  grBest->DrawClone("p");
  //  grSecondBest->DrawClone("p");
  

  TMarker *marky = new TMarker(trueSin2T23,trueDm,29);
  marky->SetMarkerColor(kRed+2);
  marky->SetMarkerSize(2);
  if(trueDm>0)
    canCont->cd(1);
  marky->Draw("same");

  
  canCont->cd(1);
  TLegend *leggy = new TLegend(0.45,0.6,0.7,0.9);
  leggy->SetFillColor(0);
  leggy->SetFillStyle(0);
  leggy->SetBorderSize(0);
  //  leggy->AddEntry("blank","90% C.L.","l");
  leggy->AddEntry(histContNormalNQPQ90,"CC Selected (90%)","l");
  leggy->AddEntry(histContNormalAll90,"CC+NC Selected (90%)","l");
  leggy->AddEntry(marky,"Input Values","p");
  //  leggy->AddEntry(grBest,"Fake Best Fits","p");

  //  leggy->AddEntry(histContNormalJustFHC90,"No RHC","l");
  leggy->Draw("same");

  return canCont;
}


Double_t getT13PenaltyTerm(Double_t t13) {
  //From pdg sin^2(t13)=0.0251 ± 0.0034
  Double_t sin2t13=TMath::Power(TMath::Sin(t13),2);
  return TMath::Power((sin2t13-0.0251)/0.0034,2);
}
