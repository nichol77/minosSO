

void runNuDstLooperRunVIINDData()
{

  gSystem->CompileMacro("src/OscCalc.C","k");
   gSystem->CompileMacro("src/NuDstLooper.C","k");
   TChain *theChain = new TChain("s");
   theChain->Add("/minos/data/analysis/NuMuBar/DSTs/2012/R2.7_2011_09_07/sam/data/near/run7/dogwood5/microDSTs/NuDSTMicro*.root");
   NuDstLooper fred(theChain);
   fred.MakeHistos("/minos/data/users/rjn/near/runvii_nd_data.root",1,"runvii_nd_data");

}
