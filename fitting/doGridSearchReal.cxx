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


Double_t getLL(TH1D *histData, TH1D *histPred) ;
void doGridSearchReal(int run);
Long64_t getTempIndex(Int_t dmi, Int_t t23i, Int_t t13i, Int_t deltai) ;

int main(int argc, char **argv) 
{

  if(argc<2) {
    std::cerr << "Usage\n\t" << argv[0] << " <run> \n";
    return -1;
  }
  int run=atoi(argv[1]);
   

  doGridSearchReal(run);
   
}



void doGridSearchReal(int run)
{
  
  Float_t tempArray[4][MAX_T23_INDEX][MAX_T13_INDEX][MAX_DELTA_INDEX];
  for(int histType=0;histType<4;histType++) {
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


  //Next step is to open the real data files
  sprintf(fileName,"farFiles/%s_fd_data.root",runNameArray[run-1]);
  TFile *fpData = TFile::Open(fileName,"OLD");      
  if(!fpData) {
    std::cerr << "Can not open " << fileName << "\n";
    //      continue;
    return;
  }
  
  //Read in the  data files
  TH1D *histData[4]={0};
  Double_t numEventsTot[4]={0};
  
  //Loop over the four types of data
  for(int histType=0;histType<4;histType++) {	  	
    sprintf(histName,"%s_%s_fd_data",histNameArray[histType],histNameTagArray[run-1]);
    histData[histType] = (TH1D*) fpData->Get(histName);
    if(!histData[histType]) {
	std::cerr << "Couldn't get " << histName << "\n";
	break;
    }
    numEventsTot[histType]=histData[histType]->Integral();
    
  }
  
  for(int histType=0;histType<4;histType++) {	  	
    std::cout << "Integral " << histNameArray[histType] << "\t" << numEventsTot[histType] << "\n";
  }
  

  Double_t minLL=1e9;
  Int_t minDmi,minT23i,minT13i,minDeltai;
  Int_t histType=0,t23i=0,t13i=0,deltai=0,dmi=0;
  Double_t LL=0;
  TFile *fpOut=NULL;
  TTree *llTree=NULL;
  sprintf(outName,"realSurfaces/%s/realSurface.root",runNameArray[run-1]);
  fpOut=TFile::Open(outName,"RECREATE");
  llTree = new TTree("llTree","llTree");
  llTree->Branch("histType",&histType,"histType/I");
  llTree->Branch("dmi",&dmi,"dmi/I");
  llTree->Branch("t23i",&t23i,"t23i/I");
  llTree->Branch("t13i",&t13i,"t13i/I");
  llTree->Branch("deltai",&deltai,"deltai/I");
  llTree->Branch("LL",&LL,"LL/D");
  

  TH2D *histInverted[4][MAX_T13_INDEX][MAX_DELTA_INDEX]={{{0}}};
  TH2D *histNormal[4][MAX_T13_INDEX][MAX_DELTA_INDEX]={{{0}}};
  
  for(int histType2=0;histType2<4;histType2++) {
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
	  
	  //Loop over the four types of fake data
	  for(int histType=0;histType<4;histType++) {		 
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
	    
	    Double_t LL=getLL(histData[histType],&histPred);
	    if(LL<minLL) {
	      minLL=LL;
	      minDmi=dmi;
	      minT23i=t23i;
	      minT13i=t13i;
	      minDeltai=deltai;
	    }
	    llTree->Fill();	  
	  
	    if(dmArray[dmi]<0) {		    
	      histInverted[histType][t13i][deltai]->Fill(t23Array[t23i],dmArray[dmi],LL );//llArray[histType][exp][dmi][t23i][t13i][deltai]);
	    }
	    else {
	      histNormal[histType][t13i][deltai]->Fill(t23Array[t23i], dmArray[dmi],LL);//llArray[histType][exp][dmi][t23i][t13i][deltai]);
	    }
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
  
  int gotData[4]={0};
  for(int histType=0;histType<4;histType++) {
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
  std::cout << "*******************************************************************\n";
  llTree->AutoSave();
  fpOut->cd();
  for(int histType2=0;histType2<4;histType2++) {
    for(int t13i2=0;t13i2<MAX_T13_INDEX;t13i2++) {
      for(int deltai2=0;deltai2<MAX_DELTA_INDEX;deltai2++) {
	histNormal[histType2][t13i][deltai]->Write();
	histInverted[histType2][t13i][deltai]->Write();
      }
    }
  }
  fpOut->Close();
  fpData->Close();
  
}


Double_t getLL(TH1D *histData, TH1D *histPred) 
{
  Double_t value=0;
  if(histData->GetNbinsX()!=histPred->GetNbinsX()) {
    std::cerr << "histos not same size\n";
    return 0;
  }
  for(int bin=START_BIN;bin<=histData->GetNbinsX();bin++) {
    Double_t vi=histPred->GetBinContent(bin);
    Double_t ni=histData->GetBinContent(bin);    
    //    std::cout << ni << "\t" << vi << "\n";
    if(vi>0) {
      if(ni>0)
	value+=(vi-ni)+ni*TMath::Log(ni/vi);        
      else
	value+=vi;
    }
  }
  return 2*value;
}

Long64_t getTempIndex(Int_t dmi, Int_t t23i, Int_t t13i, Int_t deltai) {
   Long64_t value= deltai+
      (MAX_DELTA_INDEX)*t13i+
      (MAX_DELTA_INDEX*MAX_T13_INDEX)*t23i+
      (MAX_DELTA_INDEX*MAX_T13_INDEX*MAX_T23_INDEX)*dmi;   
   return value;
}
