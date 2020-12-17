#include "header.h"
#include <iostream>
#include <vector>
#include <bits/stdc++.h>
using namespace std; 

double media(vector<bin> v,int &n, int bin){
	n=0;
	double mean=0;
	for(int i=0; i<v.size(); i++)
		if(v[i].cutoff_slice==bin){ 
			mean=mean+v[i].triggerrate;
			n++;
		}
		
	if(n>0) return mean=mean/ n;
	else return 0;
}

double varianza(vector<bin> v, double mean, int bin){
	int n=0;
	double var=0;
	for(int i=0; i<v.size(); i++)
		if(v[i].cutoff_slice==bin){
			var=var+pow(v[i].triggerrate-mean,2);
			n++;
		}
	if(n>1) return var=var/n;
	else return 0;
}
