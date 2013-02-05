

void runNuDstLooperRunXFDData()
{
  gSystem->CompileMacro("src/OscCalc.C","k");
   gSystem->CompileMacro("src/NuDstLooper.C","k");
   TChain *theChain = new TChain("s");
   theChain->Add("/minos/data/analysis/NuMuBar/AnalysisTools/fdConcatenatedBntps/Run10SecondAttempt/NuDSTMicro2010F00048585.root");
   NuDstLooper fred(theChain);
   fred.MakeHistos("runx_fd_data.root",1,"runx_fd_data");

}
