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
	
	vector<float> v; // contiene i valori del trigger rate per cui il cutoff è < 2 GV, viene svuotato ogni ciclo di precessione orbitale
	ciclarray* b = new ciclarray(3); //array ciclico di 3 elementi, contiene il valore max del vettore v di tre cicli orbitali

	TH2F* h= new TH2F("h","",100,-180,180,100,-60,60);
	TGraph* gr=new TGraph(); // grafico dei valori di "quiete"
	TGraph* gr1=new TGraph();// grafico dei valori di attività solare
	TMultiGraph *mg = new TMultiGraph();
	TCanvas* c=new TCanvas();
	c->Divide(1,2);
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
	
	int e=0;
	int e1=0;
	float LastUpTime;
	float triggerrate;
	
	for(int i=0; i<3500; i++){ // inizializzo l'array ciclico
		t->GetEntry(i);
		if(rtiGood==0 && rtiNerr==0 && rtiSAA==false && nsec>0 && nsec<=60 && rtiLifetime>1e-4 && rtiMaxIGRFCutoff[0][1]<2){
			triggerrate=nEvt/rtiLifetime;
			v.push_back(triggerrate);
		}
	}
	
	b->queue(*max_element(v.begin(), v.end()));
	b->queue(*max_element(v.begin(), v.end()));
	b->queue(*max_element(v.begin(), v.end()));
	b->display();
	v.clear();
	
	for(int i=0; i<t->GetEntries(); i++){ 
		t->GetEntry(i);
		if(rtiGood==0 && rtiNerr==0 && rtiSAA==false && nsec>0 && nsec<=60 && rtiLifetime>1e-4){
//			h->Fill(rtiPhi,rtiTheta,rtiMaxIGRFCutoff[0][1]);

			triggerrate=nEvt/rtiLifetime;

			if(rtiMaxIGRFCutoff[0][1]<2){
				if(triggerrate > 200 + (b->get_value(0)+b->get_value(1)+b->get_value(2))/3){ // stabilisco se il trigger rate si discosta eccessivamente dalla media dei tre cicli precedenti
					gr1->SetPoint(e1, UTime, triggerrate); // se è vero lo metto in questo grafico, ma non nel vettore v
					e1++;
				}
				else{
					v.push_back(triggerrate);
					gr->SetPoint(e, UTime, triggerrate); 
					e++;
				}
				LastUpTime = UTime; // questo è un riferimento temporale per capire quando finisce un ciclo di precessione orbitale
			}
			

			
			else{
				if(v.empty()==false && UTime-LastUpTime > 30000){ // se v è pieno ed è passato abbastanza tempo dall'ultimo ciclo
					b->queue(*max_element(v.begin(), v.end())); // inserisco il massimo di v nell'array ciclico
					v.clear(); // e lo svuoto
				}
				gr->SetPoint(e, UTime, triggerrate); 
				e++;
			}
			
		}
	}


	TFile* risultati=new TFile("../risultati.root", "RECREATE");
	
	gROOT->Macro("../macros/rootstyle.C");
	
	gr->SetMarkerStyle(20);
	gr->SetMarkerSize(0.4);
	gr1->SetMarkerColor(kRed);
	gr1->SetMarkerStyle(20);
	gr1->SetMarkerSize(0.4);
	mg->Add(gr,"p");
	mg->Add(gr1,"p");
	mg->SetTitle("Trigger Rate VS Unix Time 2012");
	
	c->cd(1);
	mg->Draw();
	c->cd(2);
	h->Draw("COLZ");
	c->Draw();
	
	mg->Write("mg");
	h->Write();

	risultati->Close();
}

