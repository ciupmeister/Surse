#include <iostream>
#include <fstream>
using namespace std;

int n,m,ind[2005],v[2005];
string mt[2005];

void s(int l,int s,int d) {
	int a=s-1,b=d+1;
	for(int i=s; i<d; ++i)
		if(mt[l][ind[i]]==0) v[++a]=ind[i];
		else v[--b]=ind[i];
	
}

int main() {
	ifstream f("binar.in");
	ofstream g("binar.out");
	f>>n>>m;
	for(int i=0; i<n; ++i) getline(f,mt[i]);
	for(int i=0; i<m; ++i) ind[i]=i;
	s(0,0,m);
	return 0;
}