

void runNuDstLooperRunIVNDData()
{

  gSystem->CompileMacro("src/OscCalc.C","k");
   gSystem->CompileMacro("src/NuDstLooper.C","k");
   TChain *theChain = new TChain("s");
   theChain->Add("/minos/data/analysis/NuMuBar/DSTs/2012/R2.7_2011_09_07/sam/data/near/run4/dogwood3/microDSTs/NuDSTMicro2010*");
   NuDstLooper fred(theChain);
   fred.MakeHistos("/minos/data/users/rjn/near/runiv_nd_data.root",1,"runiv_nd_data");

}
