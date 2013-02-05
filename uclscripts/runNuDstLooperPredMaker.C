

void runNuDstLooperPredMaker(char *inputFile, char *outputFile, char *runTag, char *outTag)
{
  gSystem->CompileMacro("src/OscCalc.C","k");
  gSystem->CompileMacro("src/NuDstLooper.C","k");
  TChain *theChain = new TChain("s");
   //   theChain->Add("/minos/data/analysis/NuMuBar/DSTs/2010/R2.2/MC/D07_dogwood3/far/r1/micro2010/NuDSTMicro*.root");
  theChain->Add(inputFile);
  Long64_t nentries=theChain->GetEntries();
  if(nentries<=0) {
    std::cerr << "No entries in " << inputFile << "\n";
     gApplication->Terminate();
   }
   
  char histName[180];
  
  
  TFile *fpRat = new TFile("ndRatios/NDRatio.root");
  sprintf(histName,"histEnergyNQ_%s_nd_data_over_mc_ratio",runTag);
  TH1D *ndRatNQ = (TH1D*) fpRat->Get(histName);
  if(!ndRatNQ) {
    std::cerr << "Can't get " << histName << "\n";
    gApplication->Terminate();
  }
  sprintf(histName,"histEnergyPQ_%s_nd_data_over_mc_ratio",runTag);
  TH1D *ndRatPQ = (TH1D*) fpRat->Get(histName);
  if(!ndRatPQ) {
    std::cerr << "Can't get " << histName << "\n";
    gApplication->Terminate();
  }
  
  sprintf(histName,"histEnergyNC_%s_nd_data_over_mc_ratio",runTag);
  TH1D *ndRatNC = (TH1D*) fpRat->Get(histName);
  if(!ndRatNC) {
    std::cerr << "Can't get " << histName << "\n";
    gApplication->Terminate();
  }
  
  sprintf(histName,"histEnergyNCTrack_%s_nd_data_over_mc_ratio",runTag);
  TH1D *ndRatNCTrack = (TH1D*) fpRat->Get(histName);
  if(!ndRatNCTrack) {
    std::cerr << "Can't get " << histName << "\n";
    gApplication->Terminate();
  }
  
  
  
  NuDstLooper fred(theChain);
  fred.MakePredicitions(outputFile,ndRatNQ,ndRatPQ,ndRatNC,ndRatNCTrack,outTag); 


  gApplication->Terminate();
}
 
