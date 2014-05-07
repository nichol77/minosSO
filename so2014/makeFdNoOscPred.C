

void makeFdNoOscPred() {

  TFile *fpIn = TFile::Open("/unix/minos1/rjn/ccPlusNc/passTrees/run11/mainPass.root");
  
  TH1D *histNoOscNQ_runxi_pred_main = (TH1D*) fpIn->Get("histNoOscNQ_runxi_pred_main");
  TH1D *histNoOscPQ_runxi_pred_main = (TH1D*) fpIn->Get("histNoOscPQ_runxi_pred_main");
  TH1D *histNoOscNC_runxi_pred_main = (TH1D*) fpIn->Get("histNoOscNC_runxi_pred_main");
  TH1D *histNoOscNCTrack_runxi_pred_main = (TH1D*) fpIn->Get("histNoOscNCTrack_runxi_pred_main");
  
  TFile *fpOut = TFile::Open("minosplus_fd_pred.root","RECREATE");
  histNoOscNQ_runxi_pred_main->Write();
  histNoOscPQ_runxi_pred_main->Write();
  histNoOscNC_runxi_pred_main->Write();
  histNoOscNCTrack_runxi_pred_main->Write();
  
  fpOut->Close();
  fpIn->Close();


}
