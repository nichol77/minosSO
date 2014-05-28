

void makeRWFile() {
  TFile *fp = TFile::Open("../so2014/ratioPlot.root");
  TH1D *nu3dfd_z = (TH1D*) fp->Get("nu3dfd_z");

  TFile *fpOut = TFile::Open("reweightRun11.root","RECREATE");
  TH1D *rwFD = (TH1D*) nu3dfd_z->Clone();
  for(int bin=1;bin<=rwFD->GetNbinsX();bin++) {
    rwFD->SetBinContent(bin,1./nu3dfd_z->GetBinContent(bin));
  }
  rwFD->SetXTitle("True Neutrino Energy (GeV)");
  rwFD->SetYTitle("New/Old");
  rwFD->Write();
  fpOut->Close();
  fp->Close();
}

