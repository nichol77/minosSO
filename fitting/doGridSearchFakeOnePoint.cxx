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
#include "gridSearch.h"
#include "src/paramFuncs.h"

#define NUM_EXPS 1000

Double_t getLL(TH1D *histData, TH1D *histPred) ;
void doGridSearchFake(int run, int fakeDmBin, int fakeT23bin, int fakeT13Bin, int fakeDeltaBin, int thisDmBin, int potScale);
Long64_t getTempIndex(Int_t dmi, Int_t t23i, Int_t t13i, Int_t deltai) ;

int main(int argc, char **argv) 
{

  if(argc<7) {
    std::cerr << "Usage\n\t" << argv[0] << " <run> <dm bin> <t23 bin> <t13 bin> <delta bin>\n";
    return -1;
  }
  int run=atoi(argv[1]);
  int dmBin=atoi(argv[2]);
  int t23Bin=atoi(argv[3]);
  int t13Bin=atoi(argv[4]);
  int deltaBin=atoi(argv[5]);
  int thisDmBin=atoi(argv[6]);
  //  int thisT23Bin=atoi(argv[7]);
  int potScale=1;
  if(argc>7) {
     potScale=atoi(argv[7]);
  }
   
  //  doGridSearchFake(run,dmBin,t23Bin,t13Bin,deltaBin,thisDmBin,thisT23Bin,potScale);
  doGridSearchFake(run,dmBin,t23Bin,t13Bin,deltaBin,thisDmBin,potScale);
   
}



void doGridSearchFake(int run, int fakeDmBin, int fakeT23bin, int fakeT13Bin, int fakeDeltaBin, int thisDmBin,  int potScale)
{

  Float_t *tempArray[4][MAX_T23_INDEX][MAX_T13_INDEX][MAX_DELTA_INDEX];
  for(int histType=0;histType<4;histType++) {
    for(int t23i=0;t23i<MAX_T23_INDEX;t23i++) {
      for(int t13i=0;t13i<MAX_T13_INDEX;t13i++) {
	for(int deltai=0;deltai<MAX_DELTA_INDEX;deltai++) {
	  tempArray[histType][t23i][t13i][deltai] = new Float_t[NUM_EXPS];
	}
      }
    }
  }



  TH1::AddDirectory(kFALSE);

  Double_t binEdge[]={0,0.5,0.75,1,1.25,1.5,1.75,2,2.25,2.5,2.75,3,3.25,3.5,3.75,4,4.25,4.5,4.75,5,5.25,5.5,5.75,6,6.25,6.5,6.75,7,7.25,7.5,7.75,8,8.25,8.5,8.75,9,9.25,9.5,9.75,10,10.25,10.5,10.75,11,11.25,11.5,11.75,12,12.25,12.5,12.75,13,13.25,13.5,13.75,14,14.25,14.5,14.75,15,15.25,15.5,15.75,16,16.25,16.5,16.75,17,17.25,17.5,17.75,18,18.25,18.5,18.75,19,19.25,19.5,19.75,20,21,22,23,24,25,26,27,28,29,30,32,34,36,38,40,42,44,46,48,50,200};

  char dataPotName[180];
  char mcPotName[180];
  char histName[180];
  char dirName[180];
  char fileName[180];
  char outName[180];


  const char *histNameArray[4]={"histEnergyNQ","histEnergyPQ","histEnergyNC","histEnergyNCTrack"};
  const char *predHistNameArray[4]={"histPredNQ","histPredPQ","histPredNC","histPredNCTrack"};
  const char *fileTypeTag[3]={"main","nue","tau"};
  const char *potFileTypeTag[3]={"","Nue","Tau"};
  //  Int_t doRun[10]={1,0,0,0,0,0,0,0,0,0};

  
  const char *runNameArray[11]={"run1","run2","run3","run4","run5","run6","run7","run8","run9","run10","minosPlus"};


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
     
    scaleFactor[fileType]=potScale*dataPOT/mcPOT[fileType];
    std::cout << "Run " << runNameArray[run-1] << " " << fileTypeTag[fileType] << "\t" << dataPOT << "\t" << mcPOT[fileType] << "\t" << scaleFactor[fileType] << "\n";
  }


  //Next step is to open the fake data files  
  if(potScale>1) 
     sprintf(fileName,"fakeData/%s_scale%d_fake_%d_%d_%d_%d.root",runNameArray[run-1],potScale,fakeDmBin,fakeT23bin,fakeT13Bin,fakeDeltaBin);
  else 
     sprintf(fileName,"fakeData/%s_fake_%d_%d_%d_%d.root",runNameArray[run-1],fakeDmBin,fakeT23bin,fakeT13Bin,fakeDeltaBin);
  TFile *fpFakeData = TFile::Open(fileName,"OLD");      
  if(!fpFakeData) {
    std::cerr << "Can not open " << fileName << "\n";
    //      continue;
    return;
  }
  
  //Read in all the fake data files
  TH1D *histData[4][1000]={{0}};
  Double_t numEventsTot[4]={0};
  for(int exp=0;exp<NUM_EXPS;exp++) {
    int goodLoop=1;
    //Loop over the four types of fake data
    for(int histType=0;histType<4;histType++) {	  	
      sprintf(histName,"%s_%d",histNameArray[histType],exp);
      histData[histType][exp] = (TH1D*) fpFakeData->Get(histName);
      if(!histData[histType][exp]) {
	std::cerr << "Couldn't get " << histName << "\n";
	goodLoop=0;
	break;
      }
      numEventsTot[histType]+=histData[histType][exp]->Integral();
      
    }
    if(!goodLoop) break;
  }
  for(int histType=0;histType<4;histType++) {	  	
    std::cout << "Integral " << histNameArray[histType] << "\t" << numEventsTot[histType]/NUM_EXPS << "\n";
  }
  
  
  
  //Loop over all of the predictions
  //  for(int dmi=0;dmi<MAX_DMI_INDEX;dmi++) {
  //  for(int dmi=60;dmi<MAX_DMI_INDEX;dmi++) {
  {
    int dmi=thisDmBin;
    //  for(int dmi=0;dmi<2;dmi++) {
    std::cerr << "\n" << dmi << ":";
    TFile *fpPreds[3]={0};
    for(int fileType=0;fileType<3;fileType++) {
      sprintf(fileName,"/unix/minos1/rjn/ccPlusNc/farPreds/%s/%s%d.root",runNameArray[run-1],fileTypeTag[fileType],dmi);
      fpPreds[fileType] = TFile::Open(fileName);
    }

    for(int t23i=0;t23i<MAX_T23_INDEX;t23i++) {  
      std::cerr << "*";
      TDirectory *fpDirs[3];      
      for(int fileType=0;fileType<3;fileType++) {
	if(!fpPreds[fileType]) continue;
	sprintf(dirName,"/dmi%d/t23i%d",dmi,t23i);
	fpPreds[fileType]->cd(dirName);
	fpDirs[fileType]=gDirectory;
      }



      for(int t13i=0;t13i<MAX_T13_INDEX;t13i++) {
	for(int deltai=0;deltai<MAX_DELTA_INDEX;deltai++) {

	   //Loop over the four types of fake data
	  for(int histType=0;histType<4;histType++) {		 
	    TH1D histPred("histPred","histPred",100,binEdge);
	    for(int fileType=0;fileType<3;fileType++) {		 
	      if(!fpPreds[fileType]) continue;
	      sprintf(histName,"%s_%d_%d_%d_%d",predHistNameArray[histType],dmi,t23i,t13i,deltai);
	      TH1D *histTemp = (TH1D*) fpDirs[fileType]->Get(histName);
	      
	      if(!histTemp) {
		std::cout << "Can't find " << histName << "\n";
		break;
	      }
	      histTemp->Scale(scaleFactor[fileType]);
	      histPred.Add(histTemp);
	      delete histTemp;
	    }
		 
	    for(int exp=0;exp<NUM_EXPS;exp++) {
	      if(!histData[histType][exp]) {
		std::cerr << "No data\n";
		break;
	      }		   		    

		 
	      Double_t LL=getLL(histData[histType][exp],&histPred);
	      tempArray[histType][t23i][t13i][deltai][exp]=LL;

 	    }
	  }
	}
      }
	
      for(int fileType=0;fileType<3;fileType++) {
	if(!fpPreds[fileType]) continue;
	fpDirs[fileType]->Close();
      }

    }
    for(int fileType=0;fileType<3;fileType++) {
      //      delete fpPreds[fileType];
      if(fpPreds[fileType]) fpPreds[fileType]->Close();
    }
  }
  
  int gotData[4][NUM_EXPS]={{0}};
  for(int histType=0;histType<4;histType++) {
    for(int exp=0;exp<NUM_EXPS;exp++) {
      if(histData[histType][exp]) {
	gotData[histType][exp]=1;
	delete histData[histType][exp];
      }
    }
  }







  std::cerr << "\n";
  //  std::ofstream OutFile(fileName);
  //  OutFile << "Experiment\tHistType\tt13i\tdeltai\tLL\n";
  Int_t exp;
  Int_t histType=0,t23i=0,t13i=0,deltai=0;
  Double_t LL=0;
  TFile *fpOut=NULL;
  TTree *llTree=NULL;
  for(exp=0;exp<NUM_EXPS;exp++) {
    sprintf(outName,"fakeSurfaces/%s/dm%d",runNameArray[run-1],thisDmBin);
    gSystem->mkdir(outName,kTRUE);

    //RJn switch to only writing a new file every 100 experiments
    if(exp%100==0) {
       if(potScale==1) {
	  sprintf(outName,"fakeSurfaces/%s/dm%d/exp%d_%d_%d_%d_%d.root",runNameArray[run-1],thisDmBin,exp,fakeDmBin,fakeT23bin,fakeT13Bin,fakeDeltaBin);
       }
       else {
	  sprintf(outName,"fakeSurfaces/%s/dm%d/scale%d_exp%d_%d_%d_%d_%d.root",runNameArray[run-1],thisDmBin,potScale,exp,fakeDmBin,fakeT23bin,fakeT13Bin,fakeDeltaBin);
       }       
       fpOut=TFile::Open(outName,"RECREATE");
       llTree = new TTree("llTree","llTree");
       llTree->Branch("exp",&exp,"exp/I");
       llTree->Branch("histType",&histType,"histType/I");
       llTree->Branch("t23i",&t23i,"t23i/I");
       llTree->Branch("t13i",&t13i,"t13i/I");
       llTree->Branch("deltai",&deltai,"deltai/I");
       llTree->Branch("LL",&LL,"LL/D");
    }



    std::cerr << "#";
    for(histType=0;histType<4;histType++) {
      if(!gotData[histType][exp]) break;        
      for(t23i=0;t23i<MAX_T23_INDEX;t23i++) {
	for(t13i=0;t13i<MAX_T13_INDEX;t13i++) {
	  for(deltai=0;deltai<MAX_DELTA_INDEX;deltai++) {
	    
	    LL=tempArray[histType][t23i][t13i][deltai][exp];
	    llTree->Fill();
	    //	  OutFile << exp << "\t" << histType << "\t" << t13i << "\t" << deltai << "\t" << LL << "\n";
	    //	    OutFile << LL << "\n";
	    
	  }
	}      
      }
    }

    if(exp%100==99) {
       fpOut->cd();
       llTree->Write();
       fpOut->Close();
    }
  }
  std::cerr << "\n";
  //  OutFile.close();

  fpFakeData->Close();
  
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

Long64_t getTempIndex(Int_t dmi, Int_t t23i, Int_t t13i, Int_t deltai) {
   Long64_t value= deltai+
      (MAX_DELTA_INDEX)*t13i+
      (MAX_DELTA_INDEX*MAX_T13_INDEX)*t23i+
      (MAX_DELTA_INDEX*MAX_T13_INDEX*MAX_T23_INDEX)*dmi;   
   return value;
}
