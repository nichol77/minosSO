

void runNuDstLooperRunVNDData()
{

  gSystem->CompileMacro("src/OscCalc.C","k");
  gSystem->CompileMacro("src/NuDstLooper.C","k");
   TChain *theChain = new TChain("s");
   theChain->Add("/minos/data/analysis/NuMuBar/DSTs/2012/R2.10/sam/Data/CCselection/near/dogwood5/run5/NuDSTMicro*");
   NuDstLooper fred(theChain);
   fred.MakeHistos("/minos/data/users/rjn/nearData/runv_nd_data.root",1,"runv_nd_data");

}
