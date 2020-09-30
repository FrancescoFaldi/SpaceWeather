#include "header.h"
#include <iostream>
#include <TH2F.h>
#include <TH1F.h>
#include <TGraph.h>
#include <TCanvas.h>
#include <TTree.h>
#include <TFile.h>
#include <TChain.h>
#include "TROOT.h"
using namespace std;

void analisi(){

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
	TGraph* gr=new TGraph();
	TCanvas* c=new TCanvas();
	c->Divide(1,2);
	TChain* t=new TChain("tree;2");
	
	t->Add("../Dati/201201_60s.root");
/*	t->Add("../Dati/201202_60s.root");
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
*/
//	TFile *f = TFile::Open("201201_60s.root");
//	TTree *t = (TTree*)f->Get("tree;2");
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
	
	int e=0;

	for(int i=0; i<t->GetEntries(); i++){
		t->GetEntry(i);
		if(rtiGood==0 && rtiNerr==0 && rtiSAA==false && nsec>0 && nsec<=60 && rtiLifetime>1e-4){
			h->Fill(rtiPhi,rtiTheta,rtiMaxIGRFCutoff[0][1]);
			gr->SetPoint(e,UTime,nEvt/rtiLifetime);
			e++;
		}
	}


	TFile* risultati=new TFile("../risultati.root", "RECREATE");
	
	gROOT->Macro("../macros/rootstyle.C");
	gr->SetName("gr");
	gr->SetTitle("Trigger Rate VS Unix Time 2012");
	
	c->cd(1);
	gr->Draw();
	c->cd(2);
	h->Draw("COLZ");
	c->Draw();
	
	gr->Write();
	h->Write();

	risultati->Close();
}

