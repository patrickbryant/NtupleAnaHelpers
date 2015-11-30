#ifndef NTUPLEANAHELPERS_MUONHISTS_H
#define NTUPLEANAHELPERS_MUONHISTS_H

#include <EventLoop/Worker.h>

#include "TH1D.h"
#include "TH2D.h"
#include "TProfile.h"

//
// muonHists
//
class muonHists{
     
 public: 

  TH1F* h_pt;
  TH1F* h_pt_m;
  TH1F* h_pt_l;
  TH1F* h_eta;
  TH1F* h_phi;
  TH1F* h_isMedium;
  TH1F* h_isTight;
  TH1F* h_ptcone20;


  muonHists(std::string name, EL::Worker* wk){
    h_pt       = book(wk, name, "Pt",        "p_{T} [GeV]",   100,  0,    20);
    h_pt_m     = book(wk, name, "Pt_m",      "p_{T} [GeV]",   100,  0,    40);
    h_pt_l     = book(wk, name, "Pt_l",      "p_{T} [GeV]",   100,  0,   200);
    h_eta      = book(wk, name, "Eta",       "Eta",           100, -3,     3);
    h_phi      = book(wk, name, "Phi",       "Phi",           100, -3.2,   3.2);
    h_isMedium = book(wk, name, "isMedium",  "isMedium",        2, -0.5,   1.5);
    h_isTight  = book(wk, name, "isTight",   "isTight",         2, -0.5,   1.5);
    h_ptcone20 = book(wk, name, "ptcone20",  "ptcone20",      100, -0.1,   5);
  }

  TH1F* book(EL::Worker* wk, std::string name, std::string hname, std::string title, int nBins, float xmin, float xmax){
    TH1F* h_tmp = new TH1F((name+"_"+hname).c_str(),(hname+";"+title+";Entries").c_str(), nBins, xmin,   xmax);
    wk->addOutput(h_tmp);
    return h_tmp;
  }
  
  void Fill(const muonData& muon, const float& weight){
    h_pt       -> Fill(muon.pt,         weight);
    h_pt_l     -> Fill(muon.pt,         weight);
    h_pt_m     -> Fill(muon.pt,         weight);
    h_eta      -> Fill(muon.eta,        weight);
    h_phi      -> Fill(muon.phi,        weight);
    h_isMedium -> Fill(muon.IsMedium,   weight);
    h_isTight  -> Fill(muon.IsTight,    weight);
    h_ptcone20 -> Fill(muon.ptcone20,   weight);
  }

};

#endif
