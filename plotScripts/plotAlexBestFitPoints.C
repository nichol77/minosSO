#include "plotScripts/plotUtils.h"
#include "src/paramFuncs.h"


Double_t getDm2MuMu(Double_t dm232, Double_t dm221, Double_t theta12, Double_t theta13, Double_t theta23,Double_t deltaCP) {
   Double_t sin12= TMath::Sin(theta12);
   Double_t sin13= TMath::Sin(theta13);
   Double_t tan23= TMath::Tan(theta23);
   Double_t sin212=TMath::Sin(2*theta12);


   return dm232 + (dm221*sin12*sin12) + (dm221*TMath::Cos(deltaCP)*sin13*tan23*sin212);

}


void plotAlexBestFitPoints() {

   TFile *fpDefault= TFile::Open("fakeSurfaces/fakeSurface_run11_scale1000_fake_28_39_0_0.root");
   TH2D *histDefaultNormal = (TH2D*) fpDefault->Get("histNormal_histEnergyNQ_0_0");
   histDefaultNormal->Scale(1./1000);
   TH2D *histDefaultAndy = convertToSin2Theta23Andy(histDefaultNormal,"histDefaultAndy",0);
   TH2D *contDefaultAndy = getContours(histDefaultAndy,2);
   TH2D *contDefault = getContours(histDefaultNormal,2);

   turnOnStatsBoxes();
   char fileName[180];

   Double_t dmVals[1000];
   Double_t thetaVals[1000];
   Int_t numVals=0;


   TH1D *histDm = new TH1D("histDm","histDm",100,2,3);
   TH1D *histDmMuMu = new TH1D("histDmMuMu","histDmMuMu",100,2,3);
   TH1D *histTheta = new TH1D("histTheta","histTheta",100,0.3,0.7);
   TH2D *histNormal = getNewNormalHistogram("histNormal");//,"histNormal");

   for(int run=0;run<1000;run++) {
      if(run%10==0) std::cerr << "*";
      sprintf(fileName,"fakeSurfaces/altHornCurr/fakeSurface_%d.root",run);
      TFile *fpSurface = TFile::Open(fileName);
      if(!fpSurface) continue;

      TH2D *histNQ = (TH2D*) fpSurface->Get("histNormal_histEnergyNQ_0_0");
      TH2D *histPQ = (TH2D*) fpSurface->Get("histNormal_histEnergyPQ_0_0");
      histNQ->Add(histPQ);
      
      Double_t minX=0;
      Double_t minY=0;
      getMinPoint(histNQ,minX,minY);
      Double_t minSinSq=TMath::Power(TMath::Sin(minX),2);
      histDm->Fill(minY);
      histTheta->Fill(minSinSq);
      fpSurface->Close();
      dmVals[numVals]=minY;
      thetaVals[numVals]=minSinSq;
      numVals++;
      histNormal->Fill(minX,minY);

      histDmMuMu->Fill(1e3*getDm2MuMu(minY*1e-3,7.58e-5,0.586,0.1454,minX,0));
     
   }
   std::cerr << "\n";

   TCanvas *can = new TCanvas("can","can",800,800);
   can->Divide(1,2);
   can->cd(1);
   histDm->SetXTitle("#Deltam^{2}_{32} (10^{-3} eV^{2})");
   histDm->Draw();
   histDmMuMu->SetLineColor(kRed+2);
   histDmMuMu->Draw("sames");
   gPad->Update();
   gPad->Modified();
   moveStatsBoxes();
   can->cd(2);
   histTheta->SetXTitle("sin^{2}(#theta_{23})");
   histTheta->Draw();

   TCanvas *can2 = new TCanvas("canAndy","canAndy");
   can2->SetRightMargin(0.15);
   TGraph *gr = new TGraph(numVals,thetaVals,dmVals);
   gr->SetMarkerStyle(29);
   gr->SetMarkerColor(kRed+2);
   //   gr->Draw("ap");
   TH2D *histNormalAndy = convertToSin2Theta23Andy(histNormal,"histNormalAndy",0);
   histNormalAndy->SetStats(kFALSE);
   histNormalAndy->SetYTitle("#Deltam^{2}_{32} (eV^{2})");
   histNormalAndy->SetXTitle("sin^{2}(#theta_{23})");
   histNormalAndy->Draw("COLZ");
   contDefaultAndy->Draw("CONT3 same");


   TCanvas *can2 = new TCanvas("can3","can3");
   can2->SetRightMargin(0.15);
   TGraph *gr = new TGraph(numVals,thetaVals,dmVals);
   gr->SetMarkerStyle(29);
   gr->SetMarkerColor(kRed+2);
   //   gr->Draw("ap");
   histNormal->SetStats(kFALSE);
   histNormal->SetYTitle("#Deltam^{2}_{32} (10^{-3} eV^{2})");
   histNormal->SetXTitle("#theta_{23}");
   histNormal->Draw("COLZ");
   contDefault->Draw("CONT3 same");
   
		    


//    oscPar[OscPar::kTh23]=0.705; //From PDG, extracted from sin^2(theta_23)=0.42, will loop over this
//    oscPar[OscPar::kTh12]=0.586; /// From PDG, extracted from sin^2(theta_12) = 0.306
//    oscPar[OscPar::kTh13]=0.159; // From PDG, extracted from sin^2(theta_13) = 0.0251
//    oscPar[OscPar::kDeltaM23]=2.35e-3; // in eV^2 will loop over
//    oscPar[OscPar::kDeltaM12]=7.58e-5; // in eV^2
//    oscPar[OscPar::kDelta]=0; //Fix at zero for now
//    oscPar[OscPar::kDensity]=2.65; //In some units
//    oscPar[OscPar::kNuAntiNu]=1; // 1 for neutrinos, -1 for antineutrinos


}



