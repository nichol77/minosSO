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


void doGridSearchReal(int run);


int main(int argc, char **argv) 
{

  if(argc<2) {
    std::cerr << "Usage\n\t" << argv[0] << " <run> \n";
    return -1;
  }
  int run=atoi(argv[1]);
   

  doGridSearchReal(run);
   
}


void doGridSearchReal(int run) {



  const char *runNameArray[11]={"run1","run2","run3","run4","run5","run6","run7","run8","run9","run10","run11"};
  
  char inFile[180];
  sprintf(inFile,"farFiles/%s_fd_data.root",runNameArray[run-1]);
  char outFile[180];
  sprintf(outFile,"realSurfaces/%s/realSurface.root",runNameArray[run-1]);

  doGridSearchGeneric(run,inFile,outFile,"fd_data",1);
}
