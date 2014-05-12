

void runNuDstLooperRunIVNDMC()
{

  gSystem->CompileMacro("src/OscCalc.C","k");
   gSystem->CompileMacro("src/NuDstLooper.C","k");
   TChain *theChain = new TChain("s");
   theChain->Add("/minos/data/analysis/NuMuBar/DSTs/2011/R2.7_2011-09-07/sam/MC/near/Daikon07_Dogwood3/r4/sam/micro2010/NuDSTMicro*.root");
   NuDstLooper fred(theChain);
   fred.MakeHistos("/minos/data/users/rjn/nearMC/runiv_nd_mc.root",0,"runiv_nd_mc");

}
