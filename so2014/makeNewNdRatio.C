#include "so2014.h"


void makeNewNdRatio() {
  TFile *fpCoilData = TFile::Open("~/minos/so2014/fromMichelle/TestCoil/NDDataRun11HEDataSummary_real_CC.root");
  TH1D *histCoilDataNQ = (TH1D*) fpCoilData->Get("RecoEnergy_ND");
  TH1D *histCoilDataPQ = (TH1D*) fpCoilData->Get("RecoEnergyPQ_ND");
  TH1D *histCoilDataPot = (TH1D*) fpCoilData->Get("hTotalPot");
  Double_t dataPotCoil=histCoilDataPot->Integral();

  TFile *fpCoilMC = TFile::Open("~/minos/so2014/fromMichelle/TestCoil/NDRun11HEMCSummary_Nominal_CC.root");
  TH1D *histCoilMCNQ = (TH1D*) fpCoilMC->Get("RecoEnergy_ND");
  TH1D *histCoilMCPQ = (TH1D*) fpCoilMC->Get("RecoEnergyPQ_ND");
  TH1D *histCoilMCPot = (TH1D*) fpCoilMC->Get("hTotalPot");
  Double_t MCPotCoil=histCoilMCPot->Integral();

  histCoilDataNQ->Scale(1e17/dataPotCoil);
  histCoilDataPQ->Scale(1e17/dataPotCoil);
  histCoilMCNQ->Scale(1e17/MCPotCoil);
  histCoilMCPQ->Scale(1e17/MCPotCoil);


  TFile *fpDefaultData = TFile::Open("~/minos/so2014/fromMichelle/Default/NDDataRun11HEDataSummary_real_CC.root");
  TH1D *histDefaultDataNQ = (TH1D*) fpDefaultData->Get("RecoEnergy_ND");
  TH1D *histDefaultDataPQ = (TH1D*) fpDefaultData->Get("RecoEnergyPQ_ND");
  TH1D *histDefaultDataPot = (TH1D*) fpDefaultData->Get("hTotalPot");
  Double_t dataPotDefault=histDefaultDataPot->Integral();

  TFile *fpDefaultMC = TFile::Open("~/minos/so2014/fromMichelle/Default/NDRun11HEMCSummary_Nominal_CC.root");
  TH1D *histDefaultMCNQ = (TH1D*) fpDefaultMC->Get("RecoEnergy_ND");
  TH1D *histDefaultMCPQ = (TH1D*) fpDefaultMC->Get("RecoEnergyPQ_ND");
  TH1D *histDefaultMCPot = (TH1D*) fpDefaultMC->Get("hTotalPot");
  Double_t MCPotDefault=histDefaultMCPot->Integral();

  histDefaultDataNQ->Scale(1e17/dataPotDefault);
  histDefaultDataPQ->Scale(1e17/dataPotDefault);
  histDefaultMCNQ->Scale(1e17/MCPotDefault);
  histDefaultMCPQ->Scale(1e17/MCPotDefault);


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

  TCanvas *can = new TCanvas("canRat","canRat");
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
  leggy->AddEntry(histCoil,"ND Data/MC w/o coil cut");
  leggy->AddEntry(histDefault,"ND Data/MC default");
  leggy->Draw();

}



void plotCoilHoleCut(TH1D *histDefaultDataNQ, TH1D *histDefaultMCNQ, 
		     TH1D *histCoilDataNQ, TH1D *histCoilMCNQ) {

  TCanvas *can = new TCanvas("canND","canND");
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
  leggy->AddEntry(histCoilDataNQ,"ND Data w/o coil cut");
  leggy->AddEntry(histCoilMCNQ,"ND MC w/o coil cut");
  leggy->AddEntry(histDefaultDataNQ,"ND Data default");
  leggy->AddEntry(histDefaultMCNQ,"ND MC default");
  leggy->Draw();
}
