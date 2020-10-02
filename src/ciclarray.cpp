#include "header.h"
#include <iostream>
using namespace std;

ciclarray::ciclarray(int s){
	size=s;
	b=new float[size];
}
	
void ciclarray::queue(double value){
	for(int i=0; i<size-1; i++)
		b[i] = b[i+1];
	b[size-1] = value;
}

float ciclarray::get_value(int i){
	return b[i];
}

void ciclarray::display(){
	for(int i=0; i<size; i++)
		cout<<b[i]<<endl;
}
