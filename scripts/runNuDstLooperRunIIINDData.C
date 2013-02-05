

void runNuDstLooperRunIIINDData()
{

  gSystem->CompileMacro("src/OscCalc.C","k");
   gSystem->CompileMacro("src/NuDstLooper.C","k");
   TChain *theChain = new TChain("s");
   theChain->Add("/minos/data/analysis/NuMuBar/DSTs/2010/R2.2/Data/near/dogwood3/RunIII/micro2010/NuDSTMicro*.root");
   NuDstLooper fred(theChain);
   fred.MakeHistos("runiii_nd_data.root",1,"runiii_nd_data");

}
