#include "kfc.h"

KFC::KFC(int features) {
	fts = features;
	std::srand( (unsigned)time( NULL ) );
}

void KFC::forward() {
	set<int> currSet;
	vector<pair<double,set<int>>> maxMap;
	set<int> nums;
	double val, toBeAddedPercent=0;
	int toBeAddedFeature;
	for(int i = 1; i <= fts; i++) nums.insert(i);
	
	cout << std::fixed;
    cout << std::setprecision(1);
	cout<<"Beginning Forward Search.\n"<<endl;
	for(int i = 1; i <= fts; i++) {
		//is parent rn, branch to children
		toBeAddedFeature = *nums.begin();
		toBeAddedPercent = 0;
		for(int j : nums) {
			//adds j to currset and evaluate
			//returns random val for now
			val = evalForward(currSet,j);
			
    		
			cout<<"using feature(s) ";
			printSet(currSet,j,1);
			cout<<" accuracy is "<<val<<"%\n";
			if(toBeAddedPercent < val) {
				toBeAddedPercent = val;
				toBeAddedFeature = j;
			}
		}
		cout<<endl;

		currSet.insert(toBeAddedFeature);
		cout<<"Feature set ";
		printSet(currSet,0,0);
		cout<<" was best, accuracy is "<<toBeAddedPercent<<"%\n"<<endl;
		maxMap.push_back({toBeAddedPercent,currSet});
		nums.erase(toBeAddedFeature);
	}
	auto mx = max_element(maxMap.begin(), maxMap.end());
	cout<<"Finished search!! The best feature subset is ";
	auto it = mx->second.begin();
	cout<<*it; it++;
	for(; it != mx->second.end(); it++) {
		cout<<","<<*it;
	}
	cout<<"}, which has an accuracy of "<<mx->first<<"%"<<endl;
}




void KFC::backward() {
	set<int> currSet;
	vector<pair<double,set<int>>> maxMap;
	double val, toBeDeletedPercent=0;
	int toBeDeletedFeature;
	for(int i = 1; i <= fts; i++) currSet.insert(i);
	
	cout << std::fixed;
    cout << std::setprecision(1);
	cout<<"Beginning Backward Search.\n"<<endl;
	
	val = evalForward(currSet,1);
	cout<<"Using features ";
	printSet(currSet,0,0);
	cout<<" accuracy is "<<val<<"%\n"<<endl;

	for(int i = 1; i < fts; i++) {
		//is parent rn, branch to children
		toBeDeletedFeature = *currSet.begin();
		toBeDeletedPercent = 0;

		for(int j : currSet) {
			//removes one from the currset and calculates
		
			val = evalBackward(currSet,j);

			cout<<"Using feature(s) ";
			printSet(currSet,j,2);
			cout<<" accuracy is "<<val<<"%\n";

			if(toBeDeletedPercent < val) {
				toBeDeletedPercent = val;
				toBeDeletedFeature = j;
			}

		}
		cout<<endl;

		currSet.erase(toBeDeletedFeature);
		cout<<"Feature set ";
		printSet(currSet,0,0);
		cout<<" was best, accuracy is "<<toBeDeletedPercent<<"%\n"<<endl;
		maxMap.push_back({toBeDeletedPercent,currSet});
	}
	auto mx = max_element(maxMap.begin(), maxMap.end());
	cout<<"Finished search!! The best feature subset is ";
	printSet(mx->second, 0,0);
	cout<<", which has an accuracy of "<<mx->first<<"%"<<endl;
}



void KFC::special(){}
void KFC::printSet(set<int> s, int num, int status) {
	if(status==1) {
		s.insert(num);
	} else if(status==2) {
		s.erase(num);
	}
	auto it = s.begin();
	cout<<"{"<<*it;
	it++;
	for(;it != s.end(); it++) {
		cout<<","<<*it;
	}
	cout<<"}";
}

double KFC::evalForward(set<int>& s, int ft) {
	
    double r = (double) rand()/RAND_MAX;
    return 100*r;
}
double KFC::evalBackward(set<int>& s, int ft) {
	
    double r = (double) rand()/RAND_MAX;
    return 100*r;
}