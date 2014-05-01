#ifndef ProductionHeight_h
#define ProductionHeight_h

namespace AtNuOsc {
  double SimpleProdHeight();
  double FlatProdHeight();

  double MeanPionProdHeight(double CosZen, double Energy);
  double MeanMuonProdHeight(double CosZen, double Energy);

  double RandomKR(double BoverA);
  double RndmPionProdHeight(double CosZen, double Energy);
  double RndmMuonProdHeight(double CosZen, double Energy);

  double PDFMeanPionProdHeight(double CosZen, double Energy);
  double PDFMeanMuonProdHeight(double CosZen, double Energy);
}

#endif
