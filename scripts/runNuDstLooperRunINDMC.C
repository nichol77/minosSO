

void runNuDstLooperRunINDMC()
{
  gSystem->CompileMacro("src/OscCalc.C","k");
   gSystem->CompileMacro("src/NuDstLooper.C","k");
   TChain *theChain = new TChain("s");
   theChain->Add("/minos/data/analysis/NuMuBar/DSTs/2010/R2.2/MC/D07_dogwood3/near/r1/AllIntensities/micro2010/NuDSTMicro*.root");
   NuDstLooper fred(theChain);
   fred.MakeHistos("/minos/data/users/rjn/nearMC/runi_nd_mc.root",0,"runi_nd_mc");

}
