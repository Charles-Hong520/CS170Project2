#include "kfc.h"

#include <iostream>

using std::cout;
using std::cin;
using std::endl;

int main() {
	int featureNumber, algorithmNumber;
	string filename;
	cout<<"Welcome to Charles Hong's Feature Selection Algorithm.\n";
	cout<<"Please enter total number of features: ";
	cin>>featureNumber;
	cout<<"Type the number of the algorithm you want to run.\n";
	cout<<"1. Forward Selection\n";
	cout<<"2. Backward Elimination\n";
	cout<<"3. Charles's Special Algorithm\n";
	cin>>algorithmNumber;
	cout<<"Type the file name\n";
	cin>>filename;



	KFC k(featureNumber,filename);
	if(algorithmNumber==1) k.forward();
	else if(algorithmNumber==2) k.backward();
	else if(algorithmNumber==3) k.special();
}