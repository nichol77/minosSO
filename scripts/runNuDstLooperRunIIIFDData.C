

void runNuDstLooperRunIIIFDData()
{
  gSystem->CompileMacro("src/OscCalc.C","k");
   gSystem->CompileMacro("src/NuDstLooper.C","k");
   TChain *theChain = new TChain("s");
   theChain->Add("/minos/data/analysis/NuMuBar/DSTs/2010/R2.2/Data/far/dogwood3/DoNotLook/RunIII/NuDSTMicro2010F00039971.root");
   NuDstLooper fred(theChain);
   fred.MakeHistos("runiii_fd_data.root",1,"runiii_fd_data");

}
