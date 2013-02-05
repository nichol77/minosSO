

void runNuDstLooperRunXNDData()
{

  gSystem->CompileMacro("src/OscCalc.C","k");
   gSystem->CompileMacro("src/NuDstLooper.C","k");
   TChain *theChain = new TChain("s");
   theChain->Add("/minos/data/analysis/NuMuBar/DSTs/2012/R2.10/sam/Data/CCselection/near/dogwood5/run10/NuDSTMicro*");
   NuDstLooper fred(theChain);
   fred.MakeHistos("runx_nd_data.root",1,"runx_nd_data");

}
