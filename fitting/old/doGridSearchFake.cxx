#include <iostream>
#include <fstream>
#include "TFile.h"
#include "TF1.h"
#include "TH1.h"
#include "TH2.h"
#include "TMath.h"
#include "TCanvas.h"
#include "TString.h"
#include "TKey.h"
#include "TROOT.h"
#include "gridSearch.h"
#include "src/paramFuncs.h"

Double_t getLL(TH1D *histData, TH1D *histPred) ;
void doGridSearchFake(int run, int fakeDmBin, int fakeT23bin);


int main(int argc, char **argv) 
{

   if(argc!=4) {
      std::cerr << "Usage\n\t" << argv[0] << " <run> <dm bin> <t23 bin>\n";
      return -1;
   }
   int run=atoi(argv[1]);
   int dmBin=atoi(argv[2]);
   int t23Bin=atoi(argv[3]);
   
   doGridSearchFake(run,dmBin,t23Bin);
   
}



void doGridSearchFake(int run, int fakeDmBin, int fakeT23bin)
{
   
   Double_t binEdge[]={0,0.5,0.75,1,1.25,1.5,1.75,2,2.25,2.5,2.75,3,3.25,3.5,3.75,4,4.25,4.5,4.75,5,5.25,5.5,5.75,6,6.25,6.5,6.75,7,7.25,7.5,7.75,8,8.25,8.5,8.75,9,9.25,9.5,9.75,10,10.25,10.5,10.75,11,11.25,11.5,11.75,12,12.25,12.5,12.75,13,13.25,13.5,13.75,14,14.25,14.5,14.75,15,15.25,15.5,15.75,16,16.25,16.5,16.75,17,17.25,17.5,17.75,18,18.25,18.5,18.75,19,19.25,19.5,19.75,20,21,22,23,24,25,26,27,28,29,30,32,34,36,38,40,42,44,46,48,50,200};

   char dataPotName[180];
   char mcPotName[180];
   char histName[180];
   char fileName[180];
   char outName[180];
   int dmi,t23i;

  const char *fileTag[10]={"runi","runii","runiii","runiv","runv","runvi","runvii","runviii","runix","runx"};
  const char *histNameArray[4]={"histEnergyNQ","histEnergyPQ","histEnergyNC","histEnergyNCTrack"};
  const char *predHistNameArray[4]={"histPredNQ","histPredPQ","histPredNC","histPredNCTrack"};
  const char *fileTypeTag[3]={"main","nue","tau"};
  const char *potFileTypeTag[3]={"","Nue","Tau"};
  //  Int_t doRun[10]={1,0,0,0,0,0,0,0,0,0};

  
  TH1D *histPred[4][MAX_DMI_INDEX][MAX_T23_INDEX]={{{0}}};
  //First step is to load and scale the predictions
  //Loop over runs
  //  for(int runInd=0;runInd<10;runInd++) {
  //    if(!doRun[runInd]) continue;
  int runInd=run-1;


    sprintf(dataPotName,"pot/run%dFDDataPOT.txt",runInd+1);
    std::ifstream DataPotFile(dataPotName);
    if(!DataPotFile) {
      std::cerr << "Can not open " << dataPotName << "\n";
      return;
    }
    Double_t dataPOT=0;
    DataPotFile >> dataPOT;
    

    sprintf(fileName,"fakeSurfaces/fakeSurface_run%d_%d_%d.root",runInd+1,fakeDmBin,fakeT23bin);
    TFile *fpSurface = new TFile(fileName,"RECREATE");
    if(!fpSurface) {
      std::cerr << "Can not open " << fileName << "\n";
      return;
    }


    sprintf(fileName,"/tmp/run%d_pred_combined.root",runInd+1);
    TFile *fpCombined = new TFile(fileName,"RECREATE");
    if(!fpCombined) {
      std::cerr << "Can not open " << fileName << "\n";
      return;
    }
    for(int histType=0;histType<4;histType++) {
       for(int dmi=0;dmi<MAX_DMI_INDEX;dmi++) {
	  for(int t23i=0;t23i<MAX_T23_INDEX;t23i++) {
	     sprintf(histName,"full_%s_%d_%d",predHistNameArray[histType],dmi,t23i);
	     histPred[histType][dmi][t23i] = new TH1D(histName,histName,100,binEdge);
	  }
       }
    }
    TFile *fpPred[3]={NULL};

    //Loop over main, nue , tau
    for(int fileType=0;fileType<3;fileType++) {            
      sprintf(fileName,"farPreds/%s_pred_%s.root",fileTag[runInd],fileTypeTag[fileType]);
       fpPred[fileType]= TFile::Open(fileName);
      if(!fpPred[fileType]) {
	std::cerr << "Can't open " << fileName << "\n";
	continue;
      }


      sprintf(mcPotName,"pot/run%dFD%sMCPOT.txt",runInd+1,potFileTypeTag[fileType]);
      std::ifstream McPotFile(mcPotName);
      if(!McPotFile) {
	std::cerr << "Can not open " << mcPotName << "\n";
	continue;
      }
      Double_t mcPOT=0;
      McPotFile >> mcPOT;

      Double_t scaleFactor=dataPOT/mcPOT;
      std::cout << "Run " << runInd+1 << " " << fileTypeTag[fileType] << "\t" << dataPOT << "\t" << mcPOT << "\t" << scaleFactor << "\n";



      TIter nextkey(fpPred[fileType]->GetListOfKeys());
      TKey *key;
      int count=0;
      while ((key = ((TKey*)nextkey()))) {
         if((count%1000)==0) std::cerr << "*";
         count++;
	 //Should really add a check that the TObject inherits from TH1 here
         TH1D *thisHist = (TH1D*)key->ReadObj();
         TString histString(thisHist->GetName());
	 int histType=-1;
	 thisHist->Scale(scaleFactor);
	 if(histString.BeginsWith("histPredNQ")) {
            sscanf(histString.Data(),"histPredNQ_%d_%d",&dmi,&t23i);
	    histType=0;
         }
         else if(histString.BeginsWith("histPredPQ")) {
            sscanf(histString.Data(),"histPredPQ_%d_%d",&dmi,&t23i);
	    histType=1;
         }
         else if(histString.BeginsWith("histPredNCTrack")) {
	    //Important to check for NCTrack before NC
            sscanf(histString.Data(),"histPredNCTrack_%d_%d",&dmi,&t23i);
	    histType=3;
         }
         else if(histString.BeginsWith("histPredNC")) {
            sscanf(histString.Data(),"histPredNC_%d_%d",&dmi,&t23i);
	    histType=2;
         }                       

	 if(histType>=0) {
	    histPred[histType][dmi][t23i]->Add(thisHist);
	 
	 }
	 //	 if((count%3)==0)
	 //	   delete thisHist;
      }
      std::cerr << "\n";      
      gROOT->GetListOfFiles()->Remove(fpPred[fileType]);
    }
    //    exit(0);
    
    //    fpCombined->Write();

    //Next step is to open the fake data files
    
    sprintf(fileName,"fakeData/%s_fake_%d_%d.root",fileTag[runInd],fakeDmBin,fakeT23bin);
    TFile *fpFakeData = TFile::Open(fileName,"OLD");      
    if(!fpFakeData) {
      std::cerr << "Can not open " << fileName << "\n";
      //      continue;
      return;
    }
    
    
    for(int exp=0;exp<1000;exp++) {	
      
      std::cerr << "#";
      int goodLoop=0;
      for(int histType=0;histType<4;histType++) {	  	
	sprintf(histName,"%s_%d",histNameArray[histType],exp);
	TH1D *histData = (TH1D*) fpFakeData->Get(histName);
	if(!histData) {
	  std::cerr << "Couldn't get " << histName << "\n";
	  break;
	}
	
	fpSurface->cd();
	sprintf(outName,"histSurface_%s_%d",histNameArray[histType],exp);
	TH2D *histSurface = new TH2D(outName,outName,MAX_T23_INDEX,MIN_T23-0.5*T23_STEP_SIZE,MIN_T23+(MAX_T23_INDEX-0.5)*T23_STEP_SIZE,MAX_DMI_INDEX,1e3*(MIN_DM2-0.5*DM2_STEP_SIZE),1e3*(MIN_DM2+(MAX_DMI_INDEX-0.5)*DM2_STEP_SIZE));
	
	for(int dmi=0;dmi<MAX_DMI_INDEX;dmi++) {
	  for(int t23i=0;t23i<MAX_T23_INDEX;t23i++) {	  	  
	    //	    for(int dmi=34;dmi<35;dmi++) {
	      //	      for(int t23i=40;t23i<41;t23i++) {	  	  
	    //	    std::cout << histData->Integral() << "\t" << histPred[histType][dmi][t23i]->Integral() << "\n";
	    
	    Double_t LL=getLL(histData,histPred[histType][dmi][t23i]);
	    //	    std::cout << LL << "\n";
	    histSurface->Fill(getT23(t23i),1e3*getDeltaM2(dmi),LL);
	  }
	}
	histSurface->Write();
	  
	delete histSurface;
	delete histData;
	goodLoop=1;
      }
      if(!goodLoop) break;
    }
    

    fpSurface->Close();  
    std::cerr << "\n";    
    std::cerr << "End of loop\n";

//     for(int fileType=0;fileType<3;fileType++) {            
//       gROOT->GetListOfFiles()->Remove(fpPred[fileType]);
//     }

   //  for(int histType=0;histType<4;histType++) {
//       for(int dmi=0;dmi<MAX_DMI_INDEX;dmi++) {
// 	std::cerr << "*";
// 	for(int t23i=0;t23i<MAX_T23_INDEX;t23i++) {	 
// 	  if(histPred[histType][dmi][t23i]) delete histPred[histType][dmi][t23i];
// 	  histPred[histType][dmi][t23i]=0;
// 	  }
//       }
//       std::cerr << "\n";		
//     }      
//  }
}


Double_t getLL(TH1D *histData, TH1D *histPred) 
{
  Double_t value=0;
  if(histData->GetNbinsX()!=histPred->GetNbinsX()) {
    std::cerr << "histos not same size\n";
    return 0;
  }
  for(int bin=START_BIN;bin<=histData->GetNbinsX();bin++) {
    Double_t vi=histPred->GetBinContent(bin);
    Double_t ni=histData->GetBinContent(bin);    
    //    std::cout << ni << "\t" << vi << "\n";
    if(vi>0) {
      if(ni>0)
	value+=(vi-ni)+ni*TMath::Log(ni/vi);        
      else
	value+=vi;
    }
  }
  return 2*value;
}

