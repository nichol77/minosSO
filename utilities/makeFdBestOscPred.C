
void makeFdBestOscPred(int dmBin=28, int t23Bin=39, int t13Bin=0, int deltaBin=0);


void makeFdBestOscPred(int dmBin, int t23Bin, int t13Bin, int deltaBin) ) {
  int runInd=10;
  Double_t binEdge[]={0,0.5,0.75,1,1.25,1.5,1.75,2,2.25,2.5,2.75,3,3.25,3.5,3.75,4,4.25,4.5,4.75,5,5.25,5.5,5.75,6,6.25,6.5,6.75,7,7.25,7.5,7.75,8,8.25,8.5,8.75,9,9.25,9.5,9.75,10,10.25,10.5,10.75,11,11.25,11.5,11.75,12,12.25,12.5,12.75,13,13.25,13.5,13.75,14,14.25,14.5,14.75,15,15.25,15.5,15.75,16,16.25,16.5,16.75,17,17.25,17.5,17.75,18,18.25,18.5,18.75,19,19.25,19.5,19.75,20,21,22,23,24,25,26,27,28,29,30,32,34,36,38,40,42,44,46,48,50,200};
  
  char dataPotName[180];
  char mcPotName[180];
  char histName[180];
  char fileName[180];
  char outName[180];
  

  const char *histNameArray[4]={"histEnergyNQ","histEnergyPQ","histEnergyNC","histEnergyNCTrack"};
  const char *predHistNameArray[4]={"histPredNQ","histPredPQ","histPredNC","histPredNCTrack"};


  const char *fileTypeTag[3]={"main","nue","tau"};
  const char *potFileTypeTag[3]={"","Nue","Tau"};

  const char *runNameArray[11]={"run1","run2","run3","run4","run5","run6","run7","run8","run9","run10","run11"};

  sprintf(dataPotName,"pot/%sFDDataPOT.txt",runNameArray[runInd]);
  
  
  std::ifstream DataPotFile(dataPotName);
  if(!DataPotFile) {
    std::cerr << "Can not open " << dataPotName << "\n";
    continue;
  }
  Double_t dataPOT=0;
  DataPotFile >> dataPOT;

  sprintf(outName,"/unix/minos1/rjn/so2014/rjnData/minosplus_fd_pred_%d_%d_%d_%d.root",dmBin,t23Bin,t13Bin,deltaBin);
  TFile *fpOut = new TFile(outName,"RECREATE");
  if(!fpOut) {
    std::cerr << "unable to create " << outName << "\n";
    continue;
  }
 
  TH1D *histOut[4]={0};
  TH1D *histIn[3][4]={{0}};
  Double_t numEvents[3][4]={{0}};
  
  //Loop over main, nue , tau
  for(int fileType=0;fileType<3;fileType++) { 
    sprintf(fileName,"farPreds/%s/%s%d.root",runNameArray[runInd],fileTypeTag[fileType],dmBin);
    
    TFile *fpIn = TFile::Open(fileName);
    if(!fpIn) {
      std::cerr << "Can't open " << fileName << "\n";
      continue;
    }

    sprintf(mcPotName,"pot/%sFD%sMCPOT.txt",runNameArray[runInd],potFileTypeTag[fileType]);
    
    std::ifstream McPotFile(mcPotName);
    if(!McPotFile) {
      std::cerr << "Can not open " << mcPotName << "\n";
      continue;
    }
    Double_t mcPOT=0;
    McPotFile >> mcPOT;
    Double_t scaleFactor=dataPOT/mcPOT;
    

    
    //Loop over hist types
    for(int histType=0;histType<4;histType++) {
      sprintf(histName,"/dmi%d/t23i%d/%s_%d_%d_%d_%d",dmBin,t23Bin,predHistNameArray[histType],dmBin,t23Bin,t13Bin,deltaBin);
      histIn[fileType][histType] = (TH1D*) fpIn->Get(histName);
      if(!histIn[fileType][histType]) {
	std::cerr << "Can not open " << histName << " from " << fileName << "\n";
	continue;
      }
      
      histIn[fileType][histType]->Scale(scaleFactor);

      if(histOut[histType]==0) {
	sprintf(histName,"%s_run11_pred_%d_%d_%d_%d",predHistNameArray[histType],dmBin,t23Bin,t13Bin,deltaBin);
	histOut[histType]=(TH1D*)histIn[fileType][histType]->Clone(histName);
	histOut[histType]->SetName(histName);
	histOut[histType]->SetTitle(histName);
      }
      else {
	histOut[histType]->Add(histIn[fileType][histType]);       
      }

      numEvents[fileType][histType]=histIn[fileType][histType]->Integral();
      std::cout << histName << "\t" <<numEvents[fileType][histType] << " events " << "\n";
      fpOut->cd();
      histIn[fileType][histType]->Write();
    }
  }
  
  
  for(int histType=0;histType<4;histType++) {
    std::cout << histOut[histType]->GetName() << "\t" << histOut[histType]->Integral() << "\n";
    histOut[histType]->Write();
  }
    
  
  fpOut->Close();


}
