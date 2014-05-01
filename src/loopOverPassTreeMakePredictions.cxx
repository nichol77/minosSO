#include <iostream>
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
    std::cerr << "Usage\n\t" << argv[0] << " <outputFile>  <passFile> <start dmi> <end dmi>\n";
    return -1;
  }
  
  char *outputFile=argv[1];
  char *passFile=argv[2];
  int startDmi=atoi(argv[3]);
  int endDmi=atoi(argv[4]);  
    
  NuDstLooper fred;
  fred.MakePredicitonsFromPassTree(passFile, outputFile, startDmi,endDmi);

  return 0;

}

