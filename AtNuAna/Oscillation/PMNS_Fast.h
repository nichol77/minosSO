////////////////////////////////////////////////////////////////////////
/// \class PMNS_Fast
///
/// \brief Implementation of oscillations of neutrinos in matter in a
///        three-neutrino framework. 
///
/// Three-flavour implementation based on the following references:
///
///......................................................................
///
/// PHYSICAL REVIEW D       VOLUME 86, NUMBER 11          1 DECEMBER 2012
///
///        Constraints for nonstandard interaction epsilon_etau V_e 
///               from nue appearance in MINOS and T2K
///
///    J. A. B. Coelho, T. Kafka, W. A. Mann, J. Schneps and O. Altinok
///            Tufts University, Medford, Massachusetts 02155
///                    (Received 1 October 2012)
///
///                            11 3015
///                            --
///......................................................................
///
/// Int. J. Mod. Phys. C       VOLUME 19, NUMBER 03            MARCH 2008
///
///     Efficient numerical diagonalization of hermitian 3x3 matrices
///
///                            Joachim Kopp
///                  Max–Planck–Institut für Kernphysik 
///             Postfach 10 39 80, 69029 Heidelberg, Germany
///                    (Received 19 October 2007)
///
///                                523
///......................................................................
///
/// The code structure follows the implementation written by M. Messier
/// in the PMNS class.
///
/// \version $Id: PMNS_Fast.h,v 1.1 2013/01/19 16:09:57 jcoelho Exp $
///
/// @author joao.coelho@tufts.edu
////////////////////////////////////////////////////////////////////////
#ifndef PMNS_Fast_H
#define PMNS_Fast_H
#include <complex>

namespace AtNuOsc {
  class PMNS_Fast {
  public:
    PMNS_Fast();
    
    /// Set the parameters of the PMNS matrix
    /// @param th12    - The angle theta_12 in radians
    /// @param th23    - The angle theta_23 in radians
    /// @param th13    - The angle theta_13 in radians
    /// @param deltacp - The CPV phase delta_CP in radians
    void SetMix(double th12, double th23, double th13, double deltacp);
    
    /// Set the mass-splittings
    /// @param dm21 - m2^2-m1^2 in eV^2
    /// @param dm32 - m3^2-m2^2 in eV^2
    void SetDeltaMsqrs(double dm21, double dm32);
    
    /// Propagate a neutrino through a slab of matter
    /// @param L - length of slab (km)
    /// @param E - neutrino energy in GeV
    /// @param Ne - electron number density of matter in mole/cm^3
    /// @param anti - +1 = neutrino case, -1 = anti-neutrino case
    void PropMatter(double L, double E, double Ne, int anti=1);
    
    /// Return the probability of final state in flavour flv
    /// @param flv - final flavor (0,1,2) = (nue,numu,nutau)
    double P(int flv) const;
    
    /// Erase memory of neutrino propagate and reset neutrino
    /// to pure flavour flv. Preserves values of mixing and mass-splittings
    /// @param flv - final flavor (0,1,2) = (nue,numu,nutau)
    void ResetToFlavour(int flv=1);
    
  private:
    // A shorthand...
    typedef std::complex<double> complex;
    
  private:
    /// Build H*lv, where H is the Hamiltonian in vacuum on flavour basis   
    /// and lv is the oscillation length
    void BuildHlv();

    /// Solve the full Hamiltonian for eigenvectors and eigenvalues
    /// @param E - neutrino energy in GeV
    /// @param Ne - electron number density of matter in mole/cm^3
    /// @param anti - +1 = neutrino case, -1 = anti-neutrino case
    void SolveHam(double E, double Ne, int anti);
    
  private:
    double  fDm21;          ///< m^2_2 - m^2_1 in vacuum
    double  fDm32;          ///< m^2_3 - m^2_2 in vacuum
    double  fDm31;          ///< m^2_3 - m^2_1 in vacuum
    double  fTheta12;       ///< theta12 mixing angle
    double  fTheta23;       ///< theta23 mixing angle
    double  fTheta13;       ///< theta13 mixing angle
    double  fDeltaCP;       ///< CP violating phase
    complex fHlv[3][3];     ///< dimensionless matrix H*lv
    complex fEvec[3][3];    ///< Eigenvectors of the Hamiltonian
    double  fEval[3];       ///< Eigenvalues of the Hamiltonian
    complex fNuState[3];    ///< The neutrino current state
    double  fCachedNe;      ///< Cached electron density
    double  fCachedE;       ///< Cached neutrino energy
    int     fCachedAnti;    ///< Cached nu/nubar selector
    bool    fBuiltHlv;      ///< Tag to avoid rebuilding Hlv
  };
}
#endif
////////////////////////////////////////////////////////////////////////
