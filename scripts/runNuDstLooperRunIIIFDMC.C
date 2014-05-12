

void runNuDstLooperRunIIIFDMC()
{

  gSystem->CompileMacro("src/OscCalc.C","k");
   gSystem->CompileMacro("src/NuDstLooper.C","k");
   TChain *theChain = new TChain("s");
   theChain->Add("/minos/data/analysis/NuMuBar/DSTs/2010/R2.2/MC/D07_dogwood3/far/r3/micro2010/NuDSTMicro*.root");
   NuDstLooper fred(theChain);
   fred.MakeHistos("/minos/data/users/rjn/farMC/runiii_fd_mc.root",0,"runiii_fd_mc");

}
