

TLegend *leggyMC[4];
TLegend *leggyData[4];
TLegend *leggyRatio[4];

TCanvas *canDataArray[4];
TCanvas *canMCArray[4];
TCanvas *canRatioArray[4];

void makeNearRatios()
{

  TCanvas *canNQData = new TCanvas("canNQData","canNQData",800,500);
  TCanvas *canNQMC = new TCanvas("canNQMC","canNQMC",800,500);
  TCanvas *canPQData = new TCanvas("canPQData","canPQData",800,500);
  TCanvas *canPQMC = new TCanvas("canPQMC","canPQMC",800,500);
  TCanvas *canNCData = new TCanvas("canNCData","canNCData",800,500);
  TCanvas *canNCMC = new TCanvas("canNCMC","canNCMC",800,500);
  TCanvas *canNCTrackData = new TCanvas("canNCTrackData","canNCTrackData",800,500);
  TCanvas *canNCTrackMC = new TCanvas("canNCTrackMC","canNCTrackMC",800,500);
  TCanvas *canPQRat = new TCanvas("canPQRat","canPQRat",800,500);
  TCanvas *canNQRat = new TCanvas("canNQRat","canNQRat",800,500);
  TCanvas *canNCRat = new TCanvas("canNCRat","canNCRat",800,500);
  TCanvas *canNCTrackRat = new TCanvas("canNCTrackRat","canNCTrackRat",800,500);

  canDataArray[0]=canNQData;
  canDataArray[1]=canPQData;
  canDataArray[2]=canNCData;
  canDataArray[3]=canNCTrackData;

  canMCArray[0]=canNQMC;
  canMCArray[1]=canPQMC;
  canMCArray[2]=canNCMC;
  canMCArray[3]=canNCTrackMC;

  canRatioArray[0]=canNQRat;
  canRatioArray[1]=canPQRat;
  canRatioArray[2]=canNCRat;
  canRatioArray[3]=canNCTrackRat;


  // doARun("runI","runi",1,1,"Run I");
  // doARun("runII","runii",0,2,"Run II");
  // doARun("runIII","runiii",0,3,"Run III");
  // doARun("runV","runv",0,4,"Run V");
  // doARun("runVI","runvi",0,5,"Run VI");
  // doARun("runX","runx",0,6,"Run X");
  doARun("run11","minosplus",1,1,"MINOS+");

}



void doARun(char *potTag, char *fileTag, int firstOne, int colourNum,char *legTag) {
  Double_t potData;
  Double_t potMC;
  char dataPotFilename[180];
  char mcPotFilename[180];
  sprintf(dataPotFilename,"pot/%sNDDataPOT.txt",potTag);
  sprintf(mcPotFilename,"pot/%sNDMCPOT.txt",potTag);

  ifstream DataPOT(dataPotFilename);
  if(!DataPOT) {
    std::cerr << "Can't open " << dataPotFilename << "\n";
    return;
  }
  ifstream MCPOT(mcPotFilename);
  if(!MCPOT) {
    std::cerr << "Can't open " << mcPotFilename << "\n";
    return;
  }

  //Get the POT
  DataPOT >> potData;
  MCPOT >> potMC;

  //Now open the data and MC files and get the relevant histograms
  char dataFileName[180];
  char mcFileName[180];
  char histName[180];
  sprintf(dataFileName,"nearFiles/%s_nd_data.root",fileTag);
  sprintf(mcFileName,"nearFiles/%s_nd_mc.root",fileTag);

  TFile *fpData = TFile::Open(dataFileName);
  if(!fpData) {
    std::cerr < "Couldn't open " << dataFileName << "\n";
    return;
  }
  TFile *fpMC = TFile::Open(mcFileName);
  if(!fpMC) {
    std::cerr < "Couldn't open " << mcFileName << "\n";
    return;
  }

  char *histNameArray[4]={"histEnergyNQ","histEnergyPQ","histEnergyNC","histEnergyNCTrack"};
  char *plotTitleArray[4]={"ND (q<0)","ND (q>0)","ND NC","ND NC (with track)"};

  char histName[180];
  

  
  TFile *fpRat = 0;
  if(firstOne) fpRat=new TFile("ndRatios/NDRatioNew.root","RECREATE");
  else fpRat= new TFile("ndRatios/NDRatioNew.root","UPDATE");
  


  for(int histNum=0;histNum<4;histNum++) {
    sprintf(histName,"%s_%s_nd_data",histNameArray[histNum],fileTag);
    TH1D *histData = (TH1D*) fpData->Get(histName);
    if(!histData) {
      std::cerr << "Couldn't get " << histName << "\n";
      return;      
    }
    sprintf(histName,"%s_%s_nd_mc",histNameArray[histNum],fileTag);
    TH1D *histMC = (TH1D*) fpMC->Get(histName);
    if(!histMC) {
      std::cerr << "Couldn't get " << histName << "\n";
      return;      
    }
    
    fpRat->cd();
    sprintf(histName,"%s_%s_nd_data_over_mc_ratio",histNameArray[histNum],fileTag);
    TH1D *histRatio=histData->Clone(histName);
    histRatio->Scale(1e18/potData);
    histMC->Scale(1e18/potMC);
    histData->Scale(1e18/potData);
    histRatio->Divide(histMC);
    histRatio->Write();
    
    char plotTitle[180];
    
    canDataArray[histNum]->cd();    
    histData->SetLineColor(getNiceColour(colourNum));
    sprintf(plotTitle,"Data -- %s",plotTitleArray[histNum]);
    histData->SetTitle(plotTitle);
    histData->GetXaxis()->SetTitle("Reconstructed Energy (GeV)");
    histData->GetXaxis()->SetRangeUser(0,19.5);
    histData->GetYaxis()->SetTitle("Events per 1e18 POT");
    histData->SetStats(0);
    if(firstOne) histData->Draw();
    else histData->Draw("same");

    if(firstOne) {
      leggyData[histNum] = new TLegend(0.6,0.6,0.9,0.9);
      leggyData[histNum]->SetBorderSize(0);
      leggyData[histNum]->SetFillStyle(0);
    }
    leggyData[histNum]->AddEntry(histData,legTag,"l");
    leggyData[histNum]->Draw();

    canMCArray[histNum]->cd();    
    histMC->SetLineColor(getNiceColour(colourNum));
    sprintf(plotTitle,"MC -- %s",plotTitleArray[histNum]);
    histMC->SetTitle(plotTitle);
    histMC->GetXaxis()->SetTitle("Reconstructed Energy (GeV)");
    histMC->GetXaxis()->SetRangeUser(0,19.5);
    histMC->GetYaxis()->SetTitle("Events per 1e18 POT");
    histMC->SetStats(0);
    if(firstOne)
      histMC->Draw();
    else
      histMC->Draw("same");


    if(firstOne) {
      leggyMC[histNum] = new TLegend(0.6,0.6,0.9,0.9);
      leggyMC[histNum]->SetBorderSize(0);
      leggyMC[histNum]->SetFillStyle(0);
    }
    leggyMC[histNum]->AddEntry(histMC,legTag,"l");
    leggyMC[histNum]->Draw();


  // leggyPQMC = new TLegend(0.6,0.6,0.9,0.9);
  // leggyPQMC->SetBorderSize(0);
  // leggyPQMC->SetFillStyle(0);
  // leggyPQMC->AddEntry(histPQMc,"Run I","l");

    canRatioArray[histNum]->cd();
    histRatio->SetLineColor(getNiceColour(colourNum));
    sprintf(plotTitle,"Data/MC -- %s",plotTitleArray[histNum]);
    histRatio->SetTitle(plotTitle);
    histRatio->GetXaxis()->SetTitle("Reconstructed Energy (GeV)");
    histRatio->GetXaxis()->SetRangeUser(0,19.5);
    histRatio->GetYaxis()->SetTitle("Ratio");
    histRatio->GetYaxis()->SetRangeUser(0.5,2);
    histRatio->SetStats(0);
    if(firstOne) 
      histRatio->Draw();
    else
      histRatio->Draw("same");

    if(firstOne) {
      if(histNum<2) {
	leggyRatio[histNum] = new TLegend(0.6,0.6,0.9,0.9);
      }
      else {
	leggyRatio[histNum] = new TLegend(0.6,0.2,0.9,0.5);
      }	
      leggyRatio[histNum]->SetBorderSize(0);
      leggyRatio[histNum]->SetFillStyle(0);
    }
    leggyRatio[histNum]->AddEntry(histRatio,legTag,"l");
    leggyRatio[histNum]->Draw();

  }
  fpRat->Close();

}
