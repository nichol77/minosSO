

void plotNearThings() 
{
  TFile *fp = new TFile("nearFiles/runi_nd_mc.root");

  TH2D *histRecoTrueCC_CC_runi_nd_mc = (TH2D*) fp->Get("histRecoTrueCC_CC_runi_nd_mc");
  TH1D *histRecoCC_CC = histRecoTrueCC_CC_runi_nd_mc->ProjectionX();
  TH1D *histTrueCC_CC = histRecoTrueCC_CC_runi_nd_mc->ProjectionY();


  TH2D *histRecoTrueNC_CC_runi_nd_mc = (TH2D*) fp->Get("histRecoTrueNC_CC_runi_nd_mc");
  TH1D *histRecoNC_CC = histRecoTrueNC_CC_runi_nd_mc->ProjectionX();
  TH1D *histTrueNC_CC = histRecoTrueNC_CC_runi_nd_mc->ProjectionY();

  TH2D *histRecoTrueNCTrack_CC_runi_nd_mc = (TH2D*) fp->Get("histRecoTrueNCTrack_CC_runi_nd_mc");
  TH1D *histRecoNCTrack_CC = histRecoTrueNCTrack_CC_runi_nd_mc->ProjectionX();
  TH1D *histTrueNCTrack_CC = histRecoTrueNCTrack_CC_runi_nd_mc->ProjectionY();


  TCanvas *can = new TCanvas("can","can",800,800);
  histTrueCC_CC->SetTitle("");
  histTrueCC_CC->SetLineColor(getNiceColour(0));
  histTrueCC_CC->SetLineWidth(3);
  histTrueCC_CC->GetXaxis()->SetTitle("True Energy (GeV)");
  histTrueCC_CC->GetXaxis()->SetRangeUser(0,20);
  histTrueCC_CC->GetYaxis()->SetTitle("#Events (arb. POT)");
  histTrueCC_CC->Draw();
  histTrueNC_CC->SetLineColor(getNiceColour(1));
  histTrueNC_CC->SetLineWidth(3);
  histTrueNC_CC->Draw("same");
  histTrueNCTrack_CC->SetLineColor(getNiceColour(2));
  histTrueNCTrack_CC->SetLineWidth(3);
  histTrueNCTrack_CC->Draw("same");


  TLegend *leggy = new TLegend(0.6,0.6,0.9,0.9);
  leggy->SetFillColor(0);
  leggy->SetFillStyle(0);
  leggy->SetBorderSize(0);
  leggy->AddEntry(histTrueCC_CC,"CC Selected","l");
  leggy->AddEntry(histTrueNC_CC,"NC w/o track","l");
  leggy->AddEntry(histTrueNCTrack_CC,"NC w/ track","l");
  leggy->Draw("same");

}
