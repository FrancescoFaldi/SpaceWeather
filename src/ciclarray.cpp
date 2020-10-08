#include "header.h"
#include <iostream>
#include <iomanip>
using namespace std;

ciclarray::ciclarray(){
	size=5;
	//b=new double[size][2];
}

double ciclarray::get_value(int row, int col, int bin){
	return b[row][col][bin];
}

void ciclarray::queue(double mean, double sigma, double sample_size, int bin){
	for(int i=0; i<size-1; i++){
		b[i][0][bin] = b[i+1][0][bin];
		b[i][1][bin] = b[i+1][1][bin];
		b[i][2][bin] = b[i+1][2][bin];
		b[size-1][0][bin] = mean;
		b[size-1][1][bin] = sigma;
		b[size-1][2][bin] = sample_size;
	}
}

void ciclarray::display(int bin){
	for(int i=0; i<size; i++)
		cout<<b[i][0][bin]<<" "<<b[i][1][bin]<<" "<<b[i][2][bin]<<endl;
}
