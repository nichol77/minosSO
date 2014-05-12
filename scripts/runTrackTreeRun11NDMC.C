

void runTrackTreeRun11NDMC()
{

  gSystem->CompileMacro("src/OscCalc.C","k");
   gSystem->CompileMacro("src/NuDstLooper.C","k");
   TChain *theChain = new TChain("s");  
   theChain->Add("/minos/data/analysis/DST/daikon10/elm3/R3.05/near/beam/M000200Np11/microDST/NuDSTMicro2014r11n130320*");
   NuDstLooper fred(theChain);
   fred.MakeTrackTree("/minos/data/users/rjn/nearMC/trackTreeNDMC.root",0);

}
