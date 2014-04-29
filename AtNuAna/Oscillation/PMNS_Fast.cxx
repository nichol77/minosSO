////////////////////////////////////////////////////////////////////////
// $Id: PMNS_Fast.cxx,v 1.1 2013/01/19 16:09:57 jcoelho Exp $
//
// Implementation of oscillations of neutrinos in matter in an
// three-neutrino framework based on the following references:
//
//......................................................................
//
// PHYSICAL REVIEW D       VOLUME 86, NUMBER 11          1 DECEMBER 2012
//
//        Constraints for nonstandard interaction epsilon_etau V_e 
//               from nue appearance in MINOS and T2K
//
//    J. A. B. Coelho, T. Kafka, W. A. Mann, J. Schneps and O. Altinok
//            Tufts University, Medford, Massachusetts 02155
//                    (Received 1 October 2012)
//
//                            11 3015
//                            --
//......................................................................
//
// Int. J. Mod. Phys. C       VOLUME 19, NUMBER 03            MARCH 2008
//
//     Efficient numerical diagonalization of hermitian 3x3 matrices
//
//                            Joachim Kopp
//                  Max–Planck–Institut für Kernphysik 
//             Postfach 10 39 80, 69029 Heidelberg, Germany
//                    (Received 19 October 2007)
//
//                                523
//......................................................................
//
// Throughout I have taken:
//   - L to be the neutrino flight distance in km
//   - E to be the neutrino energy in GeV
//   - Dmij to be the differences between the mass-squares in eV^2
//   - Ne to be the electron number density in mole/cm^3
//   - theta12,theta23,theta13,deltaCP to be in radians
//
// The code structure follows the implementation written by M. Messier
// in the PMNS class.
//
// joao.coelho@tufts.edu
////////////////////////////////////////////////////////////////////////

#include "AtNuAna/Oscillation/PMNS_Fast.h"
#include "AtNuAna/Oscillation/MatrixDecomp/zheevh3.h"

#include <iostream>
#include <cassert>
#include <stdlib.h>

using namespace AtNuOsc;

// Some useful complex numbers
static std::complex<double> zero(0.0,0.0);
static std::complex<double> one (1.0,0.0);

// Unit conversion constants
static const double kKm2eV  = 5.06773103202e+09; ///< km to eV^-1
static const double kK2     = 4.62711492217e-09; ///< mole/GeV^2/cm^3 to eV
static const double kGeV2eV = 1.0e+09;           ///< GeV to eV

//G_F in units of GeV^-2
static const double kGf     = 1.166371E-5;


//......................................................................

PMNS_Fast::PMNS_Fast() 
{
  this->SetMix(0.,0.,0.,0.);
  this->SetDeltaMsqrs(0.,0.);
  this->ResetToFlavour(1);
  fCachedNe = 0.0;
  fCachedE =  1.0;
  fCachedAnti = 1;
  fBuiltHlv = false;
}

//......................................................................

void PMNS_Fast::SetMix(double th12, double th23, double th13, double deltacp) 
{

  fTheta12 = th12;
  fTheta23 = th23;
  fTheta13 = th13;
  fDeltaCP = deltacp;

  fBuiltHlv = false;

}

//......................................................................
///
/// Set the mass-splittings. These are m_2^2-m_1^2, m_3^2-m_2^2 
/// and m_3^2-m_1^2 in eV^2
///
void PMNS_Fast::SetDeltaMsqrs(double dm21, double dm32) 
{

  fDm21 = dm21;
  fDm32 = dm32;
  fDm31 = dm32 + dm21;

  fBuiltHlv = false;

}

//......................................................................
///
/// Build H*lv, where H is the Hamiltonian in vacuum on flavour basis
/// and lv is the oscillation length
///
/// This is a dimentionless hermitian matrix, so only the
/// upper triangular part needs to be filled
///
/// The construction of the Hamiltonian follows the general lines of
/// W. A. Mann et al., arXiv:1204.6338 and Physical Review D 86, 113015 (2012)
///
void PMNS_Fast::BuildHlv() 
{

  if(fBuiltHlv) return;

  double s12 = sin(fTheta12);
  double c12 = cos(fTheta12);
  double s23 = sin(fTheta23);
  double c23 = cos(fTheta23);
  double s223 = sin(2*fTheta23);
  double s23sqr = s23*s23;
  double cosCP = cos(fDeltaCP);
  complex expCP(cosCP,-sin(fDeltaCP));

  double alpha = fDm21 / fDm31;
  double alpha1 = alpha * sin(2*fTheta12);
  double alpha2 = (1 - alpha * s12*s12);

  double G = 1 + alpha * (1 - 3*c12*c12);
  double Q = cos(2*fTheta13) * alpha2;
  double GpQ = G + Q;
  double a = cos(fTheta13) * alpha1;
  double b = -sin(fTheta13) * alpha1;
  complex ff = expCP * sin(2*fTheta13) * alpha2;

  fHlv[0][0] = -Q; 
  fHlv[0][1] = a * c23 + ff * s23; 
  fHlv[0][2] = ff * c23 - a * s23; 
  fHlv[1][1] = -G + GpQ * s23sqr + b * cosCP * s223; 
  fHlv[1][2] = b * (expCP - 2 * cosCP * s23sqr) + GpQ * s223 / 2; 
  fHlv[2][2] = Q - GpQ * s23sqr - b * cosCP * s223; 

  fBuiltHlv = true;

}

//......................................................................
///
/// Solve the full Hamiltonian for eigenvectors and eigenvalues
/// This is using a method from the GLoBES software available at
/// http://www.mpi-hd.mpg.de/personalhomes/globes/3x3/
/// We should cite them accordingly
///
void PMNS_Fast::SolveHam(double E, double Ne, int anti)
{

  if(Ne!=fCachedNe || E!=fCachedE || anti!=fCachedAnti || !fBuiltHlv ){
    fCachedNe = Ne;
    fCachedE = E;
    fCachedAnti = anti;
    this->BuildHlv();
  }
  else return;

  double lv = 4 * kGeV2eV*E / fDm31; // Osc. length in eV^-1 
  double kr2GNe = kK2*M_SQRT2*kGf*Ne; // Matter potential in eV
  complex A[3][3];
  for(int i=0;i<3;i++){
    for(int j=i;j<3;j++){
      if(i==j || anti>0) A[i][j] = fHlv[i][j]/lv;
      else               A[i][j] = conj(fHlv[i][j])/lv;
    }
  }
  if(anti>0) A[0][0] += kr2GNe;
  else       A[0][0] -= kr2GNe;

  zheevh3(A,fEvec,fEval);

}

///.....................................................................
///
/// Propagate the current neutrino state over a distance L in km
/// with an energy E in GeV through constant matter of density
/// Ne in mole/cm^3. 
/// @param anti - +1 = neutrino case, -1 = anti-neutrino case
///
void PMNS_Fast::PropMatter(double L, double E, double Ne, int anti) 
{

  this->SolveHam(E, Ne, anti);

  complex nuComp[3];

  for(int i=0;i<3;i++){
    nuComp[i] = 0;
    for(int j=0;j<3;j++){
      nuComp[i] += fNuState[j] * conj(fEvec[j][i]);
    }
  }

  for(int i=0;i<3;i++){
    fNuState[i] = 0;
    for(int j=0;j<3;j++){
      complex iEval(0.0,fEval[j]);
      fNuState[i] +=  exp(-iEval * kKm2eV*L) * nuComp[j] * fEvec[i][j];
    }
  }

}

//......................................................................
///
/// Reset the neutrino state back to a pure flavour where
/// it starts
///
void PMNS_Fast::ResetToFlavour(int flv) 
{
  register int i;
  for (i=0; i<3; ++i){
    if (i==flv) fNuState[i] = one;
    else        fNuState[i] = zero;
  }
}

//......................................................................
///
/// Compute oscillation probability of flavour flv
///
/// 0 = nue, 1 = numu, 2 = nutau
///
double PMNS_Fast::P(int flv) const
{
  assert(flv>=0 && flv<3);
  return norm(fNuState[flv]);
}

////////////////////////////////////////////////////////////////////////
