#ifndef NTUPLEANAHELPERS_JETDATA_H
#define NTUPLEANAHELPERS_JETDATA_H

#include "TLorentzVector.h"

//
// Jet Data
//
class jetData{

 public:

  float pt;
  float eta;
  float phi;
  float M;
  float MV2c20;
  float Jvt;
  int   clean_passLooseBad;
  float Timing;
  float MuonSegmentCount; 

 public:

  jetData(float m_pt, float m_eta, float m_phi, float m_M, float m_MV2c20){ 
    pt     = m_pt;
    eta    = m_eta;
    phi    = m_phi;
    M      = m_M;
    MV2c20 = m_MV2c20;

    // Set directly out side of constructor
    Jvt                = -99;
    clean_passLooseBad = -99;
    Timing             = -99;
    MuonSegmentCount   = -99;
  };

  TLorentzVector vec() const{
    TLorentzVector vec = TLorentzVector();
    vec.SetPtEtaPhiM(pt,eta,phi,M);
    return vec;
  }

};

#endif
