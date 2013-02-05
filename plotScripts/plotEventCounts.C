#include "src/paramFuncs.h"


void plotEventCounts()
{

  TFile *fp = TFile::Open("other/nueTauTree.root","OLD");
  TTree *nueTauTree = (TTree*) fp->Get("nueTauTree");
  
  char plotArg[180];
  char plotCond[180];
  char histName[180];
  char histTitle[180];
  char canName[180];
  char legTag[180];
  TH1D *histNueCC[2][4][8];
  TH1D *histTot[2][4][8];

  Int_t totMin[4]={3700,212,600,1350};
  Int_t totMax[4]={4350,237,665,1455};
  Double_t nueText[4]={0.2,0.3,10,10};

  Int_t dmArray[2]={69,28};
  Int_t lineStyle[2]={1,3};


  char *mhTag[2]={"NH","IH"};

  char *histTag[4]={"CC (q<0)","CC (q>0","NC w/o track","NC w/ track"};


  for(int i=0;i<4;i++) {
    sprintf(canName,"canNue%d",i);
    TCanvas *canNue = new TCanvas(canName,canName);

    TLegend *leggy = new TLegend(0.2,0.5,0.4,0.9);
    leggy->SetBorderSize(0);
    leggy->SetFillStyle(0);
    leggy->SetFillColor(0);

    sprintf(canName,"canTot%d",i);
    TCanvas *canTot = new TCanvas(canName,canName);

    
    
    for(int mhi=0;mhi<2;mhi++) {

      for(int deltai=0;deltai<MAX_DELTA_INDEX;deltai++) {
	
	sprintf(histName,"histNueCC_%d_%d_%d",i,mhi,deltai);
	
	histNueCC[mhi][i][deltai]=new TH1D(histName,histName,101,0.3,1.3);
	
	canNue->cd();
	sprintf(plotArg,"getT23(t23i)>>%s",histName);
	sprintf(plotCond,"numNue[%d]*(dmi==%d && t13i==6 && deltai==%d)",i,dmArray[mhi],deltai);
	histNueCC[mhi][i][deltai]->SetLineColor(getNiceColour(deltai));	
	histNueCC[mhi][i][deltai]->SetLineStyle(lineStyle[mhi]);
	if(deltai==0 && mhi==0) {
	  nueTauTree->Draw(plotArg,plotCond,"L");	  
	  histNueCC[mhi][i][deltai]->GetXaxis()->SetTitle("#theta_{23}");
	  histNueCC[mhi][i][deltai]->GetYaxis()->SetTitle("Number Nue-CC Events");
	  histNueCC[mhi][i][deltai]->GetYaxis()->SetNoExponent(kTRUE);
	  sprintf(histTitle,"Nue events in %s Sample, 6#times10^{20} POT",histTag[i]);
	  histNueCC[mhi][i][deltai]->SetTitle(histTitle);
	  histNueCC[mhi][i][deltai]->GetXaxis()->SetRangeUser(0.32,1.28);

	}
	else 
	  nueTauTree->Draw(plotArg,plotCond,"same L");
	sprintf(legTag,"%s - #delta=%d#pi/4 #Deltam^{2}_{23}=%1.2f",mhTag[mhi],deltai,1e3*getDeltaM2(dmArray[mhi]));
	leggy->AddEntry(histNueCC[mhi][i][deltai],legTag,"L");
	
	
	sprintf(histName,"histTot__%d_%d_%d",i,mhi,deltai);
	histTot[mhi][i][deltai]=new TH1D(histName,histName,101,0.3,1.3);
	canTot->cd();
	sprintf(plotArg,"getT23(t23i)>>%s",histName);
	sprintf(plotCond,"numTot[%d]*(dmi==%d && t13i==6 && deltai==%d)",i,dmArray[mhi],deltai);
	histTot[mhi][i][deltai]->SetLineColor(getNiceColour(deltai));
	histTot[mhi][i][deltai]->SetLineStyle(lineStyle[mhi]);
	
	if(deltai==0 && mhi==0) {
	  nueTauTree->Draw(plotArg,plotCond,"L");
	  histTot[mhi][i][deltai]->GetXaxis()->SetTitle("#theta_{23}");
	  histTot[mhi][i][deltai]->GetYaxis()->SetTitle("Number of Events");
	  histTot[mhi][i][deltai]->GetYaxis()->SetNoExponent(kTRUE);
	  sprintf(histTitle,"Total Events in %s Sample, 6#times10^{20} POT",histTag[i]);
	  histTot[mhi][i][deltai]->SetTitle(histTitle);
	  histTot[mhi][i][deltai]->GetYaxis()->SetRangeUser(totMin[i],totMax[i]);
	  histTot[mhi][i][deltai]->GetXaxis()->SetRangeUser(0.32,1.28);
	}
	else 
	  nueTauTree->Draw(plotArg,plotCond,"same L");
	
      }	
    }
    canNue->cd();
    leggy->Draw("same");
  			
    TLatex *latexy = new TLatex();
    latexy->SetTextSize(0.04);
    latexy->SetTextAlign(12);
    char label[180];
    sprintf(label,"#theta_{13}=%1.2f",getT13(6));
    latexy->DrawLatex(0.8,nueText[i],label);
		
    canNue->Update();
    canNue->Modified();
    char outName[180];
    sprintf(outName,"canNue%d.pdf",i);
    canNue->Print(outName);

    canTot->cd();
//     leggy->DrawClone("same");
//     latexy->DrawLatex(0.7,610,label);

    canTot->Update();
    canTot->Modified();
    sprintf(outName,"canTot%d.pdf",i);
    canTot->Print(outName);
  }







}
