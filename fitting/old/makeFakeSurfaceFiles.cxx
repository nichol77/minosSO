#include <iostream>
#include <fstream>
#include "TFile.h"
#include "TF1.h"
#include "TH1.h"
#include "TTree.h"
#include "TTreeCache.h"
#include "TH2.h"
#include "TMath.h"
#include "TCanvas.h"
#include "TDirectory.h"
#include "TString.h"
#include "TKey.h"
#include "TROOT.h"
#include "gridSearch.h"
#include "src/paramFuncs.h"

#define NUM_EXPS 1000


int main(int argc, char **argv) 
{

  if(argc<8) {
    std::cerr << "Usage\n\t" << argv[0] << " <run> <dm bin> <t23 bin> <t13 bin> <delta bin> <first exp> <last exp>\n";
    return -1;
  }
  int run=atoi(argv[1]);
  int fakeDmBin=atoi(argv[2]);
  int fakeT23Bin=atoi(argv[3]);
  int fakeT13Bin=atoi(argv[4]);
  int fakeDeltaBin=atoi(argv[5]);  
  int firstExp=atoi(argv[6]);  
  int lastExp=atoi(argv[7]);   
  int potScale=1;
  if(argc>8) {
     potScale=atoi(argv[8]);
  }

  char fileName[180];
  char inName[180];
  char dirName[180];
  char outName[180];


  const char *runNameArray[11]={"run1","run2","run3","run4","run5","run6","run7","run8","run9","run10","minosPlus"};


  const char *histNameArray[4]={"histEnergyNQ","histEnergyPQ","histEnergyNC","histEnergyNCTrack"};

  if(potScale==1) {
    sprintf(fileName,"fakeSurfaces/fakeSurface_%s_exps_%d_%d_%d_%d_%d.root",runNameArray[run-1],NUM_EXPS,fakeDmBin,fakeT23Bin,fakeT13Bin,fakeDeltaBin);
  }
  else {
    sprintf(fileName,"fakeSurfaces/fakeSurface_%s_scale%d_exps_%d_%d_%d_%d_%d.root",runNameArray[run-1],potScale,NUM_EXPS,fakeDmBin,fakeT23Bin,fakeT13Bin,fakeDeltaBin);
  }
  TFile *fpSurface;
  if(firstExp==0) {
    fpSurface= new TFile(fileName,"RECREATE");
  }
  else {
    fpSurface = new TFile(fileName,"UPDATE");
  }
  if(!fpSurface) {
    std::cerr << "Can not open " << fileName << "\n";
    return -1;
  }
  
  
  TDirectory *fpExp[NUM_EXPS]={0};
  for(int exp=firstExp;exp<=lastExp;exp++) {     
    fpSurface->cd();
    sprintf(dirName,"exp%d",exp);
    fpSurface->mkdir(dirName);
    fpSurface->cd(dirName);
    fpExp[exp]=gDirectory;
  }


  //LL tree variables
  Int_t exp=0,histType=0,t23i=0,t13i=0,deltai=0;
  Double_t LL=0;



  Long64_t treeEntry[MAX_DMI_INDEX]={0};
  Long64_t lastTreeEntry[MAX_DMI_INDEX]={0};
  for(int dmi=0;dmi<MAX_DMI_INDEX;dmi++) {
    treeEntry[dmi]=firstExp*4*MAX_T23_INDEX*MAX_T13_INDEX*MAX_DELTA_INDEX;
    lastTreeEntry[dmi]=(lastExp+1)*4*MAX_T23_INDEX*MAX_T13_INDEX*MAX_DELTA_INDEX;
  }
  std::cerr << "Starting index is: " << firstExp*4*MAX_T23_INDEX*MAX_T13_INDEX*MAX_DELTA_INDEX << "\n";
  TTreeCache::SetLearnEntries(1);

  TFile *fpTrees[MAX_DMI_INDEX]={0};
  TTree *llTrees[MAX_DMI_INDEX]={0};
  for(int dmi=0;dmi<MAX_DMI_INDEX;dmi++) {
     //     std::cerr << "$";
    if(potScale==1) {
      sprintf(inName,"fakeSurfaces/%s/thisdm%d_exps_%d_%d_%d_%d_%d.root",runNameArray[run-1],dmi,NUM_EXPS,fakeDmBin,fakeT23Bin,fakeT13Bin,fakeDeltaBin);
    }
    else {
      sprintf(inName,"fakeSurfaces/%s/thisdm%d_scale%d_exps_%d_%d_%d_%d_%d.root",runNameArray[run-1],dmi,potScale,NUM_EXPS,fakeDmBin,fakeT23Bin,fakeT13Bin,fakeDeltaBin);
    }
  
    
    fpTrees[dmi] = new TFile(inName,"OLD");
    llTrees[dmi] = (TTree*) fpTrees[dmi]->Get("llTree");
    
    llTrees[dmi]->SetBranchAddress("exp",&exp);
    llTrees[dmi]->SetBranchAddress("histType",&histType);
    llTrees[dmi]->SetBranchAddress("t23i",&t23i);
    llTrees[dmi]->SetBranchAddress("t13i",&t13i);
    llTrees[dmi]->SetBranchAddress("deltai",&deltai);
    llTrees[dmi]->SetBranchAddress("LL",&LL);

    Int_t cachesize = 1000000; //10 MBytes
    llTrees[dmi]->SetCacheSize(cachesize); //<<<
    llTrees[dmi]->AddBranchToCache("*",kTRUE);    //<<< add all branches to the cache
    llTrees[dmi]->SetCacheEntryRange(treeEntry[dmi],lastTreeEntry[dmi]);
    
  }
  std::cerr << "\n";



  Double_t t23Array[MAX_T23_INDEX]={0};
  Double_t dmArray[MAX_DMI_INDEX]={0};

  for(int t23i=0;t23i<MAX_T23_INDEX;t23i++) {
    t23Array[t23i]=getT23(t23i);
  }


  for(int dmi=0;dmi<MAX_DMI_INDEX;dmi++) {
    dmArray[dmi]=1e3*getDeltaM2(dmi);
  }



  // for(int exp2=0;exp2<NUM_EXPS;exp2++) {
  //  for(int exp2=0;exp2<20;exp2++) {
  for(int exp2=firstExp;exp2<=lastExp;exp2++) {
   fpExp[exp2]->cd();
    std::cerr << "#";
    TH2D *histInverted[4][MAX_T13_INDEX][MAX_DELTA_INDEX]={{{0}}};
    TH2D *histNormal[4][MAX_T13_INDEX][MAX_DELTA_INDEX]={{{0}}};

    for(int histType2=0;histType2<4;histType2++) {
      for(int t13i2=0;t13i2<MAX_T13_INDEX;t13i2++) {
	for(int deltai2=0;deltai2<MAX_DELTA_INDEX;deltai2++) {
	  sprintf(outName,"histInverted_%s_%d_%d_%d",histNameArray[histType2],exp2,t13i2,deltai2);
	  histInverted[histType2][t13i2][deltai2]=getNewInvertedHistogram(outName);
	  
	  sprintf(outName,"histNormal_%s_%d_%d_%d",histNameArray[histType2],exp2,t13i2,deltai2);
	  histNormal[histType2][t13i2][deltai2]=getNewNormalHistogram(outName);
	}
      }
    }

    for(int dmi=0;dmi<MAX_DMI_INDEX;dmi++) {
       if(exp2==firstExp) {
	  std::cerr << "$";
       }
      for(int histType2=0;histType2<4;histType2++) {
	  for(int t23i2=0;t23i2<MAX_T23_INDEX;t23i2++) {
	    for(int t13i2=0;t13i2<MAX_T13_INDEX;t13i2++) {
	      for(int deltai2=0;deltai2<MAX_DELTA_INDEX;deltai2++) {
		llTrees[dmi]->GetEntry(treeEntry[dmi]);
		treeEntry[dmi]++;
		if(histType!=histType2 || t23i2!=t23i || t13i2!=t13i || deltai2!=deltai) {
		  std::cout << "Mismatched " << histType << " " << t23i << " " << t13i << " " << deltai
			    << "\t" << histType2 << " " << t23i2 << " " << t13i2 << " " << deltai2 << "\n";
		}
		else {
		  if(dmArray[dmi]<0) {		    
		    histInverted[histType][t13i][deltai]->Fill(t23Array[t23i],dmArray[dmi],LL );//llArray[histType][exp][dmi][t23i][t13i][deltai]);
		  }
		  else {
		    histNormal[histType][t13i][deltai]->Fill(t23Array[t23i], dmArray[dmi],LL);//llArray[histType][exp][dmi][t23i][t13i][deltai]);
		  }
		}
	      }
	    }
	  }
      }
    }
    for(int histType2=0;histType2<4;histType2++) {
      for(int t13i2=0;t13i2<MAX_T13_INDEX;t13i2++) {
	for(int deltai2=0;deltai2<MAX_DELTA_INDEX;deltai2++) {
	  histInverted[histType2][t13i2][deltai2]->Write();
	  delete histInverted[histType2][t13i2][deltai2];

	  histNormal[histType2][t13i2][deltai2]->Write();
	  delete histNormal[histType2][t13i2][deltai2];
	}
      }
     }
    fpExp[exp2]->Close();
    delete fpExp[exp2];
 }

 return 0;
}
