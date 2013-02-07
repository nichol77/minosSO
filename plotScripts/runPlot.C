

void runPlot() {
  gSystem->AddIncludePath("-I./include");
  gSystem->Load("lib/libOscillation.so");
  //  gSystem->CompileMacro("src/OscCalc.C","k");
  gSystem->CompileMacro("plotScripts/plotNumberOfEvents.C","k");
  plotNumberOfEvents();

}
