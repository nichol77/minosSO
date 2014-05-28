#include "so2014.h"




void plotFDData() {
  plotFDData(0,0);


}

void plotFDData(int histType, int plotJoe) {
  TFile *fp = TFile::Open("minosplus_fd_mc.root");
  TFile *fpPred = TFile::Open("minosplus_fd_pred.root");
  TFile *fpPredBest = TFile::Open("minosplus_fd_pred_28_39_0_0.root");
  //TFile *fpPredBest = TFile::Open("minosplus_fd_pred_79_69_0_0.root");
  TFile *fpPredJoe;
  if(histType==0) fpPredJoe= TFile::Open("minosplus_bestfit_spectra_NQ.root");
  if(histType==1) fpPredJoe= TFile::Open("minosplus_bestfit_spectra_PQ.root");

  TH1D *histEnergyPredJoe = (TH1D*) fpPredJoe->Get("bestfit_minosplus_beam");
  TFile *fpData = TFile::Open("minosplus_fd_data.root");
  TH1D *histEnergy;
  TH1D *histEnergyNoRw;
  TH1D *histEnergyPred;
  TH1D *histEnergyPredBest;
  TH1D *histEnergyData;
  if(histType==0) {

    histEnergy = (TH1D*)fp->Get("histEnergyNQ_minosplus_fd_mc");
    histEnergyNoRw = (TH1D*)fp->Get("histEnergyNQNoRw");    
    histEnergyPred = (TH1D*)fpPred->Get("histNoOscNQ_runxi_pred_main");    
    histEnergyPredBest = (TH1D*)fpPredBest->Get("histPredNQ_run11_pred_28_39_0_0");    
    histEnergyData = (TH1D*)fpData->Get("histEnergyNQ_minosplus_fd_data");

  }
  else if(histType==1) {

    histEnergy = (TH1D*)fp->Get("histEnergyPQ_minosplus_fd_mc");
    histEnergyNoRw = (TH1D*)fp->Get("histEnergyPQNoRw");    
    histEnergyPred = (TH1D*)fpPred->Get("histNoOscPQ_runxi_pred_main");    
    histEnergyPredBest = (TH1D*)fpPredBest->Get("histPredPQ_run11_pred_28_39_0_0");    
    histEnergyData = (TH1D*)fpData->Get("histEnergyPQ_minosplus_fd_data");

  }
  else if(histType==2) {

    histEnergy = (TH1D*)fp->Get("histEnergyNC_minosplus_fd_mc");
    histEnergyNoRw = (TH1D*)fp->Get("histEnergyNCNoRw");    
    histEnergyPred = (TH1D*)fpPred->Get("histNoOscNC_runxi_pred_main");    
    histEnergyPredBest = (TH1D*)fpPredBest->Get("histPredNC_run11_pred_28_39_0_0");    
    histEnergyData = (TH1D*)fpData->Get("histEnergyNC_minosplus_fd_data");

  }
  else if(histType==3) {

    histEnergy = (TH1D*)fp->Get("histEnergyPQ_minosplus_fd_mc");
    histEnergyNoRw = (TH1D*)fp->Get("histEnergyPQNoRw");    
    histEnergyPred = (TH1D*)fpPred->Get("histNoOscPQ_runxi_pred_main");    
    histEnergyPredBest = (TH1D*)fpPredBest->Get("histPredPQ_run11_pred_28_39_0_0");    
    histEnergyData = (TH1D*)fpData->Get("histEnergyPQ_minosplus_fd_data");

  }

  printEventTable(histEnergyData);


  std::ifstream inFDMCPot("pot/run11FDMCPot.txt");
  std::ifstream inFDDataPot("pot/run11FDDataPot.txt");
  Double_t fdDataPot=0;   
  inFDDataPot >> fdDataPot;
  Double_t fdMCPot=0; 
  inFDMCPot >> fdMCPot;

  Double_t potScaleMC=fdDataPot/fdMCPot;
  std::cout << potScaleMC << "\t" << fdDataPot << "\t" << fdMCPot << "\n";
  //  histEnergyNoRw->Scale(potScaleMC);
  histEnergy->Scale(potScaleMC);
  histEnergyPred->Scale(potScaleMC);

  std::cout << "histEnergyPred->GetMean(): " << histEnergyPred->GetMean() << "\n";
  std::cout << "histEnergyPred->GetRMS(): " << histEnergyPred->GetRMS() << "\n";
  std::cout << "histEnergyPred->Integral(): " << histEnergyPred->Integral() << "\n";



  std::cout << "histEnergyData->GetMean(): " << histEnergyData->GetMean() << "\n";
  std::cout << "histEnergyData->GetRMS(): " << histEnergyData->GetRMS() << "\n";
  std::cout << "histEnergyData->Integral(): " << histEnergyData->Integral() << "\n";


  TH1D *histEnergyPred = getRebinnedHist(histEnergyPred);
  TH1D *histEnergy = getRebinnedHist(histEnergy);
  TH1D *histEnergyData = getRebinnedHist(histEnergyData);
  //  TH1D *histEnergyNoRw = getRebinnedHist(histEnergyNoRw);
  TH1D *histEnergyPredBest = getRebinnedHist(histEnergyPredBest);
  TH1D *histEnergyPredJoe = getRebinnedHist(histEnergyPredJoe);

  divideByBinWidth(histEnergyPred);
  divideByBinWidth(histEnergyPredBest);
  divideByBinWidth(histEnergy);
  divideByBinWidth(histEnergyData);
  divideByBinWidth(histEnergyPredJoe);
  //  divideByBinWidth(histEnergyNoRw);
  




  TCanvas *can = new TCanvas("canFD","canFD",800,800);
  can->Divide(1,2);
  can->cd(1);
  if(histEnergyData->GetMaximum()>histEnergyPred->GetMaximum()) {
    histEnergyPred->SetMaximum(1+histEnergyData->GetMaximum()*1.1);
  }
  histEnergyPred->SetTitle("");
  histEnergyPred->GetXaxis()->SetRangeUser(0,30);
  histEnergyPred->GetXaxis()->SetTitle("Reconstructed Neutrino Energy (GeV)");
  histEnergyPred->GetYaxis()->SetTitle("Events/GeV");
  histEnergyPred->SetLineColor(50);
  histEnergyPredBest->SetLineColor(9);
  histEnergyPredJoe->SetLineColor(kGreen+2);
  histEnergyPred->Draw();
  histEnergyPredBest->Draw("same");
  histEnergy->SetLineColor(kRed);
  if(plotJoe)  histEnergyPredJoe->Draw("same");
  histEnergyData->Draw("E0 same");
  //  histEnergy->Draw("same");
  //  histEnergyNoRw->SetLineColor(kBlue);
  //  histEnergyNoRw->Draw("same");

  TLegend *leggy = new TLegend(0.6,0.5,0.88,0.9);
  leggy->SetFillColor(0);
  leggy->SetFillStyle(0);
  leggy->SetBorderSize(0);
  leggy->AddEntry((TObject*)0,"MINOS+ Preliminary","");
  leggy->AddEntry(histEnergyPred,"RJN FD No. Osc");
  leggy->AddEntry(histEnergyPredBest,"RJN FD MINOS Osc");
  leggy->AddEntry(histEnergyData,"RJN FD Data");
  //  leggy->AddEntry(histEnergy,"RJN FD MC");
  //  leggy->AddEntry(histEnergyNoRw,"RJN FD MC No RW");
  char fdDataPotText[20];
  sprintf(fdDataPotText,"FD %1.3e POT ",fdDataPot);
  leggy->AddEntry((TObject*)0,fdDataPotText, "");

  leggy->Draw();

  TGraphErrors *ratio = getRatioGraphPoissonErrors(histEnergyData,histEnergyPred);
  TH1D *ratio2 = (TH1D*) histEnergyPredBest->Clone("ratio2");
  ratio2->Divide(histEnergyPred);

  can->cd(2);
  TH1F *frameRat = gPad->DrawFrame(0,0,30,1.2);
  frameRat->GetXaxis()->SetTitle("Reconstructed Neutrino Energy (GeV)");
  frameRat->SetTitle("");
  frameRat->SetYTitle("Ratio to No Osc. ");
  ratio2->SetLineColor(9);
  ratio->SetLineWidth(2);
  ratio2->Draw("same");
  ratio->SetLineColor(kBlack);
  ratio->Draw("p");

}

