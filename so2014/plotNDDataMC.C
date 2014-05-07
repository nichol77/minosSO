
void divideByBinWidth(TH1D *hist) {
  for(int bin=1;bin<=hist->GetNbinsX();bin++) {
    hist->SetBinContent(bin,hist->GetBinContent(bin)/hist->GetBinWidth(bin));
  }
}




void plotNDDataMC() {
  plotNDDataMCPQ();

}

void plotNDDataMCNQ() {
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
  histEnergyNQNoRw->Scale(potScaleMC);
  histEnergyNQ->Scale(potScaleMC);

  Double_t potScaleData=1e17/ndDataPot;
  histEnergyNQNoRwData->Scale(potScaleData);
  histEnergyNQData->Scale(potScaleData);

  divideByBinWidth(histEnergyNQData);
  divideByBinWidth(histEnergyNQNoRwData);
  divideByBinWidth(histEnergyNQ);
  divideByBinWidth(histEnergyNQNoRw);
  


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

  TLegend *leggy = new TLegend(0.6,0.6,0.88,0.9);
  leggy->SetFillColor(0);
  leggy->SetFillStyle(0);
  leggy->SetBorderSize(0);
  leggy->AddEntry(histEnergyNQData,"RJN ND Data");
  leggy->AddEntry(histEnergyNQ,"RJN ND MC");
  leggy->AddEntry(histEnergyNQNoRw,"RJN ND MC No RW");

  leggy->Draw();

  TH1D *ratio = (TH1D*)histEnergyNQData->Clone("ratio");
  ratio->Divide(histEnergyNQ);
  TH1D *ratio2 = (TH1D*)histEnergyNQData->Clone("ratio2");
  ratio2->Divide(histEnergyNQNoRw);


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
