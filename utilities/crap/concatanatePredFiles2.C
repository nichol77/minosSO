#include <iostream>
#include <fstream>
#include "TFile.h"
#include "TF1.h"
#include "TH1.h"
#include "TMath.h"
#include "TRandom.h"
#include "src/paramFuncs.h"




void concatanatePredFiles(char *inputDirectory, int firstRun, int secondRun, char *tag)
{
   char histName[180];
   char fileName[180];


   sprintf(fileName,"%s/out%d.root",inputDirectory,secondRun);
   TFile *fpSecondRun = new TFile(fileName,"OLD");
   if(!fpSecondRun) {
     std::cerr << "Can not open " << fileName << "\n";
      return;
   }
   
   sprintf(fileName,"%s/out%d.root",inputDirectory,firstRun);
   TFile *fpFirstRun = new TFile(fileName,"UPDATE");
   if(!fpFirstRun) {
      std::cerr << "Can not open " << fileName << "\n";
      return;
   }
   

   if(tag)
     sprintf(histName,"histNoOscNQ_%s",tag);
   else
     sprintf(histName,"histNoOscNQ");
   TH1D *histNoOscNQ = (TH1D*) fpFirstRun->Get(histName);
   TH1D *tempNoOscNQ = (TH1D*) fpSecondRun->Get(histName);
   if(tempNoOscNQ && histNoOscNQ) histNoOscNQ->Add(tempNoOscNQ);
   fpFirstRun->cd();
   histNoOscNQ->Write("",TObject::kOverwrite);


   if(tag)
     sprintf(histName,"histNoOscPQ_%s",tag);
   else
     sprintf(histName,"histNoOscPQ");
   TH1D *histNoOscPQ = (TH1D*) fpFirstRun->Get(histName);
   TH1D *tempNoOscPQ = (TH1D*) fpSecondRun->Get(histName);
   if(tempNoOscPQ && histNoOscPQ) histNoOscPQ->Add(tempNoOscPQ);
   fpFirstRun->cd();
   histNoOscPQ->Write("",TObject::kOverwrite);



   if(tag)
     sprintf(histName,"histNoOscNC_%s",tag);
   else
     sprintf(histName,"histNoOscNC");
   TH1D *histNoOscNC = (TH1D*) fpFirstRun->Get(histName);
   TH1D *tempNoOscNC = (TH1D*) fpSecondRun->Get(histName);
   if(tempNoOscNC && histNoOscNC) histNoOscNC->Add(tempNoOscNC);
   fpFirstRun->cd();
   histNoOscNC->Write("",TObject::kOverwrite);



   if(tag)
     sprintf(histName,"histNoOscNCTrack_%s",tag);
   else
     sprintf(histName,"histNoOscNCTrack");
   TH1D *histNoOscNCTrack = (TH1D*) fpFirstRun->Get(histName);
   TH1D *tempNoOscNCTrack = (TH1D*) fpSecondRun->Get(histName);
   if(tempNoOscNCTrack && histNoOscNCTrack) histNoOscNCTrack->Add(tempNoOscNCTrack);
   fpFirstRun->cd();
   histNoOscNCTrack->Write("",TObject::kOverwrite);


   for(int dmi=0;dmi<MAX_DMI_INDEX;dmi++) {
     std::cerr << "*";
     for(int t23i=0;t23i<MAX_T23_INDEX;t23i++) {
       sprintf(histName,"histPredNQ_%d_%d",dmi,t23i);
       TH1D *histPredNQ = (TH1D*) fpFirstRun->Get(histName);
       TH1D *tempPredNQ = (TH1D*) fpSecondRun->Get(histName);
       if(tempPredNQ && histPredNQ) histPredNQ->Add(tempPredNQ);
       fpFirstRun->cd();
       histPredNQ->Write("",TObject::kOverwrite);



       sprintf(histName,"histPredPQ_%d_%d",dmi,t23i);
       TH1D *histPredPQ = (TH1D*) fpFirstRun->Get(histName);
       TH1D *tempPredPQ = (TH1D*) fpSecondRun->Get(histName);
       if(tempPredPQ && histPredPQ) histPredPQ->Add(tempPredPQ);
       fpFirstRun->cd();
       histPredPQ->Write("",TObject::kOverwrite);
     


       sprintf(histName,"histPredNC_%d_%d",dmi,t23i);
       TH1D *histPredNC = (TH1D*) fpFirstRun->Get(histName);
       TH1D *tempPredNC = (TH1D*) fpSecondRun->Get(histName);
       if(tempPredNC && histPredNC) histPredNC->Add(tempPredNC);
       fpFirstRun->cd();
       histPredNC->Write("",TObject::kOverwrite);



       sprintf(histName,"histPredNCTrack_%d_%d",dmi,t23i);
       TH1D *histPredNCTrack = (TH1D*) fpFirstRun->Get(histName);
       TH1D *tempPredNCTrack = (TH1D*) fpSecondRun->Get(histName);
       if(tempPredNCTrack && histPredNCTrack) histPredNCTrack->Add(tempPredNCTrack);
       fpFirstRun->cd();
       histPredNCTrack->Write("",TObject::kOverwrite);	 
     }
   }
   std::cerr << "\n";

   fpFirstRun->Close();
   
}
