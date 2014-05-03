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
TH2D *marginaliseOverHists(TH2D *inHists[], Int_t numHists, char *histName);
void subtractMinimum(TH2D*histCombi);
TH2D *convertToSin2Theta23(TH2D *histInput, char *histName) ;
Double_t th2dEval(TH2D *histInput, Double_t xValue, Double_t yValue);
void loopOverExperimentsNormalOrInverted(int normalOrInverted, int firstExp, int lastExp,TFile *fpInRun[11][10],TH2D *histFour[], TH2D *histTotal, TH2D *histNQPQ, TH2D *histTotalSub[MAX_T13_INDEX][MAX_DELTA_INDEX], TH2D *histNQPQSub[MAX_T13_INDEX][MAX_DELTA_INDEX] );
Double_t simpleBilinearInterpolate(Double_t x[2], Double_t y[2], Double_t z[4], Double_t xp, Double_t yp) ;

int getNiceColour(int index)
{
  if(index>10) return index;
  Int_t niceColours[11]={kAzure+2,kRed+1,kGreen+1,kMagenta+1,kCyan+1,kOrange+2,kGreen-2,12,40,20,41};
  return niceColours[index];
}



Double_t llArray[4][NUM_EXPS]={{0}};
Double_t t23Array[4][NUM_EXPS]={{0}};
Double_t dm2Array[4][NUM_EXPS]={{0}};

Double_t llArrayTot[NUM_EXPS]={0};
Double_t llArrayInverted[NUM_EXPS]={0};
Double_t llArrayNormal[NUM_EXPS]={0};
Double_t t23ArrayTot[NUM_EXPS]={0};
Double_t dm2ArrayTot[NUM_EXPS]={0};
Double_t t23ArrayNormal[NUM_EXPS]={0};
Double_t dm2ArrayNormal[NUM_EXPS]={0};
Double_t t23ArrayInverted[NUM_EXPS]={0};
Double_t dm2ArrayInverted[NUM_EXPS]={0};

Double_t llArrayPQNQ[NUM_EXPS]={0};
Double_t t23ArrayPQNQ[NUM_EXPS]={0};
Double_t dm2ArrayPQNQ[NUM_EXPS]={0};


//  const char *fileTag[10]={"runi","runii","runiii","runiv","runv","runvi","runvii","runviii","runix","runx"};

const char *runNameArray[11]={"run1","run2","run3","run4","run5","run6","run7","run8","run9","run10","run11"};

const char *histNameArray[4]={"histEnergyNQ","histEnergyPQ","histEnergyNC","histEnergyNCTrack"};//

  //  const char *predHistNameArray[4]={"histPredNQ","histPredPQ","histPredNC","histPredNCTrack"};
  //  const char *fileTypeTag[3]={"main","nue","tau"};
  //  const char *potFileTypeTag[3]={"","Nue","Tau"};
  //  Int_t doRun[10]={1,1,1,1,1,1,1,0,1,1};
//Int_t doRun[11]={1,1,1,1,0,0,0,0,0,0,0};   RJN 3rd May 2014
Int_t doRun[11]={0,0,0,0,0,0,0,0,0,0,0};
Int_t isRHC[11]={0,0,0,1,0,0,1,0,1,0,0};



int main(int argc, char **argv) {

 if(argc<7) {
    std::cerr << "Usage\n\t" << argv[0] << " <dm bin> <t23 bin> <t13 bin> <delta bin> <first exp> <last exp> \n";
    return -1;
  }
 int fakeDmBin=atoi(argv[1]);
 int fakeT23Bin=atoi(argv[2]);
 int fakeT13Bin=atoi(argv[3]);
 int fakeDeltaBin=atoi(argv[4]);  
 int firstExp=atoi(argv[5]);
 int lastExp=atoi(argv[6]);
 int numExps=lastExp-firstExp;
 if(numExps<=0) return -1;

 int doMinosPlus=0;
 if(argc>7) {
   doMinosPlus=atoi(argv[7]);
 }
 if(doMinosPlus) doRun[10]=1;

 
 TH1::AddDirectory(kFALSE);
 
 Double_t trueDm=1e3*getDeltaM2(fakeDmBin);
 Double_t trueT23=getT23(fakeT23Bin);
 
 
 gStyle->SetOptStat(0);
 //   gStyle->SetOptTitle(0);
 char histName[180];
 char fileName[180];
 char canName[180];
  

 for(int exp=0;exp<numExps;exp++) {
    llArrayTot[exp]=-1;
    llArrayNormal[exp]=-1;
    llArrayInverted[exp]=-1;
    llArrayPQNQ[exp]=-1;
    for(int j=0;j<4;j++) {
       llArray[j][exp]=-1;
    }
 }
 
 TFile *fpInRun[11][10]={{0}};
 
 //Loop over runs
 for(int runInd=0;runInd<11;runInd++) {
    for(int exp=firstExp;exp<=lastExp;exp+=100) {
       if(!doRun[runInd]) continue;    
       sprintf(fileName,"fakeSurfaces/fakeSurface_%s_exps_%d_to_%d_%d_%d_%d_%d.root",runNameArray[runInd],exp,exp+99,fakeDmBin,fakeT23Bin,fakeT13Bin,fakeDeltaBin);
       fpInRun[runInd][exp/100] = new TFile(fileName,"OLD");
       if(!fpInRun[runInd][exp/100]) {
	  std::cerr << "Can not open " << fileName << "\n";
	  continue;
       }
    }
 }
 if(!doMinosPlus) {
   sprintf(fileName,"fakeSurfaces/finalPlotsMinosOnly_exps%d_to_%d_%d_%d_%d_%d.root",firstExp,lastExp,fakeDmBin,fakeT23Bin,fakeT13Bin,fakeDeltaBin);
 }
 else {
   sprintf(fileName,"fakeSurfaces/finalPlots_exps%d_to_%d_%d_%d_%d_%d.root",firstExp,lastExp,fakeDmBin,fakeT23Bin,fakeT13Bin,fakeDeltaBin);
 }
 TFile *fpOut  = new TFile(fileName,"RECREATE");

 TH1::AddDirectory(kFALSE);
 //Only have histograms averaged over the runs
 sprintf(histName,"histTotalNormal");
 TH2D *histTotalNormal = getNewNormalHistogram(histName);
 
 sprintf(histName,"histNQPQNormal");
 TH2D *histNQPQNormal = getNewNormalHistogram(histName);
 
 //This is one a histogram per histType
 TH2D *histFourNormal[4];
 for(int histType=0;histType<4;histType++) {
    sprintf(histName,"histFourNormal_%s",histNameArray[histType]);
    histFourNormal[histType] = getNewNormalHistogram(histName);           
 }


 //Only have histograms averaged over the runs
 sprintf(histName,"histTotalInverted");
 TH2D *histTotalInverted = getNewInvertedHistogram(histName);
 
 sprintf(histName,"histNQPQInverted");
 TH2D *histNQPQInverted = getNewInvertedHistogram(histName);
 
 //This is one a histogram per histType
 TH2D *histFourInverted[4];
 for(int histType=0;histType<4;histType++) {
    sprintf(histName,"histFourInverted_%s",histNameArray[histType]);
    histFourInverted[histType] = getNewInvertedHistogram(histName);           
 }

 TH2D *histTotalNormalSub[MAX_T13_INDEX][MAX_DELTA_INDEX];
 TH2D *histNQPQNormalSub[MAX_T13_INDEX][MAX_DELTA_INDEX];
 TH2D *histTotalInvertedSub[MAX_T13_INDEX][MAX_DELTA_INDEX];
 TH2D *histNQPQInvertedSub[MAX_T13_INDEX][MAX_DELTA_INDEX];
 for(int t13i=0;t13i<MAX_T13_INDEX;t13i++) {
    for(int deltai=0;deltai<MAX_DELTA_INDEX;deltai++) {
       sprintf(histName,"histTotalNormalSub_%d_%d",t13i,deltai);
       histTotalNormalSub[t13i][deltai]=getNewNormalHistogram(histName);
       sprintf(histName,"histNQPQNormalSub_%d_%d",t13i,deltai);
       histNQPQNormalSub[t13i][deltai]=getNewNormalHistogram(histName);

       sprintf(histName,"histTotalInvertedSub_%d_%d",t13i,deltai);
       histTotalInvertedSub[t13i][deltai]=getNewInvertedHistogram(histName);
       sprintf(histName,"histNQPQInvertedSub_%d_%d",t13i,deltai);
       histNQPQInvertedSub[t13i][deltai]=getNewInvertedHistogram(histName);
 
    }
 }

 ///Add here RJN
 loopOverExperimentsNormalOrInverted(0, firstExp,lastExp,fpInRun,histFourNormal,histTotalNormal, histNQPQNormal,histTotalNormalSub,histNQPQNormalSub );


 //Not sure why I have to close and reopen the files. But hey it works!
 //Loop over runs
 
 //Loop over runs
 for(int runInd=0;runInd<11;runInd++) {
    for(int exp=0;exp<1000;exp+=100) {
       if(!doRun[runInd]) continue;    
       if(fpInRun[runInd][exp/100]) {
	  fpInRun[runInd][exp/100]->Close();
	  fpInRun[runInd][exp/100]=NULL;
       }
       sprintf(fileName,"fakeSurfaces/fakeSurface_%s_exps_%d_to_%d_%d_%d_%d_%d.root",runNameArray[runInd],exp,exp+99,fakeDmBin,fakeT23Bin,fakeT13Bin,fakeDeltaBin);
       fpInRun[runInd][exp/100] = new TFile(fileName,"OLD");
       if(!fpInRun[runInd][exp/100]) {
	  std::cerr << "Can not open " << fileName << "\n";
	  continue;
       }
    }
 }
 

 loopOverExperimentsNormalOrInverted(1, firstExp,lastExp,fpInRun,histFourInverted,histTotalInverted, histNQPQInverted,histTotalInvertedSub,histNQPQInvertedSub );
 
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

//   char textName[180];
//   sprintf(textName,"countSuccess_%d_%d.txt",fakeDmBin,fakeT23Bin);
//   ofstream OutText(textName);

//   OutText << trueT23 << "\t" << trueDm << "\n";
//   OutText << "Best\n";
//   for(int i=0;i<4;i++) {
//     OutText << quadLabel[i] << "\t" << quadCountBest[i] << "\n";
//   }
//   OutText << "Second\n";
//   for(int i=0;i<4;i++) {
//     OutText << quadLabel[i] << "\t" << quadCountSecond[i] << "\n";
//   }
//   OutText.close();







  char *plotTitle[4]={"CC-Selected (q<0)",
		      "CC-Selected (q>0)",
		      "NC-Selected (w/o track)",
		      "NC-Selected (w/ track)"};
  int plotInd[4]={0,1,2,3};

  sprintf(canName,"canNormalSurface");
  TCanvas *canNormalSurface  = new TCanvas(canName,canName,1200,1200);
  canNormalSurface->Divide(2,2);
  for(int canInd=0;canInd<4;canInd++) {	 
    canNormalSurface->cd(canInd+1); 
    Int_t histInd=plotInd[canInd];
    std::cout << canInd << "\t" << histInd << "\n";
    Double_t minLL=histFourNormal[histInd]->GetMinimum();
    histFourNormal[histInd]->SetMaximum(minLL+10);
    histFourNormal[histInd]->GetXaxis()->SetTitle("#theta_{23} (radians)");
    histFourNormal[histInd]->GetYaxis()->SetTitle("#Delta m^{2}_{23} (eV^{2})");
    histFourNormal[histInd]->GetZaxis()->SetTitle("-2 #Delta LL");
    histFourNormal[histInd]->SetTitle(plotTitle[canInd]);
    histFourNormal[histInd]->Draw("colz");     
  }   

  sprintf(canName,"canNormalPlusNC");
  TCanvas *canNormalPlusNC  = new TCanvas(canName,canName,800,800);
  canNormalPlusNC->Divide(1,2);
  canNormalPlusNC->cd(1);
  histTotalNormal->SetMaximum(10);
  histTotalNormal->SetTitle("All Events");
  histTotalNormal->Draw("colz");    
  canNormalPlusNC->cd(2);
  histNQPQNormal->SetMaximum(10);
  histNQPQNormal->SetTitle("Just CC Selected Events");
  histNQPQNormal->Draw("colz");
  
  
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
  histContNormalAll90->GetXaxis()->SetTitle("#theta_{23} (radians)");
  histContNormalAll90->GetYaxis()->SetTitle("#Delta m^{2}_{23} (eV^{2})");

  histContInvertedAll90->SetContour(1,&val90All);
  histContInvertedAll90->SetLineColor(1);
  histContInvertedAll90->SetLineWidth(3);   
  histContInvertedAll90->GetXaxis()->SetTitle("#theta_{23} (radians)");
  histContInvertedAll90->GetYaxis()->SetTitle("#Delta m^{2}_{23} (eV^{2})");

  //    histContNormalAll90->GetYaxis()->SetTitleOffset(1.7);
  //    histContNormalAll90->GetYaxis()->SetRangeUser(2,3);
  histContNormalAll90->Draw("cont3");
  //   TH2D *histContNQ90 = (TH2D*) histFourNormal[0]->Clone("histContNQ90");
  //   Double_t val90NQ=histContNQ90->GetMinimum()+4.61;
  //   histContNQ90->SetContour(1,&val90NQ);
  //   histContNQ90->SetLineColor(getNiceColour(0));
  //   histContNQ90->SetLineWidth(3);
  //   histContNQ90->Draw("cont3 same");

  TH2D *histContNormalNQPQ90 = (TH2D*) histNQPQNormal->Clone("histContNormalNQPQ90");
  TH2D *histContInvertedNQPQ90 = (TH2D*) histNQPQInverted->Clone("histContInvertedNQPQ90");
  Double_t val90NQPQ=histContNormalNQPQ90->GetMinimum()+4.61;
  if(histContInvertedNQPQ90->GetMinimum()<histContNormalNQPQ90->GetMinimum()) 
     val90NQPQ=histContInvertedNQPQ90->GetMinimum()+4.61;

  histContNormalNQPQ90->SetContour(1,&val90NQPQ);
  histContNormalNQPQ90->SetLineColor(getNiceColour(0));
  histContNormalNQPQ90->SetLineWidth(3);
  histContNormalNQPQ90->Draw("cont3 same");


  histContInvertedNQPQ90->SetContour(1,&val90NQPQ);
  histContInvertedNQPQ90->SetLineColor(getNiceColour(0));
  histContInvertedNQPQ90->SetLineWidth(3);
  
  canCont->cd(1);
  TGraph *grBest = new TGraph(numExps,t23ArrayTot,dm2ArrayTot);
  grBest->SetMarkerStyle(29);
  grBest->SetMarkerColor(kGreen+2);
  grBest->DrawClone("p");

  TGraph *grSecondBest = new TGraph(numExps,t23ArrayPQNQ,dm2ArrayPQNQ);
  grSecondBest->SetMarkerStyle(22);
  grSecondBest->SetMarkerColor(getNiceColour(0));
  // grSecondBest->DrawClone("p");
  

  canCont->cd(2);

  histContInvertedAll90->Draw("cont3");
  histContInvertedNQPQ90->Draw("cont3 same");
  grBest->DrawClone("p");
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
  leggy->AddEntry(grBest,"Fake Best Fits","p");

  //  leggy->AddEntry(histContNormalJustFHC90,"No RHC","l");
  leggy->Draw("same");


  fpOut->cd();
  histTotalNormal->Write();
  histNQPQNormal->Write();
  for(int histType=0;histType<4;histType++) {
     histFourNormal[histType]->Write();
  }
  for(int t13i=0;t13i<MAX_T13_INDEX;t13i++) {
     for(int deltai=0;deltai<MAX_DELTA_INDEX;deltai++) {
	histTotalNormalSub[t13i][deltai]->Write();
	histNQPQNormalSub[t13i][deltai]->Write();
     }
  }
  histTotalInverted->Write();
  histNQPQInverted->Write();
  for(int histType=0;histType<4;histType++) {
     histFourInverted[histType]->Write();
  }
  for(int t13i=0;t13i<MAX_T13_INDEX;t13i++) {
     for(int deltai=0;deltai<MAX_DELTA_INDEX;deltai++) {
	histTotalInvertedSub[t13i][deltai]->Write();
	histNQPQInvertedSub[t13i][deltai]->Write();
     }
  }
  grBest->SetNameTitle("bestFitTotal","Individual Best Fit Points");
  grBest->Write();
  grSecondBest->SetNameTitle("bestFitNQPQ","Individual Best Fit Points NQPQ Only");
  grSecondBest->Write();

  canCont->Write();

  canNormalSurface->Write();

  canNormalPlusNC->Write();

}


TH2D *marginaliseOverHists(TH2D *inHists[], Int_t numHists, char *histName)
{  
  if(numHists==0) return NULL;
  TH2D *outHist=(TH2D*)inHists[0]->Clone(histName);
  Int_t numXbins=outHist->GetNbinsX();
  Int_t numYbins=outHist->GetNbinsY();
  
  if(numHists>1) {
    for(int binx=1;binx<=numXbins;binx++) {
      for(int biny=1;biny<=numYbins;biny++) {
	Double_t value=outHist->GetBinContent(binx,biny);
	for(int i=1;i<numHists;i++) {
	  Double_t other=inHists[i]->GetBinContent(binx,biny);
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
  

  //   Double_t aSliceBin[NUM_EXPS];
  //   Double_t aSliceValue[NUM_EXPS];
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

void loopOverExperimentsNormalOrInverted(int normalOrInverted, int firstExp, int lastExp, TFile *fpInRun[11][10],TH2D *histFour[], TH2D *histTotal, TH2D *histNQPQ, TH2D *histTotalSub[MAX_T13_INDEX][MAX_DELTA_INDEX], TH2D *histNQPQSub[MAX_T13_INDEX][MAX_DELTA_INDEX] )
{
  char *tagNormalOrInverted[2]={"Normal","Inverted"};
  char histName[180];
  char dirName[180];
  
  Int_t numExps=lastExp-firstExp;


  for(int exp=firstExp;exp<=lastExp;exp++) {
    int subExp=exp-firstExp;
    TDirectory *theDirs[11]={0};
    std::cerr << "#";
    TH2D *histOneExpSub[MAX_T13_INDEX][MAX_DELTA_INDEX]={{0}};
    TH2D *histOneExpPQNQSub[MAX_T13_INDEX][MAX_DELTA_INDEX]={{0}};
    for(int t13i=0;t13i<MAX_T13_INDEX;t13i++) {
      for(int deltai=0;deltai<MAX_DELTA_INDEX;deltai++) {
	sprintf(histName,"histOneExp%sSub_%d_%d",tagNormalOrInverted[normalOrInverted],t13i,deltai);
	histOneExpSub[t13i][deltai]=getNewHistogram(normalOrInverted,histName);
	sprintf(histName,"histOneExpPQNQ%sSub_%d_%d",tagNormalOrInverted[normalOrInverted],t13i,deltai);
	histOneExpPQNQSub[t13i][deltai]=getNewHistogram(normalOrInverted,histName);
      }
    }
    
    for(int histType=0;histType<4;histType++) {
      TH2D *histSub[MAX_T13_INDEX][MAX_DELTA_INDEX]={{0}};
      for(int t13i=0;t13i<MAX_T13_INDEX;t13i++) {
	for(int deltai=0;deltai<MAX_DELTA_INDEX;deltai++) {
	  sprintf(histName,"histSub_%d_%d",t13i,deltai);
	  histSub[t13i][deltai]=getNewHistogram(normalOrInverted,histName);
	}
      }
      
      for(int runInd=0;runInd<11;runInd++) {
	if(!doRun[runInd]) continue;
	if(!theDirs[runInd]) {
	  sprintf(dirName,"exp%d",exp);
	  fpInRun[runInd][exp/100]->cd();
	  fpInRun[runInd][exp/100]->cd(dirName);
	  theDirs[runInd]=gDirectory;
	  //	  std::cerr << runInd << "\t" << dirName  << "\t" << theDirs[runInd] << "\n";
	}

	for(int t13i=0;t13i<MAX_T13_INDEX;t13i++) {
	  for(int deltai=0;deltai<MAX_DELTA_INDEX;deltai++) {
	    //	    sprintf(histName,"exp%d/hist%s_%s_%d_%d_%d",exp,tagNormalOrInverted[normalOrInverted],histNameArray[histType],exp,t13i,deltai);
	    //	    TH2D *histTemp = (TH2D*) fpInRun[runInd]->Get(histName);
	    sprintf(histName,"hist%s_%s_%d_%d_%d",tagNormalOrInverted[normalOrInverted],histNameArray[histType],exp,t13i,deltai);
	    TH2D *histTemp = (TH2D*) theDirs[runInd]->Get(histName);
	    if(!histTemp) {
	      std::cerr << "Can't get " << histName << "\n";
	    }
	    histSub[t13i][deltai]->Add(histTemp);
	    histOneExpSub[t13i][deltai]->Add(histTemp);
	    if(histType<2) {
	      histOneExpPQNQSub[t13i][deltai]->Add(histTemp);
	    }
	    delete histTemp;
	  }
	}
      }
      //Now make the marginalised histType histograms per run
      sprintf(histName,"hist%s",tagNormalOrInverted[normalOrInverted]);
      TH2D *hist = marginaliseOverHists((TH2D**)histSub,MAX_T13_INDEX*MAX_DELTA_INDEX,histName);
      for(int t13i=0;t13i<MAX_T13_INDEX;t13i++) {
	for(int deltai=0;deltai<MAX_DELTA_INDEX;deltai++) {
	  delete histSub[t13i][deltai];
	}
      }
      
      //The best fit point for this one histType
      Int_t minGlobBin=hist->GetMinimumBin();
      Double_t minLL=hist->GetMinimum();//BinContent(minGlobBin);
      
      if(minLL<llArray[histType][subExp] || llArray[histType][subExp]<0) {
	Int_t minBinX,minBinY,minBinZ;
	hist->GetBinXYZ(minGlobBin,minBinX,minBinY,minBinZ);
	Double_t minT23=hist->GetXaxis()->GetBinCenter(minBinX);
	Double_t minDm2=hist->GetYaxis()->GetBinCenter(minBinY);
	
	//	 std::cout <<  minT23 << "\t" << minDm2 << "\n";
	t23Array[histType][subExp]=minT23;
	dm2Array[histType][subExp]=minDm2;
	llArray[histType][subExp]=minLL;
      }
      
      //Now add to histFour
      histFour[histType]->Add(hist);
     
      delete hist;

    }

    //Now make the marginalised experiment histograms
    
    TH2D *histOneExp = marginaliseOverHists((TH2D**)histOneExpSub,MAX_T13_INDEX*MAX_DELTA_INDEX,"histOneExp");
    TH2D *histOneExpPQNQ =marginaliseOverHists((TH2D**)histOneExpPQNQSub,MAX_T13_INDEX*MAX_DELTA_INDEX,"histOneExpPQNQ");

    for(int t13i=0;t13i<MAX_T13_INDEX;t13i++) {
      for(int deltai=0;deltai<MAX_DELTA_INDEX;deltai++) {
	 histTotalSub[t13i][deltai]->Add(histOneExpSub[t13i][deltai]);
	 histNQPQSub[t13i][deltai]->Add(histOneExpPQNQSub[t13i][deltai]);
	 delete histOneExpSub[t13i][deltai];
	 delete histOneExpPQNQSub[t13i][deltai];
      }
    }
    histTotal->Add(histOneExp);
    histNQPQ->Add(histOneExpPQNQ);
  
    Double_t minLL=histOneExp->GetMinimum();
    Int_t minGlobBin=histOneExp->GetMinimumBin();
    Int_t minBinX,minBinY,minBinZ;
    histOneExp->GetBinXYZ(minGlobBin,minBinX,minBinY,minBinZ);
    Double_t minT23=histOneExp->GetXaxis()->GetBinCenter(minBinX);
    Double_t minDm2=histOneExp->GetYaxis()->GetBinCenter(minBinY);
      
    if(llArrayTot[subExp]>minLL || llArrayTot[subExp]<0) {
      t23ArrayTot[subExp]=minT23;
      dm2ArrayTot[subExp]=minDm2;
      llArrayTot[subExp]=minLL;
    }

    if(normalOrInverted==0) {
      if(llArrayNormal[subExp]>minLL || llArrayNormal[subExp]<0) {
	t23ArrayNormal[subExp]=minT23;
	dm2ArrayNormal[subExp]=minDm2;
	llArrayNormal[subExp]=minLL;
      }
    }
    else {
      if(llArrayInverted[subExp]>minLL || llArrayInverted[subExp]<0) {
	t23ArrayInverted[subExp]=minT23;
	dm2ArrayInverted[subExp]=minDm2;
	llArrayInverted[subExp]=minLL;
      }
    }

      

    {
      Double_t minLL=histOneExpPQNQ->GetMinimum();
      Int_t minGlobBin=histOneExpPQNQ->GetMinimumBin();
      Int_t minBinX,minBinY,minBinZ;
      histOneExpPQNQ->GetBinXYZ(minGlobBin,minBinX,minBinY,minBinZ);
      Double_t minT23=histOneExpPQNQ->GetXaxis()->GetBinCenter(minBinX);
      Double_t minDm2=histOneExpPQNQ->GetYaxis()->GetBinCenter(minBinY);
      
      //	 std::cout <<  minT23 << "\t" << minDm2 << "\n";
      if(minLL<llArrayPQNQ[subExp] || llArrayPQNQ[subExp]<0) {
	t23ArrayPQNQ[subExp]=minT23;
	dm2ArrayPQNQ[subExp]=minDm2;
	llArrayPQNQ[subExp]=minLL;
      }
    }
    
    delete histOneExp;
    delete histOneExpPQNQ;
    
    for(int runInd=0;runInd<11;runInd++) {
      if(!doRun[runInd]) continue;
      if(theDirs[runInd]) {
	theDirs[runInd]->Close();
	theDirs[runInd]=NULL;
      }
    }
  }
  std::cerr << "\n";
  
  histTotal->Scale(1./(numExps));
  //  histTotal->Scale(5);
  //  subtractMinimum(histTotal);
  histNQPQ->Scale(1./numExps);
  //  subtractMinimum(histNQPQ);
  for(int histType=0;histType<4;histType++) {	 
    histFour[histType]->Scale(1./numExps);
    //    subtractMinimum(histFour[histType]);
  }
  
  for(int t13i=0;t13i<MAX_T13_INDEX;t13i++) {
     for(int deltai=0;deltai<MAX_DELTA_INDEX;deltai++) {
	histTotalSub[t13i][deltai]->Scale(1./numExps);
	histNQPQSub[t13i][deltai]->Scale(1./numExps);
  
	//	subtractMinimum(histTotalSub[t13i][deltai]);
	//	subtractMinimum(histNQPQSub[t13i][deltai]);
     }
  }

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
