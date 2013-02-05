

void runNuDstLooperRunVFDData()
{
  gSystem->CompileMacro("src/OscCalc.C","k");
   gSystem->CompileMacro("src/NuDstLooper.C","k");
   TChain *theChain = new TChain("s");
   theChain->Add("/minos/data/analysis/NuMuBar/AnalysisTools/fdConcatenatedBntps/Run5SecondAttempt/NuDSTMicro2010F00045490.root");
   NuDstLooper fred(theChain);
   fred.MakeHistos("runv_fd_data.root",1,"runv_fd_data");

}
