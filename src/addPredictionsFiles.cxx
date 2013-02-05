#include <iostream>
#include <fstream>
#include "TFile.h"
#include "TF1.h"
#include "TH1.h"
#include "TH2.h"
#include "TMath.h"
#include "TChain.h"
#include "TDirectory.h"
#include "TString.h"
#include "TKey.h"
#include "TROOT.h"
#include "NuDstLooper.h"
#include "paramFuncs.h"



int main(int argc, char **argv) 
{

   Double_t binEdge[]={0,0.5,0.75,1,1.25,1.5,1.75,2,2.25,2.5,2.75,3,3.25,3.5,3.75,4,4.25,4.5,4.75,5,5.25,5.5,5.75,6,6.25,6.5,6.75,7,7.25,7.5,7.75,8,8.25,8.5,8.75,9,9.25,9.5,9.75,10,10.25,10.5,10.75,11,11.25,11.5,11.75,12,12.25,12.5,12.75,13,13.25,13.5,13.75,14,14.25,14.5,14.75,15,15.25,15.5,15.75,16,16.25,16.5,16.75,17,17.25,17.5,17.75,18,18.25,18.5,18.75,19,19.25,19.5,19.75,20,21,22,23,24,25,26,27,28,29,30,32,34,36,38,40,42,44,46,48,50,200};

   if(argc<4) {
      std::cerr << "Usage\n\t" << argv[0] << " <outputFile> <tag> <input file1> <input file 2> <input file 3> ...\n";
      return -1;
   }

   char *outputFile=argv[1];
   char *tag=argv[2];

   TFile *fpOut = new TFile(outputFile,"RECREATE");

   
   Int_t numInputFiles=argc-3;

   char histName[180];
   char dirName[180];
  
   TFile *fpList[100];


   for(int inFile=0;inFile<numInputFiles;inFile++) {
     fpList[inFile] = TFile::Open(argv[3+inFile],"OLD");
   }

   fpOut->cd();

   if(tag)
      sprintf(histName,"histNoOscNQ_%s",tag);
   else
      sprintf(histName,"histNoOscNQ");
   TH1D *histNoOscNQ = new TH1D(histName,"histNoOscNQ",100,binEdge);
   for(int inFile=0;inFile<numInputFiles;inFile++) {
     TH1D *histTemp = (TH1D*) fpList[inFile]->Get(histName);
     histNoOscNQ->Add(histTemp);
     delete histTemp;
   }
   histNoOscNQ->Write();


   if(tag)
      sprintf(histName,"histNoOscPQ_%s",tag);
   else
      sprintf(histName,"histNoOscPQ");
   TH1D *histNoOscPQ = new TH1D(histName,"histNoOscPQ",100,binEdge);
   for(int inFile=0;inFile<numInputFiles;inFile++) {
     TH1D *histTemp = (TH1D*) fpList[inFile]->Get(histName);
     histNoOscPQ->Add(histTemp);
     delete histTemp;
   }
   histNoOscPQ->Write();

   if(tag)
      sprintf(histName,"histNoOscNC_%s",tag);
   else
      sprintf(histName,"histNoOscNC");
   TH1D *histNoOscNC = new TH1D(histName,"histNoOscNC",100,binEdge);
   for(int inFile=0;inFile<numInputFiles;inFile++) {
     TH1D *histTemp = (TH1D*) fpList[inFile]->Get(histName);
     histNoOscNC->Add(histTemp);
     delete histTemp;
   }
   histNoOscNC->Write();


   if(tag)
      sprintf(histName,"histNoOscNCTrack_%s",tag);
   else
      sprintf(histName,"histNoOscNCTrack");
   TH1D *histNoOscNCTrack = new TH1D(histName,"histNoOscNCTrack",100,binEdge);
   for(int inFile=0;inFile<numInputFiles;inFile++) {
     TH1D *histTemp = (TH1D*) fpList[inFile]->Get(histName);
     histNoOscNCTrack->Add(histTemp);
     delete histTemp;
   }
   histNoOscNCTrack->Write();

   
   char tempHistName[180];
   char tempDirName[180];

   //   TDirectory *

   //   for(int dmi=0;dmi<MAX_DMI_INDEX;dmi++) {
   for(int dmi=0;dmi<2;dmi++) {
     std::cerr << "\n" << dmi << ": ";	        
     sprintf(dirName,"dmi%d",dmi);
     fpOut->mkdir(dirName);
     fpOut->cd(dirName);
     TDirectory *dmiDir=gDirectory;
     for(int t23i=0;t23i<MAX_T23_INDEX;t23i++) {
     std::cerr << "#";	       
       sprintf(dirName,"t23i%d",t23i);
       dmiDir->mkdir(dirName);
       dmiDir->cd(dirName);
       TDirectory *t23Dir=gDirectory;
       



       for(int t13i=0;t13i<MAX_T13_INDEX;t13i++) {	    
	 for(int deltai=0;deltai<MAX_DELTA_INDEX;deltai++) {  

	   sprintf(histName,"histPredNQ_%d_%d_%d_%d",dmi,t23i,t13i,deltai);
	   TH1D histPredNQ(histName,histName,100,binEdge);
	   sprintf(tempHistName,"/dmi%d/t23i%d/histPredNQ_%d_%d_%d_%d",dmi,t23i,dmi,t23i,t13i,deltai);
	   for(int inFile=0;inFile<numInputFiles;inFile++) {
	     TH1D *histTemp = (TH1D*) fpList[inFile]->Get(tempHistName);
	     if(histTemp) {
	       histPredNQ.Add(histTemp);
	       delete histTemp;
	     }
	   }
	   


	   sprintf(histName,"histPredPQ_%d_%d_%d_%d",dmi,t23i,t13i,deltai);
	   TH1D histPredPQ(histName,histName,100,binEdge);
	   sprintf(tempHistName,"/dmi%d/t23i%d/histPredPQ_%d_%d_%d_%d",dmi,t23i,dmi,t23i,t13i,deltai);
	   for(int inFile=0;inFile<numInputFiles;inFile++) {
	     TH1D *histTemp = (TH1D*) fpList[inFile]->Get(tempHistName);
	     if(histTemp) {
	       histPredPQ.Add(histTemp);
	       delete histTemp;
	     }
	   }

	   sprintf(histName,"histPredNC_%d_%d_%d_%d",dmi,t23i,t13i,deltai);
	   TH1D histPredNC(histName,histName,100,binEdge);
	   sprintf(tempHistName,"/dmi%d/t23i%d/histPredNC_%d_%d_%d_%d",dmi,t23i,dmi,t23i,t13i,deltai);
	   for(int inFile=0;inFile<numInputFiles;inFile++) {
	     TH1D *histTemp = (TH1D*) fpList[inFile]->Get(tempHistName);
	     if(histTemp) {
	       histPredNC.Add(histTemp);
	       delete histTemp;
	     }
	   }

	   sprintf(histName,"histPredNCTrack_%d_%d_%d_%d",dmi,t23i,t13i,deltai);
	   TH1D histPredNCTrack(histName,histName,100,binEdge);
	   sprintf(tempHistName,"/dmi%d/t23i%d/histPredNCTrack_%d_%d_%d_%d",dmi,t23i,dmi,t23i,t13i,deltai);
	   for(int inFile=0;inFile<numInputFiles;inFile++) {
	     TH1D *histTemp = (TH1D*) fpList[inFile]->Get(tempHistName);

	     if(histTemp) {
	       histPredNCTrack.Add(histTemp);
	       delete histTemp;
	     }
	   }


	   sprintf(histName,"histCCPredNQ_%d_%d_%d_%d",dmi,t23i,t13i,deltai);
	   TH1D histCCPredNQ(histName,histName,100,binEdge);
	   sprintf(tempHistName,"/dmi%d/t23i%d/histCCPredNQ_%d_%d_%d_%d",dmi,t23i,dmi,t23i,t13i,deltai);
	   for(int inFile=0;inFile<numInputFiles;inFile++) {
	     TH1D *histTemp = (TH1D*) fpList[inFile]->Get(tempHistName);

	     if(histTemp) {
	       histCCPredNQ.Add(histTemp);
	       delete histTemp;
	     }
	   }


	   sprintf(histName,"histCCPredPQ_%d_%d_%d_%d",dmi,t23i,t13i,deltai);
	   TH1D histCCPredPQ(histName,histName,100,binEdge);
	   sprintf(tempHistName,"/dmi%d/t23i%d/histCCPredPQ_%d_%d_%d_%d",dmi,t23i,dmi,t23i,t13i,deltai);
	   for(int inFile=0;inFile<numInputFiles;inFile++) {
	     TH1D *histTemp = (TH1D*) fpList[inFile]->Get(tempHistName);

	     if(histTemp) {
	       histCCPredPQ.Add(histTemp);
	       delete histTemp;
	     }
	     }


	   sprintf(histName,"histCCPredNC_%d_%d_%d_%d",dmi,t23i,t13i,deltai);
	   TH1D histCCPredNC(histName,histName,100,binEdge);
	   sprintf(tempHistName,"/dmi%d/t23i%d/histCCPredNC_%d_%d_%d_%d",dmi,t23i,dmi,t23i,t13i,deltai);
	   for(int inFile=0;inFile<numInputFiles;inFile++) {
	     TH1D *histTemp = (TH1D*) fpList[inFile]->Get(tempHistName);
	     histCCPredNC.Add(histTemp);
	     delete histTemp;
	   }


	   sprintf(histName,"histCCPredNCTrack_%d_%d_%d_%d",dmi,t23i,t13i,deltai);
	   TH1D histCCPredNCTrack(histName,histName,100,binEdge);
	   sprintf(tempHistName,"/dmi%d/t23i%d/histCCPredNCTrack_%d_%d_%d_%d",dmi,t23i,dmi,t23i,t13i,deltai);
	   for(int inFile=0;inFile<numInputFiles;inFile++) {
	     TH1D *histTemp = (TH1D*) fpList[inFile]->Get(tempHistName);
	     if(histTemp) {
	       histCCPredNCTrack.Add(histTemp);
	       delete histTemp;
	     }
	   }



	   histPredNQ.Write();
	   histPredPQ.Write();
	   histPredNC.Write();
	   histPredNCTrack.Write();
	   histCCPredNQ.Write();
	   histCCPredPQ.Write();
	   histCCPredNC.Write();
	   histCCPredNCTrack.Write();

	 }
       }
       
       t23Dir->Close();
     }
     
     dmiDir->Close();
   }
}
