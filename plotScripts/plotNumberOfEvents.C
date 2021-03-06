#include "AtNuAna/Oscillation/OscCalc.h"
//#include "src/OscCalc.h"
#include "TMath.h"
#include "TCanvas.h"
#include "TGraph.h"
#include "TF1.h"
#include "TBox.h"
#include "TH1.h"
#include "TLegend.h"

TGraph *getShadedGraph(TCanvas *c1, TF1 *f1, TF1 *f2);
Double_t oscFuncVsT23(Double_t *x, Double_t *par);
Double_t diffFuncVsT23(Double_t *x, Double_t *par) ;
Double_t oscFuncVsDelta(Double_t *x, Double_t *par);
void plotNumberOfNumuEvents();
void plotNumberOfNueEvents(double L, double E);


OscCalc fOscCalc;
Int_t inu,inunoosc;

void plotNumberOfEvents(double L, double E)
{
  //  plotNumberOfNumuEvents();
  plotNumberOfNueEvents(L,E);

}


void plotNumberOfNumuEvents() {

  int doAntiNu=0;

   Double_t oscPar[12]={0};
   oscPar[OscPar::kL]=735; // km //MINOS
   //   oscPar[OscPar::kL]=810; // km //NOvA
   //oscPar[OscPar::kL]=2300; // km //LBNO
   
   oscPar[OscPar::kL]=1300; //km //LBNE
   oscPar[OscPar::kTh23]=0.705; //From PDG, extracted from sin^2(theta_23)=0.42, will loop over this
   oscPar[OscPar::kTh12]=0.586; /// From PDG, extracted from sin^2(theta_12) = 0.306
   oscPar[OscPar::kTh13]=0.159; // From PDG, extracted from sin^2(theta_13) = 0.0251
   oscPar[OscPar::kDeltaM23]=2.38e-3; // in eV^2 will loop over
   oscPar[OscPar::kDeltaM12]=7.58e-5; // in eV^2
   oscPar[OscPar::kDelta]=0; //Fix at zero for now
   oscPar[OscPar::kDensity]=1.470; //In some units
   oscPar[OscPar::kNuAntiNu]=1; // 1 for neutrinos, -1 for antineutrinos
   oscPar[9]=3; //Energy in GeV
   oscPar[10]=1; //Normalisation
   oscPar[11]=-2.46e-3; //IH dm23
   if(doAntiNu) {
     inu=-14;
     inunoosc=-14;
   }
   else {
     inu=14;
     inunoosc=14;
   }


   //   oscPar[OscPar::kDeltaM23]=-2.44e-3; // in eV^2 will loop over
   //   TCanvas *canDelta = new TCanvas();
   //   TF1 *funcDelta = new TF1("funcDelta",oscFuncVsDelta,0,2*TMath::Pi(),11);
   //   funcDelta->SetParameters(oscPar);
   //   funcDelta->Draw();
   
   

   TCanvas *can = new TCanvas();
   TH1F *framey=can->DrawFrame(0,-1,TMath::PiOver2(),1);
   framey->GetXaxis()->SetTitle("#theta_{23} (radians)");
   //
   if(doAntiNu)
     framey->GetYaxis()->SetTitle("anti-#nu_{e} Events / unit");
   else
     framey->GetYaxis()->SetTitle("#nu_{e} Events / unit");

   oscPar[OscPar::kDeltaM23]=2.38e-3; // in eV^2 will loop over
   
   oscPar[OscPar::kDelta]=0;//5.5*TMath::PiOver4();
     
   TF1 *funcDiff = new TF1("funcDiff",diffFuncVsT23,0,TMath::PiOver2(),12);

   for(Double_t dm23=-2.435e-3;dm23>-2.45e-3;dm23-=1e-6) {
     oscPar[11]=dm23;
     funcDiff->SetParameters(oscPar);
     funcDiff->DrawClone("l same");
   }

//    TF1 *funcOsc = new TF1("funcOsc",oscFuncVsT23,0,TMath::PiOver2(),11);
//    funcOsc->SetParameters(oscPar);


   
//    oscPar[OscPar::kDeltaM23]=-2.44e-3; // in eV^2 will loop over
//    //   oscPar[OscPar::kDeltaM23]=-2.38e-3; // in eV^2 will loop over
//    oscPar[OscPar::kDelta]=0;//6.5*TMath::PiOver4();
//    TF1 *funcOsc2 = new TF1("funcOsc2",oscFuncVsT23,0,TMath::PiOver2(),11);
//    funcOsc2->SetParameters(oscPar);

//    funcOsc->SetLineColor(kRed+1);
//    //   funcOsc->SetFillColor(kRed+1);
//    //   funcOsc->SetFillStyle(3001);

//    funcOsc2->SetLineColor(kBlue+1);
//    funcOsc2->SetLineStyle(2);
//    //   funcOsc2->SetFillColor(kBlue+1);
//    //   funcOsc2->SetFillStyle(3001);
   
//    funcOsc->Draw("l");
//    funcOsc2->Draw("l same");


//    TLegend *leggy = new TLegend(0.2,0.7,0.5,0.9);
//    leggy->SetBorderSize(0);
//    leggy->SetFillColor(0);
//    leggy->SetFillStyle(0);
//    leggy->AddEntry(funcOsc,"NH","f");
//    leggy->AddEntry(funcOsc2,"IH","f");
//    leggy->Draw("same");


}


void plotNumberOfNueEvents(double L, double E) {
  int doAntiNu=0;

   Double_t oscPar[11]={0};
   oscPar[OscPar::kL]=L;//735; // km //MINOS
   //   oscPar[OscPar::kL]=810; // km //NOvA
   //   oscPar[OscPar::kL]=2300; // km //LBNO
   oscPar[OscPar::kTh23]=0.705; //From PDG, extracted from sin^2(theta_23)=0.42, will loop over this
   oscPar[OscPar::kTh12]=0.586; /// From PDG, extracted from sin^2(theta_12) = 0.306
   oscPar[OscPar::kTh13]=0.159; // From PDG, extracted from sin^2(theta_13) = 0.0251
   oscPar[OscPar::kDeltaM23]=2.38e-3; // in eV^2 will loop over
   oscPar[OscPar::kDeltaM12]=7.58e-5; // in eV^2
   oscPar[OscPar::kDelta]=0; //Fix at zero for now
   oscPar[OscPar::kDensity]=1.470; //In some units
   oscPar[OscPar::kNuAntiNu]=1; // 1 for neutrinos, -1 for antineutrinos
   oscPar[9]=E;//2; //Energy in GeV
   oscPar[10]=1000; //Normalisation
   if(doAntiNu) {
     inu=-12;
     inunoosc=-14;
     oscPar[10]/=3;
   }
   else {
     inu=12;
     inunoosc=14;
   }


   //   oscPar[OscPar::kDeltaM23]=-2.44e-3; // in eV^2 will loop over
   //   TCanvas *canDelta = new TCanvas();
   //   TF1 *funcDelta = new TF1("funcDelta",oscFuncVsDelta,0,2*TMath::Pi(),11);
   //   funcDelta->SetParameters(oscPar);
   //   funcDelta->Draw();
   
   

   TCanvas *can = new TCanvas();
   TH1F *framey=can->DrawFrame(0,0,TMath::PiOver2(),1000);
   framey->GetXaxis()->SetTitle("#theta_{23} (radians)");
   //
   if(doAntiNu)
     framey->GetYaxis()->SetTitle("anti-#nu_{e} Events / unit");
   else
     framey->GetYaxis()->SetTitle("#nu_{e} Events / unit");

   oscPar[OscPar::kDeltaM23]=2.38e-3; // in eV^2 will loop over
   if(doAntiNu)
     oscPar[OscPar::kDelta]=5.5*TMath::PiOver4();
   else 
     oscPar[OscPar::kDelta]=6.5*TMath::PiOver4();
     
   TF1 *funcOsc = new TF1("funcOsc",oscFuncVsT23,0,TMath::PiOver2(),11);
   funcOsc->SetParameters(oscPar);
   //   funcOsc->Draw("");

   if(doAntiNu)
     oscPar[OscPar::kDelta]=1.5*TMath::PiOver4();
   else
     oscPar[OscPar::kDelta]=2.5*TMath::PiOver4();     
   TF1 *funcOsc2 = new TF1("funcOsc2",oscFuncVsT23,0,TMath::PiOver2(),11);
   funcOsc2->SetParameters(oscPar);

   
   oscPar[OscPar::kDeltaM23]=-2.44e-3; // in eV^2 will loop over
   if(doAntiNu)
     oscPar[OscPar::kDelta]=6.5*TMath::PiOver4();
   else
     oscPar[OscPar::kDelta]=5.5*TMath::PiOver4();
   TF1 *funcOsc3 = new TF1("funcOsc3",oscFuncVsT23,0,TMath::PiOver2(),11);
   funcOsc3->SetParameters(oscPar);
   //   funcOsc->Draw("");

   if(doAntiNu)
     oscPar[OscPar::kDelta]=2.5*TMath::PiOver4();
   else
     oscPar[OscPar::kDelta]=1.5*TMath::PiOver4();
   TF1 *funcOsc4 = new TF1("funcOsc4",oscFuncVsT23,0,TMath::PiOver2(),11);
   funcOsc4->SetParameters(oscPar);


   funcOsc->SetFillColor(kRed+1);
   funcOsc->SetFillStyle(3001);
   TGraph *grNorm=getShadedGraph(can,funcOsc,funcOsc2);
   grNorm->SetName("grNorm");

   funcOsc3->SetFillColor(kBlue+1);
   funcOsc3->SetFillStyle(3001);
   TGraph *grInv=getShadedGraph(can,funcOsc3,funcOsc4);
   grInv->SetName("grInv");

   grNorm->Draw("f");
   grInv->Draw("f");
   
   framey->GetXaxis()->SetRangeUser(0.4,1.2);
   framey->GetYaxis()->SetNoExponent(1);

   int frameTop=100;
   if(doAntiNu)
     frameTop/=3.;
   framey->GetYaxis()->SetRangeUser(0,frameTop);

   TLegend *leggy = new TLegend(0.2,0.7,0.5,0.9);
   leggy->SetBorderSize(0);
   leggy->SetFillColor(0);
   leggy->SetFillStyle(0);
   leggy->AddEntry(grNorm,"NH","f");
   leggy->AddEntry(grInv,"IH","f");
   leggy->Draw("same");


//    TBox *boxy = new TBox(0.625,0,0.946,frameTop);
//    boxy->SetLineWidth(0);
//    boxy->SetFillColor(kOrange+1);
//    boxy->SetFillStyle(3002);
//    boxy->DrawBox(0.625,0,0.946,frameTop);
//    boxy->SetFillStyle(3002);
//    boxy->SetFillColor(kGreen+2);
//    boxy->DrawBox(TMath::ASin(TMath::Sqrt(0.96*0.975))/2,0,TMath::ASin(TMath::Sqrt(0.96*1.025))/2,frameTop);
//    boxy->DrawBox(TMath::PiOver2()-TMath::ASin(TMath::Sqrt(0.96*0.975))/2,0,TMath::PiOver2()-TMath::ASin(TMath::Sqrt(0.96*1.025))/2,frameTop);;
//    boxy->SetFillStyle(3002);
//    boxy->SetFillColor(kOrange+3);
//    boxy->DrawBox(TMath::ASin(TMath::Sqrt(0.96*0.99))/2,0,TMath::ASin(TMath::Sqrt(0.96*1.01))/2,frameTop);
//    boxy->DrawBox(TMath::PiOver2()-TMath::ASin(TMath::Sqrt(0.96*0.99))/2,0,TMath::PiOver2()-TMath::ASin(TMath::Sqrt(0.96*1.01))/2,frameTop);


}





Double_t oscFuncVsDelta(Double_t *x, Double_t *par) 
{
  Double_t delta=x[0];
  par[OscPar::kDelta]=delta;
  
  fOscCalc.SetOscParam(par);
  return par[10]*fOscCalc.Oscillate(inu,inunoosc,par[9]);

}


Double_t oscFuncVsT23(Double_t *x, Double_t *par) 
{
  Double_t t23=x[0];
  par[OscPar::kTh23]=t23;
  
  fOscCalc.SetOscParam(par);
  return par[10]*fOscCalc.Oscillate(inu,inunoosc,par[9]);

}


Double_t diffFuncVsT23(Double_t *x, Double_t *par) 
{
  Double_t tempDM2NH=par[OscPar::kDeltaM23];
  Double_t tempDM2IH=par[11];
  Double_t t23=x[0];
  par[OscPar::kTh23]=t23;  
  fOscCalc.SetOscParam(par);
  Double_t NH=par[10]*fOscCalc.Oscillate(inu,inunoosc,par[9]);
  par[OscPar::kDeltaM23]=tempDM2IH;
  fOscCalc.SetOscParam(par);
  Double_t IH=par[10]*fOscCalc.Oscillate(inu,inunoosc,par[9]);
  par[OscPar::kDeltaM23]=tempDM2NH;
  return (NH-IH);
}






TGraph *getShadedGraph(TCanvas *c1, TF1 *f1, TF1 *f2) {
   //shade the area between f1 and f2 and draw f3 on top
   
   //create a TGraph to store the function values
   //shaded area is the fill/color/style of f1
   TGraph *gr = new TGraph();
   gr->SetFillColor(f1->GetFillColor());
   gr->SetFillStyle(f1->GetFillStyle());
   //   f3->Draw("l");
   c1->Update();
   //get picture range
   Double_t xmin = c1->GetUxmin();
   Double_t xmax = c1->GetUxmax();
   Double_t ymin = c1->GetUymin();
   Double_t ymax = c1->GetUymax();
   
   //process first function
   Int_t npx = f1->GetNpx();
   Int_t npoints=0;
   Double_t dx = (xmax-xmin)/npx;
   Double_t x = xmin+0.5*dx;
   while (x <= xmax) {
      Double_t y = f1->Eval(x);
      if (y < ymin) y = ymin;
      if (y > ymax) y = ymax;
      gr->SetPoint(npoints,x,y);
      npoints++;
      x += dx;
   }
   //process second function
   x = xmax-0.5*dx;
   while (x >= xmin) {
      Double_t y = f2->Eval(x);
      if (y < ymin) y = ymin;
      if (y > ymax) y = ymax;
      gr->SetPoint(npoints,x,y);
      npoints++;
      x -= dx;
   }
   //   gr->Draw("f");     //draw graph with fill area option
   return gr;
}
