#ifndef __KFC_H__
#define __KFC_H__
#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include <iomanip>
#include <time.h>

using namespace std;
class KFC {
private:
	int fts;
public:
	KFC(int features);
	void forward();
	void backward();
	void special();
	double evalForward(set<int>& s, int ft);
	double evalBackward(set<int>& s, int ft);
	void printSet(set<int> s, int num, int status);
};


#endif