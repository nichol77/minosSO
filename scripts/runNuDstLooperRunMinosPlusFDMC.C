

void runNuDstLooperRunMinosPlusFDMC()
{

  gSystem->CompileMacro("src/OscCalc.C","k");
   gSystem->CompileMacro("src/NuDstLooper.C","k");
   TChain *theChain = new TChain("s");
   theChain->Add("/minos/data/analysis/DST/daikon10/elm3/R3.05/far/beam/M000200Np11Take2/microDST/mixed/NuDSTMicro*.root");
   //   theChain->Add("/minos/data/analysis/NuMuBar/MINOSPlusSamples/DSTs/M000200N_NOVA/far/microDSTs/NuDSTMicro2010r0f210310*.root");
   NuDstLooper fred(theChain);
   fred.MakeHistos("/minos/data/users/rjn/farMC/minosplus_fd_mc.root",0,"minosplus_fd_mc");
}
