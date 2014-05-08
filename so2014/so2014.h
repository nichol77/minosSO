
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
