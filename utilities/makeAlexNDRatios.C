


void makeAlexNDRatios() {

  for(int i=0;i<1000;i++)
    makeThisRatio("nearHornCurrNorm",i);

}



void makeThisRatio(char *fileTag,int runNum) {


  TFile *fpRealData = TFile::Open("/home/rjn/minos/ccPlusNc/so2014/minosplus_nd_data.root");
  TH1D *histEnergyNQReal = (TH1D*) fpRealData->Get("histEnergyNQ_minosplus_nd_data");
  TH1D *histEnergyPQReal = (TH1D*) fpRealData->Get("histEnergyPQ_minosplus_nd_data");

  if(!histEnergyNQReal) {
    std::cerr << "Can't get data histogram\n";
    return;
  }
  
  std::ifstream inNDDataPot("/home/rjn/minos/ccPlusNc/pot/run11NDDataPot.txt");
  Double_t ndDataPot=0;   
  inNDDataPot >> ndDataPot;
  histEnergyNQReal->Scale(1e17/ndDataPot);
  histEnergyPQReal->Scale(1e17/ndDataPot);


  
  char fileName[180];
  sprintf(fileName,"/unix/minos1/rjn/altHornCurr/%s_%d.root",fileTag,runNum);
  TFile *fpFake = TFile::Open(fileName);
  if(!fpFake) {
    std::cerr << "No Fake File\n";
    return;
  }
  TH1D *histEnergyNQFake = (TH1D*) fpFake->Get("RecoEnergy_ND");
  TH1D *histEnergyPQFake = (TH1D*) fpFake->Get("RecoEnergyPQ_ND");
  TH1D *hTotalPotFake = (TH1D*) fpFake->Get("hTotalPot");

  if(!histEnergyNQFake) {
    std::cerr << "Can't get data histogram\n";
    return;
  }

  Double_t ndFakePot = hTotalPotFake->Integral();
  histEnergyNQFake->Scale(1e17/ndFakePot);
  histEnergyPQFake->Scale(1e17/ndFakePot);


  sprintf(fileName,"/unix/minos1/rjn/altHornCurr/ratios/%s_rat_%d.root",fileTag,runNum);
  TFile *fpRatio = TFile::Open(fileName,"RECREATE");
  TH1D *ratioNQ = (TH1D*) histEnergyNQFake->Clone("ratioNQ");
  ratioNQ->Divide(histEnergyNQReal);
  ratioNQ->SetName("ratioNQ");
  ratioNQ->Write();
  TH1D *ratioPQ = (TH1D*) histEnergyPQFake->Clone("ratioPQ");
  ratioPQ->Divide(histEnergyPQReal);
  ratioPQ->SetName("ratioPQ");
  ratioPQ->Write();
  fpRatio->Close();
  fpFake->Close();
  fpRealData->Close();

}
