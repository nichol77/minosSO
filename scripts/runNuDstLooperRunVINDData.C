

void runNuDstLooperRunVINDData()
{

  gSystem->CompileMacro("src/OscCalc.C","k");
   gSystem->CompileMacro("src/NuDstLooper.C","k");
   TChain *theChain = new TChain("s");
   theChain->Add("/minos/data/analysis/NuMuBar/DSTs/2012/R2.10/sam/Data/CCselection/near/dogwood5/run6/NuDSTMicro*");
   NuDstLooper fred(theChain);
   fred.MakeHistos("runvi_nd_data.root",1,"runvi_nd_data");

}
