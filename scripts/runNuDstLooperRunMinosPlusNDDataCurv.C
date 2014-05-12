

void runNuDstLooperRunMinosPlusNDDataCurv()
{

  gSystem->CompileMacro("src/OscCalc.C","k");
   gSystem->CompileMacro("src/NuDstLooper.C","k");
   TChain *theChain = new TChain("s");
   theChain->Add("/minos/data/analysis/DST/data/elm3/R3.05/beam/near/M000200Np11/microDST/NuDSTMicro2014N0005*");
   NuDstLooper fred(theChain);
   fred.MakeHistos("/minos/data/users/rjn/nearData/minosplus_nd_data_curv.root",1,"minosplus_nd_data");

}
