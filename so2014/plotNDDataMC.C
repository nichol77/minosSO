#include "so2014.h"



void plotNDDataMC() {
  plotNDDataMCNQ();

}

void plotNDDataMCNQ() {
  TFile *fpMC = TFile::Open("/Users/rjn/minos/so2014/fromMichelle/NDRun11HEMCSummaryNorm_Nominal_CC.root");
  TH1D *histEnergyMC = (TH1D*) fpMC->Get("TrueEnergyCCOnlyEvents_ND");
  TH1D *histEnergyMC2 = (TH1D*) fpMC->Get("TrueEnergyTrueCCFidEventsAll_ND");

  TFile *fpFlux = TFile::Open("/Users/rjn/minos/so2014/fromMichelle/FluxFiles/Flavour1Run11HE.root");
  TH1D *histEnergyFlux0 = (TH1D*) fpFlux->Get("TrueEnergyCCFluxRW_ND");


  TFile *fp = TFile::Open("minosplus_nd_mc.root");
  TH1D *histEnergyNQ = (TH1D*)fp->Get("histEnergyNQ_minosplus_nd_mc");
  TH1D *histEnergyNQNoRw = (TH1D*)fp->Get("histEnergyNQNoRw");

  TFile *fpData = TFile::Open("minosplus_nd_data.root");
  TH1D *histEnergyNQData = (TH1D*)fpData->Get("histEnergyNQ_minosplus_nd_data");
  TH1D *histEnergyNQNoRwData = (TH1D*)fpData->Get("histEnergyNQNoRw");

  std::ifstream inNDMCPot("pot/run11NDMCPot.txt");
  std::ifstream inNDDataPot("pot/run11NDDataPot.txt");
  Double_t ndDataPot=0;   
  inNDDataPot >> ndDataPot;
  Double_t ndMCPot=0; 
  inNDMCPot >> ndMCPot;
  Double_t potScaleMC=1e17/ndMCPot;
  Double_t potScaleData=1e17/ndDataPot;

  TGraphErrors *grRatio =getRatioGraphPoissonErrors(histEnergyNQData,histEnergyNQ,potScaleData,potScaleMC);
  TGraphErrors *grRatio2 =getRatioGraphPoissonErrors(histEnergyNQData,histEnergyNQNoRw,potScaleData,potScaleMC);

  histEnergyNQNoRw->Scale(potScaleMC);
  histEnergyNQ->Scale(potScaleMC);
  histEnergyMC->Scale(potScaleMC);
  histEnergyMC2->Scale(0.37*potScaleMC);
  histEnergyFlux0->Scale(6);


  histEnergyNQNoRwData->Scale(potScaleData);
  histEnergyNQData->Scale(potScaleData);

  divideByBinWidth(histEnergyNQData);
  divideByBinWidth(histEnergyNQNoRwData);
  divideByBinWidth(histEnergyNQ);
  divideByBinWidth(histEnergyNQNoRw);
  divideByBinWidth(histEnergyMC);
  divideByBinWidth(histEnergyMC2);
  divideByBinWidth(histEnergyFlux0);


  TCanvas *can = new TCanvas("canND","canND",800,800);
  can->Divide(1,2);
  can->cd(1);
  histEnergyNQData->SetTitle("");
  histEnergyNQData->GetXaxis()->SetRangeUser(0,30);
  histEnergyNQData->GetXaxis()->SetTitle("Reconstructed Neutrino Energy (GeV)");
  histEnergyNQData->GetYaxis()->SetTitle("Events/1#times10^{17}POT/GeV");
  histEnergyNQData->Draw();
  histEnergyNQ->SetLineColor(kRed);
  histEnergyNQ->Draw("same");
  histEnergyNQNoRw->SetLineColor(kBlue);
  histEnergyNQNoRw->Draw("same");
  histEnergyMC->SetLineColor(kGreen+2);
  histEnergyMC->Draw("same hist");
  histEnergyMC2->SetLineColor(kGreen+4);
  histEnergyMC2->Draw("same hist");
  histEnergyFlux0->SetLineColor(kOrange+2);
  histEnergyFlux0->Draw("same hist");

  TLegend *leggy = new TLegend(0.6,0.6,0.88,0.9);
  leggy->SetFillColor(0);
  leggy->SetFillStyle(0);
  leggy->SetBorderSize(0);
  leggy->AddEntry(histEnergyNQData,"RJN ND Data");
  leggy->AddEntry(histEnergyNQ,"RJN ND MC");
  leggy->AddEntry(histEnergyNQNoRw,"RJN ND MC No RW");
  leggy->AddEntry(histEnergyMC,"True Energy");
  leggy->AddEntry(histEnergyMC2,"True Energy, True Fid");
  leggy->AddEntry(histEnergyFlux0,"Flux");

  leggy->Draw();



  TH1D *ratio = (TH1D*)histEnergyNQData->Clone("ratio");
  ratio->Divide(histEnergyNQ);
  TH1D *ratio2 = (TH1D*)histEnergyNQData->Clone("ratio2");
  ratio2->Divide(histEnergyNQNoRw);

  TGraphErrors *grRatio3 = getSmoothedGraphFivePoint(grRatio2);
  TH1D *ratio3 = convertGraphToHistogram(grRatio3);
  
  can->cd(2);
  ratio->SetLineColor(kRed);
  ratio->Draw("");
  ratio->GetXaxis()->SetRangeUser(0,30);
  ratio->GetXaxis()->SetTitle("Reconstructed Neutrino Energy (GeV)");
  //  ratio->GetYaxis()->SetRangeUser(0.7,1.3);
  ratio->SetTitle("");
  ratio->GetYaxis()->SetTitle("Data / MC");
  ratio2->SetLineColor(kBlue);
  ratio2->Draw("same");
  ratio3->SetLineColor(kGreen+2);
  ratio3->Draw("same hist");
}



void plotNDDataMCPQ() {
  TFile *fp = TFile::Open("minosplus_nd_mc.root");
  TH1D *histEnergyPQ = (TH1D*)fp->Get("histEnergyPQ_minosplus_nd_mc");
  TH1D *histEnergyPQNoRw = (TH1D*)fp->Get("histEnergyPQNoRw");

  TFile *fpData = TFile::Open("minosplus_nd_data.root");
  TH1D *histEnergyPQData = (TH1D*)fpData->Get("histEnergyPQ_minosplus_nd_data");
  TH1D *histEnergyPQNoRwData = (TH1D*)fpData->Get("histEnergyPQNoRw");

  std::ifstream inNDMCPot("pot/run11NDMCPot.txt");
  std::ifstream inNDDataPot("pot/run11NDDataPot.txt");
  Double_t ndDataPot=0;   
  inNDDataPot >> ndDataPot;
  Double_t ndMCPot=0; 
  inNDMCPot >> ndMCPot;

  Double_t potScaleMC=1e17/ndMCPot;
  histEnergyPQNoRw->Scale(potScaleMC);
  histEnergyPQ->Scale(potScaleMC);

  Double_t potScaleData=1e17/ndDataPot;
  histEnergyPQNoRwData->Scale(potScaleData);
  histEnergyPQData->Scale(potScaleData);

  divideByBinWidth(histEnergyPQData);
  divideByBinWidth(histEnergyPQNoRwData);
  divideByBinWidth(histEnergyPQ);
  divideByBinWidth(histEnergyPQNoRw);
  


  TCanvas *can = new TCanvas("canND","canND",800,800);
  can->Divide(1,2);
  can->cd(1);
  histEnergyPQData->SetTitle("");
  histEnergyPQData->GetXaxis()->SetRangeUser(0,30);
  histEnergyPQData->GetXaxis()->SetTitle("Reconstructed Neutrino Energy (GeV)");
  histEnergyPQData->GetYaxis()->SetTitle("Events/1#times10^{17}POT/GeV");
  histEnergyPQData->Draw();
  histEnergyPQ->SetLineColor(kRed);
  histEnergyPQ->Draw("same");
  histEnergyPQNoRw->SetLineColor(kBlue);
  histEnergyPQNoRw->Draw("same");

  TLegend *leggy = new TLegend(0.6,0.6,0.88,0.9);
  leggy->SetFillColor(0);
  leggy->SetFillStyle(0);
  leggy->SetBorderSize(0);
  leggy->AddEntry(histEnergyPQData,"RJN PQ ND Data");
  leggy->AddEntry(histEnergyPQ,"RJN PQ ND MC");
  leggy->AddEntry(histEnergyPQNoRw,"RJN PQ ND MC No RW");

  leggy->Draw();

  TH1D *ratio = (TH1D*)histEnergyPQData->Clone("ratio");
  ratio->Divide(histEnergyPQ);
  TH1D *ratio2 = (TH1D*)histEnergyPQData->Clone("ratio2");
  ratio2->Divide(histEnergyPQNoRw);


  can->cd(2);
  ratio->GetXaxis()->SetRangeUser(0,30);
  ratio->GetXaxis()->SetTitle("Reconstructed Neutrino Energy (GeV)");
  ratio->GetYaxis()->SetRangeUser(0.7,1.3);
  ratio->SetTitle("");
  ratio->SetYTitle("Data / MC");
  ratio->SetLineColor(kRed);
  ratio->Draw();
  ratio2->SetLineColor(kBlue);
  ratio2->Draw("same");

}
