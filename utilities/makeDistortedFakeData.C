

void makeDistortedFakeData(int dmBin, int t23Bin, int t13Bin, int deltaBin, int numExperiments, int potScale) {
   
   TFile *fpIn = TFile::Open("/home/rjn/minos/ccPlusNc/so2014/ndDoubleRatioCoilCurv.root");
   TH1D *scaleHists[4];
   scaleHists[0]=(TH1D*) fpIn->Get("doubleRatioNQ");
   scaleHists[1]=(TH1D*) fpIn->Get("doubleRatioPQ");
   scaleHists[2]=(TH1D*) fpIn->Get("doubleRatioPQ");
   scaleHists[3]=(TH1D*) fpIn->Get("doubleRatioPQ");
   
   
   gSystem->CompileMacro("/home/rjn/minos/ccPlusNc/utilities/makeFakeData.C","k");
   makeFakeData(dmBin,t23Bin,t13Bin,deltaBin,numExperiments,potScale,scaleHists);



}
