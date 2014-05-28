TGraphErrors *getRatioGraphPoissonErrors(TH1D *numerator,TH1D *denominator, double numeratorScale=1, double denominatorScale=1 );

void divideByBinWidth(TH1D *hist) {
  for(int bin=1;bin<=hist->GetNbinsX();bin++) {
    hist->SetBinContent(bin,hist->GetBinContent(bin)/hist->GetBinWidth(bin));
  }
}



void printEventTable(TH1D *hist) {
  std::cout << hist->GetName() << "\t" << hist->GetTitle() << "\n";

  Double_t num0to4=0;
  Double_t num4to8=0;
  Double_t numAbove=0;
  for(int bin=1;bin<=hist->GetNbinsX();bin++) {
    double numEvents=hist->GetBinContent(bin);
    double minE=hist->GetBinLowEdge(bin);
    double maxE=hist->GetBinLowEdge(bin)+hist->GetBinWidth(bin);
    if(maxE<=4) {
      num0to4+=numEvents;
    }
    else if(maxE<=8) {
      num4to8+=numEvents;
    }
    else {
      numAbove+=numEvents;
    }    
  }

  std::cout << "*******************************************************\n";
  std::cout << "Total: " << hist->Integral() << "\n";
  std::cout << "<4: " << num0to4 << "\n";
  std::cout << "4-8: " << num4to8 << "\n";
  std::cout << ">8: " << numAbove << "\n";
}


TH1D *getRebinnedHist(TH1D *inHist) {
  Double_t binEdge[]={0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,32,34,36,38,40,42,44,46,48,50,200};  //41 bins?
  char histName[180]; 
  sprintf(histName,"%s_rebin",inHist->GetName());
  TH1D *histOut = new TH1D(histName,"histOut",41,binEdge);

  for(int inBin=1;inBin<=inHist->GetNbinsX();inBin++) {
    histOut->Fill(inHist->GetBinCenter(inBin),inHist->GetBinContent(inBin));
  }  
  return histOut;
}

TGraphErrors *getRatioGraphPoissonErrors(TH1D *numerator,TH1D *denominator, double numeratorScale, double denominatorScale ) {
  if(denominator->GetNbinsX()!=numerator->GetNbinsX()) {
    std::cerr << "Can't make a ratio from historgams with different bins\n";
    return NULL;
  }
  Double_t xVals[1000]={0};
  Double_t yVals[1000]={0};
  Double_t exVals[1000]={0};
  Double_t eyVals[1000]={0};
  for(int i=0;i<denominator->GetNbinsX();i++) {
    //    std::cerr << i << "\n";
    xVals[i]=denominator->GetBinCenter(i+1);
    exVals[i]=denominator->GetBinWidth(i+1)/2;
    Double_t N=denominator->GetBinContent(i+1);
    Double_t k=numerator->GetBinContent(i+1);
    yVals[i]=0;
    if(N>0)
      yVals[i]=(k*numeratorScale)/(N*denominatorScale);

    if(k>0 && N>0) {
      eyVals[i]=yVals[i]*TMath::Sqrt((1./k)+(1./N));
    }
    //    std::cerr << i << "\t" << xVals[i] << "\t" << yVals[i] << "\t" << eyVals[i] << "\n";
  }
  TGraphErrors *gr = new TGraphErrors(denominator->GetNbinsX(),xVals,yVals,exVals,eyVals);
  return gr;
}


TGraphErrors *getSmoothedGraphFivePoint(TGraphErrors *grIn) {
  Int_t numPoints=grIn->GetN();
  Double_t *newY = new Double_t[numPoints];
  Double_t *newYerr = new Double_t[numPoints];
  Double_t *oldX = grIn->GetX();
  Double_t *oldY = grIn->GetY();
  Double_t *oldYErr = grIn->GetEY();
  Double_t *oldXErr = grIn->GetEX();


  for(int i=0;i<numPoints;i++) {
    Double_t value=0;
    Double_t sumWeight=0;
    Double_t sumErrors=0;
    for(int j=i-2;j<=i+2;j++) {
      if(j<0 ||j>=numPoints) continue;
      Double_t weight=3-TMath::Abs(i-j);
      if(oldYErr[j]>0) {
	weight/=oldYErr[j];
	sumWeight+=weight;
	sumErrors+=weight*weight*oldYErr[j]*oldYErr[j];
	value+=weight*oldY[j];
      }    
      //      std::cout << j << "\t" << value << "\t" << sumWeight << "\n";
    }
    sumErrors=sqrt(sumErrors);
    sumErrors/=sumWeight;
    value/=sumWeight;
    newY[i]=value;
    newYerr[i]=sumErrors;
    //    std::cerr << i << "\t" << newY[i] <<  "\t" << oldY[i] << "\t" << newYerr[i] << "\n";
  }
  TGraphErrors *gr = new TGraphErrors(numPoints,oldX,newY,oldXErr,newYerr);

  delete [] newY;
  delete [] newYerr;
  return gr;

}

TH1D *convertGraphToHistogram(TGraphErrors *gr) {

   Double_t binEdge[]={0,0.5,0.75,1,1.25,1.5,1.75,2,2.25,2.5,2.75,3,3.25,3.5,3.75,4,4.25,4.5,4.75,5,5.25,5.5,5.75,6,6.25,6.5,6.75,7,7.25,7.5,7.75,8,8.25,8.5,8.75,9,9.25,9.5,9.75,10,10.25,10.5,10.75,11,11.25,11.5,11.75,12,12.25,12.5,12.75,13,13.25,13.5,13.75,14,14.25,14.5,14.75,15,15.25,15.5,15.75,16,16.25,16.5,16.75,17,17.25,17.5,17.75,18,18.25,18.5,18.75,19,19.25,19.5,19.75,20,21,22,23,24,25,26,27,28,29,30,32,34,36,38,40,42,44,46,48,50,200};

   TH1D *histTemp = new TH1D("tempHist","tempHist",100,binEdge);
   for(int bin=1;bin<=histTemp->GetNbinsX();bin++) {
     histTemp->SetBinContent(bin,gr->GetY()[bin-1]);
     histTemp->SetBinError(bin,gr->GetEY()[bin-1]);
   }
     
   return histTemp;
}
