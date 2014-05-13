#define NuDstLooper_cxx
#include "NuDstLooper.h"
#include "OscCalc.h"
#include "paramFuncs.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TMath.h>
#include <TDirectory.h>
#include <iostream>
#include <fstream>

#define DO_COIL_CURV_TEST 0

Double_t oscillationFormula(Double_t *x, Double_t *par);
Double_t getBinContent(Double_t energy,TH1D *nearRatio, Double_t *binEdges);

void NuDstLooper::MakeHistos(char *fileName,int isData,char *tag)
{
   //   In a ROOT session, you can do:
   //      Root > .L NuDstLooper.C
   //      Root > NuDstLooper t
   //      Root > t.GetEntry(12); // Fill t data members with entry number 12
   //      Root > t.Show();       // Show values of entry 12
   //      Root > t.Show(16);     // Read and show values of entry 16
   //      Root > t.Loop();       // Loop on all entries
   //

   //     This is the loop skeleton where:
   //    jentry is the global entry number in the chain
   //    ientry is the entry number in the current Tree
   //  Note that the argument to GetEntry must be:
   //    jentry for TChain::GetEntry
   //    ientry for TTree::GetEntry and TBranch::GetEntry
   //
   //       To read only selected branches, Insert statements like:
   // METHOD1:
   //    fChain->SetBranchStatus("*",0);  // disable all branches
   //    fChain->SetBranchStatus("branchname",1);  // activate branchname
   // METHOD2: replace line
   //    fChain->GetEntry(jentry);       //read all branches
   //by  b_branchname->GetEntry(ientry); //read only this branch
   if (fChain == 0) return;

   Double_t binEdge[]={0,0.5,0.75,1,1.25,1.5,1.75,2,2.25,2.5,2.75,3,3.25,3.5,3.75,4,4.25,4.5,4.75,5,5.25,5.5,5.75,6,6.25,6.5,6.75,7,7.25,7.5,7.75,8,8.25,8.5,8.75,9,9.25,9.5,9.75,10,10.25,10.5,10.75,11,11.25,11.5,11.75,12,12.25,12.5,12.75,13,13.25,13.5,13.75,14,14.25,14.5,14.75,15,15.25,15.5,15.75,16,16.25,16.5,16.75,17,17.25,17.5,17.75,18,18.25,18.5,18.75,19,19.25,19.5,19.75,20,21,22,23,24,25,26,27,28,29,30,32,34,36,38,40,42,44,46,48,50,200};
   //   for(int i=0;i<101;i++) {
   //     std::cout << i << "\t" << binEdge[i] << "\n";
   //   }
   //   return;

   Long64_t nentries = fChain->GetEntries();



   TFile *fp = new TFile(fileName,"RECREATE");
   char histName[180];
   if(tag)
      sprintf(histName,"histEnergy_%s",tag);
   else
      sprintf(histName,"histEnergy");
   TH1D *histEnergy = new TH1D(histName,"histEnergy",100,binEdge);
   if(tag)
      sprintf(histName,"histEnergyPQ_%s",tag);
   else
      sprintf(histName,"histEnergyPQ");
   TH1D *histEnergyPQ = new TH1D(histName,"histEnergyPQ",100,binEdge);

   if(tag)
      sprintf(histName,"histEnergyNQ_%s",tag);
   else
      sprintf(histName,"histEnergyNQ");
   TH1D *histEnergyNQ = new TH1D(histName,"histEnergyNQ",100,binEdge);

   if(tag)
      sprintf(histName,"histEnergyNC_%s",tag);
   else
      sprintf(histName,"histEnergyNC");
   TH1D *histEnergyNC = new TH1D(histName,"histEnergyNC",100,binEdge);

   if(tag)
      sprintf(histName,"histEnergyNCTrack_%s",tag);
   else
      sprintf(histName,"histEnergyNCTrack");
   TH1D *histEnergyNCTrack = new TH1D(histName,"histEnergyNCTrack",100,binEdge);

   TH1D *histEnergyNoRw = new TH1D("histEnergyNoRw","histEnergyNoRw",100,binEdge);
   TH1D *histEnergyNQNoRw = new TH1D("histEnergyNQNoRw","histEnergyNQNoRw",100,binEdge);
   TH1D *histEnergyPQNoRw = new TH1D("histEnergyPQNoRw","histEnergyPQNoRw",100,binEdge);
   TH1D *histTrueEnergyNumu = new TH1D("histTrueEnergyNumu","histTrueEnergyNumu",100,binEdge);
   TH1D *histTrueEnergyNumubar = new TH1D("histTrueEnergyNumubar","histTrueEnergyNumubar",100,binEdge);
   TH1D *histTrueEnergyNue = new TH1D("histTrueEnergyNue","histTrueEnergyNue",100,binEdge);
   TH1D *histTrueEnergyNuebar = new TH1D("histTrueEnergyNuebar","histTrueEnergyNuebar",100,binEdge);
   


   TH2D *histRecoTrueCC_CC=0;
   TH2D *histRecoTrueCC_NC=0;
   TH2D *histRecoTrueCC_Other=0;
   TH2D *histRecoTrueNC_CC=0;
   TH2D *histRecoTrueNC_NC=0;
   TH2D *histRecoTrueNC_Other=0;
   TH2D *histRecoTrueNCTrack_CC=0;
   TH2D *histRecoTrueNCTrack_NC=0;
   TH2D *histRecoTrueNCTrack_Other=0;
   if(!isData) {
      if(tag) 
	 sprintf(histName,"histRecoTrueCC_CC_%s",tag);
      else
	 sprintf(histName,"histRecoTrueCC_CC");
      histRecoTrueCC_CC = new TH2D(histName,histName,100,binEdge,100,binEdge);

      if(tag) 
	 sprintf(histName,"histRecoTrueCC_NC_%s",tag);
      else
	 sprintf(histName,"histRecoTrueCC_NC");
      histRecoTrueCC_NC = new TH2D(histName,histName,100,binEdge,100,binEdge);

      if(tag) 
	 sprintf(histName,"histRecoTrueCC_Other_%s",tag);
      else
	 sprintf(histName,"histRecoTrueCC_Other");
      histRecoTrueCC_Other = new TH2D(histName,histName,100,binEdge,100,binEdge);

      if(tag) 
	 sprintf(histName,"histRecoTrueNC_CC_%s",tag);
      else
	 sprintf(histName,"histRecoTrueNC_CC");
      histRecoTrueNC_CC = new TH2D(histName,histName,100,binEdge,100,binEdge);

      if(tag) 
	 sprintf(histName,"histRecoTrueNC_NC_%s",tag);
      else
	 sprintf(histName,"histRecoTrueNC_NC");
      histRecoTrueNC_NC = new TH2D(histName,histName,100,binEdge,100,binEdge);

      if(tag) 
	 sprintf(histName,"histRecoTrueNC_Other_%s",tag);
      else
	 sprintf(histName,"histRecoTrueNC_Other");
      histRecoTrueNC_Other = new TH2D(histName,histName,100,binEdge,100,binEdge);

      if(tag) 
	 sprintf(histName,"histRecoTrueNCTrack_CC_%s",tag);
      else
	 sprintf(histName,"histRecoTrueNCTrack_CC");
      histRecoTrueNCTrack_CC = new TH2D(histName,histName,100,binEdge,100,binEdge);

      if(tag) 
	 sprintf(histName,"histRecoTrueNCTrack_NC_%s",tag);
      else
	 sprintf(histName,"histRecoTrueNCTrack_NC");
      histRecoTrueNCTrack_NC = new TH2D(histName,histName,100,binEdge,100,binEdge);

      if(tag) 
	 sprintf(histName,"histRecoTrueNCTrack_Other_%s",tag);
      else
	 sprintf(histName,"histRecoTrueNCTrack_Other");
      histRecoTrueNCTrack_Other = new TH2D(histName,histName,100,binEdge,100,binEdge);

   }
   

  
   // TTree *selectedTree = (TTree*) new TTree("selectedTree","selectedTree");
   // selectedTree->Branch("run",&run,"run/I");
   // selectedTree->Branch("subRun",&subRun,"subRun/I");
   // selectedTree->Branch("snarl",&snarl,"snarl/I");
   // selectedTree->Branch("timeSec",&timeSec,"timeSec/I");
   // selectedTree->Branch("trkEn",&trkEn,"trkEn/F");
   // selectedTree->Branch("trkEnRange",&trkEnRange,"trkEnRange/F");
   // selectedTree->Branch("trkEnCurv",&trkEnCurv,"trkEnCurv/F");
   // selectedTree->Branch("shwEn",&shwEn,"shwEn/F");
   // selectedTree->Branch("shwEnLinCCCor",&shwEnLinCCCor,"shwEnLinCCCor/F");
   // selectedTree->Branch("shwEnkNN",&shwEnkNN,"shwEnkNN/F");
   // selectedTree->Branch("xEvtVtx",&xEvtVtx,"xEvtVtx/F");
   // selectedTree->Branch("yEvtVtx",&yEvtVtx,"yEvtVtx/F");
   // selectedTree->Branch("zEvtVtx",&zEvtVtx,"zEvtVtx/F");
   

   char eventList[180];
   if(tag) {
      sprintf(eventList,"eventList_%s.txt",tag);
   }
   else {
      sprintf(eventList,"eventList.txt");
   }
   //   std::ofstream EventList(eventList);


   int numStars=100;
   int starEvery=nentries/numStars;
   if(starEvery==0) starEvery++;
   Long64_t nbytes = 0, nb = 0;
   int countCutDQ=0;
   int countCutGoodBeam=0;
   int countCutCoilIsOk=0;
   int countCutLI=0;
   int countCutHorn=0;
   int countCutFidVol=0;
   int countCutRoID=0;
   int countCutTrackRec=0;
   int countCutNTrk=0;
   int countCutQP=0;
   int countPQ=0;
   int countCutTrkFitPass=0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      if(jentry%starEvery==0) std::cerr << "*";
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;


      //Moved the cut code to seperate thing
      Bool_t goodNCCandidate=false;
      int cutId=getCutId(isData,&goodNCCandidate);

      if(qp==0 && hornIsReverse) charge=1;      
      if(qp<0) charge=-1;
      if(qp>0) charge=1;

      if(cutId==0 || goodNCCandidate) {
	if(inu==-14) histTrueEnergyNumubar->Fill(energyMC,rw);
	if(inu==-12) histTrueEnergyNuebar->Fill(energyMC,rw);
	if(inu==14) histTrueEnergyNumu->Fill(energyMC,rw);
	if(inu==12) histTrueEnergyNue->Fill(energyMC,rw);

      }

      //RJN over ride coil hole cut and set to curvature
      if(DO_COIL_CURV_TEST && cutId==CUT_ID_COIL_HOLE) {
	cutId=0;
      }
      
      if(cutId==0) {
	 //Then it is a CC candidate event
	if(DO_COIL_CURV_TEST) setCCTrackEnergy();
	 if(charge==-1) countPQ++;
	 histEnergy->Fill(trkEn+shwEn,rw);
	 histEnergyNoRw->Fill(trkEn+shwEn);
	 if(charge==1) {
	    histEnergyPQ->Fill(trkEn+shwEn,rw);
	    histEnergyPQNoRw->Fill(trkEn+shwEn);
	 }
	 else {
	    histEnergyNQ->Fill(trkEn+shwEn,rw);
	    histEnergyNQNoRw->Fill(trkEn+shwEn);
	 }
	 if(!isData) {
	    if(iaction==0) {
	       histRecoTrueCC_NC->Fill(trkEn+shwEn,neuEnMC,rw);
	    }
	    else if(iaction==1 && TMath::Abs(inu)==14) {
	       histRecoTrueCC_CC->Fill(trkEn+shwEn,neuEnMC,rw);
	    }
	    else {
	       histRecoTrueCC_Other->Fill(trkEn+shwEn,neuEnMC,rw);
	    }	  
	 }
	 //	selectedTree->Fill();
	 //	EventList << run << "\t" << subRun << "\t" << snarl << "\n";
      }
      else {
	 if(goodNCCandidate) {
	    //Then it is an NC candidate event
	    Double_t ncEnergy=shwEnLinCCCor;
	    if(ntrk>0) {
	       ncEnergy+=trkEn;
	       histEnergyNCTrack->Fill(ncEnergy,rw); //At some point need to understand the shower energy scale	  
	       if(!isData) {
		  if(iaction==0) {
		     histRecoTrueNCTrack_NC->Fill(ncEnergy,neuEnMC,rw);
		  }
		  else if(iaction==1 && TMath::Abs(inu)==14) {
		     histRecoTrueNCTrack_CC->Fill(ncEnergy,neuEnMC,rw);
		  }
		  else {
		     histRecoTrueNCTrack_Other->Fill(ncEnergy,neuEnMC,rw);
		  }	  
	       }	    
	    }
	    else {
	       histEnergyNC->Fill(ncEnergy,rw);
	       if(!isData) {
		  if(iaction==0) {
		     histRecoTrueNC_NC->Fill(ncEnergy,neuEnMC,rw);
		  }
		  else if(iaction==1 && TMath::Abs(inu)==14) {
		     histRecoTrueNC_CC->Fill(ncEnergy,neuEnMC,rw);
		  }
		  else {
		     histRecoTrueNC_Other->Fill(ncEnergy,neuEnMC,rw);
		  }	  
	       }	    
	    }

	 }

	 if(cutId&0x1) 
	    countCutDQ++;
	 if(cutId&0x2)
	    countCutGoodBeam++;
	 if(cutId&0x4) 
	    countCutCoilIsOk++;
	 if(cutId&0x8)
	    countCutLI++;
	 if(cutId&0x10)
	    countCutHorn++;
	 if(cutId&0x20)
	    countCutFidVol++;
	 if(cutId&0x40)
	    countCutRoID++;
	 if(cutId&0x80)
	    countCutTrackRec++;
	 if(cutId&0x100)
	    countCutNTrk++;
	 if(cutId&0x200)
	    countCutQP++;
	 if(cutId&0x400)
	    countCutTrkFitPass++;
      }
   }
   std::cerr << "\n";
   std::cerr << "countPQ " << countPQ << "\n";
   std::cout << "histEnergy " << histEnergy->GetEntries() << "\t" << histEnergy->GetMean()  << "\t" << histEnergy->GetRMS() << "\n"; 
   std::cout << "histEnergyNC " << histEnergyNC->GetEntries() << "\t" << histEnergyNC->GetMean()  << "\t" << histEnergyNC->GetRMS() << "\n"; 
   std::cout << "histEnergyNCTrack " << histEnergyNCTrack->GetEntries() << "\t" << histEnergyNCTrack->GetMean()  << "\t" << histEnergyNCTrack->GetRMS() << "\n"; 

   std::cout << "countCutDQ \t" << countCutDQ << "\n";
   std::cout << "countCutGoodBeam \t" << countCutGoodBeam << "\n";
   std::cout << "countCutCoilIsOk \t" << countCutCoilIsOk << "\n";
   std::cout << "countCutLI \t" << countCutLI << "\n";
   std::cout << "countCutHorn \t" << countCutHorn << "\n";
   std::cout << "countCutFidVol \t" << countCutFidVol << "\n";
   std::cout << "countCutRoID \t" << countCutRoID << "\n";
   std::cout << "countCutTrackRec \t" << countCutTrackRec << "\n";
   std::cout << "countCutNTrk \t" << countCutNTrk << "\n";
   std::cout << "countCutQP \t" << countCutQP << "\n";
   std::cout << "countCutTrkFitPass \t" << countCutTrkFitPass << "\n";
   //   selectedTree->AutoSave();
   fp->Write();
}




void NuDstLooper::MakePredicitions(char *fileName, TH1D *ndRatioNQ, TH1D  *ndRatioPQ, TH1D *ndRatioNC, TH1D *ndRatioNCTrack, int startDmiIndex, int endDmiIndex, char *tag, TH1D *histRwNumu, TH1D *histRwNumubar, TH1D *histRwNue, TH1D *histRwNuebar)
{
   int isData=0;
   if (fChain == 0) return;

   Double_t oscPar[9]={0};
   oscPar[OscPar::kL]=735; // km
   oscPar[OscPar::kTh23]=0.705; //From PDG, extracted from sin^2(theta_23)=0.42, will loop over this
   oscPar[OscPar::kTh12]=0.586; /// From PDG, extracted from sin^2(theta_12) = 0.306
   oscPar[OscPar::kTh13]=0.159; // From PDG, extracted from sin^2(theta_13) = 0.0251
   oscPar[OscPar::kDeltaM23]=2.35e-3; // in eV^2 will loop over
   oscPar[OscPar::kDeltaM12]=7.58e-5; // in eV^2
   oscPar[OscPar::kDelta]=0; //Fix at zero for now
   oscPar[OscPar::kDensity]=2.65; //In some units
   oscPar[OscPar::kNuAntiNu]=1; // 1 for neutrinos, -1 for antineutrinos


   Double_t binEdge[]={0,0.5,0.75,1,1.25,1.5,1.75,2,2.25,2.5,2.75,3,3.25,3.5,3.75,4,4.25,4.5,4.75,5,5.25,5.5,5.75,6,6.25,6.5,6.75,7,7.25,7.5,7.75,8,8.25,8.5,8.75,9,9.25,9.5,9.75,10,10.25,10.5,10.75,11,11.25,11.5,11.75,12,12.25,12.5,12.75,13,13.25,13.5,13.75,14,14.25,14.5,14.75,15,15.25,15.5,15.75,16,16.25,16.5,16.75,17,17.25,17.5,17.75,18,18.25,18.5,18.75,19,19.25,19.5,19.75,20,21,22,23,24,25,26,27,28,29,30,32,34,36,38,40,42,44,46,48,50,200};
   //   for(int i=0;i<101;i++) {
   //     std::cout << i << "\t" << binEdge[i] << "\n";
   //   }
   //   return;

   Long64_t nentries = fChain->GetEntries();
 
   TFile *fp = new TFile(fileName,"RECREATE");
   char histName[180];
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
   

   Double_t energy,fnWeight;
   Int_t cutId;
   Bool_t goodNCCandidate=0;
   TTree *passTree = new TTree("passTree","Only passing events");
   passTree->Branch("iaction",&iaction,"iaction/I");
   passTree->Branch("ntrk",&ntrk,"ntrk/I");
   passTree->Branch("inu",&inu,"inu/I");
   passTree->Branch("inunoosc",&inunoosc,"inunoosc/I");
   passTree->Branch("energy",&energy,"energy/D");
   passTree->Branch("fnWeight",&fnWeight,"fnWeight/D");
   passTree->Branch("cutId",&cutId,"cutId/I");
   passTree->Branch("goodNCCandidate",&goodNCCandidate,"goodNCCandidate/O");
   passTree->Branch("charge",&charge,"charge/I");
   passTree->Branch("rw",&rw,"rw/F");
   passTree->Branch("energyMC",&energyMC,"energyMC/F");
   

   int numStars=100;
   int starEvery=nentries/numStars;
   if(starEvery==0) starEvery++;
   Long64_t nbytes = 0, nb = 0;
   int countCutDQ=0;
   int countCutGoodBeam=0;
   int countCutCoilIsOk=0;
   int countCutLI=0;
   int countCutHorn=0;
   int countCutFidVol=0;
   int countCutRoID=0;
   int countCutTrackRec=0;
   int countCutNTrk=0;
   int countCutQP=0;
   int countCutTrkFitPass=0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      if(jentry%starEvery==0) std::cerr << "*";
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      // if (Cut(ientry) < 0) continue;
     
      cutId=getCutId(isData,&goodNCCandidate);

      if(cutId==0 || goodNCCandidate) {

	double newRw=1;
	if(histRwNuebar) {
	   if(inunoosc==14) newRw=getBinContent(energyMC,histRwNumu,binEdge);
	   if(inunoosc==-14) newRw=getBinContent(energyMC,histRwNumubar,binEdge);
	   if(inunoosc==12) newRw=getBinContent(energyMC,histRwNue,binEdge);
	   if(inunoosc==-12) newRw=getBinContent(energyMC,histRwNuebar,binEdge);
	}
   	rw*=newRw;
	energy=trkEn+shwEn;
	fnWeight=1;
	 //First up fill the no osc histograms
	 if(cutId==0 && charge==1) {
	    fnWeight=getBinContent(energy,ndRatioPQ,binEdge);
	    if(inu==inunoosc)
	       histNoOscPQ->Fill(energy,rw*fnWeight);
	 }
	 else if(cutId==0){
	    fnWeight=getBinContent(energy,ndRatioNQ,binEdge);
	    if(inu==inunoosc)
	       histNoOscNQ->Fill(energy,rw*fnWeight);
	 }
	 else if(goodNCCandidate) {
	    energy=shwEnLinCCCor;
	    if(ntrk>0) {
	       energy+=trkEn;
	       fnWeight=getBinContent(energy,ndRatioNCTrack,binEdge);
	       if(inu==inunoosc)
		  histNoOscNCTrack->Fill(energy,rw*fnWeight);
	    }
	    else {
	       fnWeight=getBinContent(energy,ndRatioNC,binEdge);
	       if(inu==inunoosc)
		  histNoOscNC->Fill(energy,rw*fnWeight);
	    }	    
	 }
	 passTree->Fill();      
	
      }	    	    	 
      else {
	 if(cutId&0x1) 
	    countCutDQ++;
	 if(cutId&0x2)
	    countCutGoodBeam++;
	 if(cutId&0x4) 
	    countCutCoilIsOk++;
	 if(cutId&0x8)
	    countCutLI++;
	 if(cutId&0x10)
	    countCutHorn++;
	 if(cutId&0x20)
	    countCutFidVol++;
	 if(cutId&0x40)
	    countCutRoID++;
	 if(cutId&0x80)
	    countCutTrackRec++;
	 if(cutId&0x100)
	    countCutNTrk++;
	 if(cutId&0x200)
	    countCutQP++;
	 if(cutId&0x400)
	    countCutTrkFitPass++;
      }
   }
   std::cerr << "\n";
   std::cout << "histNoOscNQ " << histNoOscNQ->GetEntries() << "\t" << histNoOscNQ->GetMean()  << "\t" << histNoOscNQ->GetRMS() << "\n"; 


   std::cout << "countCutDQ \t" << countCutDQ << "\n";
   std::cout << "countCutGoodBeam \t" << countCutGoodBeam << "\n";
   std::cout << "countCutCoilIsOk \t" << countCutCoilIsOk << "\n";
   std::cout << "countCutLI \t" << countCutLI << "\n";
   std::cout << "countCutHorn \t" << countCutHorn << "\n";
   std::cout << "countCutFidVol \t" << countCutFidVol << "\n";
   std::cout << "countCutRoID \t" << countCutRoID << "\n";
   std::cout << "countCutTrackRec \t" << countCutTrackRec << "\n";
   std::cout << "countCutNTrk \t" << countCutNTrk << "\n";
   std::cout << "countCutQP \t" << countCutQP << "\n";
   std::cout << "countCutTrkFitPass \t" << countCutTrkFitPass << "\n";

   histNoOscNQ->Write();
   histNoOscPQ->Write();
   histNoOscNC->Write();
   histNoOscNCTrack->Write();


   Double_t deltaCPArray[MAX_DELTA_INDEX];
   Double_t t13Array[MAX_T13_INDEX];
   Double_t dm2Array[MAX_DMI_INDEX];
   Double_t t23Array[MAX_T23_INDEX];
   
   for(int dmi=0;dmi<MAX_DMI_INDEX;dmi++) {
      Double_t dm2=getDeltaM2(dmi);
      dm2Array[dmi]=dm2;
   }
   
   for(int t23i=0;t23i<MAX_T23_INDEX;t23i++) {
      Double_t t23=getT23(t23i);
      t23Array[t23i]=t23;
   }

   for(int t13i=0;t13i<MAX_T13_INDEX;t13i++) {
      Double_t t13=getT13(t13i);
	    t13Array[t13i]=t13;
   }

   for(int deltai=0;deltai<MAX_DELTA_INDEX;deltai++) {
      Double_t delta=getDeltaCP(deltai);   
      deltaCPArray[deltai]=delta;
   }
   

   Int_t passEntries= passTree->GetEntries();
   std::cout << "Events in passTree " << passEntries << "\n";

   
   //   for(int dmi=0;dmi<MAX_DMI_INDEX;dmi++) { 
   //      for(int t23i=0;t23i<MAX_T23_INDEX;t23i++) {

   char dirName[180];

   //   for(int dmi=0;dmi<MAX_DMI_INDEX;dmi++) { 
   for(int dmi=startDmiIndex;dmi<=endDmiIndex;dmi++) {
      std::cerr << dmi << ":";
      sprintf(dirName,"dmi%d",dmi);
      fp->mkdir(dirName);
      fp->cd(dirName);
      for(int t23i=0;t23i<MAX_T23_INDEX;t23i++) {
      //      for(int t23i=0;t23i<1;t23i++) {
      std::cerr << "#";	       
	sprintf(dirName,"t23i%d",t23i);
	gDirectory->mkdir(dirName);
	gDirectory->cd(dirName);
	 for(int t13i=0;t13i<MAX_T13_INDEX;t13i++) {	    
	    for(int deltai=0;deltai<MAX_DELTA_INDEX;deltai++) {  
	       oscPar[OscPar::kTh23]=t23Array[t23i];
	       oscPar[OscPar::kDeltaM23]=dm2Array[dmi];
	       oscPar[OscPar::kTh13]=t13Array[t13i];
	       oscPar[OscPar::kDelta]=deltaCPArray[deltai];
	       sprintf(histName,"histPredNQ_%d_%d_%d_%d",dmi,t23i,t13i,deltai);
	       TH1D histPredNQ(histName,histName,100,binEdge);
	       sprintf(histName,"histPredPQ_%d_%d_%d_%d",dmi,t23i,t13i,deltai);
	       TH1D histPredPQ(histName,histName,100,binEdge);
	       sprintf(histName,"histPredNC_%d_%d_%d_%d",dmi,t23i,t13i,deltai);
	       TH1D histPredNC(histName,histName,100,binEdge);
	       sprintf(histName,"histPredNCTrack_%d_%d_%d_%d",dmi,t23i,t13i,deltai);
	       TH1D histPredNCTrack(histName,histName,100,binEdge);
	       sprintf(histName,"histCCPredNQ_%d_%d_%d_%d",dmi,t23i,t13i,deltai);
	       TH1D histCCPredNQ(histName,histName,100,binEdge);
	       sprintf(histName,"histCCPredPQ_%d_%d_%d_%d",dmi,t23i,t13i,deltai);
	       TH1D histCCPredPQ(histName,histName,100,binEdge);
	       sprintf(histName,"histCCPredNC_%d_%d_%d_%d",dmi,t23i,t13i,deltai);
	       TH1D histCCPredNC(histName,histName,100,binEdge);
	       sprintf(histName,"histCCPredNCTrack_%d_%d_%d_%d",dmi,t23i,t13i,deltai);
	       TH1D histCCPredNCTrack(histName,histName,100,binEdge);
 	       for(int passEntry=0;passEntry<passEntries;passEntry++) {
		 passTree->GetEntry(passEntry);		  
		 double oscWeight=getOscWeight(oscPar);
		 //We will weight all events by oscWeight		  
 		  if(cutId==0 && charge==1) {
 		     histPredPQ.Fill(energy,rw*oscWeight*fnWeight);
		     if(iaction==1 && TMath::Abs(inu)!=14) histCCPredPQ.Fill(energy,rw*oscWeight*fnWeight);
 		  }
 		  else if(cutId==0 && charge==-1) {
		     histPredNQ.Fill(energy,rw*oscWeight*fnWeight);
		     if(iaction==1 && TMath::Abs(inu)!=14) histCCPredNQ.Fill(energy,rw*oscWeight*fnWeight);
 		  }
		  else if(goodNCCandidate && ntrk>0) {
		     histPredNCTrack.Fill(energy,rw*oscWeight*fnWeight);
		     if(iaction==1 && TMath::Abs(inu)!=14) histCCPredNCTrack.Fill(energy,rw*oscWeight*fnWeight);
		  }
		  else if(goodNCCandidate) {
		     histPredNC.Fill(energy,rw*oscWeight*fnWeight);
		     if(iaction==1 && TMath::Abs(inu)!=14) histCCPredNC.Fill(energy,rw*oscWeight*fnWeight);		     
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

// 	       histPredNQ.Delete();
// 	       histPredPQ.Delete();
// 	       histPredNC.Delete();
// 	       histPredNCTrack.Delete();
// 	       histCCPredNQ.Delete();
// 	       histCCPredPQ.Delete();
// 	       histCCPredNC.Delete();
// 	       histCCPredNCTrack.Delete();

	    }
	 }
	 gDirectory->Close();
      }
      gDirectory->Close();
   }
   std::cerr << "\n";




// 	 for(int dmi=0;dmi<MAX_DMI_INDEX;dmi++) {
// 	    for(int t23i=0;t23i<MAX_T23_INDEX;t23i++) {
// 	       for(int t13i=0;t13i<MAX_T13_INDEX;t13i++) {
// 		  for(int deltai=0;deltai<MAX_T23_INDEX;deltai++) {
// 	       }
// 	    }
// 	 }





//   fp->Write();
}


void NuDstLooper::MakePassTree(char *fileName, TH1D *ndRatioNQ, TH1D  *ndRatioPQ, TH1D *ndRatioNC, TH1D *ndRatioNCTrack, char *tag, TH1D *histRwNumu, TH1D *histRwNumubar, TH1D *histRwNue, TH1D *histRwNuebar)
{
   if (fChain == 0) return;


   int isData=0;

   //The bin edges.
   Double_t binEdge[]={0,0.5,0.75,1,1.25,1.5,1.75,2,2.25,2.5,2.75,3,3.25,3.5,3.75,4,4.25,4.5,4.75,5,5.25,5.5,5.75,6,6.25,6.5,6.75,7,7.25,7.5,7.75,8,8.25,8.5,8.75,9,9.25,9.5,9.75,10,10.25,10.5,10.75,11,11.25,11.5,11.75,12,12.25,12.5,12.75,13,13.25,13.5,13.75,14,14.25,14.5,14.75,15,15.25,15.5,15.75,16,16.25,16.5,16.75,17,17.25,17.5,17.75,18,18.25,18.5,18.75,19,19.25,19.5,19.75,20,21,22,23,24,25,26,27,28,29,30,32,34,36,38,40,42,44,46,48,50,200};

   Long64_t nentries = fChain->GetEntries();
 
   //No this is the passTree file name
   TFile *fp = new TFile(fileName,"RECREATE");
   char histName[180];
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
   

   Double_t energy,fnWeight;
   Int_t cutId;
   Bool_t goodNCCandidate=0;
   TTree *passTree = new TTree("passTree","Only passing events");
   passTree->Branch("iaction",&iaction,"iaction/I");
   passTree->Branch("ntrk",&ntrk,"ntrk/I");
   passTree->Branch("inu",&inu,"inu/I");
   passTree->Branch("inunoosc",&inunoosc,"inunoosc/I");
   passTree->Branch("energy",&energy,"energy/D");
   passTree->Branch("fnWeight",&fnWeight,"fnWeight/D");
   passTree->Branch("cutId",&cutId,"cutId/I");
   passTree->Branch("goodNCCandidate",&goodNCCandidate,"goodNCCandidate/O");
   passTree->Branch("charge",&charge,"charge/I");
   passTree->Branch("rw",&rw,"rw/F");
   passTree->Branch("energyMC",&energyMC,"energyMC/F");
   

   int numStars=100;
   int starEvery=nentries/numStars;
   if(starEvery==0) starEvery++;
   Long64_t nbytes = 0, nb = 0;
   int countCutDQ=0;
   int countCutGoodBeam=0;
   int countCutCoilIsOk=0;
   int countCutLI=0;
   int countCutHorn=0;
   int countCutFidVol=0;
   int countCutRoID=0;
   int countCutTrackRec=0;
   int countCutNTrk=0;
   int countCutQP=0;
   int countCutTrkFitPass=0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      if(jentry%starEvery==0) std::cerr << "*";
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      // if (Cut(ientry) < 0) continue;
     
      cutId=getCutId(isData,&goodNCCandidate);

      if(cutId==0 || goodNCCandidate) {

	double newRw=1;
	if(histRwNuebar) {
	   if(inunoosc==14) newRw=getBinContent(energyMC,histRwNumu,binEdge);
	   if(inunoosc==-14) newRw=getBinContent(energyMC,histRwNumubar,binEdge);
	   if(inunoosc==12) newRw=getBinContent(energyMC,histRwNue,binEdge);
	   if(inunoosc==-12) newRw=getBinContent(energyMC,histRwNuebar,binEdge);
	}
   	rw*=newRw;
	energy=trkEn+shwEn;
	fnWeight=1;
	 //First up fill the no osc histograms
	 if(cutId==0 && charge==1) {
	    fnWeight=getBinContent(energy,ndRatioPQ,binEdge);
	    if(inu==inunoosc)
	       histNoOscPQ->Fill(energy,rw*fnWeight);
	 }
	 else if(cutId==0){
	    fnWeight=getBinContent(energy,ndRatioNQ,binEdge);
	    if(inu==inunoosc)
	       histNoOscNQ->Fill(energy,rw*fnWeight);
	 }
	 else if(goodNCCandidate) {
	    energy=shwEnLinCCCor;
	    if(ntrk>0) {
	       energy+=trkEn;
	       fnWeight=getBinContent(energy,ndRatioNCTrack,binEdge);
	       if(inu==inunoosc)
		  histNoOscNCTrack->Fill(energy,rw*fnWeight);
	    }
	    else {
	       fnWeight=getBinContent(energy,ndRatioNC,binEdge);
	       if(inu==inunoosc)
		  histNoOscNC->Fill(energy,rw*fnWeight);
	    }	    
	 }
	 passTree->Fill();      
	
      }	    	    	 
      else {
	 if(cutId&0x1) 
	    countCutDQ++;
	 if(cutId&0x2)
	    countCutGoodBeam++;
	 if(cutId&0x4) 
	    countCutCoilIsOk++;
	 if(cutId&0x8)
	    countCutLI++;
	 if(cutId&0x10)
	    countCutHorn++;
	 if(cutId&0x20)
	    countCutFidVol++;
	 if(cutId&0x40)
	    countCutRoID++;
	 if(cutId&0x80)
	    countCutTrackRec++;
	 if(cutId&0x100)
	    countCutNTrk++;
	 if(cutId&0x200)
	    countCutQP++;
	 if(cutId&0x400)
	    countCutTrkFitPass++;
      }
   }
   std::cerr << "\n";
   std::cout << "histNoOscNQ " << histNoOscNQ->GetEntries() << "\t" << histNoOscNQ->GetMean()  << "\t" << histNoOscNQ->GetRMS() << "\n"; 

   std::cout << "countCutDQ \t" << countCutDQ << "\n";
   std::cout << "countCutGoodBeam \t" << countCutGoodBeam << "\n";
   std::cout << "countCutCoilIsOk \t" << countCutCoilIsOk << "\n";
   std::cout << "countCutLI \t" << countCutLI << "\n";
   std::cout << "countCutHorn \t" << countCutHorn << "\n";
   std::cout << "countCutFidVol \t" << countCutFidVol << "\n";
   std::cout << "countCutRoID \t" << countCutRoID << "\n";
   std::cout << "countCutTrackRec \t" << countCutTrackRec << "\n";
   std::cout << "countCutNTrk \t" << countCutNTrk << "\n";
   std::cout << "countCutQP \t" << countCutQP << "\n";
   std::cout << "countCutTrkFitPass \t" << countCutTrkFitPass << "\n";

   histNoOscNQ->Write();
   histNoOscPQ->Write();
   histNoOscNC->Write();
   histNoOscNCTrack->Write();
   passTree->AutoSave();
   fp->Close();
}


void  NuDstLooper::MakePredicitonsFromPassTree(char *passTreeFileName, char *fileName, int startDmiIndex, int endDmiIndex) {

  Double_t oscPar[9]={0};
  oscPar[OscPar::kL]=735; // km
  oscPar[OscPar::kTh23]=0.705; //From PDG, extracted from sin^2(theta_23)=0.42, will loop over this
  oscPar[OscPar::kTh12]=0.586; /// From PDG, extracted from sin^2(theta_12) = 0.306
  oscPar[OscPar::kTh13]=0.159; // From PDG, extracted from sin^2(theta_13) = 0.0251
  oscPar[OscPar::kDeltaM23]=2.35e-3; // in eV^2 will loop over
  oscPar[OscPar::kDeltaM12]=7.58e-5; // in eV^2
  oscPar[OscPar::kDelta]=0; //Fix at zero for now
  oscPar[OscPar::kDensity]=2.65; //In some units
  oscPar[OscPar::kNuAntiNu]=1; // 1 for neutrinos, -1 for antineutrinos

  char histName[180];


   //The bin edges.
   Double_t binEdge[]={0,0.5,0.75,1,1.25,1.5,1.75,2,2.25,2.5,2.75,3,3.25,3.5,3.75,4,4.25,4.5,4.75,5,5.25,5.5,5.75,6,6.25,6.5,6.75,7,7.25,7.5,7.75,8,8.25,8.5,8.75,9,9.25,9.5,9.75,10,10.25,10.5,10.75,11,11.25,11.5,11.75,12,12.25,12.5,12.75,13,13.25,13.5,13.75,14,14.25,14.5,14.75,15,15.25,15.5,15.75,16,16.25,16.5,16.75,17,17.25,17.5,17.75,18,18.25,18.5,18.75,19,19.25,19.5,19.75,20,21,22,23,24,25,26,27,28,29,30,32,34,36,38,40,42,44,46,48,50,200};


  TFile *fpPass = TFile::Open(passTreeFileName);
  Double_t energy,fnWeight;
  Int_t cutId;
  Bool_t goodNCCandidate=0;
  TTree *passTree = (TTree*) fpPass->Get("passTree");
  passTree->SetBranchAddress("iaction",&iaction);
  passTree->SetBranchAddress("ntrk",&ntrk);
  passTree->SetBranchAddress("inu",&inu);
  passTree->SetBranchAddress("inunoosc",&inunoosc);
  passTree->SetBranchAddress("energy",&energy);
  passTree->SetBranchAddress("fnWeight",&fnWeight);
  passTree->SetBranchAddress("cutId",&cutId);
  passTree->SetBranchAddress("goodNCCandidate",&goodNCCandidate);
  passTree->SetBranchAddress("charge",&charge);
  passTree->SetBranchAddress("rw",&rw);
  passTree->SetBranchAddress("energyMC",&energyMC);


  TFile *fp = new TFile(fileName,"RECREATE");
  
  Double_t deltaCPArray[MAX_DELTA_INDEX];
  Double_t t13Array[MAX_T13_INDEX];
  Double_t dm2Array[MAX_DMI_INDEX];
  Double_t t23Array[MAX_T23_INDEX];
  
   for(int dmi=0;dmi<MAX_DMI_INDEX;dmi++) {
      Double_t dm2=getDeltaM2(dmi);
      dm2Array[dmi]=dm2;
   }
   
   for(int t23i=0;t23i<MAX_T23_INDEX;t23i++) {
      Double_t t23=getT23(t23i);
      t23Array[t23i]=t23;
   }

   for(int t13i=0;t13i<MAX_T13_INDEX;t13i++) {
      Double_t t13=getT13(t13i);
	    t13Array[t13i]=t13;
   }

   for(int deltai=0;deltai<MAX_DELTA_INDEX;deltai++) {
      Double_t delta=getDeltaCP(deltai);   
      deltaCPArray[deltai]=delta;
   }
   
   Int_t passEntries= passTree->GetEntries();
   std::cout << "Events in passTree " << passEntries << "\n";
   fp->cd();
   
   //   for(int dmi=0;dmi<MAX_DMI_INDEX;dmi++) { 
   //      for(int t23i=0;t23i<MAX_T23_INDEX;t23i++) {

   char dirName[180];

   //   for(int dmi=0;dmi<MAX_DMI_INDEX;dmi++) { 
   for(int dmi=startDmiIndex;dmi<=endDmiIndex;dmi++) {
      std::cerr << dmi << ":";
      sprintf(dirName,"dmi%d",dmi);
      fp->mkdir(dirName);
      fp->cd(dirName);
      for(int t23i=0;t23i<MAX_T23_INDEX;t23i++) {
      //      for(int t23i=0;t23i<1;t23i++) {
      std::cerr << "#";	       
	sprintf(dirName,"t23i%d",t23i);
	gDirectory->mkdir(dirName);
	gDirectory->cd(dirName);
	 for(int t13i=0;t13i<MAX_T13_INDEX;t13i++) {	    
	    for(int deltai=0;deltai<MAX_DELTA_INDEX;deltai++) {  
	       oscPar[OscPar::kTh23]=t23Array[t23i];
	       oscPar[OscPar::kDeltaM23]=dm2Array[dmi];
	       oscPar[OscPar::kTh13]=t13Array[t13i];
	       oscPar[OscPar::kDelta]=deltaCPArray[deltai];
	       sprintf(histName,"histPredNQ_%d_%d_%d_%d",dmi,t23i,t13i,deltai);
	       TH1D histPredNQ(histName,histName,100,binEdge);
	       sprintf(histName,"histPredPQ_%d_%d_%d_%d",dmi,t23i,t13i,deltai);
	       TH1D histPredPQ(histName,histName,100,binEdge);
	       sprintf(histName,"histPredNC_%d_%d_%d_%d",dmi,t23i,t13i,deltai);
	       TH1D histPredNC(histName,histName,100,binEdge);
	       sprintf(histName,"histPredNCTrack_%d_%d_%d_%d",dmi,t23i,t13i,deltai);
	       TH1D histPredNCTrack(histName,histName,100,binEdge);
	       sprintf(histName,"histCCPredNQ_%d_%d_%d_%d",dmi,t23i,t13i,deltai);
	       TH1D histCCPredNQ(histName,histName,100,binEdge);
	       sprintf(histName,"histCCPredPQ_%d_%d_%d_%d",dmi,t23i,t13i,deltai);
	       TH1D histCCPredPQ(histName,histName,100,binEdge);
	       sprintf(histName,"histCCPredNC_%d_%d_%d_%d",dmi,t23i,t13i,deltai);
	       TH1D histCCPredNC(histName,histName,100,binEdge);
	       sprintf(histName,"histCCPredNCTrack_%d_%d_%d_%d",dmi,t23i,t13i,deltai);
	       TH1D histCCPredNCTrack(histName,histName,100,binEdge);
 	       for(int passEntry=0;passEntry<passEntries;passEntry++) {
		 passTree->GetEntry(passEntry);		  
		 double oscWeight=getOscWeight(oscPar);
		 //We will weight all events by oscWeight		  
 		  if(cutId==0 && charge==1) {
 		     histPredPQ.Fill(energy,rw*oscWeight*fnWeight);
		     if(iaction==1 && TMath::Abs(inu)!=14) histCCPredPQ.Fill(energy,rw*oscWeight*fnWeight);
 		  }
 		  else if(cutId==0 && charge==-1) {
		     histPredNQ.Fill(energy,rw*oscWeight*fnWeight);
		     if(iaction==1 && TMath::Abs(inu)!=14) histCCPredNQ.Fill(energy,rw*oscWeight*fnWeight);
 		  }
		  else if(goodNCCandidate && ntrk>0) {
		     histPredNCTrack.Fill(energy,rw*oscWeight*fnWeight);
		     if(iaction==1 && TMath::Abs(inu)!=14) histCCPredNCTrack.Fill(energy,rw*oscWeight*fnWeight);
		  }
		  else if(goodNCCandidate) {
		     histPredNC.Fill(energy,rw*oscWeight*fnWeight);
		     if(iaction==1 && TMath::Abs(inu)!=14) histCCPredNC.Fill(energy,rw*oscWeight*fnWeight);		     
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

// 	       histPredNQ.Delete();
// 	       histPredPQ.Delete();
// 	       histPredNC.Delete();
// 	       histPredNCTrack.Delete();
// 	       histCCPredNQ.Delete();
// 	       histCCPredPQ.Delete();
// 	       histCCPredNC.Delete();
// 	       histCCPredNCTrack.Delete();

	    }
	 }
	 gDirectory->Close();
      }
      gDirectory->Close();
   }
   std::cerr << "\n";




// 	 for(int dmi=0;dmi<MAX_DMI_INDEX;dmi++) {
// 	    for(int t23i=0;t23i<MAX_T23_INDEX;t23i++) {
// 	       for(int t13i=0;t13i<MAX_T13_INDEX;t13i++) {
// 		  for(int deltai=0;deltai<MAX_T23_INDEX;deltai++) {
// 	       }
// 	    }
// 	 }





//   fp->Write();
}


void NuDstLooper::MakeTrackTree(char *fileName,int isData)
{


   Long64_t nentries = fChain->GetEntries();



   TFile *fp = new TFile(fileName,"RECREATE");

   Int_t cutId;
   TTree *trackTree = (TTree*) new TTree("trackTree","trackTree");
   trackTree->Branch("trkEn",&trkEn,"trkEn/F");
   trackTree->Branch("trkEnRange",&trkEnRange,"trkEnRange/F");
   trackTree->Branch("trkEnCurv",&trkEnCurv,"trkEnCurv/F");
   trackTree->Branch("shwEn",&shwEn,"shwEn/F");
   trackTree->Branch("shwEnLinCCCor",&shwEnLinCCCor,"shwEnLinCCCor/F");
   trackTree->Branch("shwEnkNN",&shwEnkNN,"shwEnkNN/F");
   trackTree->Branch("xEvtVtx",&xEvtVtx,"xEvtVtx/F");
   trackTree->Branch("yEvtVtx",&yEvtVtx,"yEvtVtx/F");
   trackTree->Branch("zEvtVtx",&zEvtVtx,"zEvtVtx/F");
   trackTree->Branch("xTrkEnd",&xTrkEnd,"xTrkEnd/F");
   trackTree->Branch("yTrkEnd",&yTrkEnd,"yTrkEnd/F");
   trackTree->Branch("zTrkEnd",&zTrkEnd,"zTrkEnd/F");
   trackTree->Branch("rw",&rw,"rw/F");
   trackTree->Branch("cutId",&cutId,"cutId/I");
   

   int numStars=100;
   int starEvery=nentries/numStars;
   if(starEvery==0) starEvery++;
   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      if(jentry%starEvery==0) std::cerr << "*";
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;

      //Moved the cut code to seperate thing
      Bool_t goodNCCandidate=false;
      cutId=getCutId(isData,&goodNCCandidate);

      if(qp==0 && hornIsReverse) charge=1;      
      if(qp<0) charge=-1;
      if(qp>0) charge=1;


      if(cutId==0 || cutId==CUT_ID_COIL_HOLE || cutId==CUT_ID_TRK_FIT_PASS || cutId==(CUT_ID_TRK_FIT_PASS+CUT_ID_COIL_HOLE)) {
	 //Then it is a CC candidate event
	 trackTree->Fill();
      }
      
   }
   trackTree->AutoSave();
   fp->Close();
}



Double_t NuDstLooper::getOscWeight(Double_t *par)
{
   static OscCalc fOscCalc;
   if(inunoosc>0) par[OscPar::kNuAntiNu]=1;
   if(inunoosc<0) par[OscPar::kNuAntiNu]=-1;
   fOscCalc.SetOscParam(par);
   return fOscCalc.Oscillate(inu,inunoosc,energyMC);
}

Int_t NuDstLooper::getCutId(Int_t isData, Bool_t *goodNCCandidate)
{
   Int_t cutId=0;
   if(!(isGoodDataQuality || !cutOnDataQuality)) {
      cutId+=CUT_ID_DATA_QUALITY;
   }
   if(isData) {
    
      if(!goodBeam ) {
	cutId+=CUT_ID_BEAM;
      }
      if(!coilIsOk ) {
	 cutId+=CUT_ID_COIL;
      }
      if(!(!isLI && litime==-1)) {
	 cutId+=CUT_ID_LI;
      }
    
      if(TMath::Abs(hornCur)<=155 || hornCur==-999999) {
	 cutId+=CUT_ID_HORN;
      }
   }
   if(!isInFidVolCC) {
      cutId+=CUT_ID_FID_VOL;
   }
  
   const double phFrac = evtphsigcor/TMath::Max(snarlPulseHeight, 1e-10);
   if(!(detector == 0x01 || (detector==0x02 && (nevt < 2 || (nevt == 2 && phFrac > 0.75))))) {
      cutId+=CUT_ID_PH_FRAC;
   }
  
   *goodNCCandidate=0;
   if(!cutId) *goodNCCandidate=1;

   //Below here we are dealing solely with track related quantities
   const double eps = 1./160.;
   // Cut on CC/NC PID
   //   Bool_t goodPID=(roID > 0.25+eps) || (jmID > 0.5+eps);
   Bool_t goodPID=(roID > 0.3+eps);
  

   if(!goodPID) {
     cutId+=CUT_ID_PID;
      //	continue;
   }

   //sigqp == 1e-4 is an error code
   if(!(sigqp > 0.00011 || sigqp < 0.000099)) {
      cutId+=CUT_ID_SIGQP;
   }
  
  
  
   if(ntrk<1) {
     cutId+=CUT_ID_NTRK;
      //	continue;
   }
   Int_t goodTrack=0;  
   if(trkfitpass==1) goodTrack=1;
   else cutId+=CUT_ID_TRK_FIT_PASS;
  
  
   //These are the new track end cuts in the ND
   if(detector==1) {
     if(xTrkEnd<=0.0 || rTrkEnd<=0.6) {
       goodTrack=0;
       cutId+=CUT_ID_COIL_HOLE;
     }
     if(containmentFlag==2) {
       goodTrack=0;   ///New containment cut in ND
       cutId+=CUT_ID_ND_CONTAINMENT;
     }
   }
  
  
   if(!goodTrack) {
      if(ntrk>0) *goodNCCandidate=0;
   }
  
  
   if(detector!=1 && dirCosNu<=0.6) {
      cutId+=CUT_ID_DIR_COS;//continue;
   }
  

   return cutId;


}

void NuDstLooper::setCCTrackEnergy() {
  if(detector==1) {
    if(xTrkEnd<=0. || rTrkEnd<=0.6) {
      trkEn=trkEnCurv;
    }    
  }
}

Double_t oscillationFormula(Double_t *x, Double_t *par)
{
   Double_t E=x[0];
   Double_t L=735;
   Double_t dm2=par[0];
   Double_t sin2=par[1];
   //  par[2]=1;
   if(E>0)
      return (1.-sin2*TMath::Power(TMath::Sin(1.27*dm2*L/E),2));
   return 0;
}

Double_t getBinContent(Double_t energy,TH1D *nearRatio, Double_t *binEdges)
{
   int nbins=nearRatio->GetNbinsX();
   for(int i=0;i<nbins;i++) {
      if(energy>binEdges[i] && energy<binEdges[i+1]) {
	 //yay      
	 return nearRatio->GetBinContent(i+1);
      }
   }
   return 1;
}
