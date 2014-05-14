#include "plotScripts/plotUtils.h"




void plotDistortedContours() {
   TFile *fpDefault= TFile::Open("fakeSurfaces/fakeSurface_run11_scale1000_fake_28_39_0_0.root");
   TFile *fpDistorted= TFile::Open("fakeSurfaces/fakeSurface_run11_distorted_scale1000_fake_28_39_0_0.root");

   TH2D *histDefaultInverted = (TH2D*) fpDefault->Get("histInverted_histEnergyNQ_0_0");
   TH2D *histDistortedInverted = (TH2D*) fpDistorted->Get("histInverted_histEnergyNQ_0_0");

   histDefaultInverted->Scale(1./1000);
   histDistortedInverted->Scale(1./1000);


   TH2D *contDefault = getContours(histDefaultInverted,2);
   TH2D *contDistorted = getContours(histDistortedInverted,2);


   TCanvas *can = new TCanvas("can","can",800,600);
   contDefault->SetLineColor(kBlack);
   contDistorted->SetLineColor(kRed);

   
   //   histDistortedInverted->SetTitle("");
   //  histDistortedInverted->GetXaxis()->SetTitle("#theta_{23}");
   //   histDistortedInverted->GetYaxis()->SetTitle("#Delta m^{2}_{23} (#times 10^{-3} eV^{2})");
   contDefault->SetTitle("");
   contDefault->GetXaxis()->SetTitle("#theta_{23}");
   contDefault->GetYaxis()->SetTitle("#Delta m^{2}_{23} (#times 10^{-3} eV^{2})");
   //   histDistortedInverted->Draw("COLZ");
   contDefault->Draw("cont3");
   contDistorted->Draw("cont3 same");
   TMarker *bfDefault=drawBestFit(contDefault);
   TMarker *bfDistorted=drawBestFit(contDistorted);

   TLegend *leggy = new TLegend(0.73,0.73,0.9,0.9);
   leggy->SetFillColor(0);
   leggy->SetFillStyle(0);
   leggy->SetBorderSize(0);
   leggy->AddEntry(contDefault,"Default 90%","l");
   leggy->AddEntry(bfDefault,"Best Fit","p");
   leggy->AddEntry(contDistorted,"Coil Syst. 90%","l");
   leggy->AddEntry(bfDistorted,"Best Fit","p");
   leggy->Draw("same");

}



