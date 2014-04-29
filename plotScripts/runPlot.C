


void runPlot() {
  gSystem->CompileMacro("src/OscCalc.C","k");
  gSystem->CompileMacro("plotScripts/plotNumberOfEvents.C","k");
  plotNumberOfEvents();

}
