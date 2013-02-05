

void runNuDstLooperRunVIFDData()
{
  gSystem->CompileMacro("src/OscCalc.C","k");
   gSystem->CompileMacro("src/NuDstLooper.C","k");
   TChain *theChain = new TChain("s");
   theChain->Add("/minos/data/analysis/NuMuBar/AnalysisTools/fdConcatenatedBntps/Run6SecondAttempt/NuDSTMicro2010F00045783.root");
   NuDstLooper fred(theChain);
   fred.MakeHistos("runvi_fd_data.root",1,"runvi_fd_data");

}
