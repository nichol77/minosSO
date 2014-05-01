1#include <iostream>
#include <fstream>
#include "TFile.h"
#include "TF1.h"
#include "TH1.h"
#include "TH2.h"
#include "TMath.h"
#include "TChain.h"
#include "TString.h"
#include "TKey.h"
#include "TROOT.h"
#include "NuDstLooper.h"



int main(int argc, char **argv) 
{
   if(argc<5) {
      std::cerr << "Usage\n\t" << argv[0] << " <outputFile> <runTag> <outTag> <input dir> <rw file>\n";
      return -1;
   }

   char *outputFile=argv[1];
   char *runTag=argv[2];
   char *outTag=argv[3];
   char *inDir=argv[4];
   int doRw=0;
   char rwFilename[180];
   if(argc>5) {
     doRw=1;
     sprintf(rwFilename,"%s",argv[5]);
   }

   std::cout << doRw << "\t" << rwFilename << "\n";
   //   return -1;

   char inputFileWildCard[FILENAME_MAX];
   sprintf(inputFileWildCard,"%s/NuDSTMicro*.root",inDir);

   TChain *theChain = new TChain("s");
   theChain->Add(inputFileWildCard);

   std::cout << theChain->GetEntries() << "\n";
   
   Long64_t nentries=theChain->GetEntries();
   if(nentries<=0) {
     return -1;
   }
   
   
  char histName[180];
  
  
  TFile *fpRat = new TFile("/home/rjn/minos/ccPlusNc/ndRatios/NDRatioNew.root");
  sprintf(histName,"histEnergyNQ_%s_nd_data_over_mc_ratio",runTag);
  TH1D *ndRatNQ = (TH1D*) fpRat->Get(histName);
  if(!ndRatNQ) {
    std::cerr << "Can't get " << histName << "\n";
    return -1;
  }
  sprintf(histName,"histEnergyPQ_%s_nd_data_over_mc_ratio",runTag);
  TH1D *ndRatPQ = (TH1D*) fpRat->Get(histName);
  if(!ndRatPQ) {
    std::cerr << "Can't get " << histName << "\n";
    return -1;
  }
  
  sprintf(histName,"histEnergyNC_%s_nd_data_over_mc_ratio",runTag);
  TH1D *ndRatNC = (TH1D*) fpRat->Get(histName);
  if(!ndRatNC) {
    std::cerr << "Can't get " << histName << "\n";
    return -1;
  }
  
  sprintf(histName,"histEnergyNCTrack_%s_nd_data_over_mc_ratio",runTag);
  TH1D *ndRatNCTrack = (TH1D*) fpRat->Get(histName);
  if(!ndRatNCTrack) {
    std::cerr << "Can't get " << histName << "\n";
    return -1;
  }
  
  char *rwHistNameArray[4]={"histTrueEnergyNumu_mp_run3_ratio","histTrueEnergyNumubar_mp_run3_ratio","histTrueEnergyNue_mp_run3_ratio","histTrueEnergyNuebar_mp_run3_ratio"};
  TH1D *rwHists[4]={0};
  if(doRw) {
     TFile *fpRw = new TFile(rwFilename);
     for(int i=0;i<4;i++) {
	rwHists[i]=(TH1D*) fpRw->Get(rwHistNameArray[i]);
	std::cout << rwHists[i] << "\t" << rwHistNameArray[i] << "\n";
     }
  }
  //  return -1;
    

  NuDstLooper fred(theChain);
  if(!doRw) {
    fred.MakePassTree(outputFile,ndRatNQ,ndRatPQ,ndRatNC,ndRatNCTrack,outTag); 
  } 
  else {
    fred.MakePassTree(outputFile,ndRatNQ,ndRatPQ,ndRatNC,ndRatNCTrack,outTag,rwHists[0],rwHists[1],rwHists[2],rwHists[3]); 
  }

  return 0;

}

// void runNuDstLooperFourFilePredMaker(char *inputFile1,char *inputFile2,char *inputFile3,char *inputFile4, char *outputFile, char *runTag, char *outTag)
// {
//   gSystem->CompileMacro("src/OscCalc.C","k");
//   gSystem->CompileMacro("src/NuDstLooper.C","k");
//   
//    //   theChain->Add("/minos/data/analysis/NuMuBar/DSTs/2010/R2.2/MC/D07_dogwood3/far/r1/micro2010/NuDSTMicro*.root");
//   theChain->Add(inputFile1);
//   theChain->Add(inputFile2);
//   theChain->Add(inputFile3);
//   theChain->Add(inputFile4);
 
  


//   return -1;
// }
 
