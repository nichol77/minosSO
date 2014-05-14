#ifndef PARAM_FUNCS_H
#define PARAM_FUNCS_H

#include "TMath.h"
#include "TH2D.h"



#define MAX_DELTA_INDEX 4
#define MAX_T13_INDEX 1
#define MAX_DMI_INDEX 100
#define MAX_T23_INDEX 100
#define MAX_SIN2_INDEX 101

#define MIN_T13 1.45425819453369298e-01
#define T13_STEP_SIZE 0.01

#define MIN_DELTA 0
#define DELTA_STEP_SIZE TMath::PiOver2()


#define MIN_DM2 -3e-3
#define MIN_NEG_DM2 MIN_DM2
#define MIN_POS_DM2 +2e-3
#define DM2_STEP_SIZE 2e-5

#define MIN_T23 0.3
#define T23_STEP_SIZE 0.01

#define MIN_SIN2 0.5
#define SIN2_STEP_SIZE 5e-3

inline Double_t getDeltaM2(int dmi) {
  Double_t dm2=MIN_DM2+dmi*(DM2_STEP_SIZE);
  if(dmi>=(MAX_DMI_INDEX/2)) {
    dm2=MIN_POS_DM2+(dmi-(MAX_DMI_INDEX/2))*(DM2_STEP_SIZE);
  }
  return dm2;
}

inline Double_t getT23(int t23i) {  
  Double_t t23=MIN_T23+T23_STEP_SIZE*t23i;
  return t23;
}

inline Double_t getDeltaCP(int deltai) {
   Double_t delta=MIN_DELTA+DELTA_STEP_SIZE*deltai;
   return delta;
}


inline Double_t getT13(int t13i) {  
  Double_t t13=MIN_T13+T13_STEP_SIZE*t13i;
  return t13;
}


inline Double_t getSinSq2T23(int sin2i) {
  Double_t sin2=MIN_SIN2+sin2i*SIN2_STEP_SIZE;
  return sin2;
}


inline Double_t getFirstT23(Double_t sinSq2t23) 
{
  return TMath::ASin(TMath::Sqrt(sinSq2t23))/2.0;  
}

inline Double_t getOtherT23(Double_t firstT23)
{
  return ((TMath::Pi()/2)-firstT23);
}

inline Double_t getSecondT23(Double_t sinSq2t23)
{  
  return  getOtherT23(getFirstT23(sinSq2t23));
}

inline Int_t getT23IFromT23(Double_t t23) {
   return TMath::Nint((t23-MIN_T23)/T23_STEP_SIZE);
}

inline Int_t getDmiFromDm(Double_t dm2) {
   if(dm2<0)
      return TMath::Nint((dm2-MIN_DM2)/DM2_STEP_SIZE);
   return (MAX_DMI_INDEX/2)+TMath::Nint((dm2-MIN_POS_DM2)/DM2_STEP_SIZE);
}

inline TH2D *getNewInvertedHistogram(const char *outName) {

   return new TH2D (outName,outName,MAX_T23_INDEX,MIN_T23-0.5*T23_STEP_SIZE,MIN_T23+(MAX_T23_INDEX-0.5)*T23_STEP_SIZE,
		    MAX_DMI_INDEX/2,1e3*(MIN_NEG_DM2-0.5*DM2_STEP_SIZE),1e3*(MIN_NEG_DM2+(MAX_DMI_INDEX/2)*DM2_STEP_SIZE));
}

inline TH2D *getNewNormalHistogram(const char *outName) {
   return new TH2D(outName,outName,MAX_T23_INDEX,MIN_T23-0.5*T23_STEP_SIZE,MIN_T23+(MAX_T23_INDEX-0.5)*T23_STEP_SIZE,
		   MAX_DMI_INDEX/2,1e3*(MIN_POS_DM2-0.5*DM2_STEP_SIZE),1e3*(MIN_POS_DM2+(MAX_DMI_INDEX/2)*DM2_STEP_SIZE));
}

#endif
