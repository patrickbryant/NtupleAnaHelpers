#ifndef NTUPLEANAHELPERS_MUONDATA_H
#define NTUPLEANAHELPERS_MUONDATA_H

#include "TLorentzVector.h"

//
// Muon Data
//
class muonData{
  
 public:
  
  float pt;
  float eta;
  float phi;
  float M;
  int   IsMedium;
  int   IsTight;
  float ptcone20;

  muonData(float m_pt, float m_eta, float m_phi, float m_M){ 

    pt     = m_pt;
    eta    = m_eta;
    phi    = m_phi;
    M      = m_M;

    // Set directly out side of constructor
    IsMedium          = -99;
    IsTight           = -99;
    ptcone20          = -99;
      
  }

  TLorentzVector vec() const{
    TLorentzVector vec = TLorentzVector();
    vec.SetPtEtaPhiM(pt,eta,phi,M);
    return vec;
  }

};

#endif
