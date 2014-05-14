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


void doGridSearchDistorted(int run, int dmBin,int t23Bin,int t13Bin, int deltaBin,int distorted, int potScale);


int main(int argc, char **argv) 
{

  if(argc<8) {
    std::cerr << "Usage\n\t" << argv[0] << " <run> <dm bin> <t23 bin> <t13 bin> <delta bin><distortedFlag> <potScale> \n";
    return -1;
  }
  int run=atoi(argv[1]);

  int dmBin=atoi(argv[2]);
  int t23Bin=atoi(argv[3]);
  int t13Bin=atoi(argv[4]);
  int deltaBin=atoi(argv[5]);
  int distorted=atoi(argv[6]);
  int potScale=atoi(argv[7]);
   

  doGridSearchDistorted(run,dmBin,t23Bin,t13Bin,deltaBin,distorted,potScale);
   
}


void doGridSearchDistorted(int run, int dmBin,int t23Bin,int t13Bin, int deltaBin,int distorted, int potScale)
 {



  const char *runNameArray[11]={"run1","run2","run3","run4","run5","run6","run7","run8","run9","run10","run11"};
  
  char inFile[180];
  char *distortedTag[2]={"","distorted_"};

  char potTag[180];
  sprintf(potTag,"");
  if(potScale>1) {
     sprintf(potTag,"scale%d_",potScale);
  }

  sprintf(inFile,"fakeData/%s_%s%sfake_%d_%d_%d_%d.root",runNameArray[run-1],distortedTag[distorted],potTag,dmBin,t23Bin,t13Bin,deltaBin);
  char outFile[180];
  sprintf(outFile,"fakeSurfaces/fakeSurface_%s_%s%sfake_%d_%d_%d_%d.root",runNameArray[run-1],distortedTag[distorted],potTag,dmBin,t23Bin,t13Bin,deltaBin);

  doGridSearchGeneric(run,inFile,outFile,"0",potScale,1);
}
