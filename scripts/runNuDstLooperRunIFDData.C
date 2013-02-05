

void runNuDstLooperRunIFDData()
{

  gSystem->CompileMacro("src/OscCalc.C","k");
   gSystem->CompileMacro("src/NuDstLooper.C","k");
   TChain *theChain = new TChain("s");
   theChain->Add("/minos/data/analysis/NuMuBar/DSTs/2010/R2.2/Data/far/dogwood3/DoNotLook/RunI/NuDSTMicro2010F00031720.root");
   NuDstLooper fred(theChain);
   fred.MakeHistos("runi_fd_data.root",1,"runi_fd_data");

}
