
#include "src/paramFuncs.h"

TLegend *leggyNue[4];
TLegend *leggyMain[4];
TLegend *leggyRatio[4];
TLegend *leggyNoOsc[4];

TCanvas *canMainArray[4];
TCanvas *canNoOscArray[4];
TCanvas *canNueArray[4];
TCanvas *canRatioArray[4];
//#define DM_BIN 61
//#define DM_BIN 31
//#define T23_BIN 39
#define T13_BIN 6
//#define DELTA_BIN 0

int DO_MAIN_NUE_PLOTS=0;

TFile *fpRat = 0;

void plotFarPreds()
{
  fpRat=0;
  if(DO_MAIN_NUE_PLOTS) {
  TCanvas *canNQMain = new TCanvas("canNQMain","canNQMain",800,500);
  TCanvas *canNQNue = new TCanvas("canNQNue","canNQNue",800,500);
  TCanvas *canPQMain = new TCanvas("canPQMain","canPQMain",800,500);
  TCanvas *canPQNue = new TCanvas("canPQNue","canPQNue",800,500);
  TCanvas *canNCMain = new TCanvas("canNCMain","canNCMain",800,500);
  TCanvas *canNCNue = new TCanvas("canNCNue","canNCNue",800,500);
  TCanvas *canNCTrackMain = new TCanvas("canNCTrackMain","canNCTrackMain",800,500);
  TCanvas *canNCTrackNue = new TCanvas("canNCTrackNue","canNCTrackNue",800,500);
  }

  TCanvas *canPQRat = new TCanvas("canPQRat","canPQRat",800,500);
  TCanvas *canNQRat = new TCanvas("canNQRat","canNQRat",800,500);
  TCanvas *canNCRat = new TCanvas("canNCRat","canNCRat",800,500);
  TCanvas *canNCTrackRat = new TCanvas("canNCTrackRat","canNCTrackRat",800,500);

  TCanvas *canPQNoOsc = new TCanvas("canPQNoOsc","canPQNoOsc",800,500);
  TCanvas *canNQNoOsc = new TCanvas("canNQNoOsc","canNQNoOsc",800,500);
  TCanvas *canNCNoOsc = new TCanvas("canNCNoOsc","canNCNoOsc",800,500);
  TCanvas *canNCTrackNoOsc = new TCanvas("canNCTrackNoOsc","canNCTrackNoOsc",800,500);

  if(DO_MAIN_NUE_PLOTS) {
  canMainArray[0]=canNQMain;
  canMainArray[1]=canPQMain;
  canMainArray[2]=canNCMain;
  canMainArray[3]=canNCTrackMain;

  canNueArray[0]=canNQNue;
  canNueArray[1]=canPQNue;
  canNueArray[2]=canNCNue;
  canNueArray[3]=canNCTrackNue;
  }
  canRatioArray[0]=canNQRat;
  canRatioArray[1]=canPQRat;
  canRatioArray[2]=canNCRat;
  canRatioArray[3]=canNCTrackRat;

  canNoOscArray[0]=canNQNoOsc;
  canNoOscArray[1]=canPQNoOsc;
  canNoOscArray[2]=canNCNoOsc;
  canNoOscArray[3]=canNCTrackNoOsc;


//   doARun("run1","run1",1,1,"#delta=0",0);
//   doARun("run1","run1",0,2,"#delta=#pi/4",1);
//   doARun("run1","run1",0,3,"#delta=#pi/2",2);
//   doARun("run1","run1",0,4,"#delta=3#pi/4",3);
//   doARun("run1","run1",0,5,"#delta=#pi",4);
//   doARun("run1","run1",0,6,"#delta=5#pi/4",5);
//   doARun("run1","run1",0,7,"#delta=3#pi/2",6);
//   doARun("run1","run1",0,8,"#delta=7#pi/4",7);


  doARun("run3","minosPlus",1,4,69,58,0);
  doARun("run3","minosPlus",0,0,69,39,0);
  for(int deltai=2;deltai<8;deltai+=2) {
     doARun("run3","minosPlus",0,deltai/2,69,39,deltai);
     doARun("run3","minosPlus",0,4+deltai/2,69,58,deltai);
  }
  for(int deltai=0;deltai<8;deltai+=2) {
     doARun("run3","minosPlus",0,8+deltai/2,28,39,deltai);
     doARun("run3","minosPlus",0,12+deltai/2,28,58,deltai);
  }

   char plotName[180];
   for(int i=0;i<4;i++) {
      if(DO_MAIN_NUE_PLOTS) {
	canMainArray[i]->Update();
	canMainArray[i]->Modified();
	sprintf(plotName,"%s.pdf",canMainArray[i]->GetName());
	canMainArray[i]->Print(plotName);
	
	canNueArray[i]->Update();
	canNueArray[i]->Modified();
	sprintf(plotName,"%s.pdf",canNueArray[i]->GetName());
	canNueArray[i]->Print(plotName);
	
	canRatioArray[i]->Update();
	canRatioArray[i]->Modified();
	sprintf(plotName,"%s.pdf",canRatioArray[i]->GetName());
	canRatioArray[i]->Print(plotName);
      }

	
      canNoOscArray[i]->Update();
      canNoOscArray[i]->Modified();
      sprintf(plotName,"%s.pdf",canNoOscArray[i]->GetName());
      canNoOscArray[i]->Print(plotName);

   }
}



void doARun(char *potFileTag, char *predFileTag, int firstOne, int colourNum,int dmi,int t23i,int deltai) {
  char legTag[180];
  sprintf(legTag,"#Deltam^{2}=%1.2e, #theta_{23}=%0.2f #delta = %d #pi/4",getDeltaM2(dmi),getT23(t23i),deltai);
  Double_t potMain;
  Double_t potNue;
  Double_t potTau;
  char mainPotFilename[180];
  char nuePotFilename[180];
  char tauPotFilename[180];
  sprintf(mainPotFilename,"pot/%sFDMCPOT.txt",potFileTag);
  sprintf(nuePotFilename,"pot/%sFDNueMCPOT.txt",potFileTag);
  sprintf(tauPotFilename,"pot/%sFDTauMCPOT.txt",potFileTag);

  ifstream MainPOT(mainPotFilename);
  if(!MainPOT) {
    std::cerr << "Can't open " << mainPotFilename << "\n";
    return;
  }
  ifstream NuePOT(nuePotFilename);
  if(!NuePOT) {
    std::cerr << "Can't open " << nuePotFilename << "\n";
    return;
  }
  ifstream TauPOT(tauPotFilename);
  if(!TauPOT) {
    std::cerr << "Can't open " << tauPotFilename << "\n";
    return;
  }
  //Get the POT
  MainPOT >> potMain;
  NuePOT >> potNue;
  TauPOT >> potTau;

  //Now open the data and Nue files and get the relevant histograms
  char mainFileName[180];
  char nueFileName[180];
  char tauFileName[180];
  char histName[180];
  sprintf(mainFileName,"farPreds/%s/main%d.root",predFileTag,dmi);
  sprintf(nueFileName,"farPreds/%s/nue%d.root",predFileTag,dmi);
  sprintf(tauFileName,"farPreds/%s/tau%d.root",predFileTag,dmi);

  TFile *fpMain = TFile::Open(mainFileName);
  if(!fpMain) {
    std::cerr < "Couldn't open " << mainFileName << "\n";
    return;
  }
  TFile *fpNue = TFile::Open(nueFileName);
  if(!fpNue) {
    std::cerr < "Couldn't open " << nueFileName << "\n";
    return;
  }
  TFile *fpTau = TFile::Open(tauFileName);
  if(!fpTau) {
    std::cerr < "Couldn't open " << tauFileName << "\n";
    return;
  }
  char *histNameArray[4]={"histPredNQ","histPredPQ","histPredNC","histPredNCTrack"};
  char *cchistNameArray[4]={"histCCPredNQ","histCCPredPQ","histCCPredNC","histCCPredNCTrack"};
  char *histNoOscNameArray[4]={"histNoOscNQ","histNoOscPQ","histNoOscNC","histNoOscNCTrack"};
  char *plotTitleArray[4]={"(q<0)","(q>0)","NC","NC (with track)"};

  char histName[180];
  

  TH1D *histNoOsc[4]={0};
  TH1D *histNoOscScaled[4]={0};
  for(int histNum=0;histNum<4;histNum++) {
     sprintf(histName,"%s_minosplus_pred_main",histNoOscNameArray[histNum]);
     histNoOsc[histNum]=(TH1D*)fpMain->Get(histName);
     if(!histNoOsc[histNum]) {
	std::cerr << "Couldn't get " << histName << "\n";
     }
     sprintf(histName,"%s_%s_pred_main_scaled",histNoOscNameArray[histNum],predFileTag);
     histNoOscScaled[histNum]=(TH1D*)histNoOsc[histNum]->Clone(histName);
     histNoOscScaled[histNum]->Scale(1e18/potMain);
  }

  
  if(!fpRat) fpRat=new TFile("/tmp/farFile.root","RECREATE");
  fpRat->cd(); 





  for(int histNum=0;histNum<4;histNum++) {
    sprintf(histName,"/dmi%d/t23i%d/%s_%d_%d_%d_%d",dmi,t23i,histNameArray[histNum],dmi,t23i,T13_BIN,deltai);
    TH1D *histMain = (TH1D*) fpMain->Get(histName);
    if(!histMain) {
      std::cerr << "Couldn't get " << histName << "\n";
      return;      
    }

    TH1D *histTau = (TH1D*) fpTau->Get(histName);
    if(!histTau) {
      std::cerr << "Couldn't get " << histName << "\n";
      return;      
    }

    //    sprintf(histName,"/dmi%d/t23i%d/%s_%d_%d_%d_%d",dmi,t23i,histNameArray[histNum],dmi,t23i,T13_BIN,DELTA_BIN);
    TH1D *histNue = (TH1D*) fpNue->Get(histName);
    if(!histNue) {
      std::cerr << "Couldn't get " << histName << "\n";
      return;      
    }
    
    sprintf(histName,"/dmi%d/t23i%d/%s_%d_%d_%d_%d",dmi,t23i,cchistNameArray[histNum],dmi,t23i,T13_BIN,deltai);
    TH1D *histNueCC = (TH1D*) fpNue->Get(histName);
    if(!histNueCC) {
      std::cerr << "Couldn't get " << histName << "\n";
      return;      
    }
    

    fpRat->cd();
    sprintf(histName,"%s_%s_nd_data_over_mc_ratio",histNameArray[histNum],predFileTag);
    histNue->Scale(1e18/potNue);
    histNueCC->Scale(1e18/potNue);
    histMain->Scale(1e18/potMain);
    histTau->Scale(1e18/potTau);
    histMain->Add(histNue);
    histMain->Add(histTau);

    sprintf(histName,"%s_%s_over_no_osc",histNameArray[histNum],predFileTag);
    TH1D *histMainRat=histMain->Clone(histName);
    histMainRat->Divide(histNoOscScaled[histNum]);

    TH1D *histRatio=histNueCC->Clone(histName);
    histRatio->Divide(histMain);
    histRatio->Write();
    


    std::cout << histNameArray[histNum] << "\t" << 600*histNueCC->Integral() << "\t" << 600*histNue->Integral() << "\t" 
	      << 600*histMain->Integral() << "\n";

    char plotTitle[180];
 
    if(DO_MAIN_NUE_PLOTS) {
       canMainArray[histNum]->cd();    
       histMain->SetLineColor(getNiceColour(colourNum));
       sprintf(plotTitle,"Main+Nue+Tau -- %s",plotTitleArray[histNum]);
       histMain->SetTitle(plotTitle);
       histMain->GetXaxis()->SetTitle("Reconstructed Energy (GeV)");
       histMain->GetXaxis()->SetRangeUser(0,19.5);
       histMain->GetYaxis()->SetTitle("Events per 1e18 POT");
       histMain->GetYaxis()->SetNoExponent(1);
       histMain->SetStats(0);
       if(firstOne) histMain->Draw();
       else histMain->Draw("same");
       
       if(firstOne) {
	  leggyMain[histNum] = new TLegend(0.6,0.3,0.9,0.9);
	  leggyMain[histNum]->SetBorderSize(0);
	  leggyMain[histNum]->SetFillStyle(0);
       }
       leggyMain[histNum]->AddEntry(histMain,legTag,"l");
       leggyMain[histNum]->Draw();
       
       canNueArray[histNum]->cd();    
       histNueCC->SetLineColor(getNiceColour(colourNum));
       sprintf(plotTitle,"True Nue CC -- %s",plotTitleArray[histNum]);
       histNueCC->SetTitle(plotTitle);
       histNueCC->GetXaxis()->SetTitle("Reconstructed Energy (GeV)");
       histNueCC->GetXaxis()->SetRangeUser(0,19.5);
       histNueCC->GetYaxis()->SetTitle("Events per 1e18 POT");
       histNueCC->GetYaxis()->SetNoExponent(1);
       histNueCC->SetStats(0);
       if(firstOne)
	  histNueCC->Draw();
       else
	  histNueCC->Draw("same");
       
       
       if(firstOne) {
	  leggyNue[histNum] = new TLegend(0.6,0.3,0.9,0.9);
	  leggyNue[histNum]->SetBorderSize(0);
	  leggyNue[histNum]->SetFillStyle(0);
       }
       leggyNue[histNum]->AddEntry(histNueCC,legTag,"l");
       leggyNue[histNum]->Draw();
    }

  // leggyPQNue = new TLegend(0.6,0.6,0.9,0.9);
  // leggyPQNue->SetBorderSize(0);
  // leggyPQNue->SetFillStyle(0);
  // leggyPQNue->AddEntry(histPQMc,"Run I","l");


    canNoOscArray[histNum]->cd();    
    histMainRat->SetLineColor(getNiceColour(colourNum));
    sprintf(plotTitle,"Ratio to No Oscillations -- %s",plotTitleArray[histNum]);
    histMainRat->SetTitle(plotTitle);
    histMainRat->GetXaxis()->SetTitle("Reconstructed Energy (GeV)");
    histMainRat->GetXaxis()->SetRangeUser(0,19.5);
    histMainRat->GetYaxis()->SetTitle("Ratio");
    histMainRat->GetYaxis()->SetNoExponent(1);
    histMainRat->SetStats(0);
    if(firstOne) histMainRat->Draw();
    else histMainRat->Draw("same");
    
    if(firstOne) {
       leggyNoOsc[histNum] = new TLegend(0.6,0.3,0.9,0.9);
       leggyNoOsc[histNum]->SetBorderSize(0);
       leggyNoOsc[histNum]->SetFillStyle(0);
    }
    leggyNoOsc[histNum]->AddEntry(histMainRat,legTag,"l");
    leggyNoOsc[histNum]->Draw();


    canRatioArray[histNum]->cd();
    histRatio->SetLineColor(getNiceColour(colourNum));
    sprintf(plotTitle,"Nue CC/Total -- %s",plotTitleArray[histNum]);
    histRatio->SetTitle(plotTitle);
    histRatio->GetXaxis()->SetTitle("Reconstructed Energy (GeV)");
    histRatio->GetXaxis()->SetRangeUser(0,19.5);
    histRatio->GetYaxis()->SetTitle("Ratio");
    histRatio->GetYaxis()->SetNoExponent(1);
    histRatio->GetYaxis()->SetRangeUser(0,0.2);
    histRatio->SetStats(0);
    if(firstOne) 
      histRatio->Draw();
    else
      histRatio->Draw("same");

    if(firstOne) {
      if(histNum<2) {
	leggyRatio[histNum] = new TLegend(0.6,0.3,0.9,0.9);
      }
      else {
	leggyRatio[histNum] = new TLegend(0.6,0.3,0.9,0.9);
      }	
      leggyRatio[histNum]->SetBorderSize(0);
      leggyRatio[histNum]->SetFillStyle(0);
    }
    leggyRatio[histNum]->AddEntry(histRatio,legTag,"l");
    leggyRatio[histNum]->Draw();

  }
  //  fpRat->Close();

}
