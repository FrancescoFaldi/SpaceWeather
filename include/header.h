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
using std::vector;

struct cutoff_bin{
	double triggerrate;
	int cutoff_slice;
};

struct events{
	double triggerrate;
	UInt_t UTime;
};

void analisi();
void theta_vs_phi();
double media(vector<cutoff_bin> v,int &n, int bin);
double varianza(vector<cutoff_bin> v, double mean, int bin);

class ciclarray{
	int size;
	double b[5][3][10];

	public:
	ciclarray();
	void queue(double mean, double sigma, double sample_size, int bin);
	double get_value(int row, int col, int bin);
	void display(int bin);

};
