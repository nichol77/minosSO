#ifndef GRID_SEARCH_H
#define GRID_SEARCH_H

#include "TH1.h"

//#define START_BIN 1 //All energy bins
#define START_BIN 6   //2 GeV Cut off




Double_t getLL(TH1D *histData, TH1D *histPred) ;
Long64_t getTempIndex(Int_t dmi, Int_t t23i, Int_t t13i, Int_t deltai) ;
void doGridSearchGeneric(int run,char *inFile, char *outFile,char *histTag, int potScale,int fakeData=0);

#endif
