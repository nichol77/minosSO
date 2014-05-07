
void divideByBinWidth(TH1D *hist) {
  for(int bin=1;bin<=hist->GetNbinsX();bin++) {
    hist->SetBinContent(bin,hist->GetBinContent(bin)/hist->GetBinWidth(bin));
  }
}



void printEventTable(TH1D *hist) {
  std::cout << hist->GetName() << "\t" << hist->GetTitle() << "\n";

  Double_t num0to4=0;
  Double_t num4to8=0;
  Double_t numAbove=0;
  for(int bin=1;bin<=hist->GetNbinsX();bin++) {
    double numEvents=hist->GetBinContent(bin);
    double minE=hist->GetBinLowEdge(bin);
    double maxE=hist->GetBinLowEdge(bin)+hist->GetBinWidth(bin);
    if(maxE<=4) {
      num0to4+=numEvents;
    }
    else if(maxE<=8) {
      num4to8+=numEvents;
    }
    else {
      numAbove+=numEvents;
    }    
  }

  std::cout << "*******************************************************\n";
  std::cout << "Total: " << hist->Integral() << "\n";
  std::cout << "<4: " << num0to4 << "\n";
  std::cout << "4-8: " << num4to8 << "\n";
  std::cout << ">8: " << numAbove << "\n";
}

void plotFDPred() {
  plotFDPred(1,0,0,1,1,0,0);
  plotFDPred(0,0,0,1,1,0,0);

}

void plotFDPred(int pqNQ, int showRawMC, int showTunedMC,int showWrongFlux, int showWrongFlxuRw, int showJoe, int showMichelle) {

  TFile *fp = TFile::Open("minosplus_fd_mc.root");
  TFile *fpWrongFlux = TFile::Open("minosplus_fd_mc_old_flux.root");
  TFile *fpPred = TFile::Open("minosplus_fd_pred.root");
  TFile *fpPredWrongRw = TFile::Open("minosplus_fd_pred_wrongflux_rw.root");
  TFile *fpPredWrong = TFile::Open("minosplus_fd_pred_wrongflux.root");
  TFile *fpPredMichelle = TFile::Open("~/minos/so2014/fromMichelle/Spectra/oscfit.Neutrino2014.Spectra.NewTemplates.NoResBin.RealNDData.MinosPlusOnly.atmos.NumuOnly.normal.full.syst.noosc.root");
  TFile *fpBeamMatrix;

  TH1D *histEnergy;
  TH1D *histEnergyWrongFlux;
  TH1D *histEnergyNoRw;
  TH1D *histEnergyPred;
  TH1D *histEnergyPredWrong;
  TH1D *histEnergyPredWrongRw;
  TH1D *histBeamMatrix;
  TH1D *histEnergyMichelle;
  if(pqNQ==1) {
    histEnergy = (TH1D*)fp->Get("histEnergyPQ_minosplus_fd_mc");
    histEnergyWrongFlux = (TH1D*)fpWrongFlux->Get("histEnergyPQ_minosplus_fd_mc");
    histEnergyNoRw = (TH1D*)fp->Get("histEnergyPQNoRw");
    histEnergyPred= (TH1D*)fpPred->Get("histNoOscPQ_runxi_pred_main");
    histEnergyPredWrong= (TH1D*)fpPredWrong->Get("histNoOscPQ_runxi_pred_main");
    histEnergyPredWrongRw= (TH1D*)fpPredWrongRw->Get("histNoOscPQ_runxi_pred_main");
    histEnergyMichelle = (TH1D*)fpPredMichelle->Get("hist_run11_cv_numu_nubar");
    fpBeamMatrix = TFile::Open("minosplus_bestfit_spectra_PQ.root");
    histBeamMatrix = (TH1D*) fpBeamMatrix->Get("unosc_minosplus_beam");
    histBeamMatrix->SetNameTitle("bmPred","PQ - Beam Matrix Prediction");
    histEnergy->SetNameTitle("tunedMC","PQ - Tuned MC");
    histEnergyMichelle->SetNameTitle("mmPred","NQ - MM Beam Matrix Prediction");
    histEnergyNoRw->SetNameTitle("rawMC","PQ - Raw MC");
    histEnergyPred->SetNameTitle("fnPred","PQ - F/N Prediction Flux Reweighted");
    histEnergyPredWrong->SetNameTitle("fnPredRw","PQ -F/N Prediction");
  }
  else if(pqNQ==0) {
    histEnergy = (TH1D*)fp->Get("histEnergyNQ_minosplus_fd_mc");
    histEnergyWrongFlux = (TH1D*)fpWrongFlux->Get("histEnergyNQ_minosplus_fd_mc");
    histEnergyNoRw = (TH1D*)fp->Get("histEnergyNQNoRw");
    histEnergyPred= (TH1D*)fpPred->Get("histNoOscNQ_runxi_pred_main");
    histEnergyPredWrong= (TH1D*)fpPredWrong->Get("histNoOscNQ_runxi_pred_main");
    histEnergyPredWrongRw= (TH1D*)fpPredWrongRw->Get("histNoOscNQ_runxi_pred_main");
    histEnergyMichelle = (TH1D*)fpPredMichelle->Get("hist_run11_cv_numu_nu");
    fpBeamMatrix = TFile::Open("minosplus_bestfit_spectra_NQ.root");
    histBeamMatrix = (TH1D*) fpBeamMatrix->Get("unosc_minosplus_beam");
    histBeamMatrix->SetNameTitle("joePred","NQ - Joe Beam Matrix Prediction");
    histEnergyMichelle->SetNameTitle("mmPred","NQ - MM Beam Matrix Prediction");
    histEnergy->SetNameTitle("tunedMC","NQ - Tuned MC");
    histEnergyNoRw->SetNameTitle("rawMC","NQ - Raw MC");
    histEnergyPred->SetNameTitle("fnPred","NQ - F/N Prediction Flux Reweighted");
    histEnergyPredWrong->SetNameTitle("fnPredRw","NQ -F/N Prediction");
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
  histEnergyNoRw->Scale(potScaleMC);
  histEnergy->Scale(potScaleMC);
  histEnergyWrongFlux->Scale(potScaleMCWrongFlux);
  histEnergyPred->Scale(potScaleMC);

  histEnergyPredWrong->Scale(potScaleMCWrongFlux);
  histEnergyPredWrongRw->Scale(potScaleMCWrongFlux);

  printEventTable(histEnergyPred);
  printEventTable(histEnergyPredWrong);
  printEventTable(histBeamMatrix);
  printEventTable(histEnergyMichelle);

  // std::cout << "histEnergyPred->GetMean(): " << histEnergyPred->GetMean() << "\n";
  // std::cout << "histEnergyPred->GetRMS(): " << histEnergyPred->GetRMS() << "\n";
  // std::cout << "histEnergyPred->Integral(): " << histEnergyPred->Integral() << "\n";



  // std::cout << "histEnergy->GetMean(): " << histEnergy->GetMean() << "\n";
  // std::cout << "histEnergy->GetRMS(): " << histEnergy->GetRMS() << "\n";
  // std::cout << "histEnergy->Integral(): " << histEnergy->Integral() << "\n";

  divideByBinWidth(histEnergyPred);
  divideByBinWidth(histEnergyPredWrong);
  divideByBinWidth(histEnergyPredWrongRw);
  divideByBinWidth(histEnergy);
  divideByBinWidth(histEnergyWrongFlux);
  divideByBinWidth(histEnergyNoRw);
  divideByBinWidth(histBeamMatrix);
  divideByBinWidth(histEnergyMichelle);
  
  char *canNames[2]={"canFDNQ","canFDPQ"};

  TCanvas *can = new TCanvas(canNames[pqNQ],canNames[pqNQ],800,800);
  can->Divide(1,2);
  can->cd(1);
  if(histEnergy->GetMaximum()>histEnergyPred->GetMaximum()) {
    histEnergyPred->SetMaximum(histEnergy->GetMaximum()*1.1);
  }
  histEnergyPred->SetTitle("");
  histEnergyPred->GetXaxis()->SetRangeUser(0,30);
  histEnergyPred->GetXaxis()->SetTitle("Reconstructed Neutrino Energy (GeV)");
  histEnergyPred->GetYaxis()->SetTitle("Events/GeV");
  histEnergyPred->Draw();
  histEnergyPredWrong->SetLineColor(39);
  if(showWrongFlux) histEnergyPredWrong->Draw("same");
  histEnergyPredWrongRw->SetLineColor(9);
  if(showWrongFlxuRw) histEnergyPredWrongRw->Draw("same");
  histEnergy->SetLineColor(kRed);
  histEnergy->Draw("same");
  histEnergyWrongFlux->SetLineColor(kViolet);
  if(showWrongFlux) histEnergyWrongFlux->Draw("same");
  histEnergyNoRw->SetLineColor(kBlue);
  if(showRawMC) histEnergyNoRw->Draw("same");
  histBeamMatrix->SetLineColor(kGreen+2);
  if(showJoe) histBeamMatrix->Draw("same");
  histEnergyMichelle->SetLineColor(kOrange+2);
  if(showMichelle) histEnergyMichelle->Draw("same");

  TLegend *leggy = new TLegend(0.6,0.5,0.88,0.9);
  leggy->SetFillColor(0);
  leggy->SetFillStyle(0);
  leggy->SetBorderSize(0);
  leggy->AddEntry(histEnergyPred,"RJN FD Pred New FD MC");
  if(showWrongFlux) leggy->AddEntry(histEnergyPredWrong,"RJN FD Pred Wrong Flux");
  if(showWrongFlxuRw) leggy->AddEntry(histEnergyPredWrongRw,"RJN FD Pred Wrong Flux RW");
  leggy->AddEntry(histEnergy,"RJN New FD MC");
  if(showWrongFlux) leggy->AddEntry(histEnergyWrongFlux,"RJN Old FD MC");
  if(showRawMC)  leggy->AddEntry(histEnergyNoRw,"RJN FD MC Untuned");
  if(showJoe) leggy->AddEntry(histBeamMatrix,"JOC FD Pred");
  if(showMichelle) leggy->AddEntry(histEnergyMichelle,"MM FD Pred");
  char fdDataPotText[20];
  sprintf(fdDataPotText,"FD %1.3e POT ",fdDataPot);
  leggy->AddEntry((TObject*)0,fdDataPotText, "");

  leggy->Draw();

  TH1D *ratio = (TH1D*)histEnergyPred->Clone("ratio");
  ratio->Divide(histEnergy);
  TH1D *ratio3 = (TH1D*)histEnergyPredWrong->Clone("ratio3");
  ratio3->Divide(histEnergy);
  TH1D *ratio4 = (TH1D*)histBeamMatrix->Clone("ratio4");
  ratio4->Divide(histEnergy);
  TH1D *ratio5 = (TH1D*)histEnergyMichelle->Clone("ratio5");
  ratio5->Divide(histEnergy);
  TH1D *ratio6 = (TH1D*)histEnergyPredWrongRw->Clone("ratio6");
  ratio6->Divide(histEnergy);


  can->cd(2);
  ratio->GetXaxis()->SetRangeUser(0,30);
  ratio->GetXaxis()->SetTitle("Reconstructed Neutrino Energy (GeV)");
  ratio->GetYaxis()->SetRangeUser(0.7,1.3);
  ratio->SetTitle("");
  ratio->SetYTitle("Pred / MC");
  ratio->SetLineColor(kBlack);
  ratio->Draw();

  ratio3->SetLineColor(39);
  if(showWrongFlux)ratio3->Draw("same");
  ratio4->SetLineColor(kGreen+2);
  if(showJoe) ratio4->Draw("same");
  ratio5->SetLineColor(kOrange+2);
  if(showMichelle) ratio5->Draw("same");
  ratio6->SetLineColor(9);
  if(showWrongFlxuRw)ratio6->Draw("same");

}


