/*
 * File:   main.cpp
 * Author: petru
 *
 * Created on 2010-10-13
 */

#include <iomanip>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

short h,n,m,p,par[1<<15],st[1<<15];
double dp[1<<15],sol=1000111000,x;

inline int nrb(int i) {//returneaza numarul de biti din reprez binara a lui i
	return i?1+nrb(i&(i-1)):0;
}

void calc(int i,int m1,int m2) {
	if(st[m2]>=m||nrb(m1|m2)>n) return;
	if(i==m) {
		if(dp[m1|m2]>(x=dp[m1]+(nrb(m2)>1?p:0)+(double)st[m2]/nrb(m2))) dp[m1|m2]=x,par[m1|m2]=m2;
		return;
	}
	calc(i+1,m1,m2);
	calc(i+1,m1,m2|(1<<i));
	calc(i+1,m1|(1<<i),m2);
}

vector <vector <int> > rez,aux;

void print(int m1) {
	if(!m1) {
		sort(aux.begin(),aux.end());
		return ;
	}
	vector <int> x;
	x.clear();
	for(int i=0; i<m; ++i) if(par[m1]&(1<<i)) x.push_back(i+1);
	aux.push_back(x);
	x.clear();
	print(m1^par[m1]);
}

int main()
{
	ifstream f("scara2.in");
	ofstream g("scara2.out");
	f>>h>>n>>m>>p;
	++m;
	int lim=1<<m;
    for(int i=1; i<lim; ++i) {
		dp[i]=1000111000;
		for(int j=0; j<m; ++j) if(i&(1<<j)) st[i]+=j+1;
	}
	calc(0,0,0);
	for(int i=0; i<lim;++i) if(nrb(i)==n&&st[i]==h&&sol>=dp[i]) {
        aux.clear();
        print(i);
        if(sol>dp[i]||sol==dp[i]&&aux<rez) sol=dp[i],rez=aux;
    }
	print(0);
	g<<fixed<<setprecision(2)<<sol<<'\n';
	for(int i=0; i<rez.size(); ++i) for(int j=0; j<rez[i].size();++j) g<<rez[i][j]<<' ';
	return 0;
}




