#include <iostream>
#include <fstream>
#include "TFile.h"
#include "TTree.h"
#include "TF1.h"
#include "TH1.h"
#include "TMath.h"
#include "TRandom.h"
#include "src/paramFuncs.h"



void makeNueTree()
{
  Double_t binEdge[]={0,0.5,0.75,1,1.25,1.5,1.75,2,2.25,2.5,2.75,3,3.25,3.5,3.75,4,4.25,4.5,4.75,5,5.25,5.5,5.75,6,6.25,6.5,6.75,7,7.25,7.5,7.75,8,8.25,8.5,8.75,9,9.25,9.5,9.75,10,10.25,10.5,10.75,11,11.25,11.5,11.75,12,12.25,12.5,12.75,13,13.25,13.5,13.75,14,14.25,14.5,14.75,15,15.25,15.5,15.75,16,16.25,16.5,16.75,17,17.25,17.5,17.75,18,18.25,18.5,18.75,19,19.25,19.5,19.75,20,21,22,23,24,25,26,27,28,29,30,32,34,36,38,40,42,44,46,48,50,200};

  TH1::AddDirectory(kFALSE);
  char *potFileTag="run3";
  //  char *predFileTag="run3";
  char *predFileTag="minosPlus";
  
  Double_t potScale=6e20;

  Double_t potMain;
  Double_t potNue;
  Double_t potTau;
  char mainPotFilename[180];
  char nuePotFilename[180];
  char tauPotFilename[180];
  sprintf(mainPotFilename,"pot/%sFDMCPOT.txt",potFileTag);
  sprintf(nuePotFilename,"pot/%sFDNueMCPOT.txt",potFileTag);
  sprintf(tauPotFilename,"pot/%sFDTauMCPOT.txt",potFileTag);

  ifstream MainPOT(mainPotFilename);
  if(!MainPOT) {
    std::cerr << "Can't open " << mainPotFilename << "\n";
    return;
  }
  ifstream NuePOT(nuePotFilename);
  if(!NuePOT) {
    std::cerr << "Can't open " << nuePotFilename << "\n";
    return;
  }
  ifstream TauPOT(tauPotFilename);
  if(!TauPOT) {
    std::cerr << "Can't open " << tauPotFilename << "\n";
    return;
  }
  //Get the POT
  MainPOT >> potMain;
  NuePOT >> potNue;
  TauPOT >> potTau;

  char *histNameArray[4]={"histPredNQ","histPredPQ","histPredNC","histPredNCTrack"};
  char *cchistNameArray[4]={"histCCPredNQ","histCCPredPQ","histCCPredNC","histCCPredNCTrack"};
  
   
  int dmi,t23i,t13i,deltai,histNum;
  double numTot[4],numNue[4],numTau[4];
  double numTot1[4],numNue1[4],numTau1[4];
  double numTot2[4],numNue2[4],numTau2[4];
  double numTot3[4],numNue3[4],numTau3[4];
  TFile *fpOut = new TFile("/unix/minos1/rjn/ccPlusNc/other/nueTauTree.root","RECREATE");
  TTree *nueTauTree = new TTree("nueTauTree","nueTauTree");
  nueTauTree->SetDirectory(fpOut);
  nueTauTree->Branch("dmi",&dmi,"dmi/I");
  nueTauTree->Branch("t23i",&t23i,"t23i/I");
  nueTauTree->Branch("t13i",&t13i,"t13i/I");
  nueTauTree->Branch("deltai",&deltai,"deltai/I");
  //  nueTauTree->Branch("histNum",&histNum,"histNum/I");
  nueTauTree->Branch("numTot",numTot,"numTot[4]/D");
  nueTauTree->Branch("numNue",numNue,"numNue[4]/D");
  nueTauTree->Branch("numTau",numTau,"numTau[4]/D");
  nueTauTree->Branch("numTot1",numTot1,"numTot1[4]/D");
  nueTauTree->Branch("numNue1",numNue1,"numNue1[4]/D");
  nueTauTree->Branch("numTau1",numTau1,"numTau1[4]/D");
  nueTauTree->Branch("numTot2",numTot2,"numTot2[4]/D");
  nueTauTree->Branch("numNue2",numNue2,"numNue2[4]/D");
  nueTauTree->Branch("numTau2",numTau2,"numTau2[4]/D");
  nueTauTree->Branch("numTot3",numTot3,"numTot3[4]/D");
  nueTauTree->Branch("numNue3",numNue3,"numNue3[4]/D");
  nueTauTree->Branch("numTau3",numTau3,"numTau3[4]/D");
  
  for(dmi=0;dmi<MAX_DMI_INDEX;dmi+=1) {
  //  for(dmi=0;dmi<65;dmi++) {
  //    if(dmi==25 || dmi==40) continue;
    //Now open the data and Nue files and get the relevant histograms
    char mainFileName[180];
    char nueFileName[180];
    char tauFileName[180];
    char histName[180];
    sprintf(mainFileName,"farPreds/%s/main%d.root",predFileTag,dmi);
    sprintf(nueFileName,"farPreds/%s/nue%d.root",predFileTag,dmi);
    sprintf(tauFileName,"farPreds/%s/tau%d.root",predFileTag,dmi);
    
    TFile fpMain(mainFileName);
    if(!fpMain.IsOpen()) {
      //      std::cerr < "Couldn't open " << mainFileName << "\n";
      return;
    }
    TFile fpNue(nueFileName);
    if(!fpNue.IsOpen()) {
      //      std::cerr < "Couldn't open " << nueFileName << "\n";
      return;
    }
    TFile fpTau(tauFileName);
    if(!fpTau.IsOpen()) {
      //      std::cerr < "Couldn't open " << tauFileName << "\n";
      return;
    }


    for(t23i=0;t23i<MAX_T23_INDEX;t23i++) {
      std::cerr << "#";
      for(t13i=0;t13i<MAX_T13_INDEX;t13i++) {
	for(deltai=0;deltai<MAX_DELTA_INDEX;deltai++) {	  
	  for(histNum=0;histNum<4;histNum++) {
	    sprintf(histName,"/dmi%d/t23i%d/%s_%d_%d_%d_%d",dmi,t23i,histNameArray[histNum],dmi,t23i,t13i,deltai);
	    TH1D *histMain = (TH1D*) fpMain.Get(histName);
	    if(!histMain) {
	      std::cerr << "Couldn't get " << histName << "\n";
	      return;      
	    }
	    
	    TH1D *histTau = (TH1D*) fpTau.Get(histName);
	    if(!histTau) {
	      std::cerr << "Couldn't get " << histName << "\n";
	      return;      
	    }
	    
	    //    sprintf(histName,"/dmi%d/t23i%d/%s_%d_%d_%d_%d",dmi,t23i,histNameArray[histNum],dmi,t23i,t13i,DELTA_BIN);
	    TH1D *histNue = (TH1D*) fpNue.Get(histName);
	    if(!histNue) {
	      std::cerr << "Couldn't get " << histName << "\n";
	      return;      
	    }
	    
	    sprintf(histName,"/dmi%d/t23i%d/%s_%d_%d_%d_%d",dmi,t23i,cchistNameArray[histNum],dmi,t23i,t13i,deltai);
	    TH1D *histNueCC = (TH1D*) fpNue.Get(histName);
	    if(!histNueCC) {
	      std::cerr << "Couldn't get " << histName << "\n";
	      return;      
	    }


	    
	    sprintf(histName,"/dmi%d/t23i%d/%s_%d_%d_%d_%d",dmi,t23i,cchistNameArray[histNum],dmi,t23i,t13i,deltai);
	    TH1D *histTauCC = (TH1D*) fpTau.Get(histName);
	    if(!histTauCC) {
	      std::cerr << "Couldn't get " << histName << "\n";
	      return;      
	    }
	    

	    histNue->Scale(potScale/potNue);
	    histNueCC->Scale(potScale/potNue);
	    histMain->Scale(potScale/potMain);
	    histTau->Scale(potScale/potTau);
	    histTauCC->Scale(potScale/potTau);
	    histMain->Add(histNue);
	    histMain->Add(histTau);

	    numTot[histNum]=histMain->Integral();
	    numNue[histNum]=histNueCC->Integral();
	    numTau[histNum]=histTauCC->Integral();


	    numTot1[histNum]=histMain->Integral(4,100);
	    numNue1[histNum]=histNueCC->Integral(4,100);
	    numTau1[histNum]=histTauCC->Integral(4,100);

	    numTot2[histNum]=histMain->Integral(8,100);
	    numNue2[histNum]=histNueCC->Integral(8,100);
	    numTau2[histNum]=histTauCC->Integral(8,100);


	    numTot3[histNum]=histMain->Integral(12,100);
	    numNue3[histNum]=histNueCC->Integral(12,100);
	    numTau3[histNum]=histTauCC->Integral(12,100);

	    delete histMain;
	    delete histNueCC;
	    delete histNue;
	    delete histTauCC;
	    delete histTau;
	    
	  }
	  nueTauTree->Fill();
	    
	    
	}
      }
    }
    std::cerr << "\n";
  }
  fpOut->cd();
  nueTauTree->Write();

}
