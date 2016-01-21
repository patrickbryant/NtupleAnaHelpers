#ifndef NTUPLEANAHELPERS_JETDATA_H
#define NTUPLEANAHELPERS_JETDATA_H

#include "TLorentzVector.h"
#include <NtupleAnaHelpers/muonData.h>
#include <vector>

//
// Jet Data
//
class jetData{

 public:

  float pt;
  float eta;
  float phi;
  float E;
  float MV2c20;
  float Jvt;
  int   clean_passLooseBad;
  float Timing;
  float MuonSegmentCount; 
  const muonData* matchedMuon;
  bool  isTagged;
 
 public:

  jetData(float m_pt, float m_eta, float m_phi, float m_E, float m_MV2c20){ 
    pt     = m_pt;
    eta    = m_eta;
    phi    = m_phi;
    E      = m_E;
    MV2c20 = m_MV2c20;

    // Set directly out side of constructor
    Jvt                = -99;
    clean_passLooseBad = -99;
    Timing             = -99;
    MuonSegmentCount   = -99;
    matchedMuon        = 0;
    isTagged           = false;
  };

  TLorentzVector vec() const{
    TLorentzVector vec = TLorentzVector();
    vec.SetPtEtaPhiE(pt,eta,phi,E);
    return vec;
  }

  void muonInJetCorrection(const std::vector<muonData>& muons){

    TLorentzVector jetVec = vec();
    float minDr           = 0.5;
    const muonData* minDr_muon  = 0;

    for(const muonData& muon : muons){
      TLorentzVector muonVec = muon.vec();
      
      if(muonVec.Pt()  < 4)               continue;
      if(!muon.IsMedium && !muon.IsTight) continue;

      float thisDr = jetVec.DeltaR(muonVec);
      if(thisDr < minDr){
	minDr      = thisDr;
	minDr_muon = &muon;
      }

    }

    if(minDr < 0.4){
      matchedMuon = minDr_muon;

      TLorentzVector matchedMuonVec = minDr_muon->vec();
      TLorentzVector muon_elossVec  = minDr_muon->vec_eLoss();

      TLorentzVector JetNoMuon = (jetVec - muon_elossVec);
      TLorentzVector newVec    = (JetNoMuon + matchedMuonVec);

      pt  = newVec.Pt ();
      eta = newVec.Eta();
      phi = newVec.Phi();
      E   = newVec.E  ();      
    }

    return;
  }

};

#endif
