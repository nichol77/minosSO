
void plotTrackEffThings() {

   plotTrackEffThings("trkEn+shwEnkNN","Neutrino Energy (GeV)","rw*((cutId==0 || cutId==128 || cutId==640 || cutId==512) )",
   		     "rw*((cutId==0) )",
		      "All Cuts.");
  

   // plotTrackEffThings("trkEn","Track Energy (GeV)","rw*(cutId==0 || cutId==128 || cutId==640 || cutId==512)",
   // 		     "rw*((cutId==0 || cutId==512) && ((xTrkEnd*xTrkEnd +yTrkEnd*yTrkEnd)>0.1))",
   // 		     "New Coil Hole Cut Eff.");

  // plotTrackEffThings("trkEn","Track Energy (GeV)","rw*(cutId==0 || cutId==128 || cutId==640 || cutId==512)",
  //   		     "rw*(cutId==0)",
  //   		     "New Coil Hole Cut Eff.");

   //  plotTrackEffThings("zTrkEnd-zEvtVtx","Trk End - Evt Vtx (m)","rw*(cutId==0 || cutId==128 || cutId==640 || cutId==512)",
   //    		     "rw*(cutId==0)",
   //    		     "New Coil Hole Cut Eff.");
}



void plotTrackEffThings(char *plotString, char *xTitle,char *mcDenom, char *mcNumer, char *ratioTitle) {

  std::ifstream inNDMCPot("pot/run11NDMCPot.txt");
  std::ifstream inNDDataPot("pot/run11NDDataPot.txt");
  Double_t ndDataPot=0;   
  inNDDataPot >> ndDataPot;
  Double_t ndMCPot=0; 
  inNDMCPot >> ndMCPot;
  Double_t potScaleMC=1e17/ndMCPot;
  Double_t potScaleData=1e17/ndDataPot;

  TFile *fpNearMC = TFile::Open("nearFiles/trackTreeNDMC.root");
  TTree *trackTreeMC = (TTree*) fpNearMC->Get("trackTree");
  TH1D *histTrackEnMC = new TH1D("histTrackEnMC","histTrackEnMC",80,0,20);
  TH1D *histTrackEnTrkFitPassMC = new TH1D("histTrackEnTrkFitPassMC","histTrackEnTrkFitPassMC",80,0,20);
  
  trackTreeMC->Project("histTrackEnMC",plotString,mcDenom);
  trackTreeMC->Project("histTrackEnTrkFitPassMC",plotString,mcNumer);

  histTrackEnMC->Scale(potScaleMC);
  histTrackEnTrkFitPassMC->Scale(potScaleMC);


  TFile *fpNearData = TFile::Open("nearFiles/trackTreeNDData.root");
  TTree *trackTreeData = (TTree*) fpNearData->Get("trackTree");
  TH1D *histTrackEnData = new TH1D("histTrackEnData","histTrackEnData",80,0,20);
  TH1D *histTrackEnTrkFitPassData = new TH1D("histTrackEnTrkFitPassData","histTrackEnTrkFitPassData",80,0,20);
  
  trackTreeData->Project("histTrackEnData",plotString,mcDenom);
  trackTreeData->Project("histTrackEnTrkFitPassData",plotString,mcNumer);

  histTrackEnData->Scale(potScaleData);
  histTrackEnTrkFitPassData->Scale(potScaleData);


  TCanvas *canTrackEn = new TCanvas("canTrackEn","canTrackEn",800,600);
  histTrackEnMC->SetTitle("");
  histTrackEnMC->SetXTitle(xTitle);
  histTrackEnMC->SetYTitle("Events / 10^{17} POT");
  histTrackEnMC->Draw();
  histTrackEnTrkFitPassMC->SetLineColor(getNiceColour(1));
  histTrackEnTrkFitPassMC->Draw("same");
  histTrackEnData->SetLineColor(getNiceColour(2));
  histTrackEnData->Draw("same");
  histTrackEnTrkFitPassData->SetLineColor(getNiceColour(3));
  histTrackEnTrkFitPassData->Draw("same");

  
  TCanvas *canTrackEnEff = new TCanvas("canTrackEnEff","canTrackEnEff",800,600);
  canTrackEnEff->SetGridy();
  canTrackEnEff->SetGridx();
  TH1D *ratioTrkFitPassMC = (TH1D*) histTrackEnTrkFitPassMC->Clone("ratioTrkFitPassMC");
  ratioTrkFitPassMC->Divide(histTrackEnMC);
  ratioTrkFitPassMC->SetLineColor(getNiceColour(1));
  TH1D *ratioTrkFitPassData = (TH1D*) histTrackEnTrkFitPassData->Clone("ratioTrkFitPassData");
  ratioTrkFitPassData->Divide(histTrackEnData);
  ratioTrkFitPassMC->SetTitle("");
  ratioTrkFitPassMC->SetXTitle(xTitle);
  ratioTrkFitPassMC->SetYTitle(ratioTitle);
  ratioTrkFitPassMC->Draw();
  ratioTrkFitPassData->SetLineColor(kBlack);
  ratioTrkFitPassData->Draw("same");

  TH1D *doubleRatio = ratioTrkFitPassData->Clone("doubleRatio");
  doubleRatio->Divide(ratioTrkFitPassMC);
  doubleRatio->SetLineColor(getNiceColour(2));
  doubleRatio->Draw("same");
  


  TLegend *leggy = new TLegend(0.6,0.2,0.88,0.5);
  leggy->SetFillColor(0);
  leggy->SetFillStyle(0);
  leggy->SetBorderSize(0);
  leggy->AddEntry(ratioTrkFitPassData,"Data","l");
  leggy->AddEntry(ratioTrkFitPassMC,"MC","l");
  leggy->AddEntry(doubleRatio,"Data/MC","l");
  leggy->Draw("same");


  TCanvas *canOther = new TCanvas("canOther","canOther");
  TH1D *finalDataMC = (TH1D*) histTrackEnTrkFitPassData->Clone("finalDataMC");
  finalDataMC->Divide(histTrackEnTrkFitPassMC);
  finalDataMC->SetLineColor(getNiceColour(3));
  finalDataMC->SetTitle("");
  finalDataMC->SetYTitle("Data/MC");
  finalDataMC->SetXTitle(xTitle);
  finalDataMC->Draw("");

  TH1D *initialDataMC = (TH1D*) histTrackEnData->Clone("initialDataMC");
  initialDataMC->Divide(histTrackEnMC);
  initialDataMC->SetLineColor(getNiceColour(4));
  initialDataMC->Draw("same");  
  TLegend *leggy2 =  makeLegendBoxInBottomRightCorner(0.3,0.3);
  leggy2->AddEntry(finalDataMC,"Data/MC All Cuts","l");
  leggy2->AddEntry(initialDataMC,"Data/MC no coil+tfp","l");
  leggy2->Draw("same");
}
