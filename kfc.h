#ifndef __KFC_H__
#define __KFC_H__
#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include <iomanip>
#include <time.h>
#include <fstream>
#include <sstream>
#include <limits>
#include <cmath>

using namespace std;
class KFC {
private:
	int fts;
	vector<vector<double> > data;
public:
	KFC(int features,string& filename);
	void forward();
	void backward();
	void special();
	double evalForward(set<int> s, int ft);
	double evalBackward(set<int> s, int ft);
	void printSet(set<int> s, int num, int status);
	double euclDistOfFeatures(vector<int>& feats, vector<double>& a, vector<double>& b);
	double loocv(vector<int>& feats);
	void input(string& filename);
};


#endif