#ifndef AtNuOscillate_h
#define AtNuOscillate_h

#include "AtNuAna/Oscillation/PMNS.h"

class AtNuOscillate
{
 public:
  AtNuOscillate();
 ~AtNuOscillate() {;}

  AtNuOsc::PMNS GetPMNS() {return fPMNS;}

  void SetDMSq12(double d) {fDMSq12 = d; SetPMNS();}
  double GetDMSq12() {return fDMSq12;}

  void SetDMSq23(double d) {fDMSq23 = d; SetPMNS();}
  double GetDMSq23() {return fDMSq23;}

  void SetTheta23(double d) {fTheta23 = d; SetPMNS();}
  double GetTheta23() {return fTheta23;}


  void SetSinSq2Theta12(double d) {fSinSq2Theta12 = d; SetPMNS();}
  double GetSinSq2Theta12() {return fSinSq2Theta12;}

  void SetSinSq2Theta23(double d) {fSinSq2Theta23 = d; SetPMNS();}
  double GetSinSq2Theta23() {return fSinSq2Theta23;}

  void SetSinSq2Theta13(double d) {fSinSq2Theta13 = d; SetPMNS();}
  double GetSinSq2Theta13() {return fSinSq2Theta13;}

  void SetDeltaCP(double d) {fDeltaCP = d; SetPMNS();}
  double GetDeltaCP() {return fDeltaCP;}

  void DoMatterEffects(bool b=true) {fMatterEffects=b;}
  
  
  void SetInnerCoreRadius(double d) {fInnerCoreRadius = d;} 
  double GetInnerCoreRadius() {return fInnerCoreRadius;} 
 
  void SetInnerCoreNe(double d) {fInnerCoreNe = d;} 
  double GetInnerCoreNe() {return fInnerCoreNe;} 

  void SetOuterCoreRadius(double d) {fOuterCoreRadius = d;} 
  double GetOuterCoreRadius() {return fOuterCoreRadius;} 
  
  void SetOuterCoreNe(double d) {fOuterCoreNe = d;} 
  double GetOuterCoreNe() {return fOuterCoreNe;} 
  
  void SetMantleRadius(double d) {fMantleRadius = d;} 
  double GetMantleRadius() {return fMantleRadius;} 
  
  void SetMantleNe(double d) {fMantleNe = d;} 
  double GetMantleNe() {return fMantleNe;} 
  
  void SetCrustNe(double d) {fCrustNe = d;} 
  double GetCrustNe() {return fCrustNe;} 
  
  void SetAtmosphereNe(double d) {fAtmosphereNe = d;}
  double GetAtmosphereNe() {return fAtmosphereNe;}

  void SetPMNS();

  int ProdHeightMethod() {return fProdHeightMethod;}
  void ProdHeightMethod(int i) {fProdHeightMethod=i;}

  int ParentIDnu() {return fParentIDnu;}
  void ParentIDnu(int i) {fParentIDnu=i;}

  double ProductionHeight(double CosZenith, double Energy);
  double ProductionHeight(int ParentIDnu, double CosZenith, double Energy);
  double NuLength(double CosZenith, double Energy=0);

  void PropagateAtNu(double CosZenith, double Energy, int Anti);
  void PropagateAtNuVacuum(double CosZenith, double Energy, int Anti);
  void PropagateAtNuMatter(double CosZenith, double Energy, int Anti);  

  void PropagateAtNu(double CosZenith, double Energy, double Height, int Anti);
  void PropagateAtNuVacuum(double CosZenith, double Energy, double Height, int Anti);
  void PropagateAtNuMatter(double CosZenith, double Energy, double Height, int Anti);

  // Probability of inu->jnu (0=e, 1=mu, 2=tau)
  double OscProb(int inu, int jnu);
  
  // Probability of ipdg->jpdg (12=e, 14=mu, 16=tau)
  double OscProb(int ipdg, int jpdg, double CosZenith, double Energy);
  double OscProb(int ipdg, int jpdg, double CosZenith, double Energy, double Height);

  // Static methods
  static double ProductionHeight(int ProdHeightMethod, int ParentIDnu, 
                                 double CosZenith, double Energy);

  static double PropagationLength(double CosZenith, double ProdHeight);

  static double PropagationLength(int ProdHeightMethod, int ParentIDnu, 
                                  double CosZenith, double Energy);

 private:
  //Oscillation parameters
  double fDMSq12;
  double fDMSq23;
  double fTheta23;//Just the angle (In RADIANS!!)
  double fSinSq2Theta12;
  double fSinSq2Theta23;
  double fSinSq2Theta13;
  double fDeltaCP;

  AtNuOsc::PMNS fPMNS;

  //Necessary settings for the production height methods
  int fProdHeightMethod; //0=Flat, 1=Mean, 2=Rndm, 3=PDFMean
  int fParentIDnu; //Production height differs for nu_mu and nu_e

  //Earth size and density parameters
  bool fMatterEffects;
  double fInnerCoreRadius; //km
  double fInnerCoreNe; //electron density mols(e-)/cm^3
  double fOuterCoreRadius; //km
  double fOuterCoreNe; //electron density mols(e-)/cm^3
  double fMantleRadius; //km
  double fMantleNe; //electron density mols(e-)/cm^3
  double fCrustNe; //electron density mols(e-)/cm^3
  double fAtmosphereNe; //electron density mols(e-)/cm^3 

};

#endif // AtNuOscillate_h
