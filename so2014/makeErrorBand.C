#include "so2014.h"
void makeErrorBand() {
  makeErrorBand(0);

}

void makeErrorBand(int pqNQ) {

  TFile *fpPred = TFile::Open("minosplus_fd_pred.root");
  TFile *fpBeamMatrix;
  TH1D *histEnergyPred;
  TH1D *histBeamMatrix;
  if(pqNQ==1) {
    histEnergyPred= (TH1D*)fpPred->Get("histNoOscPQ_runxi_pred_main");
    fpBeamMatrix = TFile::Open("minosplus_bestfit_spectra_PQ.root");
    histBeamMatrix = (TH1D*) fpBeamMatrix->Get("unosc_minosplus_beam");
  }
  else if(pqNQ==0) {
    histEnergyPred= (TH1D*)fpPred->Get("histNoOscNQ_runxi_pred_main");
    fpBeamMatrix = TFile::Open("minosplus_bestfit_spectra_NQ.root");
    histBeamMatrix = (TH1D*) fpBeamMatrix->Get("unosc_minosplus_beam");
  }
  else {
    std::cerr << "pqNQ must be 0 or 1\n";
    return;
  }

  std::ifstream inFDMCPot("pot/run11FDMCPOT.txt");
  std::ifstream inFDMCWrongFluxPot("pot/run11FDMCWrongFluxPOT.txt");
  std::ifstream inFDDataPot("pot/run11FDDataPOT.txt");
  Double_t fdDataPot=0;   
  inFDDataPot >> fdDataPot;
  Double_t fdMCPot=0; 
  inFDMCPot >> fdMCPot;
  Double_t fdMCWrongFluxPot=0; 
  inFDMCWrongFluxPot >> fdMCWrongFluxPot;

  Double_t potScaleMC=fdDataPot/fdMCPot;
  Double_t potScaleMCWrongFlux=fdDataPot/fdMCWrongFluxPot;
  std::cout << potScaleMC << "\t" << fdDataPot << "\t" << fdMCPot << "\t" << fdMCWrongFluxPot << "\n";;
  histEnergyPred->Scale(potScaleMC);


  divideByBinWidth(histEnergyPred);
  divideByBinWidth(histBeamMatrix);


  TCanvas *can = new TCanvas();
  histEnergyPred->Draw();
  histBeamMatrix->SetLineColor(kRed+2);
  histBeamMatrix->Draw("same");


  TCanvas *can2 = new TCanvas();
  TH1D *errorBand = (TH1D*)histEnergyPred->Clone("errorBand");
  
  for(int bin=1;bin<=errorBand->GetNbinsX();bin++) {
    errorBand->SetBinContent(bin,1);
    Double_t fn=histEnergyPred->GetBinContent(bin);
    Double_t bm=histBeamMatrix->GetBinContent(bin);
    Double_t error=TMath::Abs(bm-fn)/fn;
    std::cout << fn << "\t" << bm << "\t" << error << "\n";
    if(fn<1e-8) error=0;
    errorBand->SetBinError(bin,error);
  }
  errorBand->SetFillStyle(3002);
  errorBand->SetFillColor(kBlack);
  errorBand->GetXaxis()->SetTitle("Neutrino Energy (GeV)");
  errorBand->GetYaxis()->SetTitle("Error Band");
  errorBand->GetXaxis()->SetRangeUser(0,20);
  errorBand->GetYaxis()->SetRangeUser(0.7,1.3);
  errorBand->Draw("e3");

  TFile *fpAlex = TFile::Open("../farFiles/alexErrorBand.root");
  TGraphAsymmErrors *grAlexError = (TGraphAsymmErrors*) fpAlex->Get("grAlexError");
  grAlexError->SetFillColor(kRed+2);
  grAlexError->SetFillStyle(3001);
  grAlexError->Draw("3");
  can2->Update();
  can2->Modified();

  TLegend *leggy = makeLegendBoxInTopLeftCorner(0.3,0.3);
  leggy->AddEntry(errorBand,"Matrix vs F/N","f");
  leggy->AddEntry(grAlexError,"F/N Flux Shifts","f");
  leggy->Draw("same");

}


