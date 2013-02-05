#include <iostream>
#include <fstream>
#include "TFile.h"
#include "TF1.h"
#include "TH1.h"
#include "TH2.h"
#include "TMath.h"
#include "TCanvas.h"
#include "TDirectory.h"
#include "TString.h"
#include "TKey.h"
#include "TROOT.h"
#include "gridSearch.h"
#include "src/paramFuncs.h"

#define NUM_EXPS 1000

Double_t getLL(TH1D *histData, TH1D *histPred) ;
void doGridSearchFake(int run, int fakeDmBin, int fakeT23bin, int fakeT13Bin, int fakeDeltaBin,int thisExp, int potScale);
Long64_t getTempIndex(Int_t dmi, Int_t t23i, Int_t t13i, Int_t deltai) ;

int main(int argc, char **argv) 
{

  if(argc<6) {
    std::cerr << "Usage\n\t" << argv[0] << " <run> <dm bin> <t23 bin> <t13 bin> <delta bin> <exp no>\n";
    return -1;
  }
  int run=atoi(argv[1]);
  int dmBin=atoi(argv[2]);
  int t23Bin=atoi(argv[3]);
  int t13Bin=atoi(argv[4]);
  int deltaBin=atoi(argv[5]); 
  int expNo=atoi(argv[6]);   
  int potScale=1;
  if(argc>7) {
     potScale=atoi(argv[7]);
  }
   
  doGridSearchFake(run,dmBin,t23Bin,t13Bin,deltaBin,expNo,potScale);
   
}



void doGridSearchFake(int run, int fakeDmBin, int fakeT23bin, int fakeT13Bin, int fakeDeltaBin, int thisExp, int potScale)
{
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
  //  Int_t doRun[10]={1,0,0,0,0,0,0,0,0,0};

  


  sprintf(dataPotName,"pot/run%dFDDataPOT.txt",run);
  std::ifstream DataPotFile(dataPotName);
  if(!DataPotFile) {
    std::cerr << "Can not open " << dataPotName << "\n";
    return;
  }
  Double_t dataPOT=0;
  DataPotFile >> dataPOT;
  
  if(potScale==1) {
    sprintf(fileName,"fakeSurfaces/run%d/fakeSurface_run%d_exp%d_of_%d_%d_%d_%d_%d.root",run,run,thisExp,NUM_EXPS,fakeDmBin,fakeT23bin,fakeT13Bin,fakeDeltaBin);
  }
  else {
    sprintf(fileName,"fakeSurfaces/run%d/fakeSurface_run%d_scale%d_exp%d_of_%d_%d_%d_%d_%d.root",run,run,potScale,thisExp,NUM_EXPS,fakeDmBin,fakeT23bin,fakeT13Bin,fakeDeltaBin);
  }
  TFile *fpSurface = new TFile(fileName,"RECREATE");
  if(!fpSurface) {
    std::cerr << "Can not open " << fileName << "\n";
    return;
  }
  

  Double_t mcPOT[3]; //main, nue and tau
  Double_t scaleFactor[3]; //main, nue and tau
  
  //Loop over main, nue , tau
  for(int fileType=0;fileType<3;fileType++) { 

    sprintf(mcPotName,"pot/run%dFD%sMCPOT.txt",run,potFileTypeTag[fileType]);
    std::ifstream McPotFile(mcPotName);
    if(!McPotFile) {
      std::cerr << "Can not open " << mcPotName << "\n";
      continue;
    }
    McPotFile >> mcPOT[fileType];     
     
    scaleFactor[fileType]=potScale*dataPOT/mcPOT[fileType];
    std::cout << "Run " << run << " " << fileTypeTag[fileType] << "\t" << dataPOT << "\t" << mcPOT[fileType] << "\t" << scaleFactor[fileType] << "\n";
  }


  //Next step is to open the fake data files  
  if(potScale>1) 
     sprintf(fileName,"fakeData/run%d_scale%d_fake_%d_%d_%d_%d.root",run,potScale,fakeDmBin,fakeT23bin,fakeT13Bin,fakeDeltaBin);
  else 
     sprintf(fileName,"fakeData/run%d_fake_%d_%d_%d_%d.root",run,fakeDmBin,fakeT23bin,fakeT13Bin,fakeDeltaBin);
  TFile *fpFakeData = TFile::Open(fileName,"OLD");      
  if(!fpFakeData) {
    std::cerr << "Can not open " << fileName << "\n";
    //      continue;
    return;
  }
  
  //Read in all the fake data files
  TH1D *histData[4]={0};
  Double_t numEventsTot[4]={0};
  
  //Loop over the four types of fake data
  for(int histType=0;histType<4;histType++) {	  	
    sprintf(histName,"%s_%d",histNameArray[histType],thisExp);
    histData[histType] = (TH1D*) fpFakeData->Get(histName);
    if(!histData[histType]) {
      std::cerr << "Couldn't get " << histName << "\n";
      break;
    }
    numEventsTot[histType]=histData[histType]->Integral();
  }

  for(int histType=0;histType<4;histType++) {	  	
    std::cout << "Integral " << histNameArray[histType] << "\t" << numEventsTot[histType] << "\n";
  }

  //Need to reorder this so that we don't have to keep all the predictions in memory
  //  TH2D *histSurface[4][1000][MAX_T13_INDEX][MAX_DELTA_INDEX]={{{{0}}}};
  //  Float_t llArray[4][NUM_EXPS][MAX_DMI_INDEX][MAX_T23_INDEX][MAX_T13_INDEX][MAX_DELTA_INDEX]={{{{{{0}}}}}};
  
  Float_t *tempArray[4];
  for(int i=0;i<4;i++) {
    tempArray[i] = new Float_t[MAX_DMI_INDEX*MAX_T23_INDEX*MAX_T13_INDEX*MAX_DELTA_INDEX];  
  }



  //Loop over all of the predictions
  for(int dmi=0;dmi<MAX_DMI_INDEX;dmi++) {
  //  for(int dmi=60;dmi<MAX_DMI_INDEX;dmi++) {
    //  for(int dmi=0;dmi<2;dmi++) {
    std::cerr << "\n" << dmi << ":";
    TFile *fpPreds[3]={0};
    for(int fileType=0;fileType<3;fileType++) {
      sprintf(fileName,"/unix/minos1/rjn/ccPlusNc/farPreds/run%d/%s%d.root",run,fileTypeTag[fileType],dmi);
      fpPreds[fileType] = TFile::Open(fileName);
    }

    for(int t23i=0;t23i<MAX_T23_INDEX;t23i++) {
      std::cerr << "*";
      TDirectory *fpDirs[3];      
      for(int fileType=0;fileType<3;fileType++) {
	if(!fpPreds[fileType]) continue;
	sprintf(dirName,"/dmi%d/t23i%d",dmi,t23i);
	fpPreds[fileType]->cd(dirName);
	fpDirs[fileType]=gDirectory;
      }



      for(int t13i=0;t13i<MAX_T13_INDEX;t13i++) {
	for(int deltai=0;deltai<MAX_DELTA_INDEX;deltai++) {

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
	    //     if(histType==3 && t13i==fakeT13Bin && deltai==fakeDeltaBin && t23i==fakeT23bin) {
	    // 		 std::cout << histType << "\t" <<exp << "\t" << LL
	    // 			   << "\t" << histData[histType][exp]->Integral()
	    // 			   << "\t"<< histPred.Integral() << "\n";
	    // 	      }


	      tempArray[histType][getTempIndex(dmi,t23i,t13i,deltai)]+=LL;

	  }
	}
      }
      
	
      for(int fileType=0;fileType<3;fileType++) {
	if(!fpPreds[fileType]) continue;
	fpDirs[fileType]->Close();
      }

    }
    for(int fileType=0;fileType<3;fileType++) {
      delete fpPreds[fileType];
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



  
  
  for(int histType=0;histType<4;histType++) {
    if(!histData[histType]) break;
    fpSurface->cd();
    
    sprintf(outName,"histBestInverted_%s_%d",histNameArray[histType],thisExp);
    TH2D histBestInverted(outName,outName,MAX_T23_INDEX,MIN_T23-0.5*T23_STEP_SIZE,MIN_T23+(MAX_T23_INDEX-0.5)*T23_STEP_SIZE,MAX_DMI_INDEX/2,1e3*(MIN_NEG_DM2-0.5*DM2_STEP_SIZE),1e3*(MIN_NEG_DM2+(MAX_DMI_INDEX/2)*DM2_STEP_SIZE));
    sprintf(outName,"histBestNormal_%s_%d",histNameArray[histType],thisExp);
    TH2D histBestNormal(outName,outName,MAX_T23_INDEX,MIN_T23-0.5*T23_STEP_SIZE,MIN_T23+(MAX_T23_INDEX-0.5)*T23_STEP_SIZE,MAX_DMI_INDEX/2,1e3*(MIN_POS_DM2-0.5*DM2_STEP_SIZE),1e3*(MIN_POS_DM2+(MAX_DMI_INDEX/2)*DM2_STEP_SIZE));
	
      Float_t bestLL[MAX_DMI_INDEX][MAX_T23_INDEX]={{0}}; //Generic large number

      for(int dmi=0;dmi<MAX_DMI_INDEX;dmi++) {
	for(int t23i=0;t23i<MAX_T23_INDEX;t23i++) {
	  bestLL[dmi][t23i]=-1;
	}
      }
	

      for(int t13i=0;t13i<MAX_T13_INDEX;t13i++) {
	for(int deltai=0;deltai<MAX_DELTA_INDEX;deltai++) {
	  sprintf(outName,"histInverted_%s_%d_%d_%d",histNameArray[histType],thisExp,t13i,deltai);
	  TH2D histInverted(outName,outName,MAX_T23_INDEX,MIN_T23-0.5*T23_STEP_SIZE,MIN_T23+(MAX_T23_INDEX-0.5)*T23_STEP_SIZE,
			    MAX_DMI_INDEX/2,1e3*(MIN_NEG_DM2-0.5*DM2_STEP_SIZE),1e3*(MIN_NEG_DM2+(MAX_DMI_INDEX/2)*DM2_STEP_SIZE));
	  sprintf(outName,"histNormal_%s_%d_%d_%d",histNameArray[histType],thisExp,t13i,deltai);
	  TH2D histNormal(outName,outName,MAX_T23_INDEX,MIN_T23-0.5*T23_STEP_SIZE,MIN_T23+(MAX_T23_INDEX-0.5)*T23_STEP_SIZE,
			  MAX_DMI_INDEX/2,1e3*(MIN_POS_DM2-0.5*DM2_STEP_SIZE),1e3*(MIN_POS_DM2+(MAX_DMI_INDEX/2)*DM2_STEP_SIZE));

	      
	  for(int dmi=0;dmi<MAX_DMI_INDEX;dmi++) {
	    for(int t23i=0;t23i<MAX_T23_INDEX;t23i++) {
	      Double_t LL=tempArray[histType][getTempIndex(dmi,t23i,t13i,deltai)];
	      if(LL<bestLL[dmi][t23i] || bestLL[dmi][t23i]<0) bestLL[dmi][t23i]=LL;

	      if(dmArray[dmi]<0) {

		histInverted.Fill(t23Array[t23i],dmArray[dmi],LL );//llArray[histType][exp][dmi][t23i][t13i][deltai]);
	      }
	      else {
		histNormal.Fill(t23Array[t23i], dmArray[dmi],LL);//llArray[histType][exp][dmi][t23i][t13i][deltai]);
	      }
	    }
	  }
	  histInverted.Write();
	  histNormal.Write();

	}
      }
	
      for(int dmi=0;dmi<MAX_DMI_INDEX;dmi++) {
	for(int t23i=0;t23i<MAX_T23_INDEX;t23i++) {
	  Double_t LL=bestLL[dmi][t23i];	      
	  if(dmArray[dmi]<0) {		 
	    histBestInverted.Fill(t23Array[t23i],dmArray[dmi],LL );//llArray[histType][exp][dmi][t23i][t13i][deltai]);
	  }
	  else {
	    histBestNormal.Fill(t23Array[t23i], dmArray[dmi],LL);//llArray[histType][exp][dmi][t23i][t13i][deltai]);
	  }
	}
      }
	
      histBestNormal.Write();
      histBestInverted.Write();
  }


fpSurface->Close();   
std::cerr << "End of loop\n";
  
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
