

void runConcatanate(int firstRun, int secondRun)
{
   gSystem->CompileMacro("utilities/concatanatePredFiles2.C","k");
      concatanatePredFiles("/unix/minos1/rjn/ccPlusNc/farPreds/run1/",firstRun,secondRun,"runi_pred_main") ;   
   std::cout << firstRun << "\t" << secondRun << "\n";
   gApplication->Terminate();
}
