

void runNuDstLooperRunMinosPlusFDData()
{

  gSystem->CompileMacro("src/OscCalc.C","k");
   gSystem->CompileMacro("src/NuDstLooper.C","k");
   TChain *theChain = new TChain("s");
   theChain->Add("/minos/data/analysis/DST/data/elm3/R3.05/beam/far/.M000200Np11/microDST/*");
   NuDstLooper fred(theChain);
   fred.MakeHistos("/minos/data/users/rjn/farData/minosplus_fd_data.root",1,"minosplus_fd_data");

}
