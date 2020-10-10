#include "header.h"
#include <ostream>
using namespace std;

int main(int argc, char *argv[]){
	if(argc>2){
		cout<<"Err: too many arguments"<<endl;
		return 0;
	}
	else if(strcmp(argv[1], "analisi") == 0){
		analisi();
		return 0;
	}
	else if(strcmp(argv[1], "theta_vs_phi") == 0){
		theta_vs_phi();
		return 0;
	}
	else{
		cout<<argv[1]<<endl;
		cout<<"Err: invalid argument"<<endl;
		return 0;
	}

}
