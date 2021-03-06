#include <iostream>
#include <fstream>
using namespace std;

int n,m,ind[2005],v[2005];
char mt[2005][2005];

void so(int l,int s,int d) {
	if(l==n) return;
	int a=s-1,b=d+1;
	for(int i=s; i<=d; ++i)
		if(mt[l][ind[i]]=='0') v[++a]=ind[i];
		else v[--b]=ind[i];
	for(int i=s; i<=a; ++i) ind[i]=v[i];
	for(int i=a+1,j=d; i<=d; ++i,--j) ind[i]=v[j];
	if(a>s) so(l+1,s,a);
	if(b<d) so(l+1,a+1,d);
}

int main() {
	ifstream f("binar.in");
	ofstream g("binar.out");
	f>>n>>m;
	f.get();
	for(int i=0; i<n; ++i) f>>mt[i];
	for(int i=0; i<m; ++i) ind[i]=i;
	so(0,0,m-1);
	for(int i=0; i<m; ++i) g<<ind[i]+1<<' ';
	return 0;
}