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
  float EnergyLoss;

  muonData(float m_pt, float m_eta, float m_phi, float m_M){ 

    pt     = m_pt;
    eta    = m_eta;
    phi    = m_phi;
    M      = m_M;

    // Set directly out side of constructor
    IsMedium          = -99;
    IsTight           = -99;
    ptcone20          = -99;
    EnergyLoss        = 0;
  }

  TLorentzVector vec() const{
    TLorentzVector vec = TLorentzVector();
    vec.SetPtEtaPhiM(pt,eta,phi,M);
    return vec;
  }


  TLorentzVector vec_eLoss() const{

    float theta_muon = vec().Theta();
    float elossX     = EnergyLoss * sin(theta_muon) * cos(phi);
    float elossY     = EnergyLoss * sin(theta_muon) * sin(phi);
    float elossZ     = EnergyLoss * cos(theta_muon);

    TLorentzVector muonELoss(elossX,elossY,elossZ,EnergyLoss);

    return muonELoss;
  }


};

#endif
