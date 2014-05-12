#include "so2014.h"


void makeNewNdRatio() {
  std::ifstream inNDMCPot("pot/run11NDMCPOT.txt");
  std::ifstream inNDDataPot("pot/run11NDDataPOT.txt");
  Double_t ndDataPot=0;   
  inNDDataPot >> ndDataPot;
  Double_t ndMCPot=0; 
  inNDMCPot >> ndMCPot;



  TFile *fpCoilData = TFile::Open("minosplus_nd_data_curv.root");
  TH1D *histCoilDataNQ = (TH1D*) fpCoilData->Get("histEnergyNQ_minosplus_nd_data");
  TH1D *histCoilDataPQ = (TH1D*) fpCoilData->Get("histEnergyPQ_minosplus_nd_data");

  TFile *fpCoilMC = TFile::Open("minosplus_nd_mc_curv.root");
  TH1D *histCoilMCNQ = (TH1D*) fpCoilMC->Get("histEnergyNQ_minosplus_nd_mc");
  TH1D *histCoilMCPQ = (TH1D*) fpCoilMC->Get("histEnergyPQ_minosplus_nd_mc");

  histCoilDataNQ->Scale(1e17/ndDataPot);
  histCoilDataPQ->Scale(1e17/ndDataPot);
  histCoilMCNQ->Scale(1e17/ndMCPot);
  histCoilMCPQ->Scale(1e17/ndMCPot);


  TFile *fpDefaultData = TFile::Open("minosplus_nd_data.root");
  TH1D *histDefaultDataNQ = (TH1D*) fpDefaultData->Get("histEnergyNQ_minosplus_nd_data");
  TH1D *histDefaultDataPQ = (TH1D*) fpDefaultData->Get("histEnergyPQ_minosplus_nd_data");   

  TFile *fpDefaultMC = TFile::Open("minosplus_nd_mc.root");
  TH1D *histDefaultMCNQ = (TH1D*) fpDefaultMC->Get("histEnergyNQ_minosplus_nd_mc");
  TH1D *histDefaultMCPQ = (TH1D*) fpDefaultMC->Get("histEnergyPQ_minosplus_nd_mc");


  histDefaultDataNQ->Scale(1e17/ndDataPot);
  histDefaultDataPQ->Scale(1e17/ndDataPot);
  histDefaultMCNQ->Scale(1e17/ndMCPot);
  histDefaultMCPQ->Scale(1e17/ndMCPot);


  divideByBinWidth(histDefaultMCPQ);
  divideByBinWidth(histDefaultMCNQ);
  divideByBinWidth(histCoilMCPQ);
  divideByBinWidth(histCoilMCNQ);
  divideByBinWidth(histDefaultDataPQ);
  divideByBinWidth(histDefaultDataNQ);
  divideByBinWidth(histCoilDataPQ);
  divideByBinWidth(histCoilDataNQ);

  plotCoilHoleCut(histDefaultDataNQ,histDefaultMCNQ,histCoilDataNQ,histCoilMCNQ);

  TH1D *ratioDefaultNQ = (TH1D*) histDefaultDataNQ->Clone("ratioDefaultNQ");
  ratioDefaultNQ->SetNameTitle("ratioDefaultNQ","ratioDefaultNQ");
  ratioDefaultNQ->Divide(histDefaultMCNQ);

  TH1D *ratioDefaultPQ = (TH1D*) histDefaultDataPQ->Clone("ratioDefaultPQ");
  ratioDefaultPQ->SetNameTitle("ratioDefaultPQ","ratioDefaultPQ");
  ratioDefaultPQ->Divide(histDefaultMCPQ);

  TH1D *ratioCoilNQ = (TH1D*) histCoilDataNQ->Clone("ratioCoilNQ");
  ratioCoilNQ->SetNameTitle("ratioCoilNQ","ratioCoilNQ");
  ratioCoilNQ->Divide(histCoilMCNQ);

  TH1D *ratioCoilPQ = (TH1D*) histCoilDataPQ->Clone("ratioCoilPQ");
  ratioCoilPQ->SetNameTitle("ratioCoilPQ","ratioCoilPQ");
  ratioCoilPQ->Divide(histCoilMCPQ);

  plotRatios(ratioDefaultNQ,ratioCoilNQ);


  TFile *fpOut = new TFile("ndDoubleRatioCoil.root","RECREATE");
  ratioDefaultNQ->Write();
  ratioDefaultPQ->Write();
  ratioCoilNQ->Write();
  ratioCoilPQ->Write();
  TH1D *doubleRatioNQ = (TH1D*)ratioCoilNQ->Clone("doubleRatioNQ");
  doubleRatioNQ->SetName("doubleRatioNQ");
  doubleRatioNQ->Divide(ratioDefaultNQ);
  doubleRatioNQ->Write();

  TH1D *doubleRatioPQ = (TH1D*)ratioCoilPQ->Clone("doubleRatioPQ");
  doubleRatioPQ->SetName("doubleRatioPQ");
  doubleRatioPQ->Divide(ratioDefaultPQ);
  doubleRatioPQ->Write();

  new TCanvas();
  doubleRatioNQ->Draw();
  doubleRatioPQ->Draw("same");



}

void plotRatios(TH1D *histDefault, TH1D *histCoil) {

  TCanvas *can = new TCanvas("canRat","canRat",800,600);
  histCoil->SetLineColor(kRed);
  histDefault->SetXTitle("Reconstructed Energy (GeV)");
  histDefault->SetYTitle("Data / MC");
  histDefault->SetTitle("");
  histDefault->GetXaxis()->SetRangeUser(0,30);
  histDefault->Draw();
  histCoil->Draw("same");


  TLegend *leggy = new TLegend(0.5,0.2,0.9,0.5);
  leggy->SetFillColor(0);
  leggy->SetFillStyle(0);
  leggy->SetBorderSize(0);
  leggy->AddEntry(histCoil,"ND Data/MC w/o coil cut curv");
  leggy->AddEntry(histDefault,"ND Data/MC default");
  leggy->Draw();

}



void plotCoilHoleCut(TH1D *histDefaultDataNQ, TH1D *histDefaultMCNQ, 
		     TH1D *histCoilDataNQ, TH1D *histCoilMCNQ) {

  TCanvas *can = new TCanvas("canND","canND",800,600);
  histCoilMCNQ->SetLineColor(kRed);
  histCoilDataNQ->SetLineColor(kRed);
  histCoilDataNQ->SetXTitle("Reconstructed Energy (GeV)");
  histCoilDataNQ->SetYTitle("Events / 10^{17} POT / GeV");
  histCoilDataNQ->GetXaxis()->SetRangeUser(0,30);
  histCoilDataNQ->SetTitle("");
  histCoilDataNQ->Draw();
  histCoilMCNQ->SetLineStyle(2);
  histCoilMCNQ->Draw("same");
  histDefaultDataNQ->Draw("same");
  histDefaultMCNQ->SetLineStyle(2);
  histDefaultMCNQ->Draw("same");


  TLegend *leggy = new TLegend(0.6,0.5,0.88,0.9);
  leggy->SetFillColor(0);
  leggy->SetFillStyle(0);
  leggy->SetBorderSize(0);
  leggy->AddEntry(histCoilDataNQ,"ND Data w/o coil cut curv");
  leggy->AddEntry(histCoilMCNQ,"ND MC w/o coil cut curv");
  leggy->AddEntry(histDefaultDataNQ,"ND Data default");
  leggy->AddEntry(histDefaultMCNQ,"ND MC default");
  leggy->Draw();
}
