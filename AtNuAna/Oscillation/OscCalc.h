/*********************************************************************
//RJN hacked version to use Joao's new full formula version

// Welcome the the OscCalc class - hopefully your one stop shop for 
//   computing three flavor neutrino oscillations.
//
// This code works under the assumption that you want a quick solution
//  and so it stores and holds values for the sins and cosines, and 
//  other temporary values.  If you want a high precision answer you should find 
//  Mark Messier's code which was living in AtNu last I looked.
//  This code combines expansions in alpha and sinth13 to produce a pretty robust 
//  and rapid calculation.  For an evaluation of the difference between these 
//  formula and the exact solutions please see Appendix A in my thesis.  You will 
//  also find a derivation for these formula there - Josh Boehm 04-27-2009
**************************************************************************/

#ifndef OSCCALC_H
#define OSCCALC_H

#include "AtNuAna/Oscillation/PMNS_Fast.h"

namespace OscPar
{
   typedef enum EOscPar{
     kTh12 = 0,
     kTh23 = 1,
     kTh13 = 2,
     kDeltaM23 = 3,
     kDeltaM12 = 4,
     kDelta = 5,
     kDensity = 6,
     kL = 7,
     kNuAntiNu = 8,
     kUnknown = 9
   } OscPar_t;


#if !defined(__CINT__) || defined(__MAKECINT__)
   // Numbers pulled from 2006 PDG pg 97
   static const double z_a = 0.5; //average Z/A
   static const double A_av = 6.0221415e23; //avogadro's number
   static const double invCmToeV = 1.97326968e-5; //convert 1/cm to eV
   static const double invCmToGeV = 1.97326968e-14; //convert 1/cm to GeV
   static const double invKmToeV = 1.97326968e-10; //convert 1/km to eV
   static const double Gf = 1.166371e-5; //fermi constant (GeV^{-2})
   static const double root2 = 1.41421356;
#endif
}


class OscCalc
{
  public:

   OscCalc();

   void GetOscParam(double* par);
   double GetOscParam(OscPar::OscPar_t pos);
   void SetOscParam(double * par);

   double Oscillate(int nuFlavor, int nonOscNuFlavor, double Energy);
   double Oscillate(int nuFlavor, int nonOscNuFlavor, double Energy, double * par);



  private:
   double fOscPar[10];
   double fElecDensity;
   AtNuOsc::PMNS_Fast fPMNS;

};


#endif


