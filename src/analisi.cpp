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

//ANALISI ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	vector<cutoff_bin> v; // contiene i valori del trigger rate per cui il cutoff è < 2 GV, viene svuotato ogni ciclo di precessione orbitale
	vector<events> ev;
	ciclarray* b = new ciclarray(); //array ciclico di 5 elementi, contiene media, varianza e N del vettore v per 5 cicli orbitali

	int e=0;
	double LastUpTime;
	double triggerrate;
	int test=0;
	int cutoff_slice;
	int n=0;
	int N=0;
	double m;
	double var;
	double mu;
	double sigma;

// PUNTO 1 - inizializzo l'array ciclico (vedere punto 2 per spiegazioni) ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	for(int i=0; i<3500; i++){
		t->GetEntry(i);
		if(rtiGood==0 && rtiNerr==0 && rtiSAA==false && nsec>0 && nsec<=60 && rtiLifetime>1e-4 && rtiMaxIGRFCutoff[0][1]<2){
			triggerrate=nEvt/rtiLifetime;
			test=(int)rtiMaxIGRFCutoff[0][1];
			if(test>0) cutoff_slice= (int)(rtiMaxIGRFCutoff[0][1]*10-10);
			else cutoff_slice = 0;
			v.push_back({triggerrate,cutoff_slice});

		}
	}
	for(int j=0; j<10; j++){
		m=media(v,n,j);
		var=varianza(v,m,j);
		b->queue(m,var,n,j);
		b->queue(m,var,n,j);
		b->queue(m,var,n,j);
		b->queue(m,var,n,j);
		b->queue(m,var,n,j);

		b->display(j);
		cout<<endl;
	}
	v.clear();

//PUNTO 2 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	for(int i=0; i<t->GetEntries(); i++){
		t->GetEntry(i);
		if(rtiGood==0 && rtiNerr==0 && rtiSAA==false && nsec>0 && nsec<=60 && rtiLifetime>1e-4){ //taglio
			//h->Fill(rtiPhi,rtiTheta,rtiMaxIGRFCutoff[0][1]);

			triggerrate=nEvt/rtiLifetime;

			if(rtiMaxIGRFCutoff[0][1]<2){ //condizione di sensibilità

				test=(int)rtiMaxIGRFCutoff[0][1]; //stabilisco in quale bin di cutoff mi trovo
				if(test>0) cutoff_slice= (int)(rtiMaxIGRFCutoff[0][1]*10-10);
				else cutoff_slice = 0;

				N=0; //calcolo la media e combino la varianza dei 5 precedenti periodi di quiete
				mu=0;
				sigma=0;

				for(int j=0; j<5; j++){
					mu = mu + b->get_value(j,2,cutoff_slice) * b->get_value(j,0,cutoff_slice);
					N = N + b->get_value(j,2,cutoff_slice);
				}

				mu = mu / N;

				N=0;
				for(int j=0; j<5; j++){
					sigma = sigma + b->get_value(j,2,cutoff_slice) * ( b->get_value(j,1,cutoff_slice) + pow(b->get_value(j,0,cutoff_slice)-mu,2) );
					if(b->get_value(j,2,cutoff_slice)>1) N = N + b->get_value(j,2,cutoff_slice);
				}

				sigma = sqrt(sigma / N);

				//a questo punto decido se nel periodo di sensibilità c'è attività o meno

				if(  (triggerrate - mu)/sigma >5   ) //il trigger rate si discosta eccessivamente dalla media dei tre cicli precedenti?
					ev.push_back({triggerrate, UTime});// se è vero lo metto in questo vettore, ma non nel vettore v

				else{
					v.push_back({triggerrate,cutoff_slice});
					gr->SetPoint(e, UTime, triggerrate);
					e++;
				}
				LastUpTime = UTime; // questo è un riferimento temporale per capire quando finisce un ciclo di precessione orbitale
			}



			else{
				if(v.empty()==false && UTime-LastUpTime > 30000){ // se v è pieno ed è passato abbastanza tempo dall'ultimo ciclo
					for(int j=0; j<10; j++){
						m=media(v,n,j);
						var=varianza(v,m,j);
						b->queue(m,var,n,j);// inserisco media varianza e numero di elementi di v , relativi ad un bin di cutoff, nell'array ciclico
					}
					v.clear(); // e lo svuoto
				}
				gr->SetPoint(e, UTime, triggerrate);
				e++;
			}



		}
	}

//di seguito elimino gli eventi con occorrenze (consecutive) inferiori a 3
//e disegno in rosso gli eventi identificati come "attività"

	e=0;
	vector<events> ev_good;
	vector<events> temp;
	for(int i=0; i<ev.size(); i++){
		temp.push_back({ev[i].triggerrate, ev[i].UTime});
		e++;
		if(e<4 && (ev[i+1].UTime - temp[e-1].UTime) >30000){
			temp.clear();
			e=0;
		}
		if(e>4 && (ev[i+1].UTime - temp[e-1].UTime) >30000){
			for(int j=0; j<temp.size(); j++) ev_good.push_back({temp[j].triggerrate, temp[j].UTime});
			temp.clear();
			e=0;
		}
	}
	for(int i=0; i<ev_good.size(); i++) gr1->SetPoint(i, ev_good[i].UTime, ev_good[i].triggerrate);

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

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
