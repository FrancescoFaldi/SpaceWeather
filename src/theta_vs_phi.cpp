#include "header.h"
#include <iostream>
#include <TH2F.h>
#include <TH1F.h>
#include <TGraph.h>
#include <TMultiGraph.h>
#include <TCanvas.h>
#include <TTree.h>
#include <TFile.h>
#include <TChain.h>
#include "TROOT.h"
#include <vector>
#include <bits/stdc++.h>
using namespace std;

void theta_vs_phi(){

  Short_t nsec;
  Float_t nEvt;
  UInt_t UTime;
  Float_t rtiTheta;
  Float_t rtiPhi;
  Int_t rtiGood;
  Float_t rtiNerr;
  bool rtiSAA;
  Float_t rtiLifetime;
  Float_t rtiMaxIGRFCutoff[4][2];

  TH2F* h= new TH2F("h","",100,-180,180,100,-60,60);
  TCanvas* c=new TCanvas();
  TChain* t=new TChain("tree;2");

  t->Add("../Dati/201201_60s.root");
  t->Add("../Dati/201202_60s.root");
  t->Add("../Dati/201203_60s.root");
  t->Add("../Dati/201204_60s.root");
  t->Add("../Dati/201205_60s.root");
  t->Add("../Dati/201206_60s.root");
  t->Add("../Dati/201207_60s.root");
  t->Add("../Dati/201208_60s.root");
  t->Add("../Dati/201209_60s.root");
  t->Add("../Dati/201210_60s.root");
  t->Add("../Dati/201211_60s.root");
  t->Add("../Dati/201212_60s.root");

  t->SetBranchAddress("nsec", &nsec);
  t->SetBranchAddress("nEvt", &nEvt);
  t->SetBranchAddress("UTime", &UTime);
  t->SetBranchAddress("rtiTheta", &rtiTheta);
  t->SetBranchAddress("rtiPhi", &rtiPhi);
  t->SetBranchAddress("rtiGood", &rtiGood);
  t->SetBranchAddress("rtiNerr", &rtiNerr);
  t->SetBranchAddress("rtiSAA", &rtiSAA);
  t->SetBranchAddress("rtiLifetime", &rtiLifetime);
  t->SetBranchAddress("rtiMaxIGRFCutoff", &rtiMaxIGRFCutoff);


  for(int i=0; i<t->GetEntries(); i++){
    t->GetEntry(i);
    if(rtiGood==0 && rtiNerr==0 && rtiSAA==false && nsec>0 && nsec<=60 && rtiLifetime>1e-4) //taglio
      h->Fill(rtiPhi,rtiTheta,rtiMaxIGRFCutoff[0][1]);
  }

  TFile* risultati=new TFile("../theta_vs_phi.root", "RECREATE");

	gROOT->Macro("../macros/rootstyle.C");

  c->cd();
	h->Draw("COLZ");
  c->Draw();
  h->Write();

  risultati->Close();

}
