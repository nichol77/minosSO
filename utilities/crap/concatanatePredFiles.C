#include <iostream>
#include <fstream>
#include "TFile.h"
#include "TF1.h"
#include "TH1.h"
#include "TKey.h"
#include "TString.h"
#include "TMath.h"
#include "TRandom.h"
#include "TApplication.h"
#include "TROOT.h"
#include "src/paramFuncs.h"




void concatanatePredFiles(char *inputDirectory, char *outFile, char *tag)
{
   char histName[180];
   char fileName[180];


   Double_t binEdge[]={0,0.5,0.75,1,1.25,1.5,1.75,2,2.25,2.5,2.75,3,3.25,3.5,3.75,4,4.25,4.5,4.75,5,5.25,5.5,5.75,6,6.25,6.5,6.75,7,7.25,7.5,7.75,8,8.25,8.5,8.75,9,9.25,9.5,9.75,10,10.25,10.5,10.75,11,11.25,11.5,11.75,12,12.25,12.5,12.75,13,13.25,13.5,13.75,14,14.25,14.5,14.75,15,15.25,15.5,15.75,16,16.25,16.5,16.75,17,17.25,17.5,17.75,18,18.25,18.5,18.75,19,19.25,19.5,19.75,20,21,22,23,24,25,26,27,28,29,30,32,34,36,38,40,42,44,46,48,50,200};

   const char *predHistNameArray[4]={"histPredNQ","histPredPQ","histPredNC","histPredNCTrack"};

   TFile *fpOut = new TFile(outFile,"RECREATE");
   if(!fpOut) {
      std::cerr << "Can not open " << outFile << "\n";
      return;
   }
   

   if(tag)
     sprintf(histName,"histNoOscNQ_%s",tag);
   else
     sprintf(histName,"histNoOscNQ");
   TH1D *histNoOscNQ = new TH1D(histName,"histNoOscNQ",100,binEdge);

   if(tag)
     sprintf(histName,"histNoOscPQ_%s",tag);
   else
     sprintf(histName,"histNoOscPQ");
   TH1D *histNoOscPQ = new TH1D(histName,"histNoOscPQ",100,binEdge);

   if(tag)
     sprintf(histName,"histNoOscNC_%s",tag);
   else
     sprintf(histName,"histNoOscNC");
   TH1D *histNoOscNC = new TH1D(histName,"histNoOscNC",100,binEdge);

   if(tag)
     sprintf(histName,"histNoOscNCTrack_%s",tag);
   else
     sprintf(histName,"histNoOscNCTrack");
   TH1D *histNoOscNCTrack = new TH1D(histName,"histNoOscNCTrack",100,binEdge);
   
   
   TH1D *histPredNQ[MAX_DMI_INDEX][MAX_T23_INDEX];
   TH1D *histPredPQ[MAX_DMI_INDEX][MAX_T23_INDEX];
   TH1D *histPredNC[MAX_DMI_INDEX][MAX_T23_INDEX];
   TH1D *histPredNCTrack[MAX_DMI_INDEX][MAX_T23_INDEX];

   for(int dmi=0;dmi<MAX_DMI_INDEX;dmi++) {
     for(int t23i=0;t23i<MAX_T23_INDEX;t23i++) {
       sprintf(histName,"histPredNQ_%d_%d",dmi,t23i);
       histPredNQ[dmi][t23i] = new TH1D(histName,histName,100,binEdge);
       sprintf(histName,"histPredPQ_%d_%d",dmi,t23i);
       histPredPQ[dmi][t23i] = new TH1D(histName,histName,100,binEdge);
       sprintf(histName,"histPredNC_%d_%d",dmi,t23i);
       histPredNC[dmi][t23i] = new TH1D(histName,histName,100,binEdge);
       sprintf(histName,"histPredNCTrack_%d_%d",dmi,t23i);
       histPredNCTrack[dmi][t23i] = new TH1D(histName,histName,100,binEdge);
     }
   }


   Int_t dmi;
   Int_t t23i;

   for(int outNum=0;outNum<1;outNum++) {
      sprintf(fileName,"%s/out%d.root",inputDirectory,outNum);
      TFile fpIn(fileName,"OLD");
      if(!fpIn.IsOpen()) break;


      TIter nextkey(fpIn.GetListOfKeys());
      TKey *key;
      int count=0;
      while (key = (TKey*)nextkey()) {
	 if(count%1000==0) std::cerr << "*";
	 count++;
	 TH1D *thisHist = (TH1D*)key->ReadObj();
	 TString histString(thisHist->GetName());
	 if(histString.BeginsWith("histNoOsc")) {
	    //One of the no osc histograms
	    if(histString.BeginsWith("histNoOscNQ")) {
	       histNoOscNQ->Add(thisHist);
	    }
	    else if(histString.BeginsWith("histNoOscPQ")) {
	       histNoOscPQ->Add(thisHist);
	    }
	    else if(histString.BeginsWith("histNoOscNC")) {
	       histNoOscNC->Add(thisHist);
	    }
	    else if(histString.BeginsWith("histNoOscNCTrack")) {
	       histNoOscNCTrack->Add(thisHist);
	    }
	 }	 
	 
	 else if(histString.BeginsWith("histPredNQ")) {
	    sscanf(histString.Data(),"histPredNQ_%d_%d",&dmi,&t23i);
	    //	    std::cout << "Got " << histString.Data() << "\t" <<dmi << "\t" << t23i << "\n";
	    histPredNQ[dmi][t23i]->Add(thisHist);
	 }
	 else if(histString.BeginsWith("histPredPQ")) {
	    sscanf(histString.Data(),"histPredPQ_%d_%d",&dmi,&t23i);
	    //	    std::cout << "Got " << histString.Data() << "\t" <<dmi << "\t" << t23i << "\n";
	    histPredPQ[dmi][t23i]->Add(thisHist);
	 }
	 else if(histString.BeginsWith("histPredNC")) {
	    sscanf(histString.Data(),"histPredNC_%d_%d",&dmi,&t23i);
	    //	    std::cout << "Got " << histString.Data() << "\t" <<dmi << "\t" << t23i << "\n";
	    histPredNC[dmi][t23i]->Add(thisHist);
	 }
	 else if(histString.BeginsWith("histPredNCTrack")) {
	    sscanf(histString.Data(),"histPredNCTrack_%d_%d",&dmi,&t23i);
	    //	    std::cout << "Got " << histString.Data() << "\t" <<dmi << "\t" << t23i << "\n";
	    histPredNCTrack[dmi][t23i]->Add(thisHist);
	 }	 	    	 
	 //	 thisHist->Delete();
	 delete thisHist;
      }
      std::cerr <<"\n";
      gROOT->GetListOfFiles()->Remove(&fpIn);
      
   


      
     //  TH1D *tempNoOscNQ=(TH1D*)fpIn.Get(histNoOscNQ->GetName());
//       if(tempNoOscNQ) {histNoOscNQ->Add(tempNoOscNQ); delete tempNoOscNQ;}
//       TH1D *tempNoOscPQ=(TH1D*)fpIn.Get(histNoOscPQ->GetName());
//       if(tempNoOscPQ) { histNoOscPQ->Add(tempNoOscPQ); delete tempNoOscPQ;}

//       TH1D *tempNoOscNC=(TH1D*)fpIn.Get(histNoOscNC->GetName());
//       if(tempNoOscNC) {histNoOscNC->Add(tempNoOscNC); delete tempNoOscNC;}

//       TH1D *tempNoOscNCTrack=(TH1D*)fpIn.Get(histNoOscNCTrack->GetName());
//       if(tempNoOscNCTrack) {histNoOscNCTrack->Add(tempNoOscNCTrack); delete tempNoOscNCTrack;}
   }


   fpOut->Write();
   fpOut->Close();
   std::cout << "Closed file\n";
   gApplication->Terminate();

}
