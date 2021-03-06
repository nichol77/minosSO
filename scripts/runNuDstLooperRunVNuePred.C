

void runNuDstLooperRunVNuePred()
{
  gSystem->CompileMacro("src/OscCalc.C","k");
   gSystem->CompileMacro("src/NuDstLooper.C","k");
   TChain *theChain = new TChain("s");
   theChain->Add("/minos/data/analysis/NuMuBar/DSTs/2010/R2.2/MC/D07_dogwood3/nue/r3/NuDSTMicro*.root");   ///Using old r3 MC DSTs for now


   TFile *fpRat = new TFile("ndratios/NDRatio.root");
   TH1D *ndRatNQ = (TH1D*) fpRat->Get("histEnergyNQ_runv_nd_data_over_mc_ratio");
   TH1D *ndRatPQ = (TH1D*) fpRat->Get("histEnergyPQ_runv_nd_data_over_mc_ratio");
   TH1D *ndRatNC = (TH1D*) fpRat->Get("histEnergyNC_runv_nd_data_over_mc_ratio");
   TH1D *ndRatNCTrack = (TH1D*) fpRat->Get("histEnergyNCTrack_runv_nd_data_over_mc_ratio");

   NuDstLooper fred(theChain);
   fred.MakePredicitions("/minos/data/users/rjn/farPred/runv_pred_nue.root",ndRatNQ,ndRatPQ,ndRatNC,ndRatNCTrack,"runv_pred_nue"); 

}
 
