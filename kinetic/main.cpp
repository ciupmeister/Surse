#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#define DN 505
#define DT 10005
#define CNST 10002
using namespace std;

int n,m;
vector<int> poz[DT];

int getvl(int vl, int t) {
  int a=vl%10000,b=vl/10000;
  return a+b*t;
}

int lb(int u,int vl) {
  int ls=0,ld=poz[u].size()-1,m;
  for(;ls<=ld;) {
    m=(ls+ld)>>1;
    if(poz[u][m]<getvl(vl,u)) ls=m+1;
    else ld=m-1;
  }
  for(;poz[u][ls]>=getvl(vl,u) && ls; --ls);
  for(;poz[u][ls]<getvl(vl,u) && ls<poz[u].size()-1;++ls);
  if(poz[u][ls]<getvl(vl,u)) return -1;
  return ls;
}

int ub(int u,int vl) {
  int ls=0,ld=poz[u].size()-1,m;
  for(;ls<=ld;) {
    m=(ls+ld)>>1;
    if(poz[u][m]<getvl(vl,u)) ls=m+1;
    else ld=m-1;
  }
  for(;poz[u][ls]>getvl(vl,u) && ls>=0; --ls);
  for(;poz[u][ls]<=getvl(vl,u) && ls<poz[u].size();++ls);
  return ls;
}

int main()
{
    ifstream f("kinetic.in");
    ofstream g("kinetic.out");
    f>>n>>m;
    for(int i=0; i<n; ++i) {
      int a,b;
      f>>a>>b;
      for(int t=0; t<CNST; ++t) poz[t].push_back(a+b*t);
      poz[CNST].push_back(b*10000+a);
    }
    for(int t=0; t<=CNST; ++t) sort(poz[t].begin(),poz[t].end());
    for(int i=0; i<m; ++i) {
      int x,y,t;
      f>>x>>y>>t;
      if(x>y) swap(x,y);
      int st,dr;
      st=lb(t,x); dr=ub(t,y);
     // cout<<t<<' '<<x<<' '<<st<<' '<<y<<' '<<dr<<'\n';
      if(st==-1) {
        g<<"0\n";
        continue;
      }
      g<<dr-st<<'\n';
    }
    return 0;
}
