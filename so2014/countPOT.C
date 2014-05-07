
Double_t countPOTFromFile(char *inFile)
{

  char filename[180];
  ifstream FileList(inFile);
  Double_t totalPOT=0;
  while(FileList >> filename) {
    TFile fp(filename);
    if(fp.Get("s")) {
      //Tree exist
      TH1F *hTotalPot = (TH1F*)fp.Get("hTotalPot");
      totalPOT+=hTotalPot->Integral();      
    }
  }
  std::cout << "\n\n" << totalPOT << "\n";
  return totalPOT;

}

void countPOTNDData() {
  //FD Data
  int doRun[10]={1,1,1,1,1,1,1,0,1,1};
  char *ndDataFilePaths[10]={"/minos/data/analysis/NuMuBar/DSTs/2010/R2.2/Data/near/dogwood3/RunI/micro2010/NuDSTMicro*.root",
			    "/minos/data/analysis/NuMuBar/DSTs/2010/R2.2/Data/near/dogwood3/RunII/micro2010/NuDSTMicro*.root",
			    "/minos/data/analysis/NuMuBar/DSTs/2010/R2.2/Data/near/dogwood3/RunIII/micro2010/NuDSTMicro*.root",
			    "/minos/data/analysis/NuMuBar/DSTs/2012/R2.7_2011_09_07/sam/data/near/run4/dogwood3/microDSTs/NuDSTMicro2010*.root",
			    "/minos/data/analysis/NuMuBar/DSTs/2012/R2.10/sam/Data/CCselection/near/dogwood5/run5/NuDSTMicro*",
			    "/minos/data/analysis/NuMuBar/DSTs/2012/R2.10/sam/Data/CCselection/near/dogwood5/run6/NuDSTMicro*",
			    "/minos/data/analysis/NuMuBar/DSTs/2012/R2.7_2011_09_07/sam/data/near/run7/dogwood5/microDSTs/NuDSTMicro*.root"
			     ,0,
			     "/minos/data/analysis/NuMuBar/DSTs/2012/R2.7_2011_09_07/sam/data/near/run9/dogwood5/microDSTs/NuDSTMicro*.root",
			    "/minos/data/analysis/NuMuBar/DSTs/2012/R2.10/sam/Data/CCselection/near/dogwood5/run10/NuDSTMicro*"			    
  };
    
  char *execCommand[180];
  char fileList[180];
  Double_t ndDataPot[10];
  for(int runInd=0;runInd<10;runInd++) {
    if(!doRun[runInd]) continue;
    sprintf(execCommand,"rm -f runList%d.txt",runInd+1);
    gSystem->Exec((const char*)execCommand);
    sprintf(execCommand,"ls %s > runList%d.txt",ndDataFilePaths[runInd],runInd+1);
    gSystem->Exec((const char*)execCommand);
    sprintf(fileList,"runList%d.txt",runInd+1);
    
    ndDataPot[runInd]=countPOTFromFile(fileList);
  }



  char outName[180];


  for(int runInd=0;runInd<10;runInd++) {
    if(!doRun[runInd]) continue;
    std::cout << "Run " << runInd+1 << " ND Data POT " << ndDataPot[runInd] << "\n";

    sprintf(outName,"run%dNDDataPOT.txt",runInd+1);
    std::ofstream Out(outName);
    Out << ndDataPot[runInd] << "\n";
    Out.close();
  }
  
}


void countPOTNDMC() {
  //ND MC
  int doRun[10]={1,1,1,1,1,1,1,0,1,1};
  // char *ndMCFilePaths[10]={"/minos/data/analysis/NuMuBar/DSTs/2010/R2.2/MC/D07_dogwood3/near/r1/AllIntensities/micro2010/NuDSTMicro*.root",
  // 			   "/minos/data/analysis/NuMuBar/DSTs/2010/R2.2/MC/D07_dogwood3/near/r2/AllIntensities/micro2010/NuDSTMicro*.root",
  // 			   "/minos/data/analysis/NuMuBar/DSTs/2010/R2.2/MC/D07_dogwood3/near/r3/AllIntensities/micro2010/NuDSTMicro*.root",
  // 			   "/minos/data/analysis/NuMuBar/DSTs/2011/R2.7_2011-09-07/sam/MC/near/Daikon07_Dogwood3/r4/sam/micro2010/NuDSTMicro*.root",
  // 			   "/minos/data/analysis/NuMuBar/DSTs/2012/R2.10/sam/mc/CCselection/manualRun_period/D07_dogwood3/run5/r3/*/NuDSTMicro*.root",
  // 			   "/minos/data/analysis/NuMuBar/DSTs/2012/R2.10/sam/mc/CCselection/manualRun_period/D07_dogwood3/run6/r3/*/NuDSTMicro*.root",
  // 			   "/minos/data/analysis/NuMuBar/DSTs/2011/R2.7_2011-09-07/sam/MC/near/Daikon07_Dogwood3/r4/sam/micro2010/NuDSTMicro*.root",
  // 			   0,
  // 			   "/minos/data/analysis/NuMuBar/DSTs/2011/R2.7_2011-09-07/sam/MC/near/Daikon07_Dogwood3/r4/sam/micro2010/NuDSTMicro*.root",
  // 			   "/minos/data/analysis/NuMuBar/DSTs/2012/R2.10/sam/mc/CCselection/manualRun_period/D07_dogwood3/run10/r3/*/NuDSTMicro*.root"};
  char *ndMCFilePaths[10]={"/minos/data/analysis/NuMuBar/DSTs/2010/R2.2/MC/D07_dogwood3/near/r1/AllIntensities/micro2010/NuDSTMicro*.root",
			   "/minos/data/analysis/NuMuBar/DSTs/2010/R2.2/MC/D07_dogwood3/near/r2/AllIntensities/micro2010/NuDSTMicro*.root",
			   "/minos/data/analysis/NuMuBar/DSTs/2010/R2.2/MC/D07_dogwood3/near/r3/AllIntensities/micro2010/NuDSTMicro*.root",
			   "/minos/data/analysis/NuMuBar/DSTs/2011/R2.7_2011-09-07/sam/MC/near/Daikon07_Dogwood3/r4/sam/micro2010/NuDSTMicro*.root",
			   "/minos/data/analysis/NuMuBar/DSTs/2010/R2.2/MC/D07_dogwood3/near/r3/AllIntensities/micro2010/NuDSTMicro*.root",
			   "/minos/data/analysis/NuMuBar/DSTs/2010/R2.2/MC/D07_dogwood3/near/r3/AllIntensities/micro2010/NuDSTMicro*.root",
			   
			   "/minos/data/analysis/NuMuBar/DSTs/2011/R2.7_2011-09-07/sam/MC/near/Daikon07_Dogwood3/r4/sam/micro2010/NuDSTMicro*.root",
			   0,
			   "/minos/data/analysis/NuMuBar/DSTs/2011/R2.7_2011-09-07/sam/MC/near/Daikon07_Dogwood3/r4/sam/micro2010/NuDSTMicro*.root",
			   "/minos/data/analysis/NuMuBar/DSTs/2010/R2.2/MC/D07_dogwood3/near/r3/AllIntensities/micro2010/NuDSTMicro*.root"};

  
    
  char *execCommand[180];
  char fileList[180];
  Double_t ndMCPot[10];
  for(int runInd=0;runInd<10;runInd++) {
    if(!doRun[runInd]) continue;
    sprintf(execCommand,"rm -f runList%d.txt",runInd+1);
    gSystem->Exec((const char*)execCommand);
    sprintf(execCommand,"ls %s > runList%d.txt",ndMCFilePaths[runInd],runInd+1);
    gSystem->Exec((const char*)execCommand);
    sprintf(fileList,"runList%d.txt",runInd+1);
    
    ndMCPot[runInd]=countPOTFromFile(fileList);
  }


  char outName[180];

  for(int runInd=0;runInd<10;runInd++) {
    if(!doRun[runInd]) continue;
    std::cout << "Run " << runInd+1 << " ND MC POT " << ndMCPot[runInd] << "\n";
    sprintf(outName,"run%dNDMCPOT.txt",runInd+1);
    std::ofstream Out(outName);
    Out << ndMCPot[runInd] << "\n";
    Out.close();
  }
  


}





void countPOTFDMC() {
  //FD MC
  int doRun[10]={1,1,1,1,1,1,1,0,1,1};
  char *fdMCFilePaths[4]={"/minos/data/analysis/NuMuBar/DSTs/2010/R2.2/MC/D07_dogwood3/far/r1/micro2010/NuDSTMicro*.root",
			   "/minos/data/analysis/NuMuBar/DSTs/2010/R2.2/MC/D07_dogwood3/far/r2/micro2010/NuDSTMicro*.root",
			  "/minos/data/analysis/NuMuBar/DSTs/2010/R2.2/MC/D07_dogwood3/far/r3/micro2010/NuDSTMicro*.root",
			  "/minos/data/analysis/NuMuBar/DSTs/2011/R2.7_2011-09-07/sam/MC/far/Daikon07_Dogwood3/r4/micro2010/NuDSTMicro2010*.root"
			  };

    
  char *execCommand[180];
  char fileList[180];
  Double_t fdMCPot[10];
  for(int runInd=0;runInd<4;runInd++) {
    if(!doRun[runInd]) continue;
    sprintf(execCommand,"rm -f runList%d.txt",runInd+1);
    gSystem->Exec((const char*)execCommand);
    sprintf(execCommand,"ls %s > runList%d.txt",fdMCFilePaths[runInd],runInd+1);
    gSystem->Exec((const char*)execCommand);
    sprintf(fileList,"runList%d.txt",runInd+1);
    
    fdMCPot[runInd]=countPOTFromFile(fileList);
  }

char outName[180];

  for(int runInd=0;runInd<10;runInd++) {
    if(!doRun[runInd]) continue;
    int tempInd=runInd;
    if(tempInd==4 || tempInd==5 || tempInd==9) tempInd=2;
    if(tempInd==6 || tempInd==8) tempInd=3;
    
    std::cout << "Run " << runInd+1 << " FD MC POT " << fdMCPot[tempInd] << "\n";
    sprintf(outName,"run%dFDMCPOT.txt",runInd+1);
    std::ofstream Out(outName);
    Out << fdMCPot[tempInd] << "\n";
    Out.close();
  }

  
}


void countPOTFDTauMC() {
  //FD MC
  int doRun[10]={1,1,1,1,1,1,1,0,1,1};
  char *fdMCFilePaths[4]={"/minos/data/analysis/NuMuBar/DSTs/2010/R2.2/MC/D07_dogwood3/tau/r1/micro2010/NuDSTMicro*.root",
			   "/minos/data/analysis/NuMuBar/DSTs/2010/R2.2/MC/D07_dogwood3/tau/r2/micro2010/NuDSTMicro*.root",
			  "/minos/data/analysis/NuMuBar/DSTs/2010/R2.2/MC/D07_dogwood3/tau/r3/micro2010/NuDSTMicro*.root",
"/minos/data/analysis/NuMuBar/DSTs/2011/R2.7_2011-09-07/sam/MC/far/Daikon07_Dogwood3/tau/r4/micro2010/NuDSTMicro2010*"};
    
  char *execCommand[180];
  char fileList[180];
  Double_t fdMCPot[10];
  for(int runInd=0;runInd<4;runInd++) {
    if(!doRun[runInd]) continue;
    sprintf(execCommand,"rm -f runList%d.txt",runInd+1);
    gSystem->Exec((const char*)execCommand);
    sprintf(execCommand,"ls %s > runList%d.txt",fdMCFilePaths[runInd],runInd+1);
    gSystem->Exec((const char*)execCommand);
    sprintf(fileList,"runList%d.txt",runInd+1);
    
    fdMCPot[runInd]=countPOTFromFile(fileList);
    sprintf(execCommand,"rm -f runList%d.txt",runInd+1);
    gSystem->Exec((const char*)execCommand);
  }

  char outName[180];

  for(int runInd=0;runInd<10;runInd++) {
    if(!doRun[runInd]) continue;
    int tempInd=runInd;

    if(tempInd==4 || tempInd==5 || tempInd==9) tempInd=2;
    if(tempInd==6 || tempInd==8) tempInd=3;

    std::cout << "Run " << runInd+1 << " FD Tau MC POT " << fdMCPot[tempInd] << "\n";
    sprintf(outName,"run%dFDTauMCPOT.txt",runInd+1);
    std::ofstream Out(outName);
    Out << fdMCPot[tempInd] << "\n";
    Out.close();
  }  
}


void countPOTFDNueMC() {
  //FD MC
  int doRun[10]={1,1,1,0,1,1,0,0,0,1};
  char *fdMCFilePaths[4]={"/minos/data/analysis/NuMuBar/DSTs/2010/R2.2/MC/D07_dogwood3/nue/r1/NuDSTMicro*.root",
			   "/minos/data/analysis/NuMuBar/DSTs/2010/R2.2/MC/D07_dogwood3/nue/r2/NuDSTMicro*.root",
			  "/minos/data/analysis/NuMuBar/DSTs/2010/R2.2/MC/D07_dogwood3/nue/r3/NuDSTMicro*.root"};
    
  char *execCommand[180];
  char fileList[180];
  Double_t fdMCPot[10];
  for(int runInd=0;runInd<4;runInd++) {
    if(!doRun[runInd]) continue;
    sprintf(execCommand,"rm -f runList%d.txt",runInd+1);
    gSystem->Exec((const char*)execCommand);
    sprintf(execCommand,"ls %s > runList%d.txt",fdMCFilePaths[runInd],runInd+1);
    gSystem->Exec((const char*)execCommand);
    sprintf(fileList,"runList%d.txt",runInd+1);
    
    fdMCPot[runInd]=countPOTFromFile(fileList);
    sprintf(execCommand,"rm -f runList%d.txt",runInd+1);
    gSystem->Exec((const char*)execCommand);
  }

  char outName[180];

  for(int runInd=0;runInd<10;runInd++) {
    if(!doRun[runInd]) continue;
    int tempInd=runInd;
    if(tempInd>3) tempInd=2;
    std::cout << "Run " << runInd+1 << " FD Nue MC POT " << fdMCPot[tempInd] << "\n";
    sprintf(outName,"run%dFDNueMCPOT.txt",runInd+1);
    std::ofstream Out(outName);
    Out << fdMCPot[tempInd] << "\n";
    Out.close();
  }  
}


void countPOT()
{
  //  countPOTFDTauMC();
  //  countPOTNDData();
}

