

void plotBeamWeightRatio() {


  //  plotRatioND();
  plotRatioFD();
}


void plotRatioFD() {
  TFile *fp = TFile::Open("/unix/minos1/rjn/so2014/rjnData/minosplus_fd_mc.root");

  TH1D *histEnergyNQ = (TH1D*)fp->Get("histEnergyNQ_minosplus_fd_mc");
  TH1D *histEnergyNQNoRw = (TH1D*)fp->Get("histEnergyNQNoRw");


  histEnergyNQNoRw->Scale(1/1.64514989587434352e4);
  histEnergyNQ->Scale(1/1.64514989587434352e4);



//   TFile *fpMCFD = TFile::Open("/unix/minos1/rjn/so2014/fromMichelle/MinosPlusFiles/Normalized/R3.04/FDRun11HEMCSummaryNorm_Nominal_CC.root");
//   TH1D *fdMC = (TH1D*) fpMCFD->Get("RecoEnergyAll_FD");
//   TH1D *fdMCPot = (TH1D*) fpMCFD->Get("hTotalPot");
//   fdMC->Scale(1e20/hTotalPot->Integral());


//  std::cout << fdMC->Integral() << "\t" << histEnergyNQNoRw->Integral() << "\t" << histEnergyNQ->Integral() << "\n";

  TH1D *ratio = (TH1D*) histEnergyNQNoRw->Clone("ratio");
  ratio->Divide(histEnergyNQ);
  //  TH1D *ratio2 = (TH1D*) fdMC->Clone("ratio2");
  //  ratio2->Divide(histEnergyNQ);




  TCanvas *can = new TCanvas("canFD","canFD",800,800);
  can->Divide(1,2);
  can->cd(1);
  histEnergyNQ->SetLineColor(kRed);
  histEnergyNQ->Draw();
  can->Update();
  can->Modified();
  histEnergyNQ->GetXaxis()->SetRangeUser(0,50);
  //  fdMC->SetLineColor(kBlue);
  //  fdMC->Draw("same");
  histEnergyNQNoRw->Draw("same");

  TLegend *leggy = new TLegend(0.6,0.6,0.88,0.9);
  leggy->SetFillColor(0);
  leggy->SetFillStyle(0);
  leggy->SetBorderSize(0);
  leggy->AddEntry(histEnergyNQ,"RJN FD MC");
  leggy->AddEntry(histEnergyNQNoRw,"RJN FD MC no rw");
  //  leggy->AddEntry(fdMC,"MM FD MC");
  leggy->Draw();



  can->cd(2);
  ratio->GetXaxis()->SetRangeUser(0,50);
  ratio->GetYaxis()->SetRangeUser(0.8,1.3);
  ratio->SetTitle("No RW / RW");
  ratio->Draw();
//   ratio2->SetLineColor(kBlue);
//   ratio2->Draw("same");

}




void plotRatioND() {
  TFile *fp = TFile::Open("/unix/minos1/rjn/so2014/rjnData/minosplus_nd_mc.root");

  TH1D *histEnergyNQ = (TH1D*)fp->Get("histEnergyNQ_minosplus_nd_mc");
  TH1D *histEnergyNQNoRw = (TH1D*)fp->Get("histEnergyNQNoRw");



  Double_t potScale=1e20/2.83920000488738652e+19;

  histEnergyNQNoRw->Scale(potScale);
  histEnergyNQ->Scale(potScale);



  TFile *fpMCND = TFile::Open("/unix/minos1/rjn/so2014/fromMichelle/MinosPlusFiles/Normalized/R3.04/NDRun11HEMCSummaryNorm_Nominal_CC.root");
  TH1D *ndMC = (TH1D*) fpMCND->Get("RecoEnergyAll_ND");
  TH1D *ndMCPot = (TH1D*) fpMCND->Get("hTotalPot");
  std::cout << "hTotalPot->Integral() " << hTotalPot->Integral() << "\n";
  ndMC->Scale(1e20/hTotalPot->Integral());


  std::cout << ndMC->Integral() << "\t" << histEnergyNQNoRw->Integral() << "\t" << histEnergyNQ->Integral() << "\n";

  TH1D *ratio = (TH1D*) histEnergyNQNoRw->Clone("ratio");
  ratio->Divide(histEnergyNQ);
  TH1D *ratio2 = (TH1D*) ndMC->Clone("ratio2");
  ratio2->Divide(histEnergyNQ);




  TCanvas *can = new TCanvas("canND","canND",800,800);
  can->Divide(1,2);
  can->cd(1);
  histEnergyNQ->SetLineColor(kRed);
  histEnergyNQ->GetXaxis()->SetRangeUser(0,50);
  histEnergyNQ->Draw();
  ndMC->SetLineColor(kBlue);
  ndMC->Draw("same");
  histEnergyNQNoRw->Draw("same");

  TLegend *leggy = new TLegend(0.6,0.6,0.88,0.9);
  leggy->SetFillColor(0);
  leggy->SetFillStyle(0);
  leggy->SetBorderSize(0);
  leggy->AddEntry(histEnergyNQ,"RJN ND MC");
  leggy->AddEntry(histEnergyNQNoRw,"RJN ND MC no rw");
  leggy->AddEntry(ndMC,"MM ND MC");
  leggy->Draw();


  can->cd(2);
  ratio->GetXaxis()->SetRangeUser(0,50);
  ratio->GetYaxis()->SetRangeUser(0.8,1.3);
  ratio->SetTitle("No RW / RW");
  ratio->Draw();
  ratio2->SetLineColor(kBlue);
  ratio2->Draw("same");

}
