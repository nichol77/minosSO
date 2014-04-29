#include "TMath.h"
#include "TRandom.h"

#include "AtNuAna/Oscillation/AtNuOscillate.h"
#include "AtNuAna/Oscillation/ProductionHeight.h"

#include <iostream>

const double MineDepth = 0.65; //km
const double EarthRadius = 6371.315; //km

AtNuOscillate::AtNuOscillate()
{
  fDMSq12 = 8.0e-5;
  fDMSq23 = 2.5e-3;

  fSinSq2Theta12 = 0.75;
  fSinSq2Theta23 = 1.00;
  fSinSq2Theta13 = 0.00;
  fDeltaCP = 0.00;

  fTheta23 = -999;

  SetPMNS();

  fProdHeightMethod = 1;
  fParentIDnu = 0;

  fMatterEffects = true;
  fInnerCoreRadius = 1220;
  fInnerCoreNe = 6.05;
  fOuterCoreRadius = 3470;
  fOuterCoreNe = 5.205;
  fMantleRadius = 6336;
  fMantleNe = 2.215;
  fCrustNe = 1.470;
  fAtmosphereNe = 6.0e-4;
}

void AtNuOscillate::SetPMNS()
{
  //Reset the propagator
  fPMNS.Reset();

  //Set the delta M squared values
  fPMNS.SetDeltaMsqrs(fDMSq12, fDMSq23);

  //Find the angles and set the mixing matrix
  double theta12 = TMath::ASin(TMath::Sqrt(fSinSq2Theta12))/2.0;
  double theta23 = TMath::ASin(TMath::Sqrt(fSinSq2Theta23))/2.0;//When a value not equal to 1 is passed, this function effectively selects the octant < pi/4 (45 deg.)  I have added the fTheta23 variable to allow selection of either octant directly. - L. A. Corwin
  if(fTheta23 != -999) theta23 = fTheta23;

  double theta13 = TMath::ASin(TMath::Sqrt(fSinSq2Theta13))/2.0;
  fPMNS.SetMix(theta12, theta23, theta13, fDeltaCP);
}

double AtNuOscillate::OscProb(int ipdg, int jpdg, double CosZenith, double Energy)
{
  double ProdHeight = this->ProductionHeight(ipdg, CosZenith, Energy);
  return this->OscProb(ipdg, jpdg, CosZenith, Energy, ProdHeight);
}

double AtNuOscillate::OscProb(int ipdg, int jpdg, double CosZenith, double Energy, double Height)
{  
  // reject nu<->nubar transitions
  if( ( ipdg>0 && jpdg<0 )
   || ( ipdg<0 && jpdg>0 ) ){
    return 0.0;
  }

  // neutrino or anti-neutrino
  int Anti = (ipdg>=0)?+1:-1;

  // PDG->PMNS code conversion
  int inu = -1;
  if( fabs(ipdg)==12 ) inu = 0;
  if( fabs(ipdg)==14 ) inu = 1;
  if( fabs(ipdg)==16 ) inu = 2; 

  int jnu = -1;
  if( fabs(jpdg)==12 ) jnu = 0;
  if( fabs(jpdg)==14 ) jnu = 1;
  if( fabs(jpdg)==16 ) jnu = 2;

  // propagate neutrino
  this->PropagateAtNu(CosZenith, Energy, Height, Anti);

  // return oscillation probability
  return this->OscProb(inu,jnu);
}

double AtNuOscillate::OscProb(int inu, int jnu)
{
  // oscillation probability
  if( ( inu>=0 && inu<=2 )
  &&  ( jnu>=0 && jnu<=2 ) ){
    double prob = fPMNS.P(inu,jnu);
    if( isnan(prob) ){            // need to protect against NaN
      if( inu==jnu ) return 1.0;  //  if OscProb=NaN, return probability
      else return 0.0;            //  for case of no oscillations
    }
    return prob;
  }

  // sanity check
  if( inu==jnu ) return 1.0;
  else return 0.0;
}

void AtNuOscillate::PropagateAtNu(double CosZenith, double Energy, int Anti)
{
  if(fMatterEffects) PropagateAtNuMatter(CosZenith, Energy, Anti);
  else PropagateAtNuVacuum(CosZenith, Energy, Anti);
}

void AtNuOscillate::PropagateAtNu(double CosZenith, double Energy, double Height, int Anti)
{
  if(fMatterEffects) PropagateAtNuMatter(CosZenith, Energy, Height, Anti);
  else PropagateAtNuVacuum(CosZenith, Energy, Height, Anti);
}

double AtNuOscillate::ProductionHeight(double CosZenith, double Energy)
{
  return this->ProductionHeight(fProdHeightMethod,fParentIDnu,CosZenith,Energy);
}

double AtNuOscillate::ProductionHeight(int ParentIDnu, double CosZenith, double Energy)
{
  return this->ProductionHeight(fProdHeightMethod,ParentIDnu,CosZenith,Energy);
}

double AtNuOscillate::ProductionHeight(int ProdHeightMethod, int ParentIDnu, double CosZenith, double Energy)
{
  switch(ProdHeightMethod) {
    //case 0, return the flat production height
    case 0: return AtNuOsc::FlatProdHeight(); break;

    //case 1, return the mean production height
    case 1:
      //Electron Neutrinos are produced just by muon decay;
      if(abs(ParentIDnu) == 12)
       	return(AtNuOsc::MeanMuonProdHeight(CosZenith, Energy));

      //Muon Neutrinos are produced by either muon or pion decay;
      return ( (AtNuOsc::MeanPionProdHeight(CosZenith, Energy) +
                AtNuOsc::MeanMuonProdHeight(CosZenith, Energy))/2);
      break;

    //case 2, return a random production height
    case 2:
      //Electron neutrinos, and half of muon neutrino come from muon decay
      if(abs(ParentIDnu) == 12 || gRandom->Integer(2)==0)
       	return(AtNuOsc::RndmMuonProdHeight(CosZenith, Energy));

      //The other half of muon neutrinos come from pion decay
      return(AtNuOsc::RndmPionProdHeight(CosZenith, Energy));
      break;

    //case 3, return the PDF mean production height
    case 3:
      //Electron neutrinos, and half of muon neutrino come from muon decay
      if(abs(ParentIDnu) == 12)
       	return(AtNuOsc::PDFMeanMuonProdHeight(CosZenith, Energy));

      //The other half of muon neutrinos come from pion decay
      return ( (AtNuOsc::PDFMeanPionProdHeight(CosZenith, Energy) +
                AtNuOsc::PDFMeanMuonProdHeight(CosZenith, Energy))/2);
      break;

    //default case, return the flat production height
    default: return AtNuOsc::FlatProdHeight(); break;
  }
}

double AtNuOscillate::NuLength(double CosZenith, double Energy)
{
  double ProdHeight = this->ProductionHeight(CosZenith, Energy);
  return this->PropagationLength(CosZenith, ProdHeight);
}

double AtNuOscillate::PropagationLength(double CosZenith, double ProdHeight)
{
  double NuL =
    sqrt(((EarthRadius - MineDepth) *
          (EarthRadius - MineDepth) *
          CosZenith * CosZenith) +
         ((MineDepth + ProdHeight) *
          (2*EarthRadius + ProdHeight - MineDepth))) -
    (EarthRadius - MineDepth) * CosZenith;

  return NuL;
}

double AtNuOscillate::PropagationLength(int ProdHeightMethod, int ParentIDnu, double CosZenith, double Energy)
{
  double ProdHeight = AtNuOscillate::ProductionHeight(ProdHeightMethod, ParentIDnu, CosZenith, Energy);
  return AtNuOscillate::PropagationLength(CosZenith, ProdHeight);
}

void AtNuOscillate::PropagateAtNuVacuum(double CosZenith, double Energy, int Anti)
{
  double Height = this->ProductionHeight(CosZenith, Energy);
  this->PropagateAtNuVacuum(CosZenith, Energy, Height, Anti);
}

void AtNuOscillate::PropagateAtNuVacuum(double CosZenith, double Energy, double Height, int Anti)
{
  double NuL = this->PropagationLength(CosZenith, Height);

  fPMNS.Reset();
  fPMNS.PropVacuum(NuL, Energy, Anti);
}

void AtNuOscillate::PropagateAtNuMatter(double CosZenith, double Energy, int Anti)
{
  double Height = this->ProductionHeight(CosZenith, Energy);
  this->PropagateAtNuMatter(CosZenith, Energy, Height, Anti);
}

void AtNuOscillate::PropagateAtNuMatter(double CosZenith, double Energy, double Height, int Anti)
{
  double NuL = this->PropagationLength(CosZenith, Height);
  
  fPMNS.Reset();

  double SinZenith = TMath::Sqrt(1.0 - (CosZenith*CosZenith));
  //Closest approach of the neutrino path to the center of the earth
  double RApproach = (EarthRadius-MineDepth) * SinZenith;

  double tProdHeight = this->ProductionHeight(CosZenith, Energy);

  //Chord between neutrino path and the sphere of the atmosphere
  double LAtmos = 2.0 * TMath::Sqrt( (EarthRadius+tProdHeight) * (EarthRadius+tProdHeight) -
                                     (RApproach * RApproach) );

  //Chord between neutrino path and the sphere of the Earth's crust
  double LCrust = 2.0 * TMath::Sqrt( (EarthRadius * EarthRadius) -
                                     (RApproach * RApproach) );

  //Distance Neutrino Travels through the atmosphere
  double NuLAtmos = (LAtmos-LCrust)/2.0;

  //Neutrinos that just go through the Earth's Crust
  if (CosZenith > 0 || RApproach >= fMantleRadius) {

    //Propagate through the Atmosphere    
    fPMNS.PropMatter(NuLAtmos, Energy, fAtmosphereNe, Anti);
    
    //Propagate through remaining portion of crust
    fPMNS.PropMatter(NuL- NuLAtmos, Energy, fCrustNe, Anti);

    return;
  }

  //Chord between neutrino path and the sphere of the Earth's mantle
  double LMantle = 2.0 * TMath::Sqrt((fMantleRadius*fMantleRadius) -
                                     (RApproach * RApproach));

  //Distance Neutrino Travels through the crust before hitting the mantle
  double NuLCrust = (LCrust-LMantle)/2.0;

  //Neutrinos that go through Earth's Mantle + Crust
  if (RApproach > fOuterCoreRadius) {

    //Propagate through the Atmosphere 
    fPMNS.PropMatter(NuLAtmos, Energy, fAtmosphereNe, Anti);

    //Propagate through crust (first time)
    fPMNS.PropMatter(NuLCrust, Energy, fCrustNe, Anti);

    //Propagate through mantle (only time)
    fPMNS.PropMatter(LMantle, Energy, fMantleNe, Anti);

    //Propagate through remaining portion of crust (second time)
    fPMNS.PropMatter(NuL-(NuLAtmos+NuLCrust+LMantle), Energy, fCrustNe, Anti);

    return;
  }

  //Chord between neutrino path and the sphere of the Earth's outer core
  double LOuterCore = 2.0 * TMath::Sqrt((fOuterCoreRadius*fOuterCoreRadius) -
                                        (RApproach * RApproach));

  //Distance Neutrino Travels through the mantle before hitting the outer core
  double NuLMantle = (LMantle-LOuterCore)/2.0;

  //Neutrinos that go through Earth's Mantle + Crust
  if (RApproach > fInnerCoreRadius) {
    //Propagate through the Atmosphere
    fPMNS.PropMatter(NuLAtmos, Energy, fAtmosphereNe, Anti);

    //Propagate through crust (first time)
    fPMNS.PropMatter(NuLCrust, Energy, fCrustNe, Anti);

    //Propagate through mantle (first time)
    fPMNS.PropMatter(NuLMantle, Energy, fMantleNe, Anti);

    //Propagate through outer core (only time)
    fPMNS.PropMatter(LOuterCore, Energy, fOuterCoreNe, Anti);

    //Propagate through mantle (second time)
    fPMNS.PropMatter(NuLMantle, Energy, fMantleNe, Anti);

    //Propagate through remaining portion of crust (second time)
    fPMNS.PropMatter(NuL - (NuLAtmos+NuLCrust+2*NuLMantle+LOuterCore),
      Energy, fCrustNe, Anti);
    return;
  }

  //Chord between neutrino path and the sphere of the Earth's outer core
  double LInnerCore = 2.0 * TMath::Sqrt((fInnerCoreRadius*fInnerCoreRadius) -
                                        (RApproach * RApproach));

  //Distance Neutrino Travels through the outer before hitting the inner core
  double NuLOuterCore = (LOuterCore-LInnerCore)/2.0;

  //Neutrinos that go through Earth's Mantle + Crust
  //Propagate through the Atmosphere
  fPMNS.PropMatter(NuLAtmos, Energy, fAtmosphereNe, Anti);

  //Propagate through crust (first time)
  fPMNS.PropMatter(NuLCrust, Energy, fCrustNe, Anti);

  //Propagate through mantle (first time)
  fPMNS.PropMatter(NuLMantle, Energy, fMantleNe, Anti);

  //Propagate through outer core (first time)
  fPMNS.PropMatter(NuLOuterCore, Energy, fOuterCoreNe, Anti);

  //Propagate through inner core (only time)
  fPMNS.PropMatter(LInnerCore, Energy, fInnerCoreNe, Anti);

  //Propagate through outer core (second time)
  fPMNS.PropMatter(NuLOuterCore, Energy, fOuterCoreNe, Anti);

  //Propagate through mantle (second time)
  fPMNS.PropMatter(NuLMantle, Energy, fMantleNe, Anti);

  //Propagate through remaining portion of crust (second time)
  fPMNS.PropMatter(
    NuL - (NuLAtmos+NuLCrust+2*NuLMantle+2*NuLOuterCore+LInnerCore),
    Energy, fCrustNe, Anti);

  return;
}
