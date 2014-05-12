

void runNuDstLooperRunIXNDData()
{

  gSystem->CompileMacro("src/OscCalc.C","k");
   gSystem->CompileMacro("src/NuDstLooper.C","k");
   TChain *theChain = new TChain("s");
   theChain->Add("/minos/data/analysis/NuMuBar/DSTs/2012/R2.7_2011_09_07/sam/data/near/run9/dogwood5/microDSTs/NuDSTMicro*.root");
   NuDstLooper fred(theChain);
   fred.MakeHistos("/minos/data/users/rjn/near/runix_nd_data.root",1,"runix_nd_data");

}
