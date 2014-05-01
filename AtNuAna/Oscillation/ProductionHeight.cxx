#include "ProductionHeight.h"

#include "TMath.h"
#include "TRandom.h"

#include <cmath>

namespace AtNuOsc
{
  double SimpleProdHeight()
  {
    return 25.0;
  }

  double FlatProdHeight()
  {
    return 15.0;
  }

  double MeanPionProdHeight(double CosZen, double Energy)
  {
    if( Energy <= 0.0 ) return FlatProdHeight();

    // if( CosZen < -0.2 ) return SimpleProdHeight();
    Double_t CosZenith = fabs(CosZen);

    return 35.0 - 31.0*CosZenith + 15.0*CosZenith*CosZenith;
  }
  
  double MeanMuonProdHeight(double CosZen, double Energy)
  {
    if( Energy <= 0.0 ) return FlatProdHeight();
    
    // if( CosZen < -0.2 ) return SimpleProdHeight();
    Double_t CosZenith = fabs(CosZen);

    double A = 12.0 + 12.5*exp(-3.2*CosZenith);
    double B = 10.1 - 19.8*CosZenith*CosZenith +
               13.2*CosZenith*CosZenith*CosZenith;
    double C = 0.11 + 0.27 * CosZenith;
    return A + B * exp(-C * Energy);
  }


  double RandomKR(double BoverA)
  {
    double MinX = (BoverA>=0)?0:-BoverA;
    double MaxY = 1/TMath::E();
    if(MinX > 1.0) MaxY = MinX*MinX*TMath::Exp(-MinX*MinX);

    while (1) {
      double R1 = gRandom->Uniform(MinX, 4);
      double R2 = gRandom->Uniform(0, MaxY);
      if(R1*R1*TMath::Exp(-R1*R1) < R2) continue;
      return R1;
    }
    return 0;
  }

  double RndmPionProdHeight(double CosZen, double Energy)
  {
    if( Energy <= 0.0 ) return FlatProdHeight();
    
    // if( CosZen < -0.2 ) return SimpleProdHeight();
    Double_t CosZenith = fabs(CosZen);

    double A = 14.0 - 2.6*CosZenith + 0.8*CosZenith*CosZenith;
    double B = 18.1 - 28.5*CosZenith + 14.5*CosZenith*CosZenith;

    double X = RandomKR(B / A);
    return (A*X + B);
  }

  double RndmMuonProdHeight(double CosZen, double Energy)
  {
    if( Energy <= 0.0) return FlatProdHeight();
    
    // if( CosZen < -0.2 ) return SimpleProdHeight();
    Double_t CosZenith = fabs(CosZen);

    double A = 14.8 + (1+2*CosZenith)*log10(Energy) +
               3*(1-CosZenith)*log10(Energy)*log10(Energy);
    double Alpha = 28.3 - 43.7*CosZenith + 41.7*CosZenith*CosZenith - 
                   16.3*CosZenith*CosZenith*CosZenith;
    double Beta = 0.035 + 0.243*CosZenith + 0.186*CosZenith*CosZenith;
    double B = Alpha*exp(-Beta * Energy) - 10.0;

    double X = RandomKR(B / A);
    return (A*X + B);
  }

  double PDFMeanPionProdHeight(double CosZen, double Energy)
  {
    if( Energy <= 0.0) return FlatProdHeight();
    
    // if( CosZen < -0.2 ) return SimpleProdHeight();
    Double_t CosZenith = fabs(CosZen);

    double A = 14.0 - 2.6*CosZenith + 0.8*CosZenith*CosZenith;
    double B = 18.1 - 28.5*CosZenith + 14.5*CosZenith*CosZenith;

    double PDFMean = 0;
    if (B >= 0) {
      PDFMean = (A / TMath::Gamma(3/2.)) + B;
    }
    else {
      PDFMean = (TMath::Exp(-B*B/(A*A))*(A*A + B*B) /
        (A * TMath::Gamma(3/2.) * (1.0 - TMath::Gamma(3/2., B*B/(A*A))))) +
        B;
    }
    return PDFMean;
  }

  double PDFMeanMuonProdHeight(double CosZen, double Energy)
  {
    if( Energy <= 0.0) return FlatProdHeight();

    // if( CosZen < -0.2 ) return SimpleProdHeight();
    Double_t CosZenith = fabs(CosZen);

    double A = 14.8 + (1+2*CosZenith)*log10(Energy) +
               3*(1-CosZenith)*log10(Energy)*log10(Energy);
    double Alpha = 28.3 - 43.7*CosZenith + 41.7*CosZenith*CosZenith - 
                   16.3*CosZenith*CosZenith*CosZenith;
    double Beta = 0.035 + 0.243*CosZenith + 0.186*CosZenith*CosZenith;
    double B = Alpha*exp(-Beta * Energy) - 10.0;

    double PDFMean = 0;
    if (B >= 0) {
      PDFMean = (A / TMath::Gamma(3/2.)) + B;
    }
    else {
      PDFMean = (TMath::Exp(-B*B/(A*A))*(A*A + B*B) /
        (A * TMath::Gamma(3/2.) * (1.0 - TMath::Gamma(3/2., B*B/(A*A))))) +
        B;
    }
    return PDFMean;
  }
}
