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


void doGridSearchAlex(int run, int alexRun);


int main(int argc, char **argv) 
{

  if(argc<3) {
    std::cerr << "Usage\n\t" << argv[0] << " <run> <alex run> \n";
    return -1;
  }
  int run=atoi(argv[1]);
  int alexRun=atoi(argv[2]);
   

  doGridSearchAlex(run,alexRun);
  
}


void doGridSearchAlex(int run, int alexRun)
{
   
   
   char inFile[180];
   sprintf(inFile,"/unix/minos1/rjn/altHornCurr/farHornCurrNorm_%d.root",alexRun);
   char outFile[180];
   sprintf(outFile,"fakeSurfaces/altHornCurr/fakeSurface_%d.root",alexRun);
   char ratioFile[180];
   sprintf(ratioFile,"/unix/minos1/rjn/altHornCurr/ratios/nearHornCurrNorm_rat_%d.root",alexRun);

   TFile *fpRatio = TFile::Open(ratioFile);
   if(!fpRatio) {
      std::cerr << "Can not open " << ratioFile << "\n";
      return;
   }

   TH1D *ratioHists[2];
   ratioHists[0]=(TH1D*) fpRatio->Get("ratioNQ");
   ratioHists[1]=(TH1D*) fpRatio->Get("ratioPQ");
   



   Float_t tempArray[2][MAX_T23_INDEX][MAX_T13_INDEX][MAX_DELTA_INDEX];
   for(int histType=0;histType<2;histType++) {
      for(int t23i=0;t23i<MAX_T23_INDEX;t23i++) {
	 for(int t13i=0;t13i<MAX_T13_INDEX;t13i++) {
	    for(int deltai=0;deltai<MAX_DELTA_INDEX;deltai++) {
	       tempArray[histType][t23i][t13i][deltai] = 0;
	    }
	 }
      }
   }



  Double_t t23Array[MAX_T23_INDEX]={0};
  Double_t dmArray[MAX_DMI_INDEX]={0};

  for(int t23i=0;t23i<MAX_T23_INDEX;t23i++) {
    t23Array[t23i]=getT23(t23i);
  }


  for(int dmi=0;dmi<MAX_DMI_INDEX;dmi++) {
    dmArray[dmi]=1e3*getDeltaM2(dmi);
  }

  
  
  TH1::AddDirectory(kFALSE);
  
  Double_t binEdge[]={0,0.5,0.75,1,1.25,1.5,1.75,2,2.25,2.5,2.75,3,3.25,3.5,3.75,4,4.25,4.5,4.75,5,5.25,5.5,5.75,6,6.25,6.5,6.75,7,7.25,7.5,7.75,8,8.25,8.5,8.75,9,9.25,9.5,9.75,10,10.25,10.5,10.75,11,11.25,11.5,11.75,12,12.25,12.5,12.75,13,13.25,13.5,13.75,14,14.25,14.5,14.75,15,15.25,15.5,15.75,16,16.25,16.5,16.75,17,17.25,17.5,17.75,18,18.25,18.5,18.75,19,19.25,19.5,19.75,20,21,22,23,24,25,26,27,28,29,30,32,34,36,38,40,42,44,46,48,50,200};

  char dataPotName[180];
  char mcPotName[180];
  char histName[180];
  char dirName[180];
  char fileName[180];
  char outName[180];


  const char *alexHistNameArray[2]={"RecoEnergy_FD","RecoEnergyPQ_FD"};
  const char *histNameArray[4]={"histEnergyNQ","histEnergyPQ","histEnergyNC","histEnergyNCTrack"};
  const char *predHistNameArray[4]={"histPredNQ","histPredPQ","histPredNC","histPredNCTrack"};
  const char *fileTypeTag[3]={"main","nue","tau"};
  const char *potFileTypeTag[3]={"","Nue","Tau"};
  
 
  const char *runNameArray[11]={"run1","run2","run3","run4","run5","run6","run7","run8","run9","run10","run11"};
  const char *histNameTagArray[11]={"run1","run2","run3","run4","run5","run6","run7","run8","run9","run10","minosplus"};


  sprintf(dataPotName,"pot/%sFDDataPOT.txt",runNameArray[run-1]);
  std::ifstream DataPotFile(dataPotName);
  if(!DataPotFile) {
    std::cerr << "Can not open " << dataPotName << "\n";
    return;
  }
  Double_t dataPOT=0;
  DataPotFile >> dataPOT;
  

  //Next step is to open the Alex FD data files
  TFile *fpData = TFile::Open(inFile,"OLD");      
  if(!fpData) {
    std::cerr << "Can not open " << inFile << "\n";
    //      continue;
    return;
  }
  
  //Read in the  data files
  TH1D *histData[2]={0};
  Double_t numEventsTot[2]={0};
  
  //Loop over the two types of data
  TH1D *hTotalPotData = (TH1D*)fpData->Get("hTotalPot");
  dataPOT=hTotalPotData->Integral();

  for(int histType=0;histType<2;histType++) {
     sprintf(histName,"%s",alexHistNameArray[histType]);
     histData[histType] = (TH1D*) fpData->Get(histName);
     if(!histData[histType]) {
	std::cerr << "Couldn't get " << histName << "\n";
	break;
     }

     //RJN -- Need to think if this is the correct thing to do, or if we should just hcange the data POT to match the Fake Data
     //     histData[histType]->Scale(dataPOT/hTotalPotData->Integral());     
     numEventsTot[histType]=histData[histType]->Integral();
    
  }

  

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
     
    scaleFactor[fileType]=dataPOT/mcPOT[fileType];
    std::cout << "Run " << runNameArray[run-1] << " " << fileTypeTag[fileType] << "\t" << dataPOT << "\t" << mcPOT[fileType] << "\t" << scaleFactor[fileType] << "\n";
  }


  
  for(int histType=0;histType<2;histType++) {	  	
    std::cout << "Integral " << histNameArray[histType] << "\t" << numEventsTot[histType] << "\n";
  }
  

  Double_t minLL=1e9;
  Int_t minDmi=-1,minT23i=-1,minT13i=-1,minDeltai=-1;
  Int_t histType=0,t23i=0,t13i=0,deltai=0,dmi=0;
  Double_t LL=0;
  TFile *fpOut=NULL;
  TTree *llTree=NULL;
  fpOut=TFile::Open(outFile,"RECREATE");
  llTree = new TTree("llTree","llTree");
  llTree->Branch("histType",&histType,"histType/I");
  llTree->Branch("dmi",&dmi,"dmi/I");
  llTree->Branch("t23i",&t23i,"t23i/I");
  llTree->Branch("t13i",&t13i,"t13i/I");
  llTree->Branch("deltai",&deltai,"deltai/I");
  llTree->Branch("LL",&LL,"LL/D");
  

  TH2D *histInverted[2][MAX_T13_INDEX][MAX_DELTA_INDEX]={{{0}}};
  TH2D *histNormal[2][MAX_T13_INDEX][MAX_DELTA_INDEX]={{{0}}};
  
  for(int histType2=0;histType2<2;histType2++) {
    for(int t13i2=0;t13i2<MAX_T13_INDEX;t13i2++) {
      for(int deltai2=0;deltai2<MAX_DELTA_INDEX;deltai2++) {
	sprintf(outName,"histInverted_%s_%d_%d",histNameArray[histType2],t13i2,deltai2);
	histInverted[histType2][t13i2][deltai2]=getNewInvertedHistogram(outName);
	
	sprintf(outName,"histNormal_%s_%d_%d",histNameArray[histType2],t13i2,deltai2);
	histNormal[histType2][t13i2][deltai2]=getNewNormalHistogram(outName);
      }
    }
  }
  
  //Loop over all of the predictions
  for(dmi=0;dmi<MAX_DMI_INDEX;dmi++) {
    std::cerr << "\n" << dmi << ":";
    TFile *fpPreds[3]={0};
    for(int fileType=0;fileType<3;fileType++) {
      sprintf(fileName,"/unix/minos1/rjn/ccPlusNc/farPreds/%s/%s%d.root",runNameArray[run-1],fileTypeTag[fileType],dmi);
      fpPreds[fileType] = TFile::Open(fileName);
    }
    
    for(t23i=0;t23i<MAX_T23_INDEX;t23i++) {  
      std::cerr << "*";
      TDirectory *fpDirs[3];      
      for(int fileType=0;fileType<3;fileType++) {
	if(!fpPreds[fileType]) continue;
	sprintf(dirName,"/dmi%d/t23i%d",dmi,t23i);
	fpPreds[fileType]->cd(dirName);
	fpDirs[fileType]=gDirectory;
      }



      for(t13i=0;t13i<MAX_T13_INDEX;t13i++) {
	for(deltai=0;deltai<MAX_DELTA_INDEX;deltai++) {
	  

	  double LLPQNQ=0;
	  //Loop over the four types of fake data
	  for(int histType=0;histType<2;histType++) {		 
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
		 
	    if(!histData[histType]) {
	      std::cerr << "No data\n";
	      break;
	    }

	    //This is the line that "corrects" the FD predcition by the (ND Fake)/(ND Real) ratio
	    histPred.Multiply(ratioHists[histType]);
	    	    
	    Double_t LL=getLL(histData[histType],&histPred);
	    llTree->Fill();
	    if(histType<2) LLPQNQ+=LL;
	  
	    if(dmArray[dmi]<0) {		    
	      histInverted[histType][t13i][deltai]->Fill(t23Array[t23i],dmArray[dmi],LL );//llArray[histType][exp][dmi][t23i][t13i][deltai]);
	    }
	    else {
	      histNormal[histType][t13i][deltai]->Fill(t23Array[t23i], dmArray[dmi],LL);//llArray[histType][exp][dmi][t23i][t13i][deltai]);
	    }
	  }

	  if(LLPQNQ<minLL) {
	    minLL=LLPQNQ;
	    minDmi=dmi;
	    minT23i=t23i;
	    minT13i=t13i;
	    minDeltai=deltai;
	  }
	}
      }
      
      for(int fileType=0;fileType<3;fileType++) {
	if(!fpPreds[fileType]) continue;
	fpDirs[fileType]->Close();
      }
    }
    for(int fileType=0;fileType<3;fileType++) {
      if(fpPreds[fileType]) fpPreds[fileType]->Close();
    }
  }
  
  int gotData[2]={0};
  for(int histType=0;histType<2;histType++) {
    if(histData[histType]) {
      gotData[histType]=1;
      delete histData[histType];
    }
  }
  
  std::cerr << "\n";
 
  std::cout << "\n\n*******************************************************************\n";
  std::cout << "Results:\n";
  std::cout << "minLL: " << minLL << "\n";
  std::cout << "Delta m^2: " << getDeltaM2(minDmi) << "\n";
  std::cout << "Theta_23: " << getT23(minT23i) << "\n";
  std::cout << "minDmi: " << minDmi << "\n";
  std::cout << "minT13i: " << minT13i << "\n";
  std::cout << "minT23i: " << minT23i << "\n";
  std::cout << "minDeltai: " << minDeltai << "\n";
  std::cout << "*******************************************************************\n";
  llTree->AutoSave();
  fpOut->cd();
  for(int histType2=0;histType2<2;histType2++) {
    for(int t13i2=0;t13i2<MAX_T13_INDEX;t13i2++) {
      for(int deltai2=0;deltai2<MAX_DELTA_INDEX;deltai2++) {
	std::cout << histType2 << "\t" << t13i2 << "\t" << deltai2 << "\t" 
		  <<	histNormal[histType2][t13i2][deltai2]->GetName() << "\n";
	histNormal[histType2][t13i2][deltai2]->Write();
	histInverted[histType2][t13i2][deltai2]->Write();
      }
    }
  }
  fpOut->Close();
  fpData->Close();
 }
