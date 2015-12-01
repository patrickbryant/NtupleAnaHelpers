#ifndef NTUPLEANAHELPERS_JETHISTS_H
#define NTUPLEANAHELPERS_JETHISTS_H

#include <EventLoop/Worker.h>
#include <NtupleAnaHelpers/muonHists.h>

#include "TH1D.h"
#include "TH2D.h"
#include "TProfile.h"

//
// jetHists
//
class jetHists{
     
 public: 

  bool m_doTiming;
  bool m_doSegments;
  bool m_doMuonInJets;

  // Detail Level 0
  TH1F* h_pt;
  TH1F* h_pt_m;
  TH1F* h_pt_l;
  TH1F* h_eta;
  TH1F* h_phi;
  TH1F* h_jvt;
  TH1F* h_MV2c20;

  // Details
  TH2F* h_jettiming_vs_eta;
  TH1F* h_MuonSegments;
  TH1F* h_MuonSegments_l;
  TH1F* h_MuonSegments_vl;
  TProfile* h_MuonSegments_vs_eta;
  
  // muon Hists
  muonHists* h_muonInJet;

  jetHists(std::string name, EL::Worker* wk, std::string detailLevel=""){
    h_pt     = book(wk, name, "Pt",     "p_{T} [GeV]",   100,  0, 500);
    h_pt_m   = book(wk, name, "Pt_m",   "p_{T} [GeV]",   100,  0, 1000);
    h_pt_l   = book(wk, name, "Pt_l",   "p_{T} [GeV]",   100,  0, 5000);
    h_eta    = book(wk, name, "Eta",    "Eta",           100, -3,   3);
    h_phi    = book(wk, name, "Phi",    "Phi",           100, -3.2,   3.2);
    h_jvt    = book(wk, name, "Jvt",    "JVT",           100, -0.1,   1.1);
    h_MV2c20 = book(wk, name, "MV2c20", "MV2c20",        100, -0.1,   1.1);

    if(detailLevel.find("muonInJet") != std::string::npos){
      h_muonInJet = new muonHists(name+"_muonInJet", wk);
      m_doMuonInJets = true;
    }else{
      m_doMuonInJets = false;
    }
    
    if(detailLevel.find("timing") != std::string::npos){
      h_jettiming_vs_eta = new TH2F((name+"_timing_vs_eta").c_str(),"jetTime_vs_eta;jet #eta;jetTime",     50, -3.2,   3.2, 100, -10,10);
      wk->addOutput(h_jettiming_vs_eta);
      m_doTiming = true;
    }else{
      m_doTiming = false;
    }

    if(detailLevel.find("segments") != std::string::npos){
      h_MuonSegments    = book(wk, name, "MuonSegs",    "MuonSegments",          50, -0.5,   49.5);
      h_MuonSegments_l  = book(wk, name, "MuonSegs_l",  "MuonSegments",          100, -0.5,   99.5);
      h_MuonSegments_vl = book(wk, name, "MuonSegs_vl", "MuonSegments",          100, -0.5,   199.5);
      
      h_MuonSegments_vs_eta = new TProfile((name+"_MuonSegs_vs_eta").c_str(),"jetMuonSegs_vs_eta;jet #eta;MuonSegments",  50, -3.2, 3.2, -0.5, 49.5);
      wk->addOutput(h_MuonSegments_vs_eta);
      m_doSegments = true;
    }else{
      m_doSegments = false;
    }
    
  }

  TH1F* book(EL::Worker* wk, std::string name, std::string hname, std::string title, int nBins, float xmin, float xmax){
    TH1F* h_tmp = new TH1F((name+"_"+hname).c_str(),(hname+";"+title+";Entries").c_str(), nBins, xmin,   xmax);
    wk->addOutput(h_tmp);
    return h_tmp;
  }

      
  void Fill(const jetData& jet, const float& weight){
    h_pt       -> Fill(jet.pt,       weight);
    h_pt_l     -> Fill(jet.pt,       weight);
    h_pt_m     -> Fill(jet.pt,       weight);
    h_eta      -> Fill(jet.eta,      weight);
    h_phi      -> Fill(jet.phi,      weight);
    h_jvt      -> Fill(jet.Jvt,      weight);
    h_MV2c20   -> Fill(jet.MV2c20,   weight);

    if(m_doTiming){
      h_jettiming_vs_eta-> Fill(jet.eta, jet.Timing,   weight);
    }

    if(m_doSegments){
      h_MuonSegments    -> Fill(jet.MuonSegmentCount,  weight);
      h_MuonSegments_l  -> Fill(jet.MuonSegmentCount,  weight);
      h_MuonSegments_vl -> Fill(jet.MuonSegmentCount,  weight);
      h_MuonSegments_vs_eta  -> Fill(jet.eta, jet.MuonSegmentCount,  weight);
    }

    if(m_doMuonInJets){
      if(jet.matchedMuon) h_muonInJet->Fill(*jet.matchedMuon, weight);
    }

    //h_etaphi   -> Fill(eta, phi, weight);
    //h_etaphi_s -> Fill(eta, phi, weight);
  }
  
};

#endif
