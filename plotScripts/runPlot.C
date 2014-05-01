

void runPlot(double L=735, double E=2) {
  gSystem->AddIncludePath("-I./include");
  gSystem->Load("lib/libOscillation.so");
  //  gSystem->CompileMacro("src/OscCalc.C","k");
  gSystem->CompileMacro("plotScripts/plotNumberOfEvents.C","k");
  plotNumberOfEvents(L,E);

}
