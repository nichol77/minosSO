#include "OscCalc.h"
#include "TMath.h"
#include <cmath>
#include <cstdlib>
#include <iostream>

using namespace std; 

OscCalc::OscCalc()
{
  for(int i = 0; i < 9; i++) fOscPar[i] = 0;  
  double par[9] = {0};
  SetOscParam(par);
}

double OscCalc::Oscillate(int nuFlavor, int nonOscNuFlavor, double Energy, double * par)
{
  SetOscParam(par);
  return Oscillate(nuFlavor, nonOscNuFlavor, Energy); 
}


double OscCalc::Oscillate(int nuFlavor, int nonOscNuFlavor,  double Energy)
{

  if(nonOscNuFlavor > 0) fOscPar[OscPar::kNuAntiNu]=1;
  else fOscPar[OscPar::kNuAntiNu]=-1;

  double prob = 0.0;

  int initial_flavour=1; ///numu
  if(abs(nonOscNuFlavor)==12) initial_flavour=0; //nue
  if(abs(nonOscNuFlavor)==16) initial_flavour=2; //nutau

  int final_flavour=1; ///numu
  if(abs(nuFlavor)==12) final_flavour=0; //nue
  if(abs(nuFlavor)==16) final_flavour=2; //nutau  

  fPMNS.ResetToFlavour(initial_flavour);
  fPMNS.PropMatter(fOscPar[OscPar::kL],Energy,fElecDensity,fOscPar[OscPar::kNuAntiNu]);
  prob=fPMNS.P(final_flavour);

  if(prob<0) prob =0;
  if(prob>1) prob=1;
  if(TMath::IsNaN(prob)) prob=0;

  return prob;
}

void OscCalc::SetOscParam(double *par)
{
  for(int i = 0; i < int(OscPar::kUnknown); i++){
    fOscPar[i]=par[i];
  }
  fElecDensity=fOscPar[OscPar::kDensity];
  fPMNS.SetMix(fOscPar[OscPar::kTh12],fOscPar[OscPar::kTh23],fOscPar[OscPar::kTh13],fOscPar[OscPar::kDelta]);
  fPMNS.SetDeltaMsqrs(fOscPar[OscPar::kDeltaM12],fOscPar[OscPar::kDeltaM23]);

}

void OscCalc::GetOscParam(double *par)
{
  for(int i = 0; i < int(OscPar::kUnknown); i++){
    par[i] = fOscPar[i];
  }
}

double OscCalc::GetOscParam(OscPar::OscPar_t pos)
{
  if(pos >=0 && pos < OscPar::kUnknown)
    return fOscPar[pos];
  else 
    return -9999;
}

