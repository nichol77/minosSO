

void runNuDstLooperRunIIFDData()
{
  gSystem->CompileMacro("src/OscCalc.C","k");
   gSystem->CompileMacro("src/NuDstLooper.C","k");
   TChain *theChain = new TChain("s");
   theChain->Add("/minos/data/analysis/NuMuBar/DSTs/2010/R2.2/Data/far/dogwood3/DoNotLook/RunII/NuDSTMicro2010F00036570.root");
   NuDstLooper fred(theChain);
   fred.MakeHistos("runii_fd_data.root",1,"runii_fd_data");

}
