#include "kfc.h"

KFC::KFC(int features,string& filename) {
	fts = features;
	// std::srand( (unsigned)time( NULL ) );
	input(filename);
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
	printSet(mx->second, 0,0);
	cout<<", which has an accuracy of "<<mx->first<<"%"<<endl;
}




void KFC::backward() {
	set<int> currSet;
	vector<pair<double,set<int> > > maxMap;
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

double KFC::evalForward(set<int> s, int ft) {
    s.insert(ft);
    vector<int> v(s.begin(), s.end());
    return 100*loocv(v); //eval only these features in the set 
}
double KFC::evalBackward(set<int> s, int ft) {
    s.erase(ft);
    vector<int> v(s.begin(), s.end());
    return 100*loocv(v); //eval only these features in the set
}

double KFC::euclDistOfFeatures(vector<int>& feats, vector<double>& a, vector<double>& b) {
	//compare eucl dist of obj a and b
	double dist = 0, tmp;
	for(int feature : feats) {
		tmp = (a[feature] - b[feature]);
		dist += tmp * tmp;
	}
	return sqrt(dist);
}

double KFC::loocv(vector<int>& feats) {
	//input will have a stl::set of features, actually vector
	//vector of n objects with features in set, 2D
	//
	int n = data.size();
	double distance; 
	int correct_classified = 0;
	vector<pair<double,double> > nn(n,make_pair(std::numeric_limits<double>::max(),0)); //mindist of NN, class of NN
	for(int i = 0; i < n-1; i++) {
		for(int j = i+1; j < n; j++) {
			distance = euclDistOfFeatures(feats, data[i], data[j]);
			if(distance < nn[i].first) {
				nn[i].first = distance;
				nn[i].second = (int)data[j][0];
			}
			if(distance < nn[j].first) {
				nn[j].first = distance;
				nn[j].second = (int)data[i][0];
			}
		}
	}
	for(int i = 0; i < n; i++) {
		if((int)data[i][0]==nn[i].second) {
			correct_classified++;
		}
	}
	//returns accuracy of this set of features
	return (double)correct_classified/(double)n; 
}


void KFC::input(string& filename) {
	string line;

	ifstream fin(filename);
	while(getline(fin,line)) {
		data.push_back(vector<double>(1));
		stringstream ss(line);
		ss>>data.back()[0];
		double in;
		while(ss>>in) {
			data.back().push_back(in);
		}
	}
}


