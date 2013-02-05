

void runNuDstLooperRunXNDMC()
{

  gSystem->CompileMacro("src/OscCalc.C","k");
   gSystem->CompileMacro("src/NuDstLooper.C","k");
   TChain *theChain = new TChain("s");
   theChain->Add("/minos/data/analysis/NuMuBar/DSTs/2012/R2.10/sam/mc/CCselection/manualRun_period/D07_dogwood3/run10/r3/i124/NuDSTMicro*.root"); //Run X MC
   theChain->Add("/minos/data/analysis/NuMuBar/DSTs/2012/R2.10/sam/mc/CCselection/manualRun_period/D07_dogwood3/run10/r3/i191/NuDSTMicro*.root"); //Run X MC
   theChain->Add("/minos/data/analysis/NuMuBar/DSTs/2012/R2.10/sam/mc/CCselection/manualRun_period/D07_dogwood3/run10/r3/i213/NuDSTMicro*.root"); //Run X MC
   theChain->Add("/minos/data/analysis/NuMuBar/DSTs/2012/R2.10/sam/mc/CCselection/manualRun_period/D07_dogwood3/run10/r3/i224/NuDSTMicro*.root"); //Run X MC
   theChain->Add("/minos/data/analysis/NuMuBar/DSTs/2012/R2.10/sam/mc/CCselection/manualRun_period/D07_dogwood3/run10/r3/i232/NuDSTMicro*.root"); //Run X MC
   theChain->Add("/minos/data/analysis/NuMuBar/DSTs/2012/R2.10/sam/mc/CCselection/manualRun_period/D07_dogwood3/run10/r3/i243/NuDSTMicro*.root"); //Run X MC
   theChain->Add("/minos/data/analysis/NuMuBar/DSTs/2012/R2.10/sam/mc/CCselection/manualRun_period/D07_dogwood3/run10/r3/i257/NuDSTMicro*.root"); //Run X MC
   theChain->Add("/minos/data/analysis/NuMuBar/DSTs/2012/R2.10/sam/mc/CCselection/manualRun_period/D07_dogwood3/run10/r3/i282/NuDSTMicro*.root"); //Run X MC
   theChain->Add("/minos/data/analysis/NuMuBar/DSTs/2012/R2.10/sam/mc/CCselection/manualRun_period/D07_dogwood3/run10/r3/i303/NuDSTMicro*.root"); //Run X MC
   theChain->Add("/minos/data/analysis/NuMuBar/DSTs/2012/R2.10/sam/mc/CCselection/manualRun_period/D07_dogwood3/run10/r3/i324/NuDSTMicro*.root"); //Run X MC
   NuDstLooper fred(theChain);
   fred.MakeHistos("runx_nd_mc.root",0,"runx_nd_mc");

}
