//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Fri May 28 10:15:11 2010 by ROOT version 5.20/00
// from TTree s/s
// found on file: /unix/minos1/rjn/2010/R2.2/data/near/dogwood3/pHE/micro2010/NuDSTMicro2010N00010233.root
//////////////////////////////////////////////////////////

#ifndef NuDstLooper_h
#define NuDstLooper_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TH1D.h>


class NuDstLooper {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

   // Declaration of leaf types
 //NuEvent         *s;
   UInt_t          fUniqueID;
   UInt_t          fBits;
   Int_t           index;
   Int_t           entry;
   Int_t           run;
   Int_t           subRun;
   Int_t           runType;
   Int_t           errorCode;
   Int_t           snarl;
   Int_t           trigSrc;
   Int_t           timeFrame;
   Int_t           remoteSpillType;
   Int_t           detector;
   Int_t           simFlag;
   Int_t           timeSec;
   Int_t           timeNanoSec;
   Double_t        timeSeconds;
   Double_t        trigtime;
   Double_t        medianTime;
   Double_t        timeEvtMin;
   Double_t        timeEvtMax;
   Double_t        crateT0;
   Int_t           nearestSpillSec;
   Int_t           nearestSpillNanosec;
   Double_t        timeToNearestSpill;
   Int_t           planeEvtHdrBeg;
   Int_t           planeEvtHdrEnd;
   Double_t        snarlPulseHeight;
   Bool_t          isGoodDataQuality;
   Bool_t          isGoodDataQualityRUN;
   Bool_t          isGoodDataQualityCOIL;
   Bool_t          isGoodDataQualityHV;
   Bool_t          isGoodDataQualityGPS;
   Int_t           numActiveCrates;
   Int_t           numTimeFrames;
   Int_t           numGoodSnarls;
   Float_t         snarlRateMedian;
   Float_t         snarlRateMax;
   Int_t           deltaSecToSpillGPS;
   Int_t           deltaNanoSecToSpillGPS;
   Int_t           gpsError;
   Int_t           gpsSpillType;
   Bool_t          coilIsOk;
   Bool_t          coilIsReverse;
   Float_t         coilCurrent;
   Bool_t          isLI;
   Int_t           litag;
   Double_t        litime;
   Float_t         energy;
   Float_t         energyCC;
   Float_t         energyNC;
   Float_t         energyRM;
   Float_t         trkEn;
   Float_t         trkEnRange;
   Float_t         trkEnCurv;
   Float_t         shwEn;
   Float_t         shwEnCC;
   Float_t         shwEnNC;
   Float_t         resolution;
   Bool_t          isInFidVolCC;
   Bool_t          isGoodTrackReclamation;
   Bool_t          isNCClean;
   Float_t         y;
   Float_t         q2;
   Float_t         x;
   Float_t         w2;
   Float_t         dirCosNu;
   Int_t           evt;
   Int_t           slc;
   Int_t           nevt;
   Int_t           ndigitEvt;
   Int_t           nstripEvt;
   Int_t           nshw;
   Int_t           ntrk;
   Int_t           primshw;
   Int_t           primtrk;
   Float_t         rawPhEvt;
   Float_t         evtphsigcor;
   Float_t         evtphsigmap;
   Int_t           planeEvtN;
   Int_t           planeEvtNu;
   Int_t           planeEvtNv;
   Float_t         roIDEvt;
   Float_t         knn01TrkActivePlanesEvt;
   Float_t         knn10TrkMeanPhEvt;
   Float_t         knn20LowHighPhEvt;
   Float_t         knn40TrkPhFracEvt;
   Float_t         roIDNuMuBarEvt;
   Float_t         relativeAngleEvt;
   Float_t         jmIDEvt;
   Float_t         jmTrackPlaneEvt;
   Float_t         jmEndPhEvt;
   Float_t         jmMeanPhEvt;
   Float_t         jmScatteringUEvt;
   Float_t         jmScatteringVEvt;
   Float_t         jmScatteringUVEvt;
   Float_t         jmEventknnIDEvt;
   Float_t         jmEventknn208Evt;
   Float_t         jmEventknn207Evt;
   Float_t         jmEventknn206Evt;
   Float_t         jmEventknn205Evt;
   Float_t         jmEventknn204Evt;
   Float_t         xEvtVtx;
   Float_t         yEvtVtx;
   Float_t         zEvtVtx;
   Float_t         uEvtVtx;
   Float_t         vEvtVtx;
   Int_t           planeEvtVtx;
   Int_t           planeEvtBeg;
   Int_t           planeEvtBegu;
   Int_t           planeEvtBegv;
   Float_t         xEvtEnd;
   Float_t         yEvtEnd;
   Float_t         zEvtEnd;
   Float_t         uEvtEnd;
   Float_t         vEvtEnd;
   Int_t           planeEvtEnd;
   Int_t           planeEvtEndu;
   Int_t           planeEvtEndv;
   Bool_t          trkExists;
   Int_t           trkIndex;
   Int_t           ndigitTrk;
   Int_t           nstripTrk;
   Float_t         trkEnCorRange;
   Float_t         trkEnCorCurv;
   Float_t         trkShwEnNear;
   Float_t         trkShwEnNearDW;
   Float_t         trkMomentumRange;
   Float_t         trkMomentumTransverse;
   Float_t         trkResolution;
   Int_t           containedTrk;
   Int_t           trkfitpass;
   Float_t         trkvtxdcosz;
   Float_t         trkvtxdcosy;
   Int_t           trknplane;
   Int_t           charge;
   Float_t         qp;
   Float_t         qp_rangebiased;
   Float_t         sigqp;
   Float_t         qp_sigqp;
   Float_t         chi2;
   Float_t         ndof;
   Float_t         qpFraction;
   Int_t           trkVtxUVDiffPl;
   Int_t           trkLength;
   Int_t           planeTrkNu;
   Int_t           planeTrkNv;
   Int_t           ntrklike;
   Float_t         trkphsigcor;
   Float_t         trkphsigmap;
   Int_t           trkIdMC;
   Int_t           trkfitpassSA;
   Float_t         trkvtxdcoszSA;
   Int_t           chargeSA;
   Float_t         qpSA;
   Float_t         sigqpSA;
   Float_t         chi2SA;
   Float_t         ndofSA;
   Float_t         probSA;
   Float_t         xTrkVtxSA;
   Float_t         yTrkVtxSA;
   Float_t         zTrkVtxSA;
   Float_t         uTrkVtxSA;
   Float_t         vTrkVtxSA;
   Float_t         jitter;
   Float_t         jPID;
   Float_t         majC;
   Float_t         smoothMajC;
   Float_t         xTrkVtx;
   Float_t         yTrkVtx;
   Float_t         zTrkVtx;
   Float_t         uTrkVtx;
   Float_t         vTrkVtx;
   Int_t           planeTrkVtx;
   Int_t           planeTrkBeg;
   Int_t           planeTrkBegu;
   Int_t           planeTrkBegv;
   Int_t           stripTrkBeg;
   Int_t           stripTrkBegu;
   Int_t           stripTrkBegv;
   Short_t         stripTrkEnd;
   Short_t         stripTrkEndu;
   Short_t         stripTrkEndv;
   Bool_t          stripTrkBegIsu;
   Bool_t          stripTrkEndIsu;
   Int_t           regionTrkVtx;
   Char_t          edgeRegionTrkVtx;
   Char_t          edgeRegionTrkEnd;
   Float_t         phiTrkVtx;
   Float_t         phiTrkEnd;
   Short_t         parallelStripTrkVtx;
   Short_t         parallelStripTrkVtxNoShift;
   Short_t         parallelStripTrkEnd;
   Char_t          stripTrkBegPerpFlag;
   Char_t          stripTrkEndPerpFlag;
   Short_t         stripHoveNumTrkVtx;
   Short_t         stripHoveNumTrkVtxNoShift;
   Short_t         stripHoveNumTrkEnd;
   Float_t         xTrkEnd;
   Float_t         yTrkEnd;
   Float_t         zTrkEnd;
   Float_t         uTrkEnd;
   Float_t         vTrkEnd;
   Int_t           planeTrkEnd;
   Int_t           planeTrkEndu;
   Int_t           planeTrkEndv;
   Float_t         drTrkFidall;
   Float_t         dzTrkFidall;
   Float_t         drTrkFidvtx;
   Float_t         dzTrkFidvtx;
   Float_t         drTrkFidend;
   Float_t         dzTrkFidend;
   Float_t         traceTrkFidall;
   Float_t         traceTrkFidvtx;
   Float_t         traceTrkFidend;
   Float_t         cosPrTrkVtx;
   Bool_t          shwExists;
   Int_t           ndigitShw;
   Int_t           nstripShw;
   Int_t           nplaneShw;
   Float_t         shwEnCor;
   Float_t         shwEnNoCor;
   Float_t         shwEnMip;
   Float_t         shwEnLinCCNoCor;
   Float_t         shwEnLinCCCor;
   Float_t         shwEnWtCCNoCor;
   Float_t         shwEnWtCCCor;
   Float_t         shwEnLinNCNoCor;
   Float_t         shwEnLinNCCor;
   Float_t         shwEnWtNCNoCor;
   Float_t         shwEnWtNCCor;
   Float_t         shwResolution;
   Float_t         shwEnkNN;
   Float_t         shwEnReskNN;
   Int_t           planeShwBeg;
   Int_t           planeShwEnd;
   Int_t           planeShwMax;
   Float_t         xShwVtx;
   Float_t         yShwVtx;
   Float_t         zShwVtx;
   Bool_t          trkExists1;
   Int_t           trkIndex1;
   Int_t           ndigitTrk1;
   Int_t           nstripTrk1;
   Float_t         trkEnCorRange1;
   Float_t         trkEnCorCurv1;
   Float_t         trkShwEnNear1;
   Float_t         trkShwEnNearDW1;
   Float_t         trkMomentumRange1;
   Float_t         trkMomentumTransverse1;
   Int_t           containedTrk1;
   Int_t           trkfitpass1;
   Float_t         trkvtxdcosz1;
   Float_t         trkvtxdcosy1;
   Int_t           trknplane1;
   Int_t           charge1;
   Float_t         qp1;
   Float_t         qp_rangebiased1;
   Float_t         sigqp1;
   Float_t         qp_sigqp1;
   Float_t         chi21;
   Float_t         ndof1;
   Float_t         qpFraction1;
   Int_t           trkVtxUVDiffPl1;
   Int_t           trkLength1;
   Int_t           planeTrkNu1;
   Int_t           planeTrkNv1;
   Int_t           ntrklike1;
   Float_t         trkphsigcor1;
   Float_t         trkphsigmap1;
   Int_t           trkIdMC1;
   Int_t           trkfitpassSA1;
   Float_t         trkvtxdcoszSA1;
   Int_t           chargeSA1;
   Float_t         qpSA1;
   Float_t         sigqpSA1;
   Float_t         chi2SA1;
   Float_t         ndofSA1;
   Float_t         probSA1;
   Float_t         xTrkVtxSA1;
   Float_t         yTrkVtxSA1;
   Float_t         zTrkVtxSA1;
   Float_t         uTrkVtxSA1;
   Float_t         vTrkVtxSA1;
   Float_t         jitter1;
   Float_t         jPID1;
   Float_t         majC1;
   Float_t         smoothMajC1;
   Float_t         roID1;
   Float_t         knn01TrkActivePlanes1;
   Float_t         knn10TrkMeanPh1;
   Float_t         knn20LowHighPh1;
   Float_t         knn40TrkPhFrac1;
   Float_t         roIDNuMuBar1;
   Float_t         relativeAngle1;
   Float_t         jmID1;
   Float_t         jmTrackPlane1;
   Float_t         jmEndPh1;
   Float_t         jmMeanPh1;
   Float_t         jmScatteringU1;
   Float_t         jmScatteringV1;
   Float_t         jmScatteringUV1;
   Float_t         xTrkVtx1;
   Float_t         yTrkVtx1;
   Float_t         zTrkVtx1;
   Float_t         uTrkVtx1;
   Float_t         vTrkVtx1;
   Int_t           planeTrkVtx1;
   Int_t           planeTrkBeg1;
   Int_t           planeTrkBegu1;
   Int_t           planeTrkBegv1;
   Int_t           stripTrkBeg1;
   Int_t           stripTrkBegu1;
   Int_t           stripTrkBegv1;
   Short_t         stripTrkEnd1;
   Short_t         stripTrkEndu1;
   Short_t         stripTrkEndv1;
   Bool_t          stripTrkBegIsu1;
   Bool_t          stripTrkEndIsu1;
   Int_t           regionTrkVtx1;
   Char_t          edgeRegionTrkVtx1;
   Char_t          edgeRegionTrkEnd1;
   Float_t         phiTrkVtx1;
   Float_t         phiTrkEnd1;
   Short_t         parallelStripTrkVtx1;
   Short_t         parallelStripTrkEnd1;
   Char_t          stripTrkBegPerpFlag1;
   Char_t          stripTrkEndPerpFlag1;
   Short_t         stripHoveNumTrkVtx1;
   Short_t         stripHoveNumTrkEnd1;
   Float_t         xTrkEnd1;
   Float_t         yTrkEnd1;
   Float_t         zTrkEnd1;
   Float_t         uTrkEnd1;
   Float_t         vTrkEnd1;
   Int_t           planeTrkEnd1;
   Int_t           planeTrkEndu1;
   Int_t           planeTrkEndv1;
   Float_t         drTrkFidall1;
   Float_t         dzTrkFidall1;
   Float_t         drTrkFidvtx1;
   Float_t         dzTrkFidvtx1;
   Float_t         drTrkFidend1;
   Float_t         dzTrkFidend1;
   Float_t         traceTrkFidall1;
   Float_t         traceTrkFidvtx1;
   Float_t         traceTrkFidend1;
   Float_t         cosPrTrkVtx1;
   Bool_t          shwExists1;
   Int_t           ndigitShw1;
   Int_t           nstripShw1;
   Int_t           nplaneShw1;
   Float_t         shwEnCor1;
   Float_t         shwEnNoCor1;
   Float_t         shwEnLinCCNoCor1;
   Float_t         shwEnLinCCCor1;
   Float_t         shwEnWtCCNoCor1;
   Float_t         shwEnWtCCCor1;
   Float_t         shwEnLinNCNoCor1;
   Float_t         shwEnLinNCCor1;
   Float_t         shwEnWtNCNoCor1;
   Float_t         shwEnWtNCCor1;
   Float_t         shwEnMip1;
   Int_t           planeShwBeg1;
   Int_t           planeShwEnd1;
   Int_t           planeShwMax1;
   Float_t         xShwVtx1;
   Float_t         yShwVtx1;
   Float_t         zShwVtx1;
   Bool_t          trkExists2;
   Int_t           trkIndex2;
   Int_t           ndigitTrk2;
   Int_t           nstripTrk2;
   Float_t         trkEnCorRange2;
   Float_t         trkEnCorCurv2;
   Float_t         trkShwEnNear2;
   Float_t         trkShwEnNearDW2;
   Float_t         trkMomentumRange2;
   Float_t         trkMomentumTransverse2;
   Int_t           containedTrk2;
   Int_t           trkfitpass2;
   Float_t         trkvtxdcosz2;
   Float_t         trkvtxdcosy2;
   Int_t           trknplane2;
   Int_t           charge2;
   Float_t         qp2;
   Float_t         qp_rangebiased2;
   Float_t         sigqp2;
   Float_t         qp_sigqp2;
   Float_t         chi22;
   Float_t         ndof2;
   Float_t         qpFraction2;
   Int_t           trkVtxUVDiffPl2;
   Int_t           trkLength2;
   Int_t           planeTrkNu2;
   Int_t           planeTrkNv2;
   Int_t           ntrklike2;
   Float_t         trkphsigcor2;
   Float_t         trkphsigmap2;
   Int_t           trkIdMC2;
   Int_t           trkfitpassSA2;
   Float_t         trkvtxdcoszSA2;
   Int_t           chargeSA2;
   Float_t         qpSA2;
   Float_t         sigqpSA2;
   Float_t         chi2SA2;
   Float_t         ndofSA2;
   Float_t         probSA2;
   Float_t         xTrkVtxSA2;
   Float_t         yTrkVtxSA2;
   Float_t         zTrkVtxSA2;
   Float_t         uTrkVtxSA2;
   Float_t         vTrkVtxSA2;
   Float_t         jitter2;
   Float_t         jPID2;
   Float_t         majC2;
   Float_t         smoothMajC2;
   Float_t         roID2;
   Float_t         knn01TrkActivePlanes2;
   Float_t         knn10TrkMeanPh2;
   Float_t         knn20LowHighPh2;
   Float_t         knn40TrkPhFrac2;
   Float_t         roIDNuMuBar2;
   Float_t         relativeAngle2;
   Float_t         jmID2;
   Float_t         jmTrackPlane2;
   Float_t         jmEndPh2;
   Float_t         jmMeanPh2;
   Float_t         jmScatteringU2;
   Float_t         jmScatteringV2;
   Float_t         jmScatteringUV2;
   Float_t         xTrkVtx2;
   Float_t         yTrkVtx2;
   Float_t         zTrkVtx2;
   Float_t         uTrkVtx2;
   Float_t         vTrkVtx2;
   Int_t           planeTrkVtx2;
   Int_t           planeTrkBeg2;
   Int_t           planeTrkBegu2;
   Int_t           planeTrkBegv2;
   Int_t           stripTrkBeg2;
   Int_t           stripTrkBegu2;
   Int_t           stripTrkBegv2;
   Short_t         stripTrkEnd2;
   Short_t         stripTrkEndu2;
   Short_t         stripTrkEndv2;
   Bool_t          stripTrkBegIsu2;
   Bool_t          stripTrkEndIsu2;
   Int_t           regionTrkVtx2;
   Char_t          edgeRegionTrkVtx2;
   Char_t          edgeRegionTrkEnd2;
   Float_t         phiTrkVtx2;
   Float_t         phiTrkEnd2;
   Short_t         parallelStripTrkVtx2;
   Short_t         parallelStripTrkEnd2;
   Char_t          stripTrkBegPerpFlag2;
   Char_t          stripTrkEndPerpFlag2;
   Short_t         stripHoveNumTrkVtx2;
   Short_t         stripHoveNumTrkEnd2;
   Float_t         xTrkEnd2;
   Float_t         yTrkEnd2;
   Float_t         zTrkEnd2;
   Float_t         uTrkEnd2;
   Float_t         vTrkEnd2;
   Int_t           planeTrkEnd2;
   Int_t           planeTrkEndu2;
   Int_t           planeTrkEndv2;
   Float_t         drTrkFidall2;
   Float_t         dzTrkFidall2;
   Float_t         drTrkFidvtx2;
   Float_t         dzTrkFidvtx2;
   Float_t         drTrkFidend2;
   Float_t         dzTrkFidend2;
   Float_t         traceTrkFidall2;
   Float_t         traceTrkFidvtx2;
   Float_t         traceTrkFidend2;
   Float_t         cosPrTrkVtx2;
   Bool_t          shwExists2;
   Int_t           ndigitShw2;
   Int_t           nstripShw2;
   Int_t           nplaneShw2;
   Float_t         shwEnCor2;
   Float_t         shwEnNoCor2;
   Float_t         shwEnLinCCNoCor2;
   Float_t         shwEnLinCCCor2;
   Float_t         shwEnWtCCNoCor2;
   Float_t         shwEnWtCCCor2;
   Float_t         shwEnLinNCNoCor2;
   Float_t         shwEnLinNCCor2;
   Float_t         shwEnWtNCNoCor2;
   Float_t         shwEnWtNCCor2;
   Float_t         shwEnMip2;
   Int_t           planeShwBeg2;
   Int_t           planeShwEnd2;
   Int_t           planeShwMax2;
   Float_t         xShwVtx2;
   Float_t         yShwVtx2;
   Float_t         zShwVtx2;
   Bool_t          trkExists3;
   Int_t           trkIndex3;
   Int_t           ndigitTrk3;
   Int_t           nstripTrk3;
   Float_t         trkEnCorRange3;
   Float_t         trkEnCorCurv3;
   Float_t         trkShwEnNear3;
   Float_t         trkShwEnNearDW3;
   Float_t         trkMomentumRange3;
   Float_t         trkMomentumTransverse3;
   Int_t           containedTrk3;
   Int_t           trkfitpass3;
   Float_t         trkvtxdcosz3;
   Float_t         trkvtxdcosy3;
   Int_t           trknplane3;
   Int_t           charge3;
   Float_t         qp3;
   Float_t         qp_rangebiased3;
   Float_t         sigqp3;
   Float_t         qp_sigqp3;
   Float_t         chi23;
   Float_t         ndof3;
   Float_t         qpFraction3;
   Int_t           trkVtxUVDiffPl3;
   Int_t           trkLength3;
   Int_t           planeTrkNu3;
   Int_t           planeTrkNv3;
   Int_t           ntrklike3;
   Float_t         trkphsigcor3;
   Float_t         trkphsigmap3;
   Int_t           trkIdMC3;
   Int_t           trkfitpassSA3;
   Float_t         trkvtxdcoszSA3;
   Int_t           chargeSA3;
   Float_t         qpSA3;
   Float_t         sigqpSA3;
   Float_t         chi2SA3;
   Float_t         ndofSA3;
   Float_t         probSA3;
   Float_t         xTrkVtxSA3;
   Float_t         yTrkVtxSA3;
   Float_t         zTrkVtxSA3;
   Float_t         uTrkVtxSA3;
   Float_t         vTrkVtxSA3;
   Float_t         jitter3;
   Float_t         jPID3;
   Float_t         majC3;
   Float_t         smoothMajC3;
   Float_t         roID3;
   Float_t         knn01TrkActivePlanes3;
   Float_t         knn10TrkMeanPh3;
   Float_t         knn20LowHighPh3;
   Float_t         knn40TrkPhFrac3;
   Float_t         roIDNuMuBar3;
   Float_t         relativeAngle3;
   Float_t         jmID3;
   Float_t         jmTrackPlane3;
   Float_t         jmEndPh3;
   Float_t         jmMeanPh3;
   Float_t         jmScatteringU3;
   Float_t         jmScatteringV3;
   Float_t         jmScatteringUV3;
   Float_t         xTrkVtx3;
   Float_t         yTrkVtx3;
   Float_t         zTrkVtx3;
   Float_t         uTrkVtx3;
   Float_t         vTrkVtx3;
   Int_t           planeTrkVtx3;
   Int_t           planeTrkBeg3;
   Int_t           planeTrkBegu3;
   Int_t           planeTrkBegv3;
   Int_t           stripTrkBeg3;
   Int_t           stripTrkBegu3;
   Int_t           stripTrkBegv3;
   Short_t         stripTrkEnd3;
   Short_t         stripTrkEndu3;
   Short_t         stripTrkEndv3;
   Bool_t          stripTrkBegIsu3;
   Bool_t          stripTrkEndIsu3;
   Int_t           regionTrkVtx3;
   Char_t          edgeRegionTrkVtx3;
   Char_t          edgeRegionTrkEnd3;
   Float_t         phiTrkVtx3;
   Float_t         phiTrkEnd3;
   Short_t         parallelStripTrkVtx3;
   Short_t         parallelStripTrkEnd3;
   Char_t          stripTrkBegPerpFlag3;
   Char_t          stripTrkEndPerpFlag3;
   Short_t         stripHoveNumTrkVtx3;
   Short_t         stripHoveNumTrkEnd3;
   Float_t         xTrkEnd3;
   Float_t         yTrkEnd3;
   Float_t         zTrkEnd3;
   Float_t         uTrkEnd3;
   Float_t         vTrkEnd3;
   Int_t           planeTrkEnd3;
   Int_t           planeTrkEndu3;
   Int_t           planeTrkEndv3;
   Float_t         drTrkFidall3;
   Float_t         dzTrkFidall3;
   Float_t         drTrkFidvtx3;
   Float_t         dzTrkFidvtx3;
   Float_t         drTrkFidend3;
   Float_t         dzTrkFidend3;
   Float_t         traceTrkFidall3;
   Float_t         traceTrkFidvtx3;
   Float_t         traceTrkFidend3;
   Float_t         cosPrTrkVtx3;
   Bool_t          shwExists3;
   Int_t           ndigitShw3;
   Int_t           nstripShw3;
   Int_t           nplaneShw3;
   Float_t         shwEnCor3;
   Float_t         shwEnNoCor3;
   Float_t         shwEnLinCCNoCor3;
   Float_t         shwEnLinCCCor3;
   Float_t         shwEnWtCCNoCor3;
   Float_t         shwEnWtCCCor3;
   Float_t         shwEnLinNCNoCor3;
   Float_t         shwEnLinNCCor3;
   Float_t         shwEnWtNCNoCor3;
   Float_t         shwEnWtNCCor3;
   Float_t         shwEnMip3;
   Int_t           planeShwBeg3;
   Int_t           planeShwEnd3;
   Int_t           planeShwMax3;
   Float_t         xShwVtx3;
   Float_t         yShwVtx3;
   Float_t         zShwVtx3;
   Bool_t          shwExists4;
   Int_t           ndigitShw4;
   Int_t           nstripShw4;
   Int_t           nplaneShw4;
   Float_t         shwEnCor4;
   Float_t         shwEnNoCor4;
   Float_t         shwEnLinCCNoCor4;
   Float_t         shwEnLinCCCor4;
   Float_t         shwEnWtCCNoCor4;
   Float_t         shwEnWtCCCor4;
   Float_t         shwEnLinNCNoCor4;
   Float_t         shwEnLinNCCor4;
   Float_t         shwEnWtNCNoCor4;
   Float_t         shwEnWtNCCor4;
   Float_t         shwEnMip4;
   Int_t           planeShwBeg4;
   Int_t           planeShwEnd4;
   Int_t           planeShwMax4;
   Float_t         xShwVtx4;
   Float_t         yShwVtx4;
   Float_t         zShwVtx4;
   Bool_t          shwExists5;
   Int_t           ndigitShw5;
   Int_t           nstripShw5;
   Int_t           nplaneShw5;
   Float_t         shwEnCor5;
   Float_t         shwEnNoCor5;
   Float_t         shwEnLinCCNoCor5;
   Float_t         shwEnLinCCCor5;
   Float_t         shwEnWtCCNoCor5;
   Float_t         shwEnWtCCCor5;
   Float_t         shwEnLinNCNoCor5;
   Float_t         shwEnLinNCCor5;
   Float_t         shwEnWtNCNoCor5;
   Float_t         shwEnWtNCCor5;
   Float_t         shwEnMip5;
   Int_t           planeShwBeg5;
   Int_t           planeShwEnd5;
   Int_t           planeShwMax5;
   Float_t         xShwVtx5;
   Float_t         yShwVtx5;
   Float_t         zShwVtx5;
   Float_t         rEvtVtx;
   Float_t         rEvtEnd;
   Float_t         distToEdgeEvtVtx;
   Int_t           evtVtxUVDiffPl;
   Float_t         rTrkVtx;
   Float_t         rTrkEnd;
   Float_t         sigqp_qp;
   Float_t         chi2PerNdof;
   Float_t         prob;
   Int_t           containmentFlag;
   Int_t           containmentFlagCC0093Std;
   Int_t           containmentFlagCC0250Std;
   Int_t           containmentFlagPitt;
   Int_t           usedRange;
   Int_t           usedCurv;
   Float_t         rw;
   Float_t         fluxErr;
   Float_t         rwActual;
   Float_t         generatorWeight;
   Float_t         detectorWeight;
   Float_t         trkEnWeight;
   Float_t         shwEnWeight;
   Float_t         beamWeight;
   Float_t         fluxErrHadProdAfterTune;
   Float_t         fluxErrTotalErrorPreTune;
   Float_t         fluxErrTotalErrorAfterTune;
   Float_t         detectorWeightNMB;
   Float_t         detectorWeightNM;
   Float_t         trkEnWeightRunI;
   Float_t         shwEnWeightRunI;
   Float_t         beamWeightRunI;
   Float_t         fluxErrHadProdAfterTuneRunI;
   Float_t         fluxErrTotalErrorPreTuneRunI;
   Float_t         fluxErrTotalErrorAfterTuneRunI;
   Float_t         detectorWeightNMBRunI;
   Float_t         detectorWeightNMRunI;
   Float_t         trkEnWeightRunII;
   Float_t         shwEnWeightRunII;
   Float_t         beamWeightRunII;
   Float_t         fluxErrHadProdAfterTuneRunII;
   Float_t         fluxErrTotalErrorPreTuneRunII;
   Float_t         fluxErrTotalErrorAfterTuneRunII;
   Float_t         detectorWeightNMBRunII;
   Float_t         detectorWeightNMRunII;
   Float_t         energyRw;
   Float_t         energyNoRw;
   Float_t         trkEnRw;
   Float_t         trkEnNoRw;
   Float_t         shwEnRw;
   Float_t         shwEnNoRw;
   Float_t         dpID;
   Float_t         abID;
   Float_t         roID;
   Float_t         knn01TrkActivePlanes;
   Float_t         knn10TrkMeanPh;
   Float_t         knn20LowHighPh;
   Float_t         knn40TrkPhFrac;
   Float_t         roIDNuMuBar;
   Float_t         relativeAngle;
   Float_t         poID;
   Float_t         poIDKin;
   Float_t         jmID;
   Float_t         jmTrackPlane;
   Float_t         jmEndPh;
   Float_t         jmMeanPh;
   Float_t         jmScatteringU;
   Float_t         jmScatteringV;
   Float_t         jmScatteringUV;
   Float_t         jmEventknnID;
   Float_t         jmEventknn208;
   Float_t         jmEventknn207;
   Float_t         jmEventknn206;
   Float_t         jmEventknn205;
   Float_t         jmEventknn204;
   Float_t         closeTimeDeltaZ;
   Int_t           edgeActivityStrips;
   Float_t         edgeActivityPH;
   Int_t           oppEdgeStrips;
   Float_t         oppEdgePH;
   Float_t         vtxMetersToCoilEvt;
   Float_t         vtxMetersToCloseEdgeEvt;
   Double_t        minTimeSeparation;
   Float_t         transverseRMSU;
   Float_t         transverseRMSV;
   Float_t         dtdz;
   Float_t         endMetersToCloseEdge;
   Float_t         vtxMetersToCloseEdgeTrk;
   Float_t         vtxMetersToCoilTrk;
   Float_t         traceEndZ;
   Float_t         pot;
   Float_t         potDB;
   Float_t         potSinceLastEvt;
   Float_t         potSinceLastEvtGood;
   Float_t         potSinceLastEvtBad;
   Float_t         potSinceLastEvtDB;
   Float_t         potSinceLastEvtGoodDB;
   Float_t         potSinceLastEvtBadDB;
   Int_t           runPeriod;
   Bool_t          hornIsReverse;
   Int_t           beamTypeDB;
   Int_t           beamType;
   Float_t         intensity;
   Float_t         hornCur;
   Bool_t          goodBeam;
   Bool_t          goodBeamSntp;
   Bool_t          isInFidVolCCMC;
   Float_t         energyMC;
   Float_t         neuEnMC;
   Float_t         neuPxMC;
   Float_t         neuPyMC;
   Float_t         neuPzMC;
   Float_t         mu1EnMC;
   Float_t         mu1PxMC;
   Float_t         mu1PyMC;
   Float_t         mu1PzMC;
   Float_t         tgtEnMC;
   Float_t         tgtPxMC;
   Float_t         tgtPyMC;
   Float_t         tgtPzMC;
   Int_t           zMC;
   Int_t           aMC;
   Int_t           nucleusMC;
   Int_t           initialStateMC;
   Int_t           hadronicFinalStateMC;
   Int_t           numPreInukeFSprotMC;
   Int_t           numPreInukeFSneutMC;
   Float_t         maxMomPreInukeFSprotMC;
   Float_t         maxMomPreInukeFSneutMC;
   Float_t         yMC;
   Float_t         y2MC;
   Float_t         xMC;
   Float_t         q2MC;
   Float_t         w2MC;
   Float_t         trkEnMC;
   Float_t         trkEn2MC;
   Float_t         shwEnMC;
   Float_t         shwEn2MC;
   Float_t         trkEndEnMC;
   Float_t         trkStartEnMC;
   Bool_t          trkContainmentMC;
   Float_t         sigma;
   Int_t           iaction;
   Int_t           iresonance;
   Int_t           inu;
   Int_t           inunoosc;
   Int_t           itg;
   Float_t         vtxxMC;
   Float_t         vtxyMC;
   Float_t         vtxzMC;
   Float_t         vtxuMC;
   Float_t         vtxvMC;
   Int_t           planeTrkVtxMC;
   Float_t         rTrkVtxMC;
   Int_t           mc;
   Int_t           mcTrk;
   Int_t           mcShw;
   Int_t           mcEvt;
   Int_t           mcTrk1;
   Int_t           mcTrk2;
   Int_t           mcTrk3;
   Int_t           mcShw1;
   Int_t           mcShw2;
   Int_t           mcShw3;
   Int_t           mcShw4;
   Int_t           mcShw5;
   Float_t         Npz;
   Float_t         NdxdzNea;
   Float_t         NdydzNea;
   Float_t         NenergyN;
   Float_t         NWtNear;
   Float_t         NdxdzFar;
   Float_t         NdydzFar;
   Float_t         NenergyF;
   Float_t         NWtFar;
   Int_t           Ndecay;
   Float_t         Vx;
   Float_t         Vy;
   Float_t         Vz;
   Float_t         pdPx;
   Float_t         pdPy;
   Float_t         pdPz;
   Float_t         ppdxdz;
   Float_t         ppdydz;
   Float_t         pppz;
   Float_t         ppenergy;
   Float_t         ppmedium;
   Float_t         ppvx;
   Float_t         ppvy;
   Float_t         ppvz;
   Int_t           ptype;
   Float_t         Necm;
   Float_t         Nimpwt;
   Float_t         tvx;
   Float_t         tvy;
   Float_t         tvz;
   Float_t         tpx;
   Float_t         tpy;
   Float_t         tpz;
   Int_t           tptype;
   Int_t           tgen;
   Int_t           InukeNwts;
   Float_t         InukePiCExchgP;
   Float_t         InukePiCExchgN;
   Float_t         InukePiEScatP;
   Float_t         InukePiEScatN;
   Float_t         InukePiInEScatP;
   Float_t         InukePiInEScatN;
   Float_t         InukePiAbsorbP;
   Float_t         InukePiAbsorbN;
   Float_t         InukePi2PiP;
   Float_t         InukePi2PiN;
   Float_t         InukeNknockP;
   Float_t         InukeNknockN;
   Float_t         InukeNNPiP;
   Float_t         InukeNNPiN;
   Float_t         InukeFormTP;
   Float_t         InukeFormTN;
   Float_t         InukePiXsecP;
   Float_t         InukePiXsecN;
   Float_t         InukeNXsecP;
   Float_t         InukeNXsecN;
   Float_t         InukeNucrad;
   Float_t         InukeWrad;
   Int_t           anaVersion;
   Int_t           releaseType;
   Int_t           recoVersion;
   Int_t           mcVersion;
   Int_t           reweightVersion;
   Bool_t          useGeneratorReweight;
   std::string          sGeneratorConfigName;
   Int_t           generatorConfigNo;
   Bool_t          useDBForDataQuality;
   Bool_t          useDBForSpillTiming;
   Bool_t          useDBForBeamInfo;
   Bool_t          cutOnDataQuality;
   Bool_t          cutOnSpillTiming;
   Bool_t          cutOnBeamInfo;
   Bool_t          applyEnergyShifts;
   Bool_t          applyBeamWeight;
   Bool_t          apply1SigmaWeight;
   Bool_t          applyDetectorWeight;
   Bool_t          applyGeneratorWeight;
   Bool_t          calcMajCurv;
   Bool_t          calcRoID;
   Bool_t          calcJmID;

   // List of branches
   TBranch        *b_s_fUniqueID;   //!
   TBranch        *b_s_fBits;   //!
   TBranch        *b_s_index;   //!
   TBranch        *b_s_entry;   //!
   TBranch        *b_s_run;   //!
   TBranch        *b_s_subRun;   //!
   TBranch        *b_s_runType;   //!
   TBranch        *b_s_errorCode;   //!
   TBranch        *b_s_snarl;   //!
   TBranch        *b_s_trigSrc;   //!
   TBranch        *b_s_timeFrame;   //!
   TBranch        *b_s_remoteSpillType;   //!
   TBranch        *b_s_detector;   //!
   TBranch        *b_s_simFlag;   //!
   TBranch        *b_s_timeSec;   //!
   TBranch        *b_s_timeNanoSec;   //!
   TBranch        *b_s_timeSeconds;   //!
   TBranch        *b_s_trigtime;   //!
   TBranch        *b_s_medianTime;   //!
   TBranch        *b_s_timeEvtMin;   //!
   TBranch        *b_s_timeEvtMax;   //!
   TBranch        *b_s_crateT0;   //!
   TBranch        *b_s_nearestSpillSec;   //!
   TBranch        *b_s_nearestSpillNanosec;   //!
   TBranch        *b_s_timeToNearestSpill;   //!
   TBranch        *b_s_planeEvtHdrBeg;   //!
   TBranch        *b_s_planeEvtHdrEnd;   //!
   TBranch        *b_s_snarlPulseHeight;   //!
   TBranch        *b_s_isGoodDataQuality;   //!
   TBranch        *b_s_isGoodDataQualityRUN;   //!
   TBranch        *b_s_isGoodDataQualityCOIL;   //!
   TBranch        *b_s_isGoodDataQualityHV;   //!
   TBranch        *b_s_isGoodDataQualityGPS;   //!
   TBranch        *b_s_numActiveCrates;   //!
   TBranch        *b_s_numTimeFrames;   //!
   TBranch        *b_s_numGoodSnarls;   //!
   TBranch        *b_s_snarlRateMedian;   //!
   TBranch        *b_s_snarlRateMax;   //!
   TBranch        *b_s_deltaSecToSpillGPS;   //!
   TBranch        *b_s_deltaNanoSecToSpillGPS;   //!
   TBranch        *b_s_gpsError;   //!
   TBranch        *b_s_gpsSpillType;   //!
   TBranch        *b_s_coilIsOk;   //!
   TBranch        *b_s_coilIsReverse;   //!
   TBranch        *b_s_coilCurrent;   //!
   TBranch        *b_s_isLI;   //!
   TBranch        *b_s_litag;   //!
   TBranch        *b_s_litime;   //!
   TBranch        *b_s_energy;   //!
   TBranch        *b_s_energyCC;   //!
   TBranch        *b_s_energyNC;   //!
   TBranch        *b_s_energyRM;   //!
   TBranch        *b_s_trkEn;   //!
   TBranch        *b_s_trkEnRange;   //!
   TBranch        *b_s_trkEnCurv;   //!
   TBranch        *b_s_shwEn;   //!
   TBranch        *b_s_shwEnCC;   //!
   TBranch        *b_s_shwEnNC;   //!
   TBranch        *b_s_resolution;   //!
   TBranch        *b_s_isInFidVolCC;   //!
   TBranch        *b_s_isGoodTrackReclamation;   //!
   TBranch        *b_s_isNCClean;   //!
   TBranch        *b_s_y;   //!
   TBranch        *b_s_q2;   //!
   TBranch        *b_s_x;   //!
   TBranch        *b_s_w2;   //!
   TBranch        *b_s_dirCosNu;   //!
   TBranch        *b_s_evt;   //!
   TBranch        *b_s_slc;   //!
   TBranch        *b_s_nevt;   //!
   TBranch        *b_s_ndigitEvt;   //!
   TBranch        *b_s_nstripEvt;   //!
   TBranch        *b_s_nshw;   //!
   TBranch        *b_s_ntrk;   //!
   TBranch        *b_s_primshw;   //!
   TBranch        *b_s_primtrk;   //!
   TBranch        *b_s_rawPhEvt;   //!
   TBranch        *b_s_evtphsigcor;   //!
   TBranch        *b_s_evtphsigmap;   //!
   TBranch        *b_s_planeEvtN;   //!
   TBranch        *b_s_planeEvtNu;   //!
   TBranch        *b_s_planeEvtNv;   //!
   TBranch        *b_s_roIDEvt;   //!
   TBranch        *b_s_knn01TrkActivePlanesEvt;   //!
   TBranch        *b_s_knn10TrkMeanPhEvt;   //!
   TBranch        *b_s_knn20LowHighPhEvt;   //!
   TBranch        *b_s_knn40TrkPhFracEvt;   //!
   TBranch        *b_s_roIDNuMuBarEvt;   //!
   TBranch        *b_s_relativeAngleEvt;   //!
   TBranch        *b_s_jmIDEvt;   //!
   TBranch        *b_s_jmTrackPlaneEvt;   //!
   TBranch        *b_s_jmEndPhEvt;   //!
   TBranch        *b_s_jmMeanPhEvt;   //!
   TBranch        *b_s_jmScatteringUEvt;   //!
   TBranch        *b_s_jmScatteringVEvt;   //!
   TBranch        *b_s_jmScatteringUVEvt;   //!
   TBranch        *b_s_jmEventknnIDEvt;   //!
   TBranch        *b_s_jmEventknn208Evt;   //!
   TBranch        *b_s_jmEventknn207Evt;   //!
   TBranch        *b_s_jmEventknn206Evt;   //!
   TBranch        *b_s_jmEventknn205Evt;   //!
   TBranch        *b_s_jmEventknn204Evt;   //!
   TBranch        *b_s_xEvtVtx;   //!
   TBranch        *b_s_yEvtVtx;   //!
   TBranch        *b_s_zEvtVtx;   //!
   TBranch        *b_s_uEvtVtx;   //!
   TBranch        *b_s_vEvtVtx;   //!
   TBranch        *b_s_planeEvtVtx;   //!
   TBranch        *b_s_planeEvtBeg;   //!
   TBranch        *b_s_planeEvtBegu;   //!
   TBranch        *b_s_planeEvtBegv;   //!
   TBranch        *b_s_xEvtEnd;   //!
   TBranch        *b_s_yEvtEnd;   //!
   TBranch        *b_s_zEvtEnd;   //!
   TBranch        *b_s_uEvtEnd;   //!
   TBranch        *b_s_vEvtEnd;   //!
   TBranch        *b_s_planeEvtEnd;   //!
   TBranch        *b_s_planeEvtEndu;   //!
   TBranch        *b_s_planeEvtEndv;   //!
   TBranch        *b_s_trkExists;   //!
   TBranch        *b_s_trkIndex;   //!
   TBranch        *b_s_ndigitTrk;   //!
   TBranch        *b_s_nstripTrk;   //!
   TBranch        *b_s_trkEnCorRange;   //!
   TBranch        *b_s_trkEnCorCurv;   //!
   TBranch        *b_s_trkShwEnNear;   //!
   TBranch        *b_s_trkShwEnNearDW;   //!
   TBranch        *b_s_trkMomentumRange;   //!
   TBranch        *b_s_trkMomentumTransverse;   //!
   TBranch        *b_s_trkResolution;   //!
   TBranch        *b_s_containedTrk;   //!
   TBranch        *b_s_trkfitpass;   //!
   TBranch        *b_s_trkvtxdcosz;   //!
   TBranch        *b_s_trkvtxdcosy;   //!
   TBranch        *b_s_trknplane;   //!
   TBranch        *b_s_charge;   //!
   TBranch        *b_s_qp;   //!
   TBranch        *b_s_qp_rangebiased;   //!
   TBranch        *b_s_sigqp;   //!
   TBranch        *b_s_qp_sigqp;   //!
   TBranch        *b_s_chi2;   //!
   TBranch        *b_s_ndof;   //!
   TBranch        *b_s_qpFraction;   //!
   TBranch        *b_s_trkVtxUVDiffPl;   //!
   TBranch        *b_s_trkLength;   //!
   TBranch        *b_s_planeTrkNu;   //!
   TBranch        *b_s_planeTrkNv;   //!
   TBranch        *b_s_ntrklike;   //!
   TBranch        *b_s_trkphsigcor;   //!
   TBranch        *b_s_trkphsigmap;   //!
   TBranch        *b_s_trkIdMC;   //!
   TBranch        *b_s_trkfitpassSA;   //!
   TBranch        *b_s_trkvtxdcoszSA;   //!
   TBranch        *b_s_chargeSA;   //!
   TBranch        *b_s_qpSA;   //!
   TBranch        *b_s_sigqpSA;   //!
   TBranch        *b_s_chi2SA;   //!
   TBranch        *b_s_ndofSA;   //!
   TBranch        *b_s_probSA;   //!
   TBranch        *b_s_xTrkVtxSA;   //!
   TBranch        *b_s_yTrkVtxSA;   //!
   TBranch        *b_s_zTrkVtxSA;   //!
   TBranch        *b_s_uTrkVtxSA;   //!
   TBranch        *b_s_vTrkVtxSA;   //!
   TBranch        *b_s_jitter;   //!
   TBranch        *b_s_jPID;   //!
   TBranch        *b_s_majC;   //!
   TBranch        *b_s_smoothMajC;   //!
   TBranch        *b_s_xTrkVtx;   //!
   TBranch        *b_s_yTrkVtx;   //!
   TBranch        *b_s_zTrkVtx;   //!
   TBranch        *b_s_uTrkVtx;   //!
   TBranch        *b_s_vTrkVtx;   //!
   TBranch        *b_s_planeTrkVtx;   //!
   TBranch        *b_s_planeTrkBeg;   //!
   TBranch        *b_s_planeTrkBegu;   //!
   TBranch        *b_s_planeTrkBegv;   //!
   TBranch        *b_s_stripTrkBeg;   //!
   TBranch        *b_s_stripTrkBegu;   //!
   TBranch        *b_s_stripTrkBegv;   //!
   TBranch        *b_s_stripTrkEnd;   //!
   TBranch        *b_s_stripTrkEndu;   //!
   TBranch        *b_s_stripTrkEndv;   //!
   TBranch        *b_s_stripTrkBegIsu;   //!
   TBranch        *b_s_stripTrkEndIsu;   //!
   TBranch        *b_s_regionTrkVtx;   //!
   TBranch        *b_s_edgeRegionTrkVtx;   //!
   TBranch        *b_s_edgeRegionTrkEnd;   //!
   TBranch        *b_s_phiTrkVtx;   //!
   TBranch        *b_s_phiTrkEnd;   //!
   TBranch        *b_s_parallelStripTrkVtx;   //!
   TBranch        *b_s_parallelStripTrkVtxNoShift;   //!
   TBranch        *b_s_parallelStripTrkEnd;   //!
   TBranch        *b_s_stripTrkBegPerpFlag;   //!
   TBranch        *b_s_stripTrkEndPerpFlag;   //!
   TBranch        *b_s_stripHoveNumTrkVtx;   //!
   TBranch        *b_s_stripHoveNumTrkVtxNoShift;   //!
   TBranch        *b_s_stripHoveNumTrkEnd;   //!
   TBranch        *b_s_xTrkEnd;   //!
   TBranch        *b_s_yTrkEnd;   //!
   TBranch        *b_s_zTrkEnd;   //!
   TBranch        *b_s_uTrkEnd;   //!
   TBranch        *b_s_vTrkEnd;   //!
   TBranch        *b_s_planeTrkEnd;   //!
   TBranch        *b_s_planeTrkEndu;   //!
   TBranch        *b_s_planeTrkEndv;   //!
   TBranch        *b_s_drTrkFidall;   //!
   TBranch        *b_s_dzTrkFidall;   //!
   TBranch        *b_s_drTrkFidvtx;   //!
   TBranch        *b_s_dzTrkFidvtx;   //!
   TBranch        *b_s_drTrkFidend;   //!
   TBranch        *b_s_dzTrkFidend;   //!
   TBranch        *b_s_traceTrkFidall;   //!
   TBranch        *b_s_traceTrkFidvtx;   //!
   TBranch        *b_s_traceTrkFidend;   //!
   TBranch        *b_s_cosPrTrkVtx;   //!
   TBranch        *b_s_shwExists;   //!
   TBranch        *b_s_ndigitShw;   //!
   TBranch        *b_s_nstripShw;   //!
   TBranch        *b_s_nplaneShw;   //!
   TBranch        *b_s_shwEnCor;   //!
   TBranch        *b_s_shwEnNoCor;   //!
   TBranch        *b_s_shwEnMip;   //!
   TBranch        *b_s_shwEnLinCCNoCor;   //!
   TBranch        *b_s_shwEnLinCCCor;   //!
   TBranch        *b_s_shwEnWtCCNoCor;   //!
   TBranch        *b_s_shwEnWtCCCor;   //!
   TBranch        *b_s_shwEnLinNCNoCor;   //!
   TBranch        *b_s_shwEnLinNCCor;   //!
   TBranch        *b_s_shwEnWtNCNoCor;   //!
   TBranch        *b_s_shwEnWtNCCor;   //!
   TBranch        *b_s_shwResolution;   //!
   TBranch        *b_s_shwEnkNN;   //!
   TBranch        *b_s_shwEnReskNN;   //!
   TBranch        *b_s_planeShwBeg;   //!
   TBranch        *b_s_planeShwEnd;   //!
   TBranch        *b_s_planeShwMax;   //!
   TBranch        *b_s_xShwVtx;   //!
   TBranch        *b_s_yShwVtx;   //!
   TBranch        *b_s_zShwVtx;   //!
   TBranch        *b_s_trkExists1;   //!
   TBranch        *b_s_trkIndex1;   //!
   TBranch        *b_s_ndigitTrk1;   //!
   TBranch        *b_s_nstripTrk1;   //!
   TBranch        *b_s_trkEnCorRange1;   //!
   TBranch        *b_s_trkEnCorCurv1;   //!
   TBranch        *b_s_trkShwEnNear1;   //!
   TBranch        *b_s_trkShwEnNearDW1;   //!
   TBranch        *b_s_trkMomentumRange1;   //!
   TBranch        *b_s_trkMomentumTransverse1;   //!
   TBranch        *b_s_containedTrk1;   //!
   TBranch        *b_s_trkfitpass1;   //!
   TBranch        *b_s_trkvtxdcosz1;   //!
   TBranch        *b_s_trkvtxdcosy1;   //!
   TBranch        *b_s_trknplane1;   //!
   TBranch        *b_s_charge1;   //!
   TBranch        *b_s_qp1;   //!
   TBranch        *b_s_qp_rangebiased1;   //!
   TBranch        *b_s_sigqp1;   //!
   TBranch        *b_s_qp_sigqp1;   //!
   TBranch        *b_s_chi21;   //!
   TBranch        *b_s_ndof1;   //!
   TBranch        *b_s_qpFraction1;   //!
   TBranch        *b_s_trkVtxUVDiffPl1;   //!
   TBranch        *b_s_trkLength1;   //!
   TBranch        *b_s_planeTrkNu1;   //!
   TBranch        *b_s_planeTrkNv1;   //!
   TBranch        *b_s_ntrklike1;   //!
   TBranch        *b_s_trkphsigcor1;   //!
   TBranch        *b_s_trkphsigmap1;   //!
   TBranch        *b_s_trkIdMC1;   //!
   TBranch        *b_s_trkfitpassSA1;   //!
   TBranch        *b_s_trkvtxdcoszSA1;   //!
   TBranch        *b_s_chargeSA1;   //!
   TBranch        *b_s_qpSA1;   //!
   TBranch        *b_s_sigqpSA1;   //!
   TBranch        *b_s_chi2SA1;   //!
   TBranch        *b_s_ndofSA1;   //!
   TBranch        *b_s_probSA1;   //!
   TBranch        *b_s_xTrkVtxSA1;   //!
   TBranch        *b_s_yTrkVtxSA1;   //!
   TBranch        *b_s_zTrkVtxSA1;   //!
   TBranch        *b_s_uTrkVtxSA1;   //!
   TBranch        *b_s_vTrkVtxSA1;   //!
   TBranch        *b_s_jitter1;   //!
   TBranch        *b_s_jPID1;   //!
   TBranch        *b_s_majC1;   //!
   TBranch        *b_s_smoothMajC1;   //!
   TBranch        *b_s_roID1;   //!
   TBranch        *b_s_knn01TrkActivePlanes1;   //!
   TBranch        *b_s_knn10TrkMeanPh1;   //!
   TBranch        *b_s_knn20LowHighPh1;   //!
   TBranch        *b_s_knn40TrkPhFrac1;   //!
   TBranch        *b_s_roIDNuMuBar1;   //!
   TBranch        *b_s_relativeAngle1;   //!
   TBranch        *b_s_jmID1;   //!
   TBranch        *b_s_jmTrackPlane1;   //!
   TBranch        *b_s_jmEndPh1;   //!
   TBranch        *b_s_jmMeanPh1;   //!
   TBranch        *b_s_jmScatteringU1;   //!
   TBranch        *b_s_jmScatteringV1;   //!
   TBranch        *b_s_jmScatteringUV1;   //!
   TBranch        *b_s_xTrkVtx1;   //!
   TBranch        *b_s_yTrkVtx1;   //!
   TBranch        *b_s_zTrkVtx1;   //!
   TBranch        *b_s_uTrkVtx1;   //!
   TBranch        *b_s_vTrkVtx1;   //!
   TBranch        *b_s_planeTrkVtx1;   //!
   TBranch        *b_s_planeTrkBeg1;   //!
   TBranch        *b_s_planeTrkBegu1;   //!
   TBranch        *b_s_planeTrkBegv1;   //!
   TBranch        *b_s_stripTrkBeg1;   //!
   TBranch        *b_s_stripTrkBegu1;   //!
   TBranch        *b_s_stripTrkBegv1;   //!
   TBranch        *b_s_stripTrkEnd1;   //!
   TBranch        *b_s_stripTrkEndu1;   //!
   TBranch        *b_s_stripTrkEndv1;   //!
   TBranch        *b_s_stripTrkBegIsu1;   //!
   TBranch        *b_s_stripTrkEndIsu1;   //!
   TBranch        *b_s_regionTrkVtx1;   //!
   TBranch        *b_s_edgeRegionTrkVtx1;   //!
   TBranch        *b_s_edgeRegionTrkEnd1;   //!
   TBranch        *b_s_phiTrkVtx1;   //!
   TBranch        *b_s_phiTrkEnd1;   //!
   TBranch        *b_s_parallelStripTrkVtx1;   //!
   TBranch        *b_s_parallelStripTrkEnd1;   //!
   TBranch        *b_s_stripTrkBegPerpFlag1;   //!
   TBranch        *b_s_stripTrkEndPerpFlag1;   //!
   TBranch        *b_s_stripHoveNumTrkVtx1;   //!
   TBranch        *b_s_stripHoveNumTrkEnd1;   //!
   TBranch        *b_s_xTrkEnd1;   //!
   TBranch        *b_s_yTrkEnd1;   //!
   TBranch        *b_s_zTrkEnd1;   //!
   TBranch        *b_s_uTrkEnd1;   //!
   TBranch        *b_s_vTrkEnd1;   //!
   TBranch        *b_s_planeTrkEnd1;   //!
   TBranch        *b_s_planeTrkEndu1;   //!
   TBranch        *b_s_planeTrkEndv1;   //!
   TBranch        *b_s_drTrkFidall1;   //!
   TBranch        *b_s_dzTrkFidall1;   //!
   TBranch        *b_s_drTrkFidvtx1;   //!
   TBranch        *b_s_dzTrkFidvtx1;   //!
   TBranch        *b_s_drTrkFidend1;   //!
   TBranch        *b_s_dzTrkFidend1;   //!
   TBranch        *b_s_traceTrkFidall1;   //!
   TBranch        *b_s_traceTrkFidvtx1;   //!
   TBranch        *b_s_traceTrkFidend1;   //!
   TBranch        *b_s_cosPrTrkVtx1;   //!
   TBranch        *b_s_shwExists1;   //!
   TBranch        *b_s_ndigitShw1;   //!
   TBranch        *b_s_nstripShw1;   //!
   TBranch        *b_s_nplaneShw1;   //!
   TBranch        *b_s_shwEnCor1;   //!
   TBranch        *b_s_shwEnNoCor1;   //!
   TBranch        *b_s_shwEnLinCCNoCor1;   //!
   TBranch        *b_s_shwEnLinCCCor1;   //!
   TBranch        *b_s_shwEnWtCCNoCor1;   //!
   TBranch        *b_s_shwEnWtCCCor1;   //!
   TBranch        *b_s_shwEnLinNCNoCor1;   //!
   TBranch        *b_s_shwEnLinNCCor1;   //!
   TBranch        *b_s_shwEnWtNCNoCor1;   //!
   TBranch        *b_s_shwEnWtNCCor1;   //!
   TBranch        *b_s_shwEnMip1;   //!
   TBranch        *b_s_planeShwBeg1;   //!
   TBranch        *b_s_planeShwEnd1;   //!
   TBranch        *b_s_planeShwMax1;   //!
   TBranch        *b_s_xShwVtx1;   //!
   TBranch        *b_s_yShwVtx1;   //!
   TBranch        *b_s_zShwVtx1;   //!
   TBranch        *b_s_trkExists2;   //!
   TBranch        *b_s_trkIndex2;   //!
   TBranch        *b_s_ndigitTrk2;   //!
   TBranch        *b_s_nstripTrk2;   //!
   TBranch        *b_s_trkEnCorRange2;   //!
   TBranch        *b_s_trkEnCorCurv2;   //!
   TBranch        *b_s_trkShwEnNear2;   //!
   TBranch        *b_s_trkShwEnNearDW2;   //!
   TBranch        *b_s_trkMomentumRange2;   //!
   TBranch        *b_s_trkMomentumTransverse2;   //!
   TBranch        *b_s_containedTrk2;   //!
   TBranch        *b_s_trkfitpass2;   //!
   TBranch        *b_s_trkvtxdcosz2;   //!
   TBranch        *b_s_trkvtxdcosy2;   //!
   TBranch        *b_s_trknplane2;   //!
   TBranch        *b_s_charge2;   //!
   TBranch        *b_s_qp2;   //!
   TBranch        *b_s_qp_rangebiased2;   //!
   TBranch        *b_s_sigqp2;   //!
   TBranch        *b_s_qp_sigqp2;   //!
   TBranch        *b_s_chi22;   //!
   TBranch        *b_s_ndof2;   //!
   TBranch        *b_s_qpFraction2;   //!
   TBranch        *b_s_trkVtxUVDiffPl2;   //!
   TBranch        *b_s_trkLength2;   //!
   TBranch        *b_s_planeTrkNu2;   //!
   TBranch        *b_s_planeTrkNv2;   //!
   TBranch        *b_s_ntrklike2;   //!
   TBranch        *b_s_trkphsigcor2;   //!
   TBranch        *b_s_trkphsigmap2;   //!
   TBranch        *b_s_trkIdMC2;   //!
   TBranch        *b_s_trkfitpassSA2;   //!
   TBranch        *b_s_trkvtxdcoszSA2;   //!
   TBranch        *b_s_chargeSA2;   //!
   TBranch        *b_s_qpSA2;   //!
   TBranch        *b_s_sigqpSA2;   //!
   TBranch        *b_s_chi2SA2;   //!
   TBranch        *b_s_ndofSA2;   //!
   TBranch        *b_s_probSA2;   //!
   TBranch        *b_s_xTrkVtxSA2;   //!
   TBranch        *b_s_yTrkVtxSA2;   //!
   TBranch        *b_s_zTrkVtxSA2;   //!
   TBranch        *b_s_uTrkVtxSA2;   //!
   TBranch        *b_s_vTrkVtxSA2;   //!
   TBranch        *b_s_jitter2;   //!
   TBranch        *b_s_jPID2;   //!
   TBranch        *b_s_majC2;   //!
   TBranch        *b_s_smoothMajC2;   //!
   TBranch        *b_s_roID2;   //!
   TBranch        *b_s_knn01TrkActivePlanes2;   //!
   TBranch        *b_s_knn10TrkMeanPh2;   //!
   TBranch        *b_s_knn20LowHighPh2;   //!
   TBranch        *b_s_knn40TrkPhFrac2;   //!
   TBranch        *b_s_roIDNuMuBar2;   //!
   TBranch        *b_s_relativeAngle2;   //!
   TBranch        *b_s_jmID2;   //!
   TBranch        *b_s_jmTrackPlane2;   //!
   TBranch        *b_s_jmEndPh2;   //!
   TBranch        *b_s_jmMeanPh2;   //!
   TBranch        *b_s_jmScatteringU2;   //!
   TBranch        *b_s_jmScatteringV2;   //!
   TBranch        *b_s_jmScatteringUV2;   //!
   TBranch        *b_s_xTrkVtx2;   //!
   TBranch        *b_s_yTrkVtx2;   //!
   TBranch        *b_s_zTrkVtx2;   //!
   TBranch        *b_s_uTrkVtx2;   //!
   TBranch        *b_s_vTrkVtx2;   //!
   TBranch        *b_s_planeTrkVtx2;   //!
   TBranch        *b_s_planeTrkBeg2;   //!
   TBranch        *b_s_planeTrkBegu2;   //!
   TBranch        *b_s_planeTrkBegv2;   //!
   TBranch        *b_s_stripTrkBeg2;   //!
   TBranch        *b_s_stripTrkBegu2;   //!
   TBranch        *b_s_stripTrkBegv2;   //!
   TBranch        *b_s_stripTrkEnd2;   //!
   TBranch        *b_s_stripTrkEndu2;   //!
   TBranch        *b_s_stripTrkEndv2;   //!
   TBranch        *b_s_stripTrkBegIsu2;   //!
   TBranch        *b_s_stripTrkEndIsu2;   //!
   TBranch        *b_s_regionTrkVtx2;   //!
   TBranch        *b_s_edgeRegionTrkVtx2;   //!
   TBranch        *b_s_edgeRegionTrkEnd2;   //!
   TBranch        *b_s_phiTrkVtx2;   //!
   TBranch        *b_s_phiTrkEnd2;   //!
   TBranch        *b_s_parallelStripTrkVtx2;   //!
   TBranch        *b_s_parallelStripTrkEnd2;   //!
   TBranch        *b_s_stripTrkBegPerpFlag2;   //!
   TBranch        *b_s_stripTrkEndPerpFlag2;   //!
   TBranch        *b_s_stripHoveNumTrkVtx2;   //!
   TBranch        *b_s_stripHoveNumTrkEnd2;   //!
   TBranch        *b_s_xTrkEnd2;   //!
   TBranch        *b_s_yTrkEnd2;   //!
   TBranch        *b_s_zTrkEnd2;   //!
   TBranch        *b_s_uTrkEnd2;   //!
   TBranch        *b_s_vTrkEnd2;   //!
   TBranch        *b_s_planeTrkEnd2;   //!
   TBranch        *b_s_planeTrkEndu2;   //!
   TBranch        *b_s_planeTrkEndv2;   //!
   TBranch        *b_s_drTrkFidall2;   //!
   TBranch        *b_s_dzTrkFidall2;   //!
   TBranch        *b_s_drTrkFidvtx2;   //!
   TBranch        *b_s_dzTrkFidvtx2;   //!
   TBranch        *b_s_drTrkFidend2;   //!
   TBranch        *b_s_dzTrkFidend2;   //!
   TBranch        *b_s_traceTrkFidall2;   //!
   TBranch        *b_s_traceTrkFidvtx2;   //!
   TBranch        *b_s_traceTrkFidend2;   //!
   TBranch        *b_s_cosPrTrkVtx2;   //!
   TBranch        *b_s_shwExists2;   //!
   TBranch        *b_s_ndigitShw2;   //!
   TBranch        *b_s_nstripShw2;   //!
   TBranch        *b_s_nplaneShw2;   //!
   TBranch        *b_s_shwEnCor2;   //!
   TBranch        *b_s_shwEnNoCor2;   //!
   TBranch        *b_s_shwEnLinCCNoCor2;   //!
   TBranch        *b_s_shwEnLinCCCor2;   //!
   TBranch        *b_s_shwEnWtCCNoCor2;   //!
   TBranch        *b_s_shwEnWtCCCor2;   //!
   TBranch        *b_s_shwEnLinNCNoCor2;   //!
   TBranch        *b_s_shwEnLinNCCor2;   //!
   TBranch        *b_s_shwEnWtNCNoCor2;   //!
   TBranch        *b_s_shwEnWtNCCor2;   //!
   TBranch        *b_s_shwEnMip2;   //!
   TBranch        *b_s_planeShwBeg2;   //!
   TBranch        *b_s_planeShwEnd2;   //!
   TBranch        *b_s_planeShwMax2;   //!
   TBranch        *b_s_xShwVtx2;   //!
   TBranch        *b_s_yShwVtx2;   //!
   TBranch        *b_s_zShwVtx2;   //!
   TBranch        *b_s_trkExists3;   //!
   TBranch        *b_s_trkIndex3;   //!
   TBranch        *b_s_ndigitTrk3;   //!
   TBranch        *b_s_nstripTrk3;   //!
   TBranch        *b_s_trkEnCorRange3;   //!
   TBranch        *b_s_trkEnCorCurv3;   //!
   TBranch        *b_s_trkShwEnNear3;   //!
   TBranch        *b_s_trkShwEnNearDW3;   //!
   TBranch        *b_s_trkMomentumRange3;   //!
   TBranch        *b_s_trkMomentumTransverse3;   //!
   TBranch        *b_s_containedTrk3;   //!
   TBranch        *b_s_trkfitpass3;   //!
   TBranch        *b_s_trkvtxdcosz3;   //!
   TBranch        *b_s_trkvtxdcosy3;   //!
   TBranch        *b_s_trknplane3;   //!
   TBranch        *b_s_charge3;   //!
   TBranch        *b_s_qp3;   //!
   TBranch        *b_s_qp_rangebiased3;   //!
   TBranch        *b_s_sigqp3;   //!
   TBranch        *b_s_qp_sigqp3;   //!
   TBranch        *b_s_chi23;   //!
   TBranch        *b_s_ndof3;   //!
   TBranch        *b_s_qpFraction3;   //!
   TBranch        *b_s_trkVtxUVDiffPl3;   //!
   TBranch        *b_s_trkLength3;   //!
   TBranch        *b_s_planeTrkNu3;   //!
   TBranch        *b_s_planeTrkNv3;   //!
   TBranch        *b_s_ntrklike3;   //!
   TBranch        *b_s_trkphsigcor3;   //!
   TBranch        *b_s_trkphsigmap3;   //!
   TBranch        *b_s_trkIdMC3;   //!
   TBranch        *b_s_trkfitpassSA3;   //!
   TBranch        *b_s_trkvtxdcoszSA3;   //!
   TBranch        *b_s_chargeSA3;   //!
   TBranch        *b_s_qpSA3;   //!
   TBranch        *b_s_sigqpSA3;   //!
   TBranch        *b_s_chi2SA3;   //!
   TBranch        *b_s_ndofSA3;   //!
   TBranch        *b_s_probSA3;   //!
   TBranch        *b_s_xTrkVtxSA3;   //!
   TBranch        *b_s_yTrkVtxSA3;   //!
   TBranch        *b_s_zTrkVtxSA3;   //!
   TBranch        *b_s_uTrkVtxSA3;   //!
   TBranch        *b_s_vTrkVtxSA3;   //!
   TBranch        *b_s_jitter3;   //!
   TBranch        *b_s_jPID3;   //!
   TBranch        *b_s_majC3;   //!
   TBranch        *b_s_smoothMajC3;   //!
   TBranch        *b_s_roID3;   //!
   TBranch        *b_s_knn01TrkActivePlanes3;   //!
   TBranch        *b_s_knn10TrkMeanPh3;   //!
   TBranch        *b_s_knn20LowHighPh3;   //!
   TBranch        *b_s_knn40TrkPhFrac3;   //!
   TBranch        *b_s_roIDNuMuBar3;   //!
   TBranch        *b_s_relativeAngle3;   //!
   TBranch        *b_s_jmID3;   //!
   TBranch        *b_s_jmTrackPlane3;   //!
   TBranch        *b_s_jmEndPh3;   //!
   TBranch        *b_s_jmMeanPh3;   //!
   TBranch        *b_s_jmScatteringU3;   //!
   TBranch        *b_s_jmScatteringV3;   //!
   TBranch        *b_s_jmScatteringUV3;   //!
   TBranch        *b_s_xTrkVtx3;   //!
   TBranch        *b_s_yTrkVtx3;   //!
   TBranch        *b_s_zTrkVtx3;   //!
   TBranch        *b_s_uTrkVtx3;   //!
   TBranch        *b_s_vTrkVtx3;   //!
   TBranch        *b_s_planeTrkVtx3;   //!
   TBranch        *b_s_planeTrkBeg3;   //!
   TBranch        *b_s_planeTrkBegu3;   //!
   TBranch        *b_s_planeTrkBegv3;   //!
   TBranch        *b_s_stripTrkBeg3;   //!
   TBranch        *b_s_stripTrkBegu3;   //!
   TBranch        *b_s_stripTrkBegv3;   //!
   TBranch        *b_s_stripTrkEnd3;   //!
   TBranch        *b_s_stripTrkEndu3;   //!
   TBranch        *b_s_stripTrkEndv3;   //!
   TBranch        *b_s_stripTrkBegIsu3;   //!
   TBranch        *b_s_stripTrkEndIsu3;   //!
   TBranch        *b_s_regionTrkVtx3;   //!
   TBranch        *b_s_edgeRegionTrkVtx3;   //!
   TBranch        *b_s_edgeRegionTrkEnd3;   //!
   TBranch        *b_s_phiTrkVtx3;   //!
   TBranch        *b_s_phiTrkEnd3;   //!
   TBranch        *b_s_parallelStripTrkVtx3;   //!
   TBranch        *b_s_parallelStripTrkEnd3;   //!
   TBranch        *b_s_stripTrkBegPerpFlag3;   //!
   TBranch        *b_s_stripTrkEndPerpFlag3;   //!
   TBranch        *b_s_stripHoveNumTrkVtx3;   //!
   TBranch        *b_s_stripHoveNumTrkEnd3;   //!
   TBranch        *b_s_xTrkEnd3;   //!
   TBranch        *b_s_yTrkEnd3;   //!
   TBranch        *b_s_zTrkEnd3;   //!
   TBranch        *b_s_uTrkEnd3;   //!
   TBranch        *b_s_vTrkEnd3;   //!
   TBranch        *b_s_planeTrkEnd3;   //!
   TBranch        *b_s_planeTrkEndu3;   //!
   TBranch        *b_s_planeTrkEndv3;   //!
   TBranch        *b_s_drTrkFidall3;   //!
   TBranch        *b_s_dzTrkFidall3;   //!
   TBranch        *b_s_drTrkFidvtx3;   //!
   TBranch        *b_s_dzTrkFidvtx3;   //!
   TBranch        *b_s_drTrkFidend3;   //!
   TBranch        *b_s_dzTrkFidend3;   //!
   TBranch        *b_s_traceTrkFidall3;   //!
   TBranch        *b_s_traceTrkFidvtx3;   //!
   TBranch        *b_s_traceTrkFidend3;   //!
   TBranch        *b_s_cosPrTrkVtx3;   //!
   TBranch        *b_s_shwExists3;   //!
   TBranch        *b_s_ndigitShw3;   //!
   TBranch        *b_s_nstripShw3;   //!
   TBranch        *b_s_nplaneShw3;   //!
   TBranch        *b_s_shwEnCor3;   //!
   TBranch        *b_s_shwEnNoCor3;   //!
   TBranch        *b_s_shwEnLinCCNoCor3;   //!
   TBranch        *b_s_shwEnLinCCCor3;   //!
   TBranch        *b_s_shwEnWtCCNoCor3;   //!
   TBranch        *b_s_shwEnWtCCCor3;   //!
   TBranch        *b_s_shwEnLinNCNoCor3;   //!
   TBranch        *b_s_shwEnLinNCCor3;   //!
   TBranch        *b_s_shwEnWtNCNoCor3;   //!
   TBranch        *b_s_shwEnWtNCCor3;   //!
   TBranch        *b_s_shwEnMip3;   //!
   TBranch        *b_s_planeShwBeg3;   //!
   TBranch        *b_s_planeShwEnd3;   //!
   TBranch        *b_s_planeShwMax3;   //!
   TBranch        *b_s_xShwVtx3;   //!
   TBranch        *b_s_yShwVtx3;   //!
   TBranch        *b_s_zShwVtx3;   //!
   TBranch        *b_s_shwExists4;   //!
   TBranch        *b_s_ndigitShw4;   //!
   TBranch        *b_s_nstripShw4;   //!
   TBranch        *b_s_nplaneShw4;   //!
   TBranch        *b_s_shwEnCor4;   //!
   TBranch        *b_s_shwEnNoCor4;   //!
   TBranch        *b_s_shwEnLinCCNoCor4;   //!
   TBranch        *b_s_shwEnLinCCCor4;   //!
   TBranch        *b_s_shwEnWtCCNoCor4;   //!
   TBranch        *b_s_shwEnWtCCCor4;   //!
   TBranch        *b_s_shwEnLinNCNoCor4;   //!
   TBranch        *b_s_shwEnLinNCCor4;   //!
   TBranch        *b_s_shwEnWtNCNoCor4;   //!
   TBranch        *b_s_shwEnWtNCCor4;   //!
   TBranch        *b_s_shwEnMip4;   //!
   TBranch        *b_s_planeShwBeg4;   //!
   TBranch        *b_s_planeShwEnd4;   //!
   TBranch        *b_s_planeShwMax4;   //!
   TBranch        *b_s_xShwVtx4;   //!
   TBranch        *b_s_yShwVtx4;   //!
   TBranch        *b_s_zShwVtx4;   //!
   TBranch        *b_s_shwExists5;   //!
   TBranch        *b_s_ndigitShw5;   //!
   TBranch        *b_s_nstripShw5;   //!
   TBranch        *b_s_nplaneShw5;   //!
   TBranch        *b_s_shwEnCor5;   //!
   TBranch        *b_s_shwEnNoCor5;   //!
   TBranch        *b_s_shwEnLinCCNoCor5;   //!
   TBranch        *b_s_shwEnLinCCCor5;   //!
   TBranch        *b_s_shwEnWtCCNoCor5;   //!
   TBranch        *b_s_shwEnWtCCCor5;   //!
   TBranch        *b_s_shwEnLinNCNoCor5;   //!
   TBranch        *b_s_shwEnLinNCCor5;   //!
   TBranch        *b_s_shwEnWtNCNoCor5;   //!
   TBranch        *b_s_shwEnWtNCCor5;   //!
   TBranch        *b_s_shwEnMip5;   //!
   TBranch        *b_s_planeShwBeg5;   //!
   TBranch        *b_s_planeShwEnd5;   //!
   TBranch        *b_s_planeShwMax5;   //!
   TBranch        *b_s_xShwVtx5;   //!
   TBranch        *b_s_yShwVtx5;   //!
   TBranch        *b_s_zShwVtx5;   //!
   TBranch        *b_s_rEvtVtx;   //!
   TBranch        *b_s_rEvtEnd;   //!
   TBranch        *b_s_distToEdgeEvtVtx;   //!
   TBranch        *b_s_evtVtxUVDiffPl;   //!
   TBranch        *b_s_rTrkVtx;   //!
   TBranch        *b_s_rTrkEnd;   //!
   TBranch        *b_s_sigqp_qp;   //!
   TBranch        *b_s_chi2PerNdof;   //!
   TBranch        *b_s_prob;   //!
   TBranch        *b_s_containmentFlag;   //!
   TBranch        *b_s_containmentFlagCC0093Std;   //!
   TBranch        *b_s_containmentFlagCC0250Std;   //!
   TBranch        *b_s_containmentFlagPitt;   //!
   TBranch        *b_s_usedRange;   //!
   TBranch        *b_s_usedCurv;   //!
   TBranch        *b_s_rw;   //!
   TBranch        *b_s_fluxErr;   //!
   TBranch        *b_s_rwActual;   //!
   TBranch        *b_s_generatorWeight;   //!
   TBranch        *b_s_detectorWeight;   //!
   TBranch        *b_s_trkEnWeight;   //!
   TBranch        *b_s_shwEnWeight;   //!
   TBranch        *b_s_beamWeight;   //!
   TBranch        *b_s_fluxErrHadProdAfterTune;   //!
   TBranch        *b_s_fluxErrTotalErrorPreTune;   //!
   TBranch        *b_s_fluxErrTotalErrorAfterTune;   //!
   TBranch        *b_s_detectorWeightNMB;   //!
   TBranch        *b_s_detectorWeightNM;   //!
   TBranch        *b_s_trkEnWeightRunI;   //!
   TBranch        *b_s_shwEnWeightRunI;   //!
   TBranch        *b_s_beamWeightRunI;   //!
   TBranch        *b_s_fluxErrHadProdAfterTuneRunI;   //!
   TBranch        *b_s_fluxErrTotalErrorPreTuneRunI;   //!
   TBranch        *b_s_fluxErrTotalErrorAfterTuneRunI;   //!
   TBranch        *b_s_detectorWeightNMBRunI;   //!
   TBranch        *b_s_detectorWeightNMRunI;   //!
   TBranch        *b_s_trkEnWeightRunII;   //!
   TBranch        *b_s_shwEnWeightRunII;   //!
   TBranch        *b_s_beamWeightRunII;   //!
   TBranch        *b_s_fluxErrHadProdAfterTuneRunII;   //!
   TBranch        *b_s_fluxErrTotalErrorPreTuneRunII;   //!
   TBranch        *b_s_fluxErrTotalErrorAfterTuneRunII;   //!
   TBranch        *b_s_detectorWeightNMBRunII;   //!
   TBranch        *b_s_detectorWeightNMRunII;   //!
   TBranch        *b_s_energyRw;   //!
   TBranch        *b_s_energyNoRw;   //!
   TBranch        *b_s_trkEnRw;   //!
   TBranch        *b_s_trkEnNoRw;   //!
   TBranch        *b_s_shwEnRw;   //!
   TBranch        *b_s_shwEnNoRw;   //!
   TBranch        *b_s_dpID;   //!
   TBranch        *b_s_abID;   //!
   TBranch        *b_s_roID;   //!
   TBranch        *b_s_knn01TrkActivePlanes;   //!
   TBranch        *b_s_knn10TrkMeanPh;   //!
   TBranch        *b_s_knn20LowHighPh;   //!
   TBranch        *b_s_knn40TrkPhFrac;   //!
   TBranch        *b_s_roIDNuMuBar;   //!
   TBranch        *b_s_relativeAngle;   //!
   TBranch        *b_s_poID;   //!
   TBranch        *b_s_poIDKin;   //!
   TBranch        *b_s_jmID;   //!
   TBranch        *b_s_jmTrackPlane;   //!
   TBranch        *b_s_jmEndPh;   //!
   TBranch        *b_s_jmMeanPh;   //!
   TBranch        *b_s_jmScatteringU;   //!
   TBranch        *b_s_jmScatteringV;   //!
   TBranch        *b_s_jmScatteringUV;   //!
   TBranch        *b_s_jmEventknnID;   //!
   TBranch        *b_s_jmEventknn208;   //!
   TBranch        *b_s_jmEventknn207;   //!
   TBranch        *b_s_jmEventknn206;   //!
   TBranch        *b_s_jmEventknn205;   //!
   TBranch        *b_s_jmEventknn204;   //!
   TBranch        *b_s_closeTimeDeltaZ;   //!
   TBranch        *b_s_edgeActivityStrips;   //!
   TBranch        *b_s_edgeActivityPH;   //!
   TBranch        *b_s_oppEdgeStrips;   //!
   TBranch        *b_s_oppEdgePH;   //!
   TBranch        *b_s_vtxMetersToCoilEvt;   //!
   TBranch        *b_s_vtxMetersToCloseEdgeEvt;   //!
   TBranch        *b_s_minTimeSeparation;   //!
   TBranch        *b_s_transverseRMSU;   //!
   TBranch        *b_s_transverseRMSV;   //!
   TBranch        *b_s_dtdz;   //!
   TBranch        *b_s_endMetersToCloseEdge;   //!
   TBranch        *b_s_vtxMetersToCloseEdgeTrk;   //!
   TBranch        *b_s_vtxMetersToCoilTrk;   //!
   TBranch        *b_s_traceEndZ;   //!
   TBranch        *b_s_pot;   //!
   TBranch        *b_s_potDB;   //!
   TBranch        *b_s_potSinceLastEvt;   //!
   TBranch        *b_s_potSinceLastEvtGood;   //!
   TBranch        *b_s_potSinceLastEvtBad;   //!
   TBranch        *b_s_potSinceLastEvtDB;   //!
   TBranch        *b_s_potSinceLastEvtGoodDB;   //!
   TBranch        *b_s_potSinceLastEvtBadDB;   //!
   TBranch        *b_s_runPeriod;   //!
   TBranch        *b_s_hornIsReverse;   //!
   TBranch        *b_s_beamTypeDB;   //!
   TBranch        *b_s_beamType;   //!
   TBranch        *b_s_intensity;   //!
   TBranch        *b_s_hornCur;   //!
   TBranch        *b_s_goodBeam;   //!
   TBranch        *b_s_goodBeamSntp;   //!
   TBranch        *b_s_isInFidVolCCMC;   //!
   TBranch        *b_s_energyMC;   //!
   TBranch        *b_s_neuEnMC;   //!
   TBranch        *b_s_neuPxMC;   //!
   TBranch        *b_s_neuPyMC;   //!
   TBranch        *b_s_neuPzMC;   //!
   TBranch        *b_s_mu1EnMC;   //!
   TBranch        *b_s_mu1PxMC;   //!
   TBranch        *b_s_mu1PyMC;   //!
   TBranch        *b_s_mu1PzMC;   //!
   TBranch        *b_s_tgtEnMC;   //!
   TBranch        *b_s_tgtPxMC;   //!
   TBranch        *b_s_tgtPyMC;   //!
   TBranch        *b_s_tgtPzMC;   //!
   TBranch        *b_s_zMC;   //!
   TBranch        *b_s_aMC;   //!
   TBranch        *b_s_nucleusMC;   //!
   TBranch        *b_s_initialStateMC;   //!
   TBranch        *b_s_hadronicFinalStateMC;   //!
   TBranch        *b_s_numPreInukeFSprotMC;   //!
   TBranch        *b_s_numPreInukeFSneutMC;   //!
   TBranch        *b_s_maxMomPreInukeFSprotMC;   //!
   TBranch        *b_s_maxMomPreInukeFSneutMC;   //!
   TBranch        *b_s_yMC;   //!
   TBranch        *b_s_y2MC;   //!
   TBranch        *b_s_xMC;   //!
   TBranch        *b_s_q2MC;   //!
   TBranch        *b_s_w2MC;   //!
   TBranch        *b_s_trkEnMC;   //!
   TBranch        *b_s_trkEn2MC;   //!
   TBranch        *b_s_shwEnMC;   //!
   TBranch        *b_s_shwEn2MC;   //!
   TBranch        *b_s_trkEndEnMC;   //!
   TBranch        *b_s_trkStartEnMC;   //!
   TBranch        *b_s_trkContainmentMC;   //!
   TBranch        *b_s_sigma;   //!
   TBranch        *b_s_iaction;   //!
   TBranch        *b_s_iresonance;   //!
   TBranch        *b_s_inu;   //!
   TBranch        *b_s_inunoosc;   //!
   TBranch        *b_s_itg;   //!
   TBranch        *b_s_vtxxMC;   //!
   TBranch        *b_s_vtxyMC;   //!
   TBranch        *b_s_vtxzMC;   //!
   TBranch        *b_s_vtxuMC;   //!
   TBranch        *b_s_vtxvMC;   //!
   TBranch        *b_s_planeTrkVtxMC;   //!
   TBranch        *b_s_rTrkVtxMC;   //!
   TBranch        *b_s_mc;   //!
   TBranch        *b_s_mcTrk;   //!
   TBranch        *b_s_mcShw;   //!
   TBranch        *b_s_mcEvt;   //!
   TBranch        *b_s_mcTrk1;   //!
   TBranch        *b_s_mcTrk2;   //!
   TBranch        *b_s_mcTrk3;   //!
   TBranch        *b_s_mcShw1;   //!
   TBranch        *b_s_mcShw2;   //!
   TBranch        *b_s_mcShw3;   //!
   TBranch        *b_s_mcShw4;   //!
   TBranch        *b_s_mcShw5;   //!
   TBranch        *b_s_Npz;   //!
   TBranch        *b_s_NdxdzNea;   //!
   TBranch        *b_s_NdydzNea;   //!
   TBranch        *b_s_NenergyN;   //!
   TBranch        *b_s_NWtNear;   //!
   TBranch        *b_s_NdxdzFar;   //!
   TBranch        *b_s_NdydzFar;   //!
   TBranch        *b_s_NenergyF;   //!
   TBranch        *b_s_NWtFar;   //!
   TBranch        *b_s_Ndecay;   //!
   TBranch        *b_s_Vx;   //!
   TBranch        *b_s_Vy;   //!
   TBranch        *b_s_Vz;   //!
   TBranch        *b_s_pdPx;   //!
   TBranch        *b_s_pdPy;   //!
   TBranch        *b_s_pdPz;   //!
   TBranch        *b_s_ppdxdz;   //!
   TBranch        *b_s_ppdydz;   //!
   TBranch        *b_s_pppz;   //!
   TBranch        *b_s_ppenergy;   //!
   TBranch        *b_s_ppmedium;   //!
   TBranch        *b_s_ppvx;   //!
   TBranch        *b_s_ppvy;   //!
   TBranch        *b_s_ppvz;   //!
   TBranch        *b_s_ptype;   //!
   TBranch        *b_s_Necm;   //!
   TBranch        *b_s_Nimpwt;   //!
   TBranch        *b_s_tvx;   //!
   TBranch        *b_s_tvy;   //!
   TBranch        *b_s_tvz;   //!
   TBranch        *b_s_tpx;   //!
   TBranch        *b_s_tpy;   //!
   TBranch        *b_s_tpz;   //!
   TBranch        *b_s_tptype;   //!
   TBranch        *b_s_tgen;   //!
   TBranch        *b_s_InukeNwts;   //!
   TBranch        *b_s_InukePiCExchgP;   //!
   TBranch        *b_s_InukePiCExchgN;   //!
   TBranch        *b_s_InukePiEScatP;   //!
   TBranch        *b_s_InukePiEScatN;   //!
   TBranch        *b_s_InukePiInEScatP;   //!
   TBranch        *b_s_InukePiInEScatN;   //!
   TBranch        *b_s_InukePiAbsorbP;   //!
   TBranch        *b_s_InukePiAbsorbN;   //!
   TBranch        *b_s_InukePi2PiP;   //!
   TBranch        *b_s_InukePi2PiN;   //!
   TBranch        *b_s_InukeNknockP;   //!
   TBranch        *b_s_InukeNknockN;   //!
   TBranch        *b_s_InukeNNPiP;   //!
   TBranch        *b_s_InukeNNPiN;   //!
   TBranch        *b_s_InukeFormTP;   //!
   TBranch        *b_s_InukeFormTN;   //!
   TBranch        *b_s_InukePiXsecP;   //!
   TBranch        *b_s_InukePiXsecN;   //!
   TBranch        *b_s_InukeNXsecP;   //!
   TBranch        *b_s_InukeNXsecN;   //!
   TBranch        *b_s_InukeNucrad;   //!
   TBranch        *b_s_InukeWrad;   //!
   TBranch        *b_s_anaVersion;   //!
   TBranch        *b_s_releaseType;   //!
   TBranch        *b_s_recoVersion;   //!
   TBranch        *b_s_mcVersion;   //!
   TBranch        *b_s_reweightVersion;   //!
   TBranch        *b_s_useGeneratorReweight;   //!
   TBranch        *b_s_sGeneratorConfigName;   //!
   TBranch        *b_s_generatorConfigNo;   //!
   TBranch        *b_s_useDBForDataQuality;   //!
   TBranch        *b_s_useDBForSpillTiming;   //!
   TBranch        *b_s_useDBForBeamInfo;   //!
   TBranch        *b_s_cutOnDataQuality;   //!
   TBranch        *b_s_cutOnSpillTiming;   //!
   TBranch        *b_s_cutOnBeamInfo;   //!
   TBranch        *b_s_applyEnergyShifts;   //!
   TBranch        *b_s_applyBeamWeight;   //!
   TBranch        *b_s_apply1SigmaWeight;   //!
   TBranch        *b_s_applyDetectorWeight;   //!
   TBranch        *b_s_applyGeneratorWeight;   //!
   TBranch        *b_s_calcMajCurv;   //!
   TBranch        *b_s_calcRoID;   //!
   TBranch        *b_s_calcJmID;   //!

   NuDstLooper(TTree *tree=0);
   virtual ~NuDstLooper();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     MakeHistos(char *fileName,int isData=0,char *tag=0);
   virtual void     MakePredicitions(char *fileName, TH1D *ndRatioNQ, TH1D *ndRatioPQ, TH1D *ndRatioNC, TH1D *ndRatioNCTrack, int startDmiIndex, int endDmiIndex, char *tag=0, TH1D *histRwNumu=0, TH1D *histRwNumubar=0, TH1D *histRwNue=0, TH1D *histRwNuebar=0); 
   virtual void     MakePassTree(char *fileName, TH1D *ndRatioNQ, TH1D *ndRatioPQ, TH1D *ndRatioNC, TH1D *ndRatioNCTrack, char *tag=0, TH1D *histRwNumu=0, TH1D *histRwNumubar=0, TH1D *histRwNue=0, TH1D *histRwNuebar=0); 
   virtual void     MakePredicitonsFromPassTree(char *passTreeFileName, char *fileName, int startDmiIndex, int endDmiIndex);

   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
   virtual Double_t getOscWeight(Double_t *par);
   virtual Int_t getCutId(Int_t isData, Bool_t *goodNCCandidate);
   virtual void setCCTrackEnergy();
};

#endif

#ifdef NuDstLooper_cxx
NuDstLooper::NuDstLooper(TTree *tree)
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("/unix/minos1/rjn/2010/R2.2/data/near/dogwood3/pHE/micro2010/NuDSTMicro2010N00010233.root");
      if (!f) {
         f = new TFile("/unix/minos1/rjn/2010/R2.2/data/near/dogwood3/pHE/micro2010/NuDSTMicro2010N00010233.root");
      }
      tree = (TTree*)gDirectory->Get("s");

   }
   Init(tree);
}

NuDstLooper::~NuDstLooper()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t NuDstLooper::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t NuDstLooper::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (!fChain->InheritsFrom(TChain::Class()))  return centry;
   TChain *chain = (TChain*)fChain;
   if (chain->GetTreeNumber() != fCurrent) {
      fCurrent = chain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void NuDstLooper::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("fUniqueID", &fUniqueID, &b_s_fUniqueID);
   fChain->SetBranchAddress("fBits", &fBits, &b_s_fBits);
   fChain->SetBranchAddress("index", &index, &b_s_index);
   fChain->SetBranchAddress("entry", &entry, &b_s_entry);
   fChain->SetBranchAddress("run", &run, &b_s_run);
   fChain->SetBranchAddress("subRun", &subRun, &b_s_subRun);
   fChain->SetBranchAddress("runType", &runType, &b_s_runType);
   fChain->SetBranchAddress("errorCode", &errorCode, &b_s_errorCode);
   fChain->SetBranchAddress("snarl", &snarl, &b_s_snarl);
   fChain->SetBranchAddress("trigSrc", &trigSrc, &b_s_trigSrc);
   fChain->SetBranchAddress("timeFrame", &timeFrame, &b_s_timeFrame);
   fChain->SetBranchAddress("remoteSpillType", &remoteSpillType, &b_s_remoteSpillType);
   fChain->SetBranchAddress("detector", &detector, &b_s_detector);
   fChain->SetBranchAddress("simFlag", &simFlag, &b_s_simFlag);
   fChain->SetBranchAddress("timeSec", &timeSec, &b_s_timeSec);
   fChain->SetBranchAddress("timeNanoSec", &timeNanoSec, &b_s_timeNanoSec);
   fChain->SetBranchAddress("timeSeconds", &timeSeconds, &b_s_timeSeconds);
   fChain->SetBranchAddress("trigtime", &trigtime, &b_s_trigtime);
   fChain->SetBranchAddress("medianTime", &medianTime, &b_s_medianTime);
   fChain->SetBranchAddress("timeEvtMin", &timeEvtMin, &b_s_timeEvtMin);
   fChain->SetBranchAddress("timeEvtMax", &timeEvtMax, &b_s_timeEvtMax);
   fChain->SetBranchAddress("crateT0", &crateT0, &b_s_crateT0);
   fChain->SetBranchAddress("nearestSpillSec", &nearestSpillSec, &b_s_nearestSpillSec);
   fChain->SetBranchAddress("nearestSpillNanosec", &nearestSpillNanosec, &b_s_nearestSpillNanosec);
   fChain->SetBranchAddress("timeToNearestSpill", &timeToNearestSpill, &b_s_timeToNearestSpill);
   fChain->SetBranchAddress("planeEvtHdrBeg", &planeEvtHdrBeg, &b_s_planeEvtHdrBeg);
   fChain->SetBranchAddress("planeEvtHdrEnd", &planeEvtHdrEnd, &b_s_planeEvtHdrEnd);
   fChain->SetBranchAddress("snarlPulseHeight", &snarlPulseHeight, &b_s_snarlPulseHeight);
   fChain->SetBranchAddress("isGoodDataQuality", &isGoodDataQuality, &b_s_isGoodDataQuality);
   fChain->SetBranchAddress("isGoodDataQualityRUN", &isGoodDataQualityRUN, &b_s_isGoodDataQualityRUN);
   fChain->SetBranchAddress("isGoodDataQualityCOIL", &isGoodDataQualityCOIL, &b_s_isGoodDataQualityCOIL);
   fChain->SetBranchAddress("isGoodDataQualityHV", &isGoodDataQualityHV, &b_s_isGoodDataQualityHV);
   fChain->SetBranchAddress("isGoodDataQualityGPS", &isGoodDataQualityGPS, &b_s_isGoodDataQualityGPS);
   fChain->SetBranchAddress("numActiveCrates", &numActiveCrates, &b_s_numActiveCrates);
   fChain->SetBranchAddress("numTimeFrames", &numTimeFrames, &b_s_numTimeFrames);
   fChain->SetBranchAddress("numGoodSnarls", &numGoodSnarls, &b_s_numGoodSnarls);
   fChain->SetBranchAddress("snarlRateMedian", &snarlRateMedian, &b_s_snarlRateMedian);
   fChain->SetBranchAddress("snarlRateMax", &snarlRateMax, &b_s_snarlRateMax);
   fChain->SetBranchAddress("deltaSecToSpillGPS", &deltaSecToSpillGPS, &b_s_deltaSecToSpillGPS);
   fChain->SetBranchAddress("deltaNanoSecToSpillGPS", &deltaNanoSecToSpillGPS, &b_s_deltaNanoSecToSpillGPS);
   fChain->SetBranchAddress("gpsError", &gpsError, &b_s_gpsError);
   fChain->SetBranchAddress("gpsSpillType", &gpsSpillType, &b_s_gpsSpillType);
   fChain->SetBranchAddress("coilIsOk", &coilIsOk, &b_s_coilIsOk);
   fChain->SetBranchAddress("coilIsReverse", &coilIsReverse, &b_s_coilIsReverse);
   fChain->SetBranchAddress("coilCurrent", &coilCurrent, &b_s_coilCurrent);
   fChain->SetBranchAddress("isLI", &isLI, &b_s_isLI);
   fChain->SetBranchAddress("litag", &litag, &b_s_litag);
   fChain->SetBranchAddress("litime", &litime, &b_s_litime);
   fChain->SetBranchAddress("energy", &energy, &b_s_energy);
   fChain->SetBranchAddress("energyCC", &energyCC, &b_s_energyCC);
   fChain->SetBranchAddress("energyNC", &energyNC, &b_s_energyNC);
   fChain->SetBranchAddress("energyRM", &energyRM, &b_s_energyRM);
   fChain->SetBranchAddress("trkEn", &trkEn, &b_s_trkEn);
   fChain->SetBranchAddress("trkEnRange", &trkEnRange, &b_s_trkEnRange);
   fChain->SetBranchAddress("trkEnCurv", &trkEnCurv, &b_s_trkEnCurv);
   fChain->SetBranchAddress("shwEn", &shwEn, &b_s_shwEn);
   fChain->SetBranchAddress("shwEnCC", &shwEnCC, &b_s_shwEnCC);
   fChain->SetBranchAddress("shwEnNC", &shwEnNC, &b_s_shwEnNC);
   fChain->SetBranchAddress("resolution", &resolution, &b_s_resolution);
   fChain->SetBranchAddress("isInFidVolCC", &isInFidVolCC, &b_s_isInFidVolCC);
   fChain->SetBranchAddress("isGoodTrackReclamation", &isGoodTrackReclamation, &b_s_isGoodTrackReclamation);
   fChain->SetBranchAddress("isNCClean", &isNCClean, &b_s_isNCClean);
   fChain->SetBranchAddress("y", &y, &b_s_y);
   fChain->SetBranchAddress("q2", &q2, &b_s_q2);
   fChain->SetBranchAddress("x", &x, &b_s_x);
   fChain->SetBranchAddress("w2", &w2, &b_s_w2);
   fChain->SetBranchAddress("dirCosNu", &dirCosNu, &b_s_dirCosNu);
   fChain->SetBranchAddress("evt", &evt, &b_s_evt);
   fChain->SetBranchAddress("slc", &slc, &b_s_slc);
   fChain->SetBranchAddress("nevt", &nevt, &b_s_nevt);
   fChain->SetBranchAddress("ndigitEvt", &ndigitEvt, &b_s_ndigitEvt);
   fChain->SetBranchAddress("nstripEvt", &nstripEvt, &b_s_nstripEvt);
   fChain->SetBranchAddress("nshw", &nshw, &b_s_nshw);
   fChain->SetBranchAddress("ntrk", &ntrk, &b_s_ntrk);
   fChain->SetBranchAddress("primshw", &primshw, &b_s_primshw);
   fChain->SetBranchAddress("primtrk", &primtrk, &b_s_primtrk);
   fChain->SetBranchAddress("rawPhEvt", &rawPhEvt, &b_s_rawPhEvt);
   fChain->SetBranchAddress("evtphsigcor", &evtphsigcor, &b_s_evtphsigcor);
   fChain->SetBranchAddress("evtphsigmap", &evtphsigmap, &b_s_evtphsigmap);
   fChain->SetBranchAddress("planeEvtN", &planeEvtN, &b_s_planeEvtN);
   fChain->SetBranchAddress("planeEvtNu", &planeEvtNu, &b_s_planeEvtNu);
   fChain->SetBranchAddress("planeEvtNv", &planeEvtNv, &b_s_planeEvtNv);
   fChain->SetBranchAddress("roIDEvt", &roIDEvt, &b_s_roIDEvt);
   fChain->SetBranchAddress("knn01TrkActivePlanesEvt", &knn01TrkActivePlanesEvt, &b_s_knn01TrkActivePlanesEvt);
   fChain->SetBranchAddress("knn10TrkMeanPhEvt", &knn10TrkMeanPhEvt, &b_s_knn10TrkMeanPhEvt);
   fChain->SetBranchAddress("knn20LowHighPhEvt", &knn20LowHighPhEvt, &b_s_knn20LowHighPhEvt);
   fChain->SetBranchAddress("knn40TrkPhFracEvt", &knn40TrkPhFracEvt, &b_s_knn40TrkPhFracEvt);
   fChain->SetBranchAddress("roIDNuMuBarEvt", &roIDNuMuBarEvt, &b_s_roIDNuMuBarEvt);
   fChain->SetBranchAddress("relativeAngleEvt", &relativeAngleEvt, &b_s_relativeAngleEvt);
   fChain->SetBranchAddress("jmIDEvt", &jmIDEvt, &b_s_jmIDEvt);
   fChain->SetBranchAddress("jmTrackPlaneEvt", &jmTrackPlaneEvt, &b_s_jmTrackPlaneEvt);
   fChain->SetBranchAddress("jmEndPhEvt", &jmEndPhEvt, &b_s_jmEndPhEvt);
   fChain->SetBranchAddress("jmMeanPhEvt", &jmMeanPhEvt, &b_s_jmMeanPhEvt);
   fChain->SetBranchAddress("jmScatteringUEvt", &jmScatteringUEvt, &b_s_jmScatteringUEvt);
   fChain->SetBranchAddress("jmScatteringVEvt", &jmScatteringVEvt, &b_s_jmScatteringVEvt);
   fChain->SetBranchAddress("jmScatteringUVEvt", &jmScatteringUVEvt, &b_s_jmScatteringUVEvt);
   fChain->SetBranchAddress("jmEventknnIDEvt", &jmEventknnIDEvt, &b_s_jmEventknnIDEvt);
   fChain->SetBranchAddress("jmEventknn208Evt", &jmEventknn208Evt, &b_s_jmEventknn208Evt);
   fChain->SetBranchAddress("jmEventknn207Evt", &jmEventknn207Evt, &b_s_jmEventknn207Evt);
   fChain->SetBranchAddress("jmEventknn206Evt", &jmEventknn206Evt, &b_s_jmEventknn206Evt);
   fChain->SetBranchAddress("jmEventknn205Evt", &jmEventknn205Evt, &b_s_jmEventknn205Evt);
   fChain->SetBranchAddress("jmEventknn204Evt", &jmEventknn204Evt, &b_s_jmEventknn204Evt);
   fChain->SetBranchAddress("xEvtVtx", &xEvtVtx, &b_s_xEvtVtx);
   fChain->SetBranchAddress("yEvtVtx", &yEvtVtx, &b_s_yEvtVtx);
   fChain->SetBranchAddress("zEvtVtx", &zEvtVtx, &b_s_zEvtVtx);
   fChain->SetBranchAddress("uEvtVtx", &uEvtVtx, &b_s_uEvtVtx);
   fChain->SetBranchAddress("vEvtVtx", &vEvtVtx, &b_s_vEvtVtx);
   fChain->SetBranchAddress("planeEvtVtx", &planeEvtVtx, &b_s_planeEvtVtx);
   fChain->SetBranchAddress("planeEvtBeg", &planeEvtBeg, &b_s_planeEvtBeg);
   fChain->SetBranchAddress("planeEvtBegu", &planeEvtBegu, &b_s_planeEvtBegu);
   fChain->SetBranchAddress("planeEvtBegv", &planeEvtBegv, &b_s_planeEvtBegv);
   fChain->SetBranchAddress("xEvtEnd", &xEvtEnd, &b_s_xEvtEnd);
   fChain->SetBranchAddress("yEvtEnd", &yEvtEnd, &b_s_yEvtEnd);
   fChain->SetBranchAddress("zEvtEnd", &zEvtEnd, &b_s_zEvtEnd);
   fChain->SetBranchAddress("uEvtEnd", &uEvtEnd, &b_s_uEvtEnd);
   fChain->SetBranchAddress("vEvtEnd", &vEvtEnd, &b_s_vEvtEnd);
   fChain->SetBranchAddress("planeEvtEnd", &planeEvtEnd, &b_s_planeEvtEnd);
   fChain->SetBranchAddress("planeEvtEndu", &planeEvtEndu, &b_s_planeEvtEndu);
   fChain->SetBranchAddress("planeEvtEndv", &planeEvtEndv, &b_s_planeEvtEndv);
   fChain->SetBranchAddress("trkExists", &trkExists, &b_s_trkExists);
   fChain->SetBranchAddress("trkIndex", &trkIndex, &b_s_trkIndex);
   fChain->SetBranchAddress("ndigitTrk", &ndigitTrk, &b_s_ndigitTrk);
   fChain->SetBranchAddress("nstripTrk", &nstripTrk, &b_s_nstripTrk);
   fChain->SetBranchAddress("trkEnCorRange", &trkEnCorRange, &b_s_trkEnCorRange);
   fChain->SetBranchAddress("trkEnCorCurv", &trkEnCorCurv, &b_s_trkEnCorCurv);
   fChain->SetBranchAddress("trkShwEnNear", &trkShwEnNear, &b_s_trkShwEnNear);
   fChain->SetBranchAddress("trkShwEnNearDW", &trkShwEnNearDW, &b_s_trkShwEnNearDW);
   fChain->SetBranchAddress("trkMomentumRange", &trkMomentumRange, &b_s_trkMomentumRange);
   //   fChain->SetBranchAddress("trkMomentumTransverse", &trkMomentumTransverse, &b_s_trkMomentumTransverse);
   fChain->SetBranchAddress("trkResolution", &trkResolution, &b_s_trkResolution);
   fChain->SetBranchAddress("containedTrk", &containedTrk, &b_s_containedTrk);
   fChain->SetBranchAddress("trkfitpass", &trkfitpass, &b_s_trkfitpass);
   fChain->SetBranchAddress("trkvtxdcosz", &trkvtxdcosz, &b_s_trkvtxdcosz);
   fChain->SetBranchAddress("trkvtxdcosy", &trkvtxdcosy, &b_s_trkvtxdcosy);
   fChain->SetBranchAddress("trknplane", &trknplane, &b_s_trknplane);
   fChain->SetBranchAddress("charge", &charge, &b_s_charge);
   fChain->SetBranchAddress("qp", &qp, &b_s_qp);
   fChain->SetBranchAddress("qp_rangebiased", &qp_rangebiased, &b_s_qp_rangebiased);
   fChain->SetBranchAddress("sigqp", &sigqp, &b_s_sigqp);
   fChain->SetBranchAddress("qp_sigqp", &qp_sigqp, &b_s_qp_sigqp);
   fChain->SetBranchAddress("chi2", &chi2, &b_s_chi2);
   fChain->SetBranchAddress("ndof", &ndof, &b_s_ndof);
   fChain->SetBranchAddress("qpFraction", &qpFraction, &b_s_qpFraction);
   fChain->SetBranchAddress("trkVtxUVDiffPl", &trkVtxUVDiffPl, &b_s_trkVtxUVDiffPl);
   fChain->SetBranchAddress("trkLength", &trkLength, &b_s_trkLength);
   fChain->SetBranchAddress("planeTrkNu", &planeTrkNu, &b_s_planeTrkNu);
   fChain->SetBranchAddress("planeTrkNv", &planeTrkNv, &b_s_planeTrkNv);
   fChain->SetBranchAddress("ntrklike", &ntrklike, &b_s_ntrklike);
   fChain->SetBranchAddress("trkphsigcor", &trkphsigcor, &b_s_trkphsigcor);
   fChain->SetBranchAddress("trkphsigmap", &trkphsigmap, &b_s_trkphsigmap);
   fChain->SetBranchAddress("trkIdMC", &trkIdMC, &b_s_trkIdMC);
   fChain->SetBranchAddress("trkfitpassSA", &trkfitpassSA, &b_s_trkfitpassSA);
   fChain->SetBranchAddress("trkvtxdcoszSA", &trkvtxdcoszSA, &b_s_trkvtxdcoszSA);
   fChain->SetBranchAddress("chargeSA", &chargeSA, &b_s_chargeSA);
   fChain->SetBranchAddress("qpSA", &qpSA, &b_s_qpSA);
   fChain->SetBranchAddress("sigqpSA", &sigqpSA, &b_s_sigqpSA);
   fChain->SetBranchAddress("chi2SA", &chi2SA, &b_s_chi2SA);
   fChain->SetBranchAddress("ndofSA", &ndofSA, &b_s_ndofSA);
   fChain->SetBranchAddress("probSA", &probSA, &b_s_probSA);
   fChain->SetBranchAddress("xTrkVtxSA", &xTrkVtxSA, &b_s_xTrkVtxSA);
   fChain->SetBranchAddress("yTrkVtxSA", &yTrkVtxSA, &b_s_yTrkVtxSA);
   fChain->SetBranchAddress("zTrkVtxSA", &zTrkVtxSA, &b_s_zTrkVtxSA);
   fChain->SetBranchAddress("uTrkVtxSA", &uTrkVtxSA, &b_s_uTrkVtxSA);
   fChain->SetBranchAddress("vTrkVtxSA", &vTrkVtxSA, &b_s_vTrkVtxSA);
   fChain->SetBranchAddress("jitter", &jitter, &b_s_jitter);
   fChain->SetBranchAddress("jPID", &jPID, &b_s_jPID);
   fChain->SetBranchAddress("majC", &majC, &b_s_majC);
   fChain->SetBranchAddress("smoothMajC", &smoothMajC, &b_s_smoothMajC);
   fChain->SetBranchAddress("xTrkVtx", &xTrkVtx, &b_s_xTrkVtx);
   fChain->SetBranchAddress("yTrkVtx", &yTrkVtx, &b_s_yTrkVtx);
   fChain->SetBranchAddress("zTrkVtx", &zTrkVtx, &b_s_zTrkVtx);
   fChain->SetBranchAddress("uTrkVtx", &uTrkVtx, &b_s_uTrkVtx);
   fChain->SetBranchAddress("vTrkVtx", &vTrkVtx, &b_s_vTrkVtx);
   fChain->SetBranchAddress("planeTrkVtx", &planeTrkVtx, &b_s_planeTrkVtx);
   fChain->SetBranchAddress("planeTrkBeg", &planeTrkBeg, &b_s_planeTrkBeg);
   fChain->SetBranchAddress("planeTrkBegu", &planeTrkBegu, &b_s_planeTrkBegu);
   fChain->SetBranchAddress("planeTrkBegv", &planeTrkBegv, &b_s_planeTrkBegv);
   fChain->SetBranchAddress("stripTrkBeg", &stripTrkBeg, &b_s_stripTrkBeg);
   fChain->SetBranchAddress("stripTrkBegu", &stripTrkBegu, &b_s_stripTrkBegu);
   fChain->SetBranchAddress("stripTrkBegv", &stripTrkBegv, &b_s_stripTrkBegv);
   fChain->SetBranchAddress("stripTrkEnd", &stripTrkEnd, &b_s_stripTrkEnd);
   fChain->SetBranchAddress("stripTrkEndu", &stripTrkEndu, &b_s_stripTrkEndu);
   fChain->SetBranchAddress("stripTrkEndv", &stripTrkEndv, &b_s_stripTrkEndv);
   fChain->SetBranchAddress("stripTrkBegIsu", &stripTrkBegIsu, &b_s_stripTrkBegIsu);
   fChain->SetBranchAddress("stripTrkEndIsu", &stripTrkEndIsu, &b_s_stripTrkEndIsu);
   fChain->SetBranchAddress("regionTrkVtx", &regionTrkVtx, &b_s_regionTrkVtx);
   fChain->SetBranchAddress("edgeRegionTrkVtx", &edgeRegionTrkVtx, &b_s_edgeRegionTrkVtx);
   fChain->SetBranchAddress("edgeRegionTrkEnd", &edgeRegionTrkEnd, &b_s_edgeRegionTrkEnd);
   fChain->SetBranchAddress("phiTrkVtx", &phiTrkVtx, &b_s_phiTrkVtx);
   fChain->SetBranchAddress("phiTrkEnd", &phiTrkEnd, &b_s_phiTrkEnd);
   fChain->SetBranchAddress("parallelStripTrkVtx", &parallelStripTrkVtx, &b_s_parallelStripTrkVtx);
   //   fChain->SetBranchAddress("parallelStripTrkVtxNoShift", &parallelStripTrkVtxNoShift, &b_s_parallelStripTrkVtxNoShift);
   fChain->SetBranchAddress("parallelStripTrkEnd", &parallelStripTrkEnd, &b_s_parallelStripTrkEnd);
   fChain->SetBranchAddress("stripTrkBegPerpFlag", &stripTrkBegPerpFlag, &b_s_stripTrkBegPerpFlag);
   fChain->SetBranchAddress("stripTrkEndPerpFlag", &stripTrkEndPerpFlag, &b_s_stripTrkEndPerpFlag);
   fChain->SetBranchAddress("stripHoveNumTrkVtx", &stripHoveNumTrkVtx, &b_s_stripHoveNumTrkVtx);
   //   fChain->SetBranchAddress("stripHoveNumTrkVtxNoShift", &stripHoveNumTrkVtxNoShift, &b_s_stripHoveNumTrkVtxNoShift);
   fChain->SetBranchAddress("stripHoveNumTrkEnd", &stripHoveNumTrkEnd, &b_s_stripHoveNumTrkEnd);
   fChain->SetBranchAddress("xTrkEnd", &xTrkEnd, &b_s_xTrkEnd);
   fChain->SetBranchAddress("yTrkEnd", &yTrkEnd, &b_s_yTrkEnd);
   fChain->SetBranchAddress("zTrkEnd", &zTrkEnd, &b_s_zTrkEnd);
   fChain->SetBranchAddress("uTrkEnd", &uTrkEnd, &b_s_uTrkEnd);
   fChain->SetBranchAddress("vTrkEnd", &vTrkEnd, &b_s_vTrkEnd);
   fChain->SetBranchAddress("planeTrkEnd", &planeTrkEnd, &b_s_planeTrkEnd);
   fChain->SetBranchAddress("planeTrkEndu", &planeTrkEndu, &b_s_planeTrkEndu);
   fChain->SetBranchAddress("planeTrkEndv", &planeTrkEndv, &b_s_planeTrkEndv);
   fChain->SetBranchAddress("drTrkFidall", &drTrkFidall, &b_s_drTrkFidall);
   fChain->SetBranchAddress("dzTrkFidall", &dzTrkFidall, &b_s_dzTrkFidall);
   fChain->SetBranchAddress("drTrkFidvtx", &drTrkFidvtx, &b_s_drTrkFidvtx);
   fChain->SetBranchAddress("dzTrkFidvtx", &dzTrkFidvtx, &b_s_dzTrkFidvtx);
   fChain->SetBranchAddress("drTrkFidend", &drTrkFidend, &b_s_drTrkFidend);
   fChain->SetBranchAddress("dzTrkFidend", &dzTrkFidend, &b_s_dzTrkFidend);
   fChain->SetBranchAddress("traceTrkFidall", &traceTrkFidall, &b_s_traceTrkFidall);
   fChain->SetBranchAddress("traceTrkFidvtx", &traceTrkFidvtx, &b_s_traceTrkFidvtx);
   fChain->SetBranchAddress("traceTrkFidend", &traceTrkFidend, &b_s_traceTrkFidend);
   fChain->SetBranchAddress("cosPrTrkVtx", &cosPrTrkVtx, &b_s_cosPrTrkVtx);
   fChain->SetBranchAddress("shwExists", &shwExists, &b_s_shwExists);
   fChain->SetBranchAddress("ndigitShw", &ndigitShw, &b_s_ndigitShw);
   fChain->SetBranchAddress("nstripShw", &nstripShw, &b_s_nstripShw);
   fChain->SetBranchAddress("nplaneShw", &nplaneShw, &b_s_nplaneShw);
   fChain->SetBranchAddress("shwEnCor", &shwEnCor, &b_s_shwEnCor);
   fChain->SetBranchAddress("shwEnNoCor", &shwEnNoCor, &b_s_shwEnNoCor);
   fChain->SetBranchAddress("shwEnMip", &shwEnMip, &b_s_shwEnMip);
   fChain->SetBranchAddress("shwEnLinCCNoCor", &shwEnLinCCNoCor, &b_s_shwEnLinCCNoCor);
   fChain->SetBranchAddress("shwEnLinCCCor", &shwEnLinCCCor, &b_s_shwEnLinCCCor);
   fChain->SetBranchAddress("shwEnWtCCNoCor", &shwEnWtCCNoCor, &b_s_shwEnWtCCNoCor);
   fChain->SetBranchAddress("shwEnWtCCCor", &shwEnWtCCCor, &b_s_shwEnWtCCCor);
   fChain->SetBranchAddress("shwEnLinNCNoCor", &shwEnLinNCNoCor, &b_s_shwEnLinNCNoCor);
   fChain->SetBranchAddress("shwEnLinNCCor", &shwEnLinNCCor, &b_s_shwEnLinNCCor);
   fChain->SetBranchAddress("shwEnWtNCNoCor", &shwEnWtNCNoCor, &b_s_shwEnWtNCNoCor);
   fChain->SetBranchAddress("shwEnWtNCCor", &shwEnWtNCCor, &b_s_shwEnWtNCCor);
   fChain->SetBranchAddress("shwResolution", &shwResolution, &b_s_shwResolution);
   fChain->SetBranchAddress("shwEnkNN", &shwEnkNN, &b_s_shwEnkNN);
   fChain->SetBranchAddress("shwEnReskNN", &shwEnReskNN, &b_s_shwEnReskNN);
   fChain->SetBranchAddress("planeShwBeg", &planeShwBeg, &b_s_planeShwBeg);
   fChain->SetBranchAddress("planeShwEnd", &planeShwEnd, &b_s_planeShwEnd);
   fChain->SetBranchAddress("planeShwMax", &planeShwMax, &b_s_planeShwMax);
   fChain->SetBranchAddress("xShwVtx", &xShwVtx, &b_s_xShwVtx);
   fChain->SetBranchAddress("yShwVtx", &yShwVtx, &b_s_yShwVtx);
   fChain->SetBranchAddress("zShwVtx", &zShwVtx, &b_s_zShwVtx);
   fChain->SetBranchAddress("trkExists1", &trkExists1, &b_s_trkExists1);
   fChain->SetBranchAddress("trkIndex1", &trkIndex1, &b_s_trkIndex1);
   fChain->SetBranchAddress("ndigitTrk1", &ndigitTrk1, &b_s_ndigitTrk1);
   fChain->SetBranchAddress("nstripTrk1", &nstripTrk1, &b_s_nstripTrk1);
   fChain->SetBranchAddress("trkEnCorRange1", &trkEnCorRange1, &b_s_trkEnCorRange1);
   fChain->SetBranchAddress("trkEnCorCurv1", &trkEnCorCurv1, &b_s_trkEnCorCurv1);
   fChain->SetBranchAddress("trkShwEnNear1", &trkShwEnNear1, &b_s_trkShwEnNear1);
   fChain->SetBranchAddress("trkShwEnNearDW1", &trkShwEnNearDW1, &b_s_trkShwEnNearDW1);
   fChain->SetBranchAddress("trkMomentumRange1", &trkMomentumRange1, &b_s_trkMomentumRange1);
   //   fChain->SetBranchAddress("trkMomentumTransverse1", &trkMomentumTransverse1, &b_s_trkMomentumTransverse1);
   fChain->SetBranchAddress("containedTrk1", &containedTrk1, &b_s_containedTrk1);
   fChain->SetBranchAddress("trkfitpass1", &trkfitpass1, &b_s_trkfitpass1);
   fChain->SetBranchAddress("trkvtxdcosz1", &trkvtxdcosz1, &b_s_trkvtxdcosz1);
   fChain->SetBranchAddress("trkvtxdcosy1", &trkvtxdcosy1, &b_s_trkvtxdcosy1);
   fChain->SetBranchAddress("trknplane1", &trknplane1, &b_s_trknplane1);
   fChain->SetBranchAddress("charge1", &charge1, &b_s_charge1);
   fChain->SetBranchAddress("qp1", &qp1, &b_s_qp1);
   fChain->SetBranchAddress("qp_rangebiased1", &qp_rangebiased1, &b_s_qp_rangebiased1);
   fChain->SetBranchAddress("sigqp1", &sigqp1, &b_s_sigqp1);
   fChain->SetBranchAddress("qp_sigqp1", &qp_sigqp1, &b_s_qp_sigqp1);
   fChain->SetBranchAddress("chi21", &chi21, &b_s_chi21);
   fChain->SetBranchAddress("ndof1", &ndof1, &b_s_ndof1);
   fChain->SetBranchAddress("qpFraction1", &qpFraction1, &b_s_qpFraction1);
   fChain->SetBranchAddress("trkVtxUVDiffPl1", &trkVtxUVDiffPl1, &b_s_trkVtxUVDiffPl1);
   fChain->SetBranchAddress("trkLength1", &trkLength1, &b_s_trkLength1);
   fChain->SetBranchAddress("planeTrkNu1", &planeTrkNu1, &b_s_planeTrkNu1);
   fChain->SetBranchAddress("planeTrkNv1", &planeTrkNv1, &b_s_planeTrkNv1);
   fChain->SetBranchAddress("ntrklike1", &ntrklike1, &b_s_ntrklike1);
   fChain->SetBranchAddress("trkphsigcor1", &trkphsigcor1, &b_s_trkphsigcor1);
   fChain->SetBranchAddress("trkphsigmap1", &trkphsigmap1, &b_s_trkphsigmap1);
   fChain->SetBranchAddress("trkIdMC1", &trkIdMC1, &b_s_trkIdMC1);
   fChain->SetBranchAddress("trkfitpassSA1", &trkfitpassSA1, &b_s_trkfitpassSA1);
   fChain->SetBranchAddress("trkvtxdcoszSA1", &trkvtxdcoszSA1, &b_s_trkvtxdcoszSA1);
   fChain->SetBranchAddress("chargeSA1", &chargeSA1, &b_s_chargeSA1);
   fChain->SetBranchAddress("qpSA1", &qpSA1, &b_s_qpSA1);
   fChain->SetBranchAddress("sigqpSA1", &sigqpSA1, &b_s_sigqpSA1);
   fChain->SetBranchAddress("chi2SA1", &chi2SA1, &b_s_chi2SA1);
   fChain->SetBranchAddress("ndofSA1", &ndofSA1, &b_s_ndofSA1);
   fChain->SetBranchAddress("probSA1", &probSA1, &b_s_probSA1);
   fChain->SetBranchAddress("xTrkVtxSA1", &xTrkVtxSA1, &b_s_xTrkVtxSA1);
   fChain->SetBranchAddress("yTrkVtxSA1", &yTrkVtxSA1, &b_s_yTrkVtxSA1);
   fChain->SetBranchAddress("zTrkVtxSA1", &zTrkVtxSA1, &b_s_zTrkVtxSA1);
   fChain->SetBranchAddress("uTrkVtxSA1", &uTrkVtxSA1, &b_s_uTrkVtxSA1);
   fChain->SetBranchAddress("vTrkVtxSA1", &vTrkVtxSA1, &b_s_vTrkVtxSA1);
   fChain->SetBranchAddress("jitter1", &jitter1, &b_s_jitter1);
   fChain->SetBranchAddress("jPID1", &jPID1, &b_s_jPID1);
   fChain->SetBranchAddress("majC1", &majC1, &b_s_majC1);
   fChain->SetBranchAddress("smoothMajC1", &smoothMajC1, &b_s_smoothMajC1);
   fChain->SetBranchAddress("roID1", &roID1, &b_s_roID1);
   fChain->SetBranchAddress("knn01TrkActivePlanes1", &knn01TrkActivePlanes1, &b_s_knn01TrkActivePlanes1);
   fChain->SetBranchAddress("knn10TrkMeanPh1", &knn10TrkMeanPh1, &b_s_knn10TrkMeanPh1);
   fChain->SetBranchAddress("knn20LowHighPh1", &knn20LowHighPh1, &b_s_knn20LowHighPh1);
   fChain->SetBranchAddress("knn40TrkPhFrac1", &knn40TrkPhFrac1, &b_s_knn40TrkPhFrac1);
   fChain->SetBranchAddress("roIDNuMuBar1", &roIDNuMuBar1, &b_s_roIDNuMuBar1);
   fChain->SetBranchAddress("relativeAngle1", &relativeAngle1, &b_s_relativeAngle1);
   fChain->SetBranchAddress("jmID1", &jmID1, &b_s_jmID1);
   fChain->SetBranchAddress("jmTrackPlane1", &jmTrackPlane1, &b_s_jmTrackPlane1);
   fChain->SetBranchAddress("jmEndPh1", &jmEndPh1, &b_s_jmEndPh1);
   fChain->SetBranchAddress("jmMeanPh1", &jmMeanPh1, &b_s_jmMeanPh1);
   fChain->SetBranchAddress("jmScatteringU1", &jmScatteringU1, &b_s_jmScatteringU1);
   fChain->SetBranchAddress("jmScatteringV1", &jmScatteringV1, &b_s_jmScatteringV1);
   fChain->SetBranchAddress("jmScatteringUV1", &jmScatteringUV1, &b_s_jmScatteringUV1);
   fChain->SetBranchAddress("xTrkVtx1", &xTrkVtx1, &b_s_xTrkVtx1);
   fChain->SetBranchAddress("yTrkVtx1", &yTrkVtx1, &b_s_yTrkVtx1);
   fChain->SetBranchAddress("zTrkVtx1", &zTrkVtx1, &b_s_zTrkVtx1);
   fChain->SetBranchAddress("uTrkVtx1", &uTrkVtx1, &b_s_uTrkVtx1);
   fChain->SetBranchAddress("vTrkVtx1", &vTrkVtx1, &b_s_vTrkVtx1);
   fChain->SetBranchAddress("planeTrkVtx1", &planeTrkVtx1, &b_s_planeTrkVtx1);
   fChain->SetBranchAddress("planeTrkBeg1", &planeTrkBeg1, &b_s_planeTrkBeg1);
   fChain->SetBranchAddress("planeTrkBegu1", &planeTrkBegu1, &b_s_planeTrkBegu1);
   fChain->SetBranchAddress("planeTrkBegv1", &planeTrkBegv1, &b_s_planeTrkBegv1);
   fChain->SetBranchAddress("stripTrkBeg1", &stripTrkBeg1, &b_s_stripTrkBeg1);
   fChain->SetBranchAddress("stripTrkBegu1", &stripTrkBegu1, &b_s_stripTrkBegu1);
   fChain->SetBranchAddress("stripTrkBegv1", &stripTrkBegv1, &b_s_stripTrkBegv1);
   fChain->SetBranchAddress("stripTrkEnd1", &stripTrkEnd1, &b_s_stripTrkEnd1);
   fChain->SetBranchAddress("stripTrkEndu1", &stripTrkEndu1, &b_s_stripTrkEndu1);
   fChain->SetBranchAddress("stripTrkEndv1", &stripTrkEndv1, &b_s_stripTrkEndv1);
   fChain->SetBranchAddress("stripTrkBegIsu1", &stripTrkBegIsu1, &b_s_stripTrkBegIsu1);
   fChain->SetBranchAddress("stripTrkEndIsu1", &stripTrkEndIsu1, &b_s_stripTrkEndIsu1);
   fChain->SetBranchAddress("regionTrkVtx1", &regionTrkVtx1, &b_s_regionTrkVtx1);
   fChain->SetBranchAddress("edgeRegionTrkVtx1", &edgeRegionTrkVtx1, &b_s_edgeRegionTrkVtx1);
   fChain->SetBranchAddress("edgeRegionTrkEnd1", &edgeRegionTrkEnd1, &b_s_edgeRegionTrkEnd1);
   fChain->SetBranchAddress("phiTrkVtx1", &phiTrkVtx1, &b_s_phiTrkVtx1);
   fChain->SetBranchAddress("phiTrkEnd1", &phiTrkEnd1, &b_s_phiTrkEnd1);
   fChain->SetBranchAddress("parallelStripTrkVtx1", &parallelStripTrkVtx1, &b_s_parallelStripTrkVtx1);
   fChain->SetBranchAddress("parallelStripTrkEnd1", &parallelStripTrkEnd1, &b_s_parallelStripTrkEnd1);
   fChain->SetBranchAddress("stripTrkBegPerpFlag1", &stripTrkBegPerpFlag1, &b_s_stripTrkBegPerpFlag1);
   fChain->SetBranchAddress("stripTrkEndPerpFlag1", &stripTrkEndPerpFlag1, &b_s_stripTrkEndPerpFlag1);
   fChain->SetBranchAddress("stripHoveNumTrkVtx1", &stripHoveNumTrkVtx1, &b_s_stripHoveNumTrkVtx1);
   fChain->SetBranchAddress("stripHoveNumTrkEnd1", &stripHoveNumTrkEnd1, &b_s_stripHoveNumTrkEnd1);
   fChain->SetBranchAddress("xTrkEnd1", &xTrkEnd1, &b_s_xTrkEnd1);
   fChain->SetBranchAddress("yTrkEnd1", &yTrkEnd1, &b_s_yTrkEnd1);
   fChain->SetBranchAddress("zTrkEnd1", &zTrkEnd1, &b_s_zTrkEnd1);
   fChain->SetBranchAddress("uTrkEnd1", &uTrkEnd1, &b_s_uTrkEnd1);
   fChain->SetBranchAddress("vTrkEnd1", &vTrkEnd1, &b_s_vTrkEnd1);
   fChain->SetBranchAddress("planeTrkEnd1", &planeTrkEnd1, &b_s_planeTrkEnd1);
   fChain->SetBranchAddress("planeTrkEndu1", &planeTrkEndu1, &b_s_planeTrkEndu1);
   fChain->SetBranchAddress("planeTrkEndv1", &planeTrkEndv1, &b_s_planeTrkEndv1);
   fChain->SetBranchAddress("drTrkFidall1", &drTrkFidall1, &b_s_drTrkFidall1);
   fChain->SetBranchAddress("dzTrkFidall1", &dzTrkFidall1, &b_s_dzTrkFidall1);
   fChain->SetBranchAddress("drTrkFidvtx1", &drTrkFidvtx1, &b_s_drTrkFidvtx1);
   fChain->SetBranchAddress("dzTrkFidvtx1", &dzTrkFidvtx1, &b_s_dzTrkFidvtx1);
   fChain->SetBranchAddress("drTrkFidend1", &drTrkFidend1, &b_s_drTrkFidend1);
   fChain->SetBranchAddress("dzTrkFidend1", &dzTrkFidend1, &b_s_dzTrkFidend1);
   fChain->SetBranchAddress("traceTrkFidall1", &traceTrkFidall1, &b_s_traceTrkFidall1);
   fChain->SetBranchAddress("traceTrkFidvtx1", &traceTrkFidvtx1, &b_s_traceTrkFidvtx1);
   fChain->SetBranchAddress("traceTrkFidend1", &traceTrkFidend1, &b_s_traceTrkFidend1);
   fChain->SetBranchAddress("cosPrTrkVtx1", &cosPrTrkVtx1, &b_s_cosPrTrkVtx1);
   fChain->SetBranchAddress("shwExists1", &shwExists1, &b_s_shwExists1);
   fChain->SetBranchAddress("ndigitShw1", &ndigitShw1, &b_s_ndigitShw1);
   fChain->SetBranchAddress("nstripShw1", &nstripShw1, &b_s_nstripShw1);
   fChain->SetBranchAddress("nplaneShw1", &nplaneShw1, &b_s_nplaneShw1);
   fChain->SetBranchAddress("shwEnCor1", &shwEnCor1, &b_s_shwEnCor1);
   fChain->SetBranchAddress("shwEnNoCor1", &shwEnNoCor1, &b_s_shwEnNoCor1);
   fChain->SetBranchAddress("shwEnLinCCNoCor1", &shwEnLinCCNoCor1, &b_s_shwEnLinCCNoCor1);
   fChain->SetBranchAddress("shwEnLinCCCor1", &shwEnLinCCCor1, &b_s_shwEnLinCCCor1);
   fChain->SetBranchAddress("shwEnWtCCNoCor1", &shwEnWtCCNoCor1, &b_s_shwEnWtCCNoCor1);
   fChain->SetBranchAddress("shwEnWtCCCor1", &shwEnWtCCCor1, &b_s_shwEnWtCCCor1);
   fChain->SetBranchAddress("shwEnLinNCNoCor1", &shwEnLinNCNoCor1, &b_s_shwEnLinNCNoCor1);
   fChain->SetBranchAddress("shwEnLinNCCor1", &shwEnLinNCCor1, &b_s_shwEnLinNCCor1);
   fChain->SetBranchAddress("shwEnWtNCNoCor1", &shwEnWtNCNoCor1, &b_s_shwEnWtNCNoCor1);
   fChain->SetBranchAddress("shwEnWtNCCor1", &shwEnWtNCCor1, &b_s_shwEnWtNCCor1);
   fChain->SetBranchAddress("shwEnMip1", &shwEnMip1, &b_s_shwEnMip1);
   fChain->SetBranchAddress("planeShwBeg1", &planeShwBeg1, &b_s_planeShwBeg1);
   fChain->SetBranchAddress("planeShwEnd1", &planeShwEnd1, &b_s_planeShwEnd1);
   fChain->SetBranchAddress("planeShwMax1", &planeShwMax1, &b_s_planeShwMax1);
   fChain->SetBranchAddress("xShwVtx1", &xShwVtx1, &b_s_xShwVtx1);
   fChain->SetBranchAddress("yShwVtx1", &yShwVtx1, &b_s_yShwVtx1);
   fChain->SetBranchAddress("zShwVtx1", &zShwVtx1, &b_s_zShwVtx1);
   fChain->SetBranchAddress("trkExists2", &trkExists2, &b_s_trkExists2);
   fChain->SetBranchAddress("trkIndex2", &trkIndex2, &b_s_trkIndex2);
   fChain->SetBranchAddress("ndigitTrk2", &ndigitTrk2, &b_s_ndigitTrk2);
   fChain->SetBranchAddress("nstripTrk2", &nstripTrk2, &b_s_nstripTrk2);
   fChain->SetBranchAddress("trkEnCorRange2", &trkEnCorRange2, &b_s_trkEnCorRange2);
   fChain->SetBranchAddress("trkEnCorCurv2", &trkEnCorCurv2, &b_s_trkEnCorCurv2);
   fChain->SetBranchAddress("trkShwEnNear2", &trkShwEnNear2, &b_s_trkShwEnNear2);
   fChain->SetBranchAddress("trkShwEnNearDW2", &trkShwEnNearDW2, &b_s_trkShwEnNearDW2);
   fChain->SetBranchAddress("trkMomentumRange2", &trkMomentumRange2, &b_s_trkMomentumRange2);
   //   fChain->SetBranchAddress("trkMomentumTransverse2", &trkMomentumTransverse2, &b_s_trkMomentumTransverse2);
   fChain->SetBranchAddress("containedTrk2", &containedTrk2, &b_s_containedTrk2);
   fChain->SetBranchAddress("trkfitpass2", &trkfitpass2, &b_s_trkfitpass2);
   fChain->SetBranchAddress("trkvtxdcosz2", &trkvtxdcosz2, &b_s_trkvtxdcosz2);
   fChain->SetBranchAddress("trkvtxdcosy2", &trkvtxdcosy2, &b_s_trkvtxdcosy2);
   fChain->SetBranchAddress("trknplane2", &trknplane2, &b_s_trknplane2);
   fChain->SetBranchAddress("charge2", &charge2, &b_s_charge2);
   fChain->SetBranchAddress("qp2", &qp2, &b_s_qp2);
   fChain->SetBranchAddress("qp_rangebiased2", &qp_rangebiased2, &b_s_qp_rangebiased2);
   fChain->SetBranchAddress("sigqp2", &sigqp2, &b_s_sigqp2);
   fChain->SetBranchAddress("qp_sigqp2", &qp_sigqp2, &b_s_qp_sigqp2);
   fChain->SetBranchAddress("chi22", &chi22, &b_s_chi22);
   fChain->SetBranchAddress("ndof2", &ndof2, &b_s_ndof2);
   fChain->SetBranchAddress("qpFraction2", &qpFraction2, &b_s_qpFraction2);
   fChain->SetBranchAddress("trkVtxUVDiffPl2", &trkVtxUVDiffPl2, &b_s_trkVtxUVDiffPl2);
   fChain->SetBranchAddress("trkLength2", &trkLength2, &b_s_trkLength2);
   fChain->SetBranchAddress("planeTrkNu2", &planeTrkNu2, &b_s_planeTrkNu2);
   fChain->SetBranchAddress("planeTrkNv2", &planeTrkNv2, &b_s_planeTrkNv2);
   fChain->SetBranchAddress("ntrklike2", &ntrklike2, &b_s_ntrklike2);
   fChain->SetBranchAddress("trkphsigcor2", &trkphsigcor2, &b_s_trkphsigcor2);
   fChain->SetBranchAddress("trkphsigmap2", &trkphsigmap2, &b_s_trkphsigmap2);
   fChain->SetBranchAddress("trkIdMC2", &trkIdMC2, &b_s_trkIdMC2);
   fChain->SetBranchAddress("trkfitpassSA2", &trkfitpassSA2, &b_s_trkfitpassSA2);
   fChain->SetBranchAddress("trkvtxdcoszSA2", &trkvtxdcoszSA2, &b_s_trkvtxdcoszSA2);
   fChain->SetBranchAddress("chargeSA2", &chargeSA2, &b_s_chargeSA2);
   fChain->SetBranchAddress("qpSA2", &qpSA2, &b_s_qpSA2);
   fChain->SetBranchAddress("sigqpSA2", &sigqpSA2, &b_s_sigqpSA2);
   fChain->SetBranchAddress("chi2SA2", &chi2SA2, &b_s_chi2SA2);
   fChain->SetBranchAddress("ndofSA2", &ndofSA2, &b_s_ndofSA2);
   fChain->SetBranchAddress("probSA2", &probSA2, &b_s_probSA2);
   fChain->SetBranchAddress("xTrkVtxSA2", &xTrkVtxSA2, &b_s_xTrkVtxSA2);
   fChain->SetBranchAddress("yTrkVtxSA2", &yTrkVtxSA2, &b_s_yTrkVtxSA2);
   fChain->SetBranchAddress("zTrkVtxSA2", &zTrkVtxSA2, &b_s_zTrkVtxSA2);
   fChain->SetBranchAddress("uTrkVtxSA2", &uTrkVtxSA2, &b_s_uTrkVtxSA2);
   fChain->SetBranchAddress("vTrkVtxSA2", &vTrkVtxSA2, &b_s_vTrkVtxSA2);
   fChain->SetBranchAddress("jitter2", &jitter2, &b_s_jitter2);
   fChain->SetBranchAddress("jPID2", &jPID2, &b_s_jPID2);
   fChain->SetBranchAddress("majC2", &majC2, &b_s_majC2);
   fChain->SetBranchAddress("smoothMajC2", &smoothMajC2, &b_s_smoothMajC2);
   fChain->SetBranchAddress("roID2", &roID2, &b_s_roID2);
   fChain->SetBranchAddress("knn01TrkActivePlanes2", &knn01TrkActivePlanes2, &b_s_knn01TrkActivePlanes2);
   fChain->SetBranchAddress("knn10TrkMeanPh2", &knn10TrkMeanPh2, &b_s_knn10TrkMeanPh2);
   fChain->SetBranchAddress("knn20LowHighPh2", &knn20LowHighPh2, &b_s_knn20LowHighPh2);
   fChain->SetBranchAddress("knn40TrkPhFrac2", &knn40TrkPhFrac2, &b_s_knn40TrkPhFrac2);
   fChain->SetBranchAddress("roIDNuMuBar2", &roIDNuMuBar2, &b_s_roIDNuMuBar2);
   fChain->SetBranchAddress("relativeAngle2", &relativeAngle2, &b_s_relativeAngle2);
   fChain->SetBranchAddress("jmID2", &jmID2, &b_s_jmID2);
   fChain->SetBranchAddress("jmTrackPlane2", &jmTrackPlane2, &b_s_jmTrackPlane2);
   fChain->SetBranchAddress("jmEndPh2", &jmEndPh2, &b_s_jmEndPh2);
   fChain->SetBranchAddress("jmMeanPh2", &jmMeanPh2, &b_s_jmMeanPh2);
   fChain->SetBranchAddress("jmScatteringU2", &jmScatteringU2, &b_s_jmScatteringU2);
   fChain->SetBranchAddress("jmScatteringV2", &jmScatteringV2, &b_s_jmScatteringV2);
   fChain->SetBranchAddress("jmScatteringUV2", &jmScatteringUV2, &b_s_jmScatteringUV2);
   fChain->SetBranchAddress("xTrkVtx2", &xTrkVtx2, &b_s_xTrkVtx2);
   fChain->SetBranchAddress("yTrkVtx2", &yTrkVtx2, &b_s_yTrkVtx2);
   fChain->SetBranchAddress("zTrkVtx2", &zTrkVtx2, &b_s_zTrkVtx2);
   fChain->SetBranchAddress("uTrkVtx2", &uTrkVtx2, &b_s_uTrkVtx2);
   fChain->SetBranchAddress("vTrkVtx2", &vTrkVtx2, &b_s_vTrkVtx2);
   fChain->SetBranchAddress("planeTrkVtx2", &planeTrkVtx2, &b_s_planeTrkVtx2);
   fChain->SetBranchAddress("planeTrkBeg2", &planeTrkBeg2, &b_s_planeTrkBeg2);
   fChain->SetBranchAddress("planeTrkBegu2", &planeTrkBegu2, &b_s_planeTrkBegu2);
   fChain->SetBranchAddress("planeTrkBegv2", &planeTrkBegv2, &b_s_planeTrkBegv2);
   fChain->SetBranchAddress("stripTrkBeg2", &stripTrkBeg2, &b_s_stripTrkBeg2);
   fChain->SetBranchAddress("stripTrkBegu2", &stripTrkBegu2, &b_s_stripTrkBegu2);
   fChain->SetBranchAddress("stripTrkBegv2", &stripTrkBegv2, &b_s_stripTrkBegv2);
   fChain->SetBranchAddress("stripTrkEnd2", &stripTrkEnd2, &b_s_stripTrkEnd2);
   fChain->SetBranchAddress("stripTrkEndu2", &stripTrkEndu2, &b_s_stripTrkEndu2);
   fChain->SetBranchAddress("stripTrkEndv2", &stripTrkEndv2, &b_s_stripTrkEndv2);
   fChain->SetBranchAddress("stripTrkBegIsu2", &stripTrkBegIsu2, &b_s_stripTrkBegIsu2);
   fChain->SetBranchAddress("stripTrkEndIsu2", &stripTrkEndIsu2, &b_s_stripTrkEndIsu2);
   fChain->SetBranchAddress("regionTrkVtx2", &regionTrkVtx2, &b_s_regionTrkVtx2);
   fChain->SetBranchAddress("edgeRegionTrkVtx2", &edgeRegionTrkVtx2, &b_s_edgeRegionTrkVtx2);
   fChain->SetBranchAddress("edgeRegionTrkEnd2", &edgeRegionTrkEnd2, &b_s_edgeRegionTrkEnd2);
   fChain->SetBranchAddress("phiTrkVtx2", &phiTrkVtx2, &b_s_phiTrkVtx2);
   fChain->SetBranchAddress("phiTrkEnd2", &phiTrkEnd2, &b_s_phiTrkEnd2);
   fChain->SetBranchAddress("parallelStripTrkVtx2", &parallelStripTrkVtx2, &b_s_parallelStripTrkVtx2);
   fChain->SetBranchAddress("parallelStripTrkEnd2", &parallelStripTrkEnd2, &b_s_parallelStripTrkEnd2);
   fChain->SetBranchAddress("stripTrkBegPerpFlag2", &stripTrkBegPerpFlag2, &b_s_stripTrkBegPerpFlag2);
   fChain->SetBranchAddress("stripTrkEndPerpFlag2", &stripTrkEndPerpFlag2, &b_s_stripTrkEndPerpFlag2);
   fChain->SetBranchAddress("stripHoveNumTrkVtx2", &stripHoveNumTrkVtx2, &b_s_stripHoveNumTrkVtx2);
   fChain->SetBranchAddress("stripHoveNumTrkEnd2", &stripHoveNumTrkEnd2, &b_s_stripHoveNumTrkEnd2);
   fChain->SetBranchAddress("xTrkEnd2", &xTrkEnd2, &b_s_xTrkEnd2);
   fChain->SetBranchAddress("yTrkEnd2", &yTrkEnd2, &b_s_yTrkEnd2);
   fChain->SetBranchAddress("zTrkEnd2", &zTrkEnd2, &b_s_zTrkEnd2);
   fChain->SetBranchAddress("uTrkEnd2", &uTrkEnd2, &b_s_uTrkEnd2);
   fChain->SetBranchAddress("vTrkEnd2", &vTrkEnd2, &b_s_vTrkEnd2);
   fChain->SetBranchAddress("planeTrkEnd2", &planeTrkEnd2, &b_s_planeTrkEnd2);
   fChain->SetBranchAddress("planeTrkEndu2", &planeTrkEndu2, &b_s_planeTrkEndu2);
   fChain->SetBranchAddress("planeTrkEndv2", &planeTrkEndv2, &b_s_planeTrkEndv2);
   fChain->SetBranchAddress("drTrkFidall2", &drTrkFidall2, &b_s_drTrkFidall2);
   fChain->SetBranchAddress("dzTrkFidall2", &dzTrkFidall2, &b_s_dzTrkFidall2);
   fChain->SetBranchAddress("drTrkFidvtx2", &drTrkFidvtx2, &b_s_drTrkFidvtx2);
   fChain->SetBranchAddress("dzTrkFidvtx2", &dzTrkFidvtx2, &b_s_dzTrkFidvtx2);
   fChain->SetBranchAddress("drTrkFidend2", &drTrkFidend2, &b_s_drTrkFidend2);
   fChain->SetBranchAddress("dzTrkFidend2", &dzTrkFidend2, &b_s_dzTrkFidend2);
   fChain->SetBranchAddress("traceTrkFidall2", &traceTrkFidall2, &b_s_traceTrkFidall2);
   fChain->SetBranchAddress("traceTrkFidvtx2", &traceTrkFidvtx2, &b_s_traceTrkFidvtx2);
   fChain->SetBranchAddress("traceTrkFidend2", &traceTrkFidend2, &b_s_traceTrkFidend2);
   fChain->SetBranchAddress("cosPrTrkVtx2", &cosPrTrkVtx2, &b_s_cosPrTrkVtx2);
   fChain->SetBranchAddress("shwExists2", &shwExists2, &b_s_shwExists2);
   fChain->SetBranchAddress("ndigitShw2", &ndigitShw2, &b_s_ndigitShw2);
   fChain->SetBranchAddress("nstripShw2", &nstripShw2, &b_s_nstripShw2);
   fChain->SetBranchAddress("nplaneShw2", &nplaneShw2, &b_s_nplaneShw2);
   fChain->SetBranchAddress("shwEnCor2", &shwEnCor2, &b_s_shwEnCor2);
   fChain->SetBranchAddress("shwEnNoCor2", &shwEnNoCor2, &b_s_shwEnNoCor2);
   fChain->SetBranchAddress("shwEnLinCCNoCor2", &shwEnLinCCNoCor2, &b_s_shwEnLinCCNoCor2);
   fChain->SetBranchAddress("shwEnLinCCCor2", &shwEnLinCCCor2, &b_s_shwEnLinCCCor2);
   fChain->SetBranchAddress("shwEnWtCCNoCor2", &shwEnWtCCNoCor2, &b_s_shwEnWtCCNoCor2);
   fChain->SetBranchAddress("shwEnWtCCCor2", &shwEnWtCCCor2, &b_s_shwEnWtCCCor2);
   fChain->SetBranchAddress("shwEnLinNCNoCor2", &shwEnLinNCNoCor2, &b_s_shwEnLinNCNoCor2);
   fChain->SetBranchAddress("shwEnLinNCCor2", &shwEnLinNCCor2, &b_s_shwEnLinNCCor2);
   fChain->SetBranchAddress("shwEnWtNCNoCor2", &shwEnWtNCNoCor2, &b_s_shwEnWtNCNoCor2);
   fChain->SetBranchAddress("shwEnWtNCCor2", &shwEnWtNCCor2, &b_s_shwEnWtNCCor2);
   fChain->SetBranchAddress("shwEnMip2", &shwEnMip2, &b_s_shwEnMip2);
   fChain->SetBranchAddress("planeShwBeg2", &planeShwBeg2, &b_s_planeShwBeg2);
   fChain->SetBranchAddress("planeShwEnd2", &planeShwEnd2, &b_s_planeShwEnd2);
   fChain->SetBranchAddress("planeShwMax2", &planeShwMax2, &b_s_planeShwMax2);
   fChain->SetBranchAddress("xShwVtx2", &xShwVtx2, &b_s_xShwVtx2);
   fChain->SetBranchAddress("yShwVtx2", &yShwVtx2, &b_s_yShwVtx2);
   fChain->SetBranchAddress("zShwVtx2", &zShwVtx2, &b_s_zShwVtx2);
   fChain->SetBranchAddress("trkExists3", &trkExists3, &b_s_trkExists3);
   fChain->SetBranchAddress("trkIndex3", &trkIndex3, &b_s_trkIndex3);
   fChain->SetBranchAddress("ndigitTrk3", &ndigitTrk3, &b_s_ndigitTrk3);
   fChain->SetBranchAddress("nstripTrk3", &nstripTrk3, &b_s_nstripTrk3);
   fChain->SetBranchAddress("trkEnCorRange3", &trkEnCorRange3, &b_s_trkEnCorRange3);
   fChain->SetBranchAddress("trkEnCorCurv3", &trkEnCorCurv3, &b_s_trkEnCorCurv3);
   fChain->SetBranchAddress("trkShwEnNear3", &trkShwEnNear3, &b_s_trkShwEnNear3);
   fChain->SetBranchAddress("trkShwEnNearDW3", &trkShwEnNearDW3, &b_s_trkShwEnNearDW3);
   fChain->SetBranchAddress("trkMomentumRange3", &trkMomentumRange3, &b_s_trkMomentumRange3);
   //   fChain->SetBranchAddress("trkMomentumTransverse3", &trkMomentumTransverse3, &b_s_trkMomentumTransverse3);
   fChain->SetBranchAddress("containedTrk3", &containedTrk3, &b_s_containedTrk3);
   fChain->SetBranchAddress("trkfitpass3", &trkfitpass3, &b_s_trkfitpass3);
   fChain->SetBranchAddress("trkvtxdcosz3", &trkvtxdcosz3, &b_s_trkvtxdcosz3);
   fChain->SetBranchAddress("trkvtxdcosy3", &trkvtxdcosy3, &b_s_trkvtxdcosy3);
   fChain->SetBranchAddress("trknplane3", &trknplane3, &b_s_trknplane3);
   fChain->SetBranchAddress("charge3", &charge3, &b_s_charge3);
   fChain->SetBranchAddress("qp3", &qp3, &b_s_qp3);
   fChain->SetBranchAddress("qp_rangebiased3", &qp_rangebiased3, &b_s_qp_rangebiased3);
   fChain->SetBranchAddress("sigqp3", &sigqp3, &b_s_sigqp3);
   fChain->SetBranchAddress("qp_sigqp3", &qp_sigqp3, &b_s_qp_sigqp3);
   fChain->SetBranchAddress("chi23", &chi23, &b_s_chi23);
   fChain->SetBranchAddress("ndof3", &ndof3, &b_s_ndof3);
   fChain->SetBranchAddress("qpFraction3", &qpFraction3, &b_s_qpFraction3);
   fChain->SetBranchAddress("trkVtxUVDiffPl3", &trkVtxUVDiffPl3, &b_s_trkVtxUVDiffPl3);
   fChain->SetBranchAddress("trkLength3", &trkLength3, &b_s_trkLength3);
   fChain->SetBranchAddress("planeTrkNu3", &planeTrkNu3, &b_s_planeTrkNu3);
   fChain->SetBranchAddress("planeTrkNv3", &planeTrkNv3, &b_s_planeTrkNv3);
   fChain->SetBranchAddress("ntrklike3", &ntrklike3, &b_s_ntrklike3);
   fChain->SetBranchAddress("trkphsigcor3", &trkphsigcor3, &b_s_trkphsigcor3);
   fChain->SetBranchAddress("trkphsigmap3", &trkphsigmap3, &b_s_trkphsigmap3);
   fChain->SetBranchAddress("trkIdMC3", &trkIdMC3, &b_s_trkIdMC3);
   fChain->SetBranchAddress("trkfitpassSA3", &trkfitpassSA3, &b_s_trkfitpassSA3);
   fChain->SetBranchAddress("trkvtxdcoszSA3", &trkvtxdcoszSA3, &b_s_trkvtxdcoszSA3);
   fChain->SetBranchAddress("chargeSA3", &chargeSA3, &b_s_chargeSA3);
   fChain->SetBranchAddress("qpSA3", &qpSA3, &b_s_qpSA3);
   fChain->SetBranchAddress("sigqpSA3", &sigqpSA3, &b_s_sigqpSA3);
   fChain->SetBranchAddress("chi2SA3", &chi2SA3, &b_s_chi2SA3);
   fChain->SetBranchAddress("ndofSA3", &ndofSA3, &b_s_ndofSA3);
   fChain->SetBranchAddress("probSA3", &probSA3, &b_s_probSA3);
   fChain->SetBranchAddress("xTrkVtxSA3", &xTrkVtxSA3, &b_s_xTrkVtxSA3);
   fChain->SetBranchAddress("yTrkVtxSA3", &yTrkVtxSA3, &b_s_yTrkVtxSA3);
   fChain->SetBranchAddress("zTrkVtxSA3", &zTrkVtxSA3, &b_s_zTrkVtxSA3);
   fChain->SetBranchAddress("uTrkVtxSA3", &uTrkVtxSA3, &b_s_uTrkVtxSA3);
   fChain->SetBranchAddress("vTrkVtxSA3", &vTrkVtxSA3, &b_s_vTrkVtxSA3);
   fChain->SetBranchAddress("jitter3", &jitter3, &b_s_jitter3);
   fChain->SetBranchAddress("jPID3", &jPID3, &b_s_jPID3);
   fChain->SetBranchAddress("majC3", &majC3, &b_s_majC3);
   fChain->SetBranchAddress("smoothMajC3", &smoothMajC3, &b_s_smoothMajC3);
   fChain->SetBranchAddress("roID3", &roID3, &b_s_roID3);
   fChain->SetBranchAddress("knn01TrkActivePlanes3", &knn01TrkActivePlanes3, &b_s_knn01TrkActivePlanes3);
   fChain->SetBranchAddress("knn10TrkMeanPh3", &knn10TrkMeanPh3, &b_s_knn10TrkMeanPh3);
   fChain->SetBranchAddress("knn20LowHighPh3", &knn20LowHighPh3, &b_s_knn20LowHighPh3);
   fChain->SetBranchAddress("knn40TrkPhFrac3", &knn40TrkPhFrac3, &b_s_knn40TrkPhFrac3);
   fChain->SetBranchAddress("roIDNuMuBar3", &roIDNuMuBar3, &b_s_roIDNuMuBar3);
   fChain->SetBranchAddress("relativeAngle3", &relativeAngle3, &b_s_relativeAngle3);
   fChain->SetBranchAddress("jmID3", &jmID3, &b_s_jmID3);
   fChain->SetBranchAddress("jmTrackPlane3", &jmTrackPlane3, &b_s_jmTrackPlane3);
   fChain->SetBranchAddress("jmEndPh3", &jmEndPh3, &b_s_jmEndPh3);
   fChain->SetBranchAddress("jmMeanPh3", &jmMeanPh3, &b_s_jmMeanPh3);
   fChain->SetBranchAddress("jmScatteringU3", &jmScatteringU3, &b_s_jmScatteringU3);
   fChain->SetBranchAddress("jmScatteringV3", &jmScatteringV3, &b_s_jmScatteringV3);
   fChain->SetBranchAddress("jmScatteringUV3", &jmScatteringUV3, &b_s_jmScatteringUV3);
   fChain->SetBranchAddress("xTrkVtx3", &xTrkVtx3, &b_s_xTrkVtx3);
   fChain->SetBranchAddress("yTrkVtx3", &yTrkVtx3, &b_s_yTrkVtx3);
   fChain->SetBranchAddress("zTrkVtx3", &zTrkVtx3, &b_s_zTrkVtx3);
   fChain->SetBranchAddress("uTrkVtx3", &uTrkVtx3, &b_s_uTrkVtx3);
   fChain->SetBranchAddress("vTrkVtx3", &vTrkVtx3, &b_s_vTrkVtx3);
   fChain->SetBranchAddress("planeTrkVtx3", &planeTrkVtx3, &b_s_planeTrkVtx3);
   fChain->SetBranchAddress("planeTrkBeg3", &planeTrkBeg3, &b_s_planeTrkBeg3);
   fChain->SetBranchAddress("planeTrkBegu3", &planeTrkBegu3, &b_s_planeTrkBegu3);
   fChain->SetBranchAddress("planeTrkBegv3", &planeTrkBegv3, &b_s_planeTrkBegv3);
   fChain->SetBranchAddress("stripTrkBeg3", &stripTrkBeg3, &b_s_stripTrkBeg3);
   fChain->SetBranchAddress("stripTrkBegu3", &stripTrkBegu3, &b_s_stripTrkBegu3);
   fChain->SetBranchAddress("stripTrkBegv3", &stripTrkBegv3, &b_s_stripTrkBegv3);
   fChain->SetBranchAddress("stripTrkEnd3", &stripTrkEnd3, &b_s_stripTrkEnd3);
   fChain->SetBranchAddress("stripTrkEndu3", &stripTrkEndu3, &b_s_stripTrkEndu3);
   fChain->SetBranchAddress("stripTrkEndv3", &stripTrkEndv3, &b_s_stripTrkEndv3);
   fChain->SetBranchAddress("stripTrkBegIsu3", &stripTrkBegIsu3, &b_s_stripTrkBegIsu3);
   fChain->SetBranchAddress("stripTrkEndIsu3", &stripTrkEndIsu3, &b_s_stripTrkEndIsu3);
   fChain->SetBranchAddress("regionTrkVtx3", &regionTrkVtx3, &b_s_regionTrkVtx3);
   fChain->SetBranchAddress("edgeRegionTrkVtx3", &edgeRegionTrkVtx3, &b_s_edgeRegionTrkVtx3);
   fChain->SetBranchAddress("edgeRegionTrkEnd3", &edgeRegionTrkEnd3, &b_s_edgeRegionTrkEnd3);
   fChain->SetBranchAddress("phiTrkVtx3", &phiTrkVtx3, &b_s_phiTrkVtx3);
   fChain->SetBranchAddress("phiTrkEnd3", &phiTrkEnd3, &b_s_phiTrkEnd3);
   fChain->SetBranchAddress("parallelStripTrkVtx3", &parallelStripTrkVtx3, &b_s_parallelStripTrkVtx3);
   fChain->SetBranchAddress("parallelStripTrkEnd3", &parallelStripTrkEnd3, &b_s_parallelStripTrkEnd3);
   fChain->SetBranchAddress("stripTrkBegPerpFlag3", &stripTrkBegPerpFlag3, &b_s_stripTrkBegPerpFlag3);
   fChain->SetBranchAddress("stripTrkEndPerpFlag3", &stripTrkEndPerpFlag3, &b_s_stripTrkEndPerpFlag3);
   fChain->SetBranchAddress("stripHoveNumTrkVtx3", &stripHoveNumTrkVtx3, &b_s_stripHoveNumTrkVtx3);
   fChain->SetBranchAddress("stripHoveNumTrkEnd3", &stripHoveNumTrkEnd3, &b_s_stripHoveNumTrkEnd3);
   fChain->SetBranchAddress("xTrkEnd3", &xTrkEnd3, &b_s_xTrkEnd3);
   fChain->SetBranchAddress("yTrkEnd3", &yTrkEnd3, &b_s_yTrkEnd3);
   fChain->SetBranchAddress("zTrkEnd3", &zTrkEnd3, &b_s_zTrkEnd3);
   fChain->SetBranchAddress("uTrkEnd3", &uTrkEnd3, &b_s_uTrkEnd3);
   fChain->SetBranchAddress("vTrkEnd3", &vTrkEnd3, &b_s_vTrkEnd3);
   fChain->SetBranchAddress("planeTrkEnd3", &planeTrkEnd3, &b_s_planeTrkEnd3);
   fChain->SetBranchAddress("planeTrkEndu3", &planeTrkEndu3, &b_s_planeTrkEndu3);
   fChain->SetBranchAddress("planeTrkEndv3", &planeTrkEndv3, &b_s_planeTrkEndv3);
   fChain->SetBranchAddress("drTrkFidall3", &drTrkFidall3, &b_s_drTrkFidall3);
   fChain->SetBranchAddress("dzTrkFidall3", &dzTrkFidall3, &b_s_dzTrkFidall3);
   fChain->SetBranchAddress("drTrkFidvtx3", &drTrkFidvtx3, &b_s_drTrkFidvtx3);
   fChain->SetBranchAddress("dzTrkFidvtx3", &dzTrkFidvtx3, &b_s_dzTrkFidvtx3);
   fChain->SetBranchAddress("drTrkFidend3", &drTrkFidend3, &b_s_drTrkFidend3);
   fChain->SetBranchAddress("dzTrkFidend3", &dzTrkFidend3, &b_s_dzTrkFidend3);
   fChain->SetBranchAddress("traceTrkFidall3", &traceTrkFidall3, &b_s_traceTrkFidall3);
   fChain->SetBranchAddress("traceTrkFidvtx3", &traceTrkFidvtx3, &b_s_traceTrkFidvtx3);
   fChain->SetBranchAddress("traceTrkFidend3", &traceTrkFidend3, &b_s_traceTrkFidend3);
   fChain->SetBranchAddress("cosPrTrkVtx3", &cosPrTrkVtx3, &b_s_cosPrTrkVtx3);
   fChain->SetBranchAddress("shwExists3", &shwExists3, &b_s_shwExists3);
   fChain->SetBranchAddress("ndigitShw3", &ndigitShw3, &b_s_ndigitShw3);
   fChain->SetBranchAddress("nstripShw3", &nstripShw3, &b_s_nstripShw3);
   fChain->SetBranchAddress("nplaneShw3", &nplaneShw3, &b_s_nplaneShw3);
   fChain->SetBranchAddress("shwEnCor3", &shwEnCor3, &b_s_shwEnCor3);
   fChain->SetBranchAddress("shwEnNoCor3", &shwEnNoCor3, &b_s_shwEnNoCor3);
   fChain->SetBranchAddress("shwEnLinCCNoCor3", &shwEnLinCCNoCor3, &b_s_shwEnLinCCNoCor3);
   fChain->SetBranchAddress("shwEnLinCCCor3", &shwEnLinCCCor3, &b_s_shwEnLinCCCor3);
   fChain->SetBranchAddress("shwEnWtCCNoCor3", &shwEnWtCCNoCor3, &b_s_shwEnWtCCNoCor3);
   fChain->SetBranchAddress("shwEnWtCCCor3", &shwEnWtCCCor3, &b_s_shwEnWtCCCor3);
   fChain->SetBranchAddress("shwEnLinNCNoCor3", &shwEnLinNCNoCor3, &b_s_shwEnLinNCNoCor3);
   fChain->SetBranchAddress("shwEnLinNCCor3", &shwEnLinNCCor3, &b_s_shwEnLinNCCor3);
   fChain->SetBranchAddress("shwEnWtNCNoCor3", &shwEnWtNCNoCor3, &b_s_shwEnWtNCNoCor3);
   fChain->SetBranchAddress("shwEnWtNCCor3", &shwEnWtNCCor3, &b_s_shwEnWtNCCor3);
   fChain->SetBranchAddress("shwEnMip3", &shwEnMip3, &b_s_shwEnMip3);
   fChain->SetBranchAddress("planeShwBeg3", &planeShwBeg3, &b_s_planeShwBeg3);
   fChain->SetBranchAddress("planeShwEnd3", &planeShwEnd3, &b_s_planeShwEnd3);
   fChain->SetBranchAddress("planeShwMax3", &planeShwMax3, &b_s_planeShwMax3);
   fChain->SetBranchAddress("xShwVtx3", &xShwVtx3, &b_s_xShwVtx3);
   fChain->SetBranchAddress("yShwVtx3", &yShwVtx3, &b_s_yShwVtx3);
   fChain->SetBranchAddress("zShwVtx3", &zShwVtx3, &b_s_zShwVtx3);
   fChain->SetBranchAddress("shwExists4", &shwExists4, &b_s_shwExists4);
   fChain->SetBranchAddress("ndigitShw4", &ndigitShw4, &b_s_ndigitShw4);
   fChain->SetBranchAddress("nstripShw4", &nstripShw4, &b_s_nstripShw4);
   fChain->SetBranchAddress("nplaneShw4", &nplaneShw4, &b_s_nplaneShw4);
   fChain->SetBranchAddress("shwEnCor4", &shwEnCor4, &b_s_shwEnCor4);
   fChain->SetBranchAddress("shwEnNoCor4", &shwEnNoCor4, &b_s_shwEnNoCor4);
   fChain->SetBranchAddress("shwEnLinCCNoCor4", &shwEnLinCCNoCor4, &b_s_shwEnLinCCNoCor4);
   fChain->SetBranchAddress("shwEnLinCCCor4", &shwEnLinCCCor4, &b_s_shwEnLinCCCor4);
   fChain->SetBranchAddress("shwEnWtCCNoCor4", &shwEnWtCCNoCor4, &b_s_shwEnWtCCNoCor4);
   fChain->SetBranchAddress("shwEnWtCCCor4", &shwEnWtCCCor4, &b_s_shwEnWtCCCor4);
   fChain->SetBranchAddress("shwEnLinNCNoCor4", &shwEnLinNCNoCor4, &b_s_shwEnLinNCNoCor4);
   fChain->SetBranchAddress("shwEnLinNCCor4", &shwEnLinNCCor4, &b_s_shwEnLinNCCor4);
   fChain->SetBranchAddress("shwEnWtNCNoCor4", &shwEnWtNCNoCor4, &b_s_shwEnWtNCNoCor4);
   fChain->SetBranchAddress("shwEnWtNCCor4", &shwEnWtNCCor4, &b_s_shwEnWtNCCor4);
   fChain->SetBranchAddress("shwEnMip4", &shwEnMip4, &b_s_shwEnMip4);
   fChain->SetBranchAddress("planeShwBeg4", &planeShwBeg4, &b_s_planeShwBeg4);
   fChain->SetBranchAddress("planeShwEnd4", &planeShwEnd4, &b_s_planeShwEnd4);
   fChain->SetBranchAddress("planeShwMax4", &planeShwMax4, &b_s_planeShwMax4);
   fChain->SetBranchAddress("xShwVtx4", &xShwVtx4, &b_s_xShwVtx4);
   fChain->SetBranchAddress("yShwVtx4", &yShwVtx4, &b_s_yShwVtx4);
   fChain->SetBranchAddress("zShwVtx4", &zShwVtx4, &b_s_zShwVtx4);
   fChain->SetBranchAddress("shwExists5", &shwExists5, &b_s_shwExists5);
   fChain->SetBranchAddress("ndigitShw5", &ndigitShw5, &b_s_ndigitShw5);
   fChain->SetBranchAddress("nstripShw5", &nstripShw5, &b_s_nstripShw5);
   fChain->SetBranchAddress("nplaneShw5", &nplaneShw5, &b_s_nplaneShw5);
   fChain->SetBranchAddress("shwEnCor5", &shwEnCor5, &b_s_shwEnCor5);
   fChain->SetBranchAddress("shwEnNoCor5", &shwEnNoCor5, &b_s_shwEnNoCor5);
   fChain->SetBranchAddress("shwEnLinCCNoCor5", &shwEnLinCCNoCor5, &b_s_shwEnLinCCNoCor5);
   fChain->SetBranchAddress("shwEnLinCCCor5", &shwEnLinCCCor5, &b_s_shwEnLinCCCor5);
   fChain->SetBranchAddress("shwEnWtCCNoCor5", &shwEnWtCCNoCor5, &b_s_shwEnWtCCNoCor5);
   fChain->SetBranchAddress("shwEnWtCCCor5", &shwEnWtCCCor5, &b_s_shwEnWtCCCor5);
   fChain->SetBranchAddress("shwEnLinNCNoCor5", &shwEnLinNCNoCor5, &b_s_shwEnLinNCNoCor5);
   fChain->SetBranchAddress("shwEnLinNCCor5", &shwEnLinNCCor5, &b_s_shwEnLinNCCor5);
   fChain->SetBranchAddress("shwEnWtNCNoCor5", &shwEnWtNCNoCor5, &b_s_shwEnWtNCNoCor5);
   fChain->SetBranchAddress("shwEnWtNCCor5", &shwEnWtNCCor5, &b_s_shwEnWtNCCor5);
   fChain->SetBranchAddress("shwEnMip5", &shwEnMip5, &b_s_shwEnMip5);
   fChain->SetBranchAddress("planeShwBeg5", &planeShwBeg5, &b_s_planeShwBeg5);
   fChain->SetBranchAddress("planeShwEnd5", &planeShwEnd5, &b_s_planeShwEnd5);
   fChain->SetBranchAddress("planeShwMax5", &planeShwMax5, &b_s_planeShwMax5);
   fChain->SetBranchAddress("xShwVtx5", &xShwVtx5, &b_s_xShwVtx5);
   fChain->SetBranchAddress("yShwVtx5", &yShwVtx5, &b_s_yShwVtx5);
   fChain->SetBranchAddress("zShwVtx5", &zShwVtx5, &b_s_zShwVtx5);
   fChain->SetBranchAddress("rEvtVtx", &rEvtVtx, &b_s_rEvtVtx);
   fChain->SetBranchAddress("rEvtEnd", &rEvtEnd, &b_s_rEvtEnd);
   fChain->SetBranchAddress("distToEdgeEvtVtx", &distToEdgeEvtVtx, &b_s_distToEdgeEvtVtx);
   fChain->SetBranchAddress("evtVtxUVDiffPl", &evtVtxUVDiffPl, &b_s_evtVtxUVDiffPl);
   fChain->SetBranchAddress("rTrkVtx", &rTrkVtx, &b_s_rTrkVtx);
   fChain->SetBranchAddress("rTrkEnd", &rTrkEnd, &b_s_rTrkEnd);
   fChain->SetBranchAddress("sigqp_qp", &sigqp_qp, &b_s_sigqp_qp);
   fChain->SetBranchAddress("chi2PerNdof", &chi2PerNdof, &b_s_chi2PerNdof);
   fChain->SetBranchAddress("prob", &prob, &b_s_prob);
   fChain->SetBranchAddress("containmentFlag", &containmentFlag, &b_s_containmentFlag);
   fChain->SetBranchAddress("containmentFlagCC0093Std", &containmentFlagCC0093Std, &b_s_containmentFlagCC0093Std);
   fChain->SetBranchAddress("containmentFlagCC0250Std", &containmentFlagCC0250Std, &b_s_containmentFlagCC0250Std);
   fChain->SetBranchAddress("containmentFlagPitt", &containmentFlagPitt, &b_s_containmentFlagPitt);
   fChain->SetBranchAddress("usedRange", &usedRange, &b_s_usedRange);
   fChain->SetBranchAddress("usedCurv", &usedCurv, &b_s_usedCurv);
   fChain->SetBranchAddress("rw", &rw, &b_s_rw);
   fChain->SetBranchAddress("fluxErr", &fluxErr, &b_s_fluxErr);
   fChain->SetBranchAddress("rwActual", &rwActual, &b_s_rwActual);
   fChain->SetBranchAddress("generatorWeight", &generatorWeight, &b_s_generatorWeight);
   fChain->SetBranchAddress("detectorWeight", &detectorWeight, &b_s_detectorWeight);
   fChain->SetBranchAddress("trkEnWeight", &trkEnWeight, &b_s_trkEnWeight);
   fChain->SetBranchAddress("shwEnWeight", &shwEnWeight, &b_s_shwEnWeight);
   fChain->SetBranchAddress("beamWeight", &beamWeight, &b_s_beamWeight);
   fChain->SetBranchAddress("fluxErrHadProdAfterTune", &fluxErrHadProdAfterTune, &b_s_fluxErrHadProdAfterTune);
   fChain->SetBranchAddress("fluxErrTotalErrorPreTune", &fluxErrTotalErrorPreTune, &b_s_fluxErrTotalErrorPreTune);
   fChain->SetBranchAddress("fluxErrTotalErrorAfterTune", &fluxErrTotalErrorAfterTune, &b_s_fluxErrTotalErrorAfterTune);
   fChain->SetBranchAddress("detectorWeightNMB", &detectorWeightNMB, &b_s_detectorWeightNMB);
   fChain->SetBranchAddress("detectorWeightNM", &detectorWeightNM, &b_s_detectorWeightNM);
   //   fChain->SetBranchAddress("trkEnWeightRunI", &trkEnWeightRunI, &b_s_trkEnWeightRunI);
   //   fCahain->SetBranchAddress("shwEnWeightRunI", &shwEnWeightRunI, &b_s_shwEnWeightRunI);
   //   fChain->SetBranchAddress("beamWeightRunI", &beamWeightRunI, &b_s_beamWeightRunI);
   //   fChain->SetBranchAddress("fluxErrHadProdAfterTuneRunI", &fluxErrHadProdAfterTuneRunI, &b_s_fluxErrHadProdAfterTuneRunI);
   //   fChain->SetBranchAddress("fluxErrTotalErrorPreTuneRunI", &fluxErrTotalErrorPreTuneRunI, &b_s_fluxErrTotalErrorPreTuneRunI);
   //   fChain->SetBranchAddress("fluxErrTotalErrorAfterTuneRunI", &fluxErrTotalErrorAfterTuneRunI, &b_s_fluxErrTotalErrorAfterTuneRunI);
   //   fChain->SetBranchAddress("detectorWeightNMBRunI", &detectorWeightNMBRunI, &b_s_detectorWeightNMBRunI);
   //   fChain->SetBranchAddress("detectorWeightNMRunI", &detectorWeightNMRunI, &b_s_detectorWeightNMRunI);
   //   fChain->SetBranchAddress("trkEnWeightRunII", &trkEnWeightRunII, &b_s_trkEnWeightRunII);
   //   fChain->SetBranchAddress("shwEnWeightRunII", &shwEnWeightRunII, &b_s_shwEnWeightRunII);
   //   fChain->SetBranchAddress("beamWeightRunII", &beamWeightRunII, &b_s_beamWeightRunII);
   //   fChain->SetBranchAddress("fluxErrHadProdAfterTuneRunII", &fluxErrHadProdAfterTuneRunII, &b_s_fluxErrHadProdAfterTuneRunII);
   //   fChain->SetBranchAddress("fluxErrTotalErrorPreTuneRunII", &fluxErrTotalErrorPreTuneRunII, &b_s_fluxErrTotalErrorPreTuneRunII);
   //   fChain->SetBranchAddress("fluxErrTotalErrorAfterTuneRunII", &fluxErrTotalErrorAfterTuneRunII, &b_s_fluxErrTotalErrorAfterTuneRunII);
   //   fChain->SetBranchAddress("detectorWeightNMBRunII", &detectorWeightNMBRunII, &b_s_detectorWeightNMBRunII);
   //   fChain->SetBranchAddress("detectorWeightNMRunII", &detectorWeightNMRunII, &b_s_detectorWeightNMRunII);
   fChain->SetBranchAddress("energyRw", &energyRw, &b_s_energyRw);
   fChain->SetBranchAddress("energyNoRw", &energyNoRw, &b_s_energyNoRw);
   fChain->SetBranchAddress("trkEnRw", &trkEnRw, &b_s_trkEnRw);
   fChain->SetBranchAddress("trkEnNoRw", &trkEnNoRw, &b_s_trkEnNoRw);
   fChain->SetBranchAddress("shwEnRw", &shwEnRw, &b_s_shwEnRw);
   fChain->SetBranchAddress("shwEnNoRw", &shwEnNoRw, &b_s_shwEnNoRw);
   fChain->SetBranchAddress("dpID", &dpID, &b_s_dpID);
   fChain->SetBranchAddress("abID", &abID, &b_s_abID);
   fChain->SetBranchAddress("roID", &roID, &b_s_roID);
   fChain->SetBranchAddress("knn01TrkActivePlanes", &knn01TrkActivePlanes, &b_s_knn01TrkActivePlanes);
   fChain->SetBranchAddress("knn10TrkMeanPh", &knn10TrkMeanPh, &b_s_knn10TrkMeanPh);
   fChain->SetBranchAddress("knn20LowHighPh", &knn20LowHighPh, &b_s_knn20LowHighPh);
   fChain->SetBranchAddress("knn40TrkPhFrac", &knn40TrkPhFrac, &b_s_knn40TrkPhFrac);
   fChain->SetBranchAddress("roIDNuMuBar", &roIDNuMuBar, &b_s_roIDNuMuBar);
   fChain->SetBranchAddress("relativeAngle", &relativeAngle, &b_s_relativeAngle);
   fChain->SetBranchAddress("poID", &poID, &b_s_poID);
   fChain->SetBranchAddress("poIDKin", &poIDKin, &b_s_poIDKin);
   fChain->SetBranchAddress("jmID", &jmID, &b_s_jmID);
   fChain->SetBranchAddress("jmTrackPlane", &jmTrackPlane, &b_s_jmTrackPlane);
   fChain->SetBranchAddress("jmEndPh", &jmEndPh, &b_s_jmEndPh);
   fChain->SetBranchAddress("jmMeanPh", &jmMeanPh, &b_s_jmMeanPh);
   fChain->SetBranchAddress("jmScatteringU", &jmScatteringU, &b_s_jmScatteringU);
   fChain->SetBranchAddress("jmScatteringV", &jmScatteringV, &b_s_jmScatteringV);
   fChain->SetBranchAddress("jmScatteringUV", &jmScatteringUV, &b_s_jmScatteringUV);
   fChain->SetBranchAddress("jmEventknnID", &jmEventknnID, &b_s_jmEventknnID);
   fChain->SetBranchAddress("jmEventknn208", &jmEventknn208, &b_s_jmEventknn208);
   fChain->SetBranchAddress("jmEventknn207", &jmEventknn207, &b_s_jmEventknn207);
   fChain->SetBranchAddress("jmEventknn206", &jmEventknn206, &b_s_jmEventknn206);
   fChain->SetBranchAddress("jmEventknn205", &jmEventknn205, &b_s_jmEventknn205);
   fChain->SetBranchAddress("jmEventknn204", &jmEventknn204, &b_s_jmEventknn204);
   fChain->SetBranchAddress("closeTimeDeltaZ", &closeTimeDeltaZ, &b_s_closeTimeDeltaZ);
   fChain->SetBranchAddress("edgeActivityStrips", &edgeActivityStrips, &b_s_edgeActivityStrips);
   fChain->SetBranchAddress("edgeActivityPH", &edgeActivityPH, &b_s_edgeActivityPH);
   fChain->SetBranchAddress("oppEdgeStrips", &oppEdgeStrips, &b_s_oppEdgeStrips);
   fChain->SetBranchAddress("oppEdgePH", &oppEdgePH, &b_s_oppEdgePH);
   fChain->SetBranchAddress("vtxMetersToCoilEvt", &vtxMetersToCoilEvt, &b_s_vtxMetersToCoilEvt);
   fChain->SetBranchAddress("vtxMetersToCloseEdgeEvt", &vtxMetersToCloseEdgeEvt, &b_s_vtxMetersToCloseEdgeEvt);
   fChain->SetBranchAddress("minTimeSeparation", &minTimeSeparation, &b_s_minTimeSeparation);
   fChain->SetBranchAddress("transverseRMSU", &transverseRMSU, &b_s_transverseRMSU);
   fChain->SetBranchAddress("transverseRMSV", &transverseRMSV, &b_s_transverseRMSV);
   fChain->SetBranchAddress("dtdz", &dtdz, &b_s_dtdz);
   fChain->SetBranchAddress("endMetersToCloseEdge", &endMetersToCloseEdge, &b_s_endMetersToCloseEdge);
   fChain->SetBranchAddress("vtxMetersToCloseEdgeTrk", &vtxMetersToCloseEdgeTrk, &b_s_vtxMetersToCloseEdgeTrk);
   fChain->SetBranchAddress("vtxMetersToCoilTrk", &vtxMetersToCoilTrk, &b_s_vtxMetersToCoilTrk);
   fChain->SetBranchAddress("traceEndZ", &traceEndZ, &b_s_traceEndZ);
   fChain->SetBranchAddress("pot", &pot, &b_s_pot);
   fChain->SetBranchAddress("potDB", &potDB, &b_s_potDB);
   fChain->SetBranchAddress("potSinceLastEvt", &potSinceLastEvt, &b_s_potSinceLastEvt);
   fChain->SetBranchAddress("potSinceLastEvtGood", &potSinceLastEvtGood, &b_s_potSinceLastEvtGood);
   fChain->SetBranchAddress("potSinceLastEvtBad", &potSinceLastEvtBad, &b_s_potSinceLastEvtBad);
   fChain->SetBranchAddress("potSinceLastEvtDB", &potSinceLastEvtDB, &b_s_potSinceLastEvtDB);
   fChain->SetBranchAddress("potSinceLastEvtGoodDB", &potSinceLastEvtGoodDB, &b_s_potSinceLastEvtGoodDB);
   fChain->SetBranchAddress("potSinceLastEvtBadDB", &potSinceLastEvtBadDB, &b_s_potSinceLastEvtBadDB);
   fChain->SetBranchAddress("runPeriod", &runPeriod, &b_s_runPeriod);
   fChain->SetBranchAddress("hornIsReverse", &hornIsReverse, &b_s_hornIsReverse);
   fChain->SetBranchAddress("beamTypeDB", &beamTypeDB, &b_s_beamTypeDB);
   fChain->SetBranchAddress("beamType", &beamType, &b_s_beamType);
   fChain->SetBranchAddress("intensity", &intensity, &b_s_intensity);
   fChain->SetBranchAddress("hornCur", &hornCur, &b_s_hornCur);
   fChain->SetBranchAddress("goodBeam", &goodBeam, &b_s_goodBeam);
   fChain->SetBranchAddress("goodBeamSntp", &goodBeamSntp, &b_s_goodBeamSntp);
   fChain->SetBranchAddress("isInFidVolCCMC", &isInFidVolCCMC, &b_s_isInFidVolCCMC);
   fChain->SetBranchAddress("energyMC", &energyMC, &b_s_energyMC);
   fChain->SetBranchAddress("neuEnMC", &neuEnMC, &b_s_neuEnMC);
   fChain->SetBranchAddress("neuPxMC", &neuPxMC, &b_s_neuPxMC);
   fChain->SetBranchAddress("neuPyMC", &neuPyMC, &b_s_neuPyMC);
   fChain->SetBranchAddress("neuPzMC", &neuPzMC, &b_s_neuPzMC);
   fChain->SetBranchAddress("mu1EnMC", &mu1EnMC, &b_s_mu1EnMC);
   fChain->SetBranchAddress("mu1PxMC", &mu1PxMC, &b_s_mu1PxMC);
   fChain->SetBranchAddress("mu1PyMC", &mu1PyMC, &b_s_mu1PyMC);
   fChain->SetBranchAddress("mu1PzMC", &mu1PzMC, &b_s_mu1PzMC);
   fChain->SetBranchAddress("tgtEnMC", &tgtEnMC, &b_s_tgtEnMC);
   fChain->SetBranchAddress("tgtPxMC", &tgtPxMC, &b_s_tgtPxMC);
   fChain->SetBranchAddress("tgtPyMC", &tgtPyMC, &b_s_tgtPyMC);
   fChain->SetBranchAddress("tgtPzMC", &tgtPzMC, &b_s_tgtPzMC);
   fChain->SetBranchAddress("zMC", &zMC, &b_s_zMC);
   fChain->SetBranchAddress("aMC", &aMC, &b_s_aMC);
   fChain->SetBranchAddress("nucleusMC", &nucleusMC, &b_s_nucleusMC);
   fChain->SetBranchAddress("initialStateMC", &initialStateMC, &b_s_initialStateMC);
   fChain->SetBranchAddress("hadronicFinalStateMC", &hadronicFinalStateMC, &b_s_hadronicFinalStateMC);
   fChain->SetBranchAddress("numPreInukeFSprotMC", &numPreInukeFSprotMC, &b_s_numPreInukeFSprotMC);
   fChain->SetBranchAddress("numPreInukeFSneutMC", &numPreInukeFSneutMC, &b_s_numPreInukeFSneutMC);
   fChain->SetBranchAddress("maxMomPreInukeFSprotMC", &maxMomPreInukeFSprotMC, &b_s_maxMomPreInukeFSprotMC);
   fChain->SetBranchAddress("maxMomPreInukeFSneutMC", &maxMomPreInukeFSneutMC, &b_s_maxMomPreInukeFSneutMC);
   fChain->SetBranchAddress("yMC", &yMC, &b_s_yMC);
   fChain->SetBranchAddress("y2MC", &y2MC, &b_s_y2MC);
   fChain->SetBranchAddress("xMC", &xMC, &b_s_xMC);
   fChain->SetBranchAddress("q2MC", &q2MC, &b_s_q2MC);
   fChain->SetBranchAddress("w2MC", &w2MC, &b_s_w2MC);
   fChain->SetBranchAddress("trkEnMC", &trkEnMC, &b_s_trkEnMC);
   fChain->SetBranchAddress("trkEn2MC", &trkEn2MC, &b_s_trkEn2MC);
   fChain->SetBranchAddress("shwEnMC", &shwEnMC, &b_s_shwEnMC);
   fChain->SetBranchAddress("shwEn2MC", &shwEn2MC, &b_s_shwEn2MC);
   fChain->SetBranchAddress("trkEndEnMC", &trkEndEnMC, &b_s_trkEndEnMC);
   fChain->SetBranchAddress("trkStartEnMC", &trkStartEnMC, &b_s_trkStartEnMC);
   fChain->SetBranchAddress("trkContainmentMC", &trkContainmentMC, &b_s_trkContainmentMC);
   fChain->SetBranchAddress("sigma", &sigma, &b_s_sigma);
   fChain->SetBranchAddress("iaction", &iaction, &b_s_iaction);
   fChain->SetBranchAddress("iresonance", &iresonance, &b_s_iresonance);
   fChain->SetBranchAddress("inu", &inu, &b_s_inu);
   fChain->SetBranchAddress("inunoosc", &inunoosc, &b_s_inunoosc);
   fChain->SetBranchAddress("itg", &itg, &b_s_itg);
   fChain->SetBranchAddress("vtxxMC", &vtxxMC, &b_s_vtxxMC);
   fChain->SetBranchAddress("vtxyMC", &vtxyMC, &b_s_vtxyMC);
   fChain->SetBranchAddress("vtxzMC", &vtxzMC, &b_s_vtxzMC);
   fChain->SetBranchAddress("vtxuMC", &vtxuMC, &b_s_vtxuMC);
   fChain->SetBranchAddress("vtxvMC", &vtxvMC, &b_s_vtxvMC);
   fChain->SetBranchAddress("planeTrkVtxMC", &planeTrkVtxMC, &b_s_planeTrkVtxMC);
   fChain->SetBranchAddress("rTrkVtxMC", &rTrkVtxMC, &b_s_rTrkVtxMC);
   fChain->SetBranchAddress("mc", &mc, &b_s_mc);
   fChain->SetBranchAddress("mcTrk", &mcTrk, &b_s_mcTrk);
   fChain->SetBranchAddress("mcShw", &mcShw, &b_s_mcShw);
   fChain->SetBranchAddress("mcEvt", &mcEvt, &b_s_mcEvt);
   fChain->SetBranchAddress("mcTrk1", &mcTrk1, &b_s_mcTrk1);
   fChain->SetBranchAddress("mcTrk2", &mcTrk2, &b_s_mcTrk2);
   fChain->SetBranchAddress("mcTrk3", &mcTrk3, &b_s_mcTrk3);
   fChain->SetBranchAddress("mcShw1", &mcShw1, &b_s_mcShw1);
   fChain->SetBranchAddress("mcShw2", &mcShw2, &b_s_mcShw2);
   fChain->SetBranchAddress("mcShw3", &mcShw3, &b_s_mcShw3);
   fChain->SetBranchAddress("mcShw4", &mcShw4, &b_s_mcShw4);
   fChain->SetBranchAddress("mcShw5", &mcShw5, &b_s_mcShw5);
   fChain->SetBranchAddress("Npz", &Npz, &b_s_Npz);
   fChain->SetBranchAddress("NdxdzNea", &NdxdzNea, &b_s_NdxdzNea);
   fChain->SetBranchAddress("NdydzNea", &NdydzNea, &b_s_NdydzNea);
   fChain->SetBranchAddress("NenergyN", &NenergyN, &b_s_NenergyN);
   fChain->SetBranchAddress("NWtNear", &NWtNear, &b_s_NWtNear);
   fChain->SetBranchAddress("NdxdzFar", &NdxdzFar, &b_s_NdxdzFar);
   fChain->SetBranchAddress("NdydzFar", &NdydzFar, &b_s_NdydzFar);
   fChain->SetBranchAddress("NenergyF", &NenergyF, &b_s_NenergyF);
   fChain->SetBranchAddress("NWtFar", &NWtFar, &b_s_NWtFar);
   fChain->SetBranchAddress("Ndecay", &Ndecay, &b_s_Ndecay);
   fChain->SetBranchAddress("Vx", &Vx, &b_s_Vx);
   fChain->SetBranchAddress("Vy", &Vy, &b_s_Vy);
   fChain->SetBranchAddress("Vz", &Vz, &b_s_Vz);
   fChain->SetBranchAddress("pdPx", &pdPx, &b_s_pdPx);
   fChain->SetBranchAddress("pdPy", &pdPy, &b_s_pdPy);
   fChain->SetBranchAddress("pdPz", &pdPz, &b_s_pdPz);
   fChain->SetBranchAddress("ppdxdz", &ppdxdz, &b_s_ppdxdz);
   fChain->SetBranchAddress("ppdydz", &ppdydz, &b_s_ppdydz);
   fChain->SetBranchAddress("pppz", &pppz, &b_s_pppz);
   fChain->SetBranchAddress("ppenergy", &ppenergy, &b_s_ppenergy);
   fChain->SetBranchAddress("ppmedium", &ppmedium, &b_s_ppmedium);
   fChain->SetBranchAddress("ppvx", &ppvx, &b_s_ppvx);
   fChain->SetBranchAddress("ppvy", &ppvy, &b_s_ppvy);
   fChain->SetBranchAddress("ppvz", &ppvz, &b_s_ppvz);
   fChain->SetBranchAddress("ptype", &ptype, &b_s_ptype);
   fChain->SetBranchAddress("Necm", &Necm, &b_s_Necm);
   fChain->SetBranchAddress("Nimpwt", &Nimpwt, &b_s_Nimpwt);
   fChain->SetBranchAddress("tvx", &tvx, &b_s_tvx);
   fChain->SetBranchAddress("tvy", &tvy, &b_s_tvy);
   fChain->SetBranchAddress("tvz", &tvz, &b_s_tvz);
   fChain->SetBranchAddress("tpx", &tpx, &b_s_tpx);
   fChain->SetBranchAddress("tpy", &tpy, &b_s_tpy);
   fChain->SetBranchAddress("tpz", &tpz, &b_s_tpz);
   fChain->SetBranchAddress("tptype", &tptype, &b_s_tptype);
   fChain->SetBranchAddress("tgen", &tgen, &b_s_tgen);
   fChain->SetBranchAddress("InukeNwts", &InukeNwts, &b_s_InukeNwts);
   fChain->SetBranchAddress("InukePiCExchgP", &InukePiCExchgP, &b_s_InukePiCExchgP);
   fChain->SetBranchAddress("InukePiCExchgN", &InukePiCExchgN, &b_s_InukePiCExchgN);
   fChain->SetBranchAddress("InukePiEScatP", &InukePiEScatP, &b_s_InukePiEScatP);
   fChain->SetBranchAddress("InukePiEScatN", &InukePiEScatN, &b_s_InukePiEScatN);
   fChain->SetBranchAddress("InukePiInEScatP", &InukePiInEScatP, &b_s_InukePiInEScatP);
   fChain->SetBranchAddress("InukePiInEScatN", &InukePiInEScatN, &b_s_InukePiInEScatN);
   fChain->SetBranchAddress("InukePiAbsorbP", &InukePiAbsorbP, &b_s_InukePiAbsorbP);
   fChain->SetBranchAddress("InukePiAbsorbN", &InukePiAbsorbN, &b_s_InukePiAbsorbN);
   fChain->SetBranchAddress("InukePi2PiP", &InukePi2PiP, &b_s_InukePi2PiP);
   fChain->SetBranchAddress("InukePi2PiN", &InukePi2PiN, &b_s_InukePi2PiN);
   fChain->SetBranchAddress("InukeNknockP", &InukeNknockP, &b_s_InukeNknockP);
   fChain->SetBranchAddress("InukeNknockN", &InukeNknockN, &b_s_InukeNknockN);
   fChain->SetBranchAddress("InukeNNPiP", &InukeNNPiP, &b_s_InukeNNPiP);
   fChain->SetBranchAddress("InukeNNPiN", &InukeNNPiN, &b_s_InukeNNPiN);
   fChain->SetBranchAddress("InukeFormTP", &InukeFormTP, &b_s_InukeFormTP);
   fChain->SetBranchAddress("InukeFormTN", &InukeFormTN, &b_s_InukeFormTN);
   fChain->SetBranchAddress("InukePiXsecP", &InukePiXsecP, &b_s_InukePiXsecP);
   fChain->SetBranchAddress("InukePiXsecN", &InukePiXsecN, &b_s_InukePiXsecN);
   fChain->SetBranchAddress("InukeNXsecP", &InukeNXsecP, &b_s_InukeNXsecP);
   fChain->SetBranchAddress("InukeNXsecN", &InukeNXsecN, &b_s_InukeNXsecN);
   fChain->SetBranchAddress("InukeNucrad", &InukeNucrad, &b_s_InukeNucrad);
   fChain->SetBranchAddress("InukeWrad", &InukeWrad, &b_s_InukeWrad);
   fChain->SetBranchAddress("anaVersion", &anaVersion, &b_s_anaVersion);
   fChain->SetBranchAddress("releaseType", &releaseType, &b_s_releaseType);
   fChain->SetBranchAddress("recoVersion", &recoVersion, &b_s_recoVersion);
   fChain->SetBranchAddress("mcVersion", &mcVersion, &b_s_mcVersion);
   fChain->SetBranchAddress("reweightVersion", &reweightVersion, &b_s_reweightVersion);
   fChain->SetBranchAddress("useGeneratorReweight", &useGeneratorReweight, &b_s_useGeneratorReweight);
   fChain->SetBranchAddress("sGeneratorConfigName", &sGeneratorConfigName, &b_s_sGeneratorConfigName);
   fChain->SetBranchAddress("generatorConfigNo", &generatorConfigNo, &b_s_generatorConfigNo);
   fChain->SetBranchAddress("useDBForDataQuality", &useDBForDataQuality, &b_s_useDBForDataQuality);
   fChain->SetBranchAddress("useDBForSpillTiming", &useDBForSpillTiming, &b_s_useDBForSpillTiming);
   fChain->SetBranchAddress("useDBForBeamInfo", &useDBForBeamInfo, &b_s_useDBForBeamInfo);
   fChain->SetBranchAddress("cutOnDataQuality", &cutOnDataQuality, &b_s_cutOnDataQuality);
   fChain->SetBranchAddress("cutOnSpillTiming", &cutOnSpillTiming, &b_s_cutOnSpillTiming);
   fChain->SetBranchAddress("cutOnBeamInfo", &cutOnBeamInfo, &b_s_cutOnBeamInfo);
   fChain->SetBranchAddress("applyEnergyShifts", &applyEnergyShifts, &b_s_applyEnergyShifts);
   fChain->SetBranchAddress("applyBeamWeight", &applyBeamWeight, &b_s_applyBeamWeight);
   fChain->SetBranchAddress("apply1SigmaWeight", &apply1SigmaWeight, &b_s_apply1SigmaWeight);
   fChain->SetBranchAddress("applyDetectorWeight", &applyDetectorWeight, &b_s_applyDetectorWeight);
   fChain->SetBranchAddress("applyGeneratorWeight", &applyGeneratorWeight, &b_s_applyGeneratorWeight);
   fChain->SetBranchAddress("calcMajCurv", &calcMajCurv, &b_s_calcMajCurv);
   fChain->SetBranchAddress("calcRoID", &calcRoID, &b_s_calcRoID);
   fChain->SetBranchAddress("calcJmID", &calcJmID, &b_s_calcJmID);
   Notify();
}

Bool_t NuDstLooper::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void NuDstLooper::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t NuDstLooper::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef NuDstLooper_cxx
