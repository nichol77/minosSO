

void runNuDstLooperRunINDData()
{

  gSystem->CompileMacro("src/OscCalc.C","k");
  gSystem->CompileMacro("src/NuDstLooper.C","k");
   TChain *theChain = new TChain("s");
   theChain->Add("/minos/data/analysis/NuMuBar/DSTs/2010/R2.2/Data/near/dogwood3/RunI/micro2010/NuDSTMicro*.root");
   NuDstLooper fred(theChain);
   fred.MakeHistos("/minos/data/users/rjn/nearData/runi_nd_data.root",1,"runi_nd_data");

}
