
void plotTrackEffThingsLeigh() {

  plotTrackEffThings("trkEn + shwEnkNN","Neutrino Energy (GeV)",
		     "rw*((cutId==0 || cutId==128 || cutId==640 || cutId==512) )",
   		     "rw*((cutId==0 || cutId==512) )",
   		     "Track Fit Pass Eff.");
  

   // plotTrackEffThings("trkEn","Track Energy (GeV)","rw*(cutId==0 || cutId==128 || cutId==640 || cutId==512)",
   // 		     "rw*((cutId==0 || cutId==512) && ((xTrkEnd*xTrkEnd +yTrkEnd*yTrkEnd)>0.1))",
   // 		     "New Coil Hole Cut Eff.");

  // plotTrackEffThings("trkEn","Track Energy (GeV)","rw*(cutId==0 || cutId==128 || cutId==640 || cutId==512)",
  //   		     "rw*(cutId==0)",
  //   		     "New Coil Hole Cut Eff.");

  //  plotTrackEffThings("trkEn","Trk End - Evt Vtx (m)","rw*(cutId==0 || cutId==128 || cutId==640 || cutId==512)",
  //    		     "rw*(cutId==0)",
  //    		     "New Coil Hole Cut Eff.");
}



void plotTrackEffThings(char *plotString, char *xTitle,char *mcDenom, char *mcNumer, char *ratioTitle) {

   Double_t binEdge[]={0,0.5,0.75,1,1.25,1.5,1.75,2,2.25,2.5,2.75,3,3.25,3.5,3.75,4,4.25,4.5,4.75,5,5.25,5.5,5.75,6,6.25,6.5,6.75,7,7.25,7.5,7.75,8,8.25,8.5,8.75,9,9.25,9.5,9.75,10,10.25,10.5,10.75,11,11.25,11.5,11.75,12,12.25,12.5,12.75,13,13.25,13.5,13.75,14,14.25,14.5,14.75,15,15.25,15.5,15.75,16,16.25,16.5,16.75,17,17.25,17.5,17.75,18,18.25,18.5,18.75,19,19.25,19.5,19.75,20,21,22,23,24,25,26,27,28,29,30,32,34,36,38,40,42,44,46,48,50,200};

  std::ifstream inNDMCPot("pot/leighNDMC.txt");
  std::ifstream inNDDataPot("pot/leighNDData.txt");
  Double_t ndDataPot=0;   
  inNDDataPot >> ndDataPot;
  Double_t ndMCPot=0; 
  inNDMCPot >> ndMCPot;
  Double_t potScaleMC=1e17/ndMCPot;
  Double_t potScaleData=1e17/ndDataPot;

  TFile *fpNearMC = TFile::Open("nearFiles/trackTreeNDMCLeigh.root");
  TTree *trackTreeMC = (TTree*) fpNearMC->Get("trackTree");
  TH1D *histTrackEnMC = new TH1D("histTrackEnMC","histTrackEnMC",100,binEdge);
  TH1D *histTrackEnTrkFitPassMC = new TH1D("histTrackEnTrkFitPassMC","histTrackEnTrkFitPassMC",100,binEdge);
  
  trackTreeMC->Project("histTrackEnMC",plotString,mcDenom);
  trackTreeMC->Project("histTrackEnTrkFitPassMC",plotString,mcNumer);

  histTrackEnMC->Scale(potScaleMC);
  histTrackEnTrkFitPassMC->Scale(potScaleMC);


  TFile *fpNearData = TFile::Open("nearFiles/trackTreeNDDataLeigh.root");
  TTree *trackTreeData = (TTree*) fpNearData->Get("trackTree");
  TH1D *histTrackEnData = new TH1D("histTrackEnData","histTrackEnData",100,binEdge);
  TH1D *histTrackEnTrkFitPassData = new TH1D("histTrackEnTrkFitPassData","histTrackEnTrkFitPassData",100,binEdge);
  
  trackTreeData->Project("histTrackEnData",plotString,mcDenom);
  trackTreeData->Project("histTrackEnTrkFitPassData",plotString,mcNumer);

  histTrackEnData->Scale(potScaleData);
  histTrackEnTrkFitPassData->Scale(potScaleData);


  TCanvas *canTrackEn = new TCanvas("canTrackEn","canTrackEn",800,600);
  histTrackEnMC->SetTitle("");
  histTrackEnMC->SetXTitle(xTitle);
  histTrackEnMC->SetYTitle("Events / 10^{17} POT");
  //  histTrackEnMC->Draw();
  histTrackEnTrkFitPassMC->SetLineColor(getNiceColour(1));
  histTrackEnTrkFitPassMC->GetXaxis()->SetTitle(xTitle);
  histTrackEnTrkFitPassMC->GetXaxis()->SetRangeUser(0,20);
  histTrackEnTrkFitPassMC->Draw("");
  histTrackEnData->SetLineColor(getNiceColour(2));
  //  histTrackEnData->Draw("same");
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

  TFile *fpRatio = TFile::Open("ndRatios/NDRatioNew.root");
  TH1D *oldDataMC =(TH1D*) fpRatio->Get("histEnergyNQ_minosplus_nd_data_over_mc_ratio");
  oldDataMC->Draw("same");


  TH1D * newOldRatio = (TH1D*) finalDataMC->Clone("newOldRatio");
  newOldRatio->Divide(oldDataMC);
  newOldRatio->SetLineColor(kGreen+2);
  //  newOldRatio->Draw("same");


  TLegend *leggy2 =  makeLegendBoxInBottomRightCorner(0.3,0.3);
  leggy2->AddEntry(oldDataMC,"Default Data/MC");
  leggy2->AddEntry(finalDataMC,"Leigh Data/MC All Cuts","l");
  leggy2->AddEntry(initialDataMC,"Leigh Data/MC no coil+tfp","l");
  //  leggy2->AddEntry(newOldRatio,"New/Old Data/MC Double ","l");
  leggy2->Draw("same");
}
