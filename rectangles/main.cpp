#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <set>
#define DN 4005
#define x first
#define y second
#define mp make_pair
using namespace std;

typedef pair<int,int> per;
typedef vector<int>::iterator it;

int n,ma[DN][DN];
vector<int> gr[DN];

struct seg {
  int x1,y1,x2,y2;
  seg(int _x1,int _y1,int _x2,int _y2) {
    x1=_x1; x2=_x2; y1=_y1; y2=_y2;
  }
} ;

vector<seg> v;

per is(seg a,seg b) {
  if(a.x1==a.x2) {
    if(b.x1==b.x2) return mp(-1,-1);
    if(a.y1<=b.y1 && b.y1<=a.y2) return mp(a.x1,b.y1);
  }else {
    if(b.y1==b.y2) return mp(-1,-1);
    if(a.x1<=b.x1 && b.x1<=a.x2) return mp(b.x1,a.y1);
  }
  return mp(-1,-1);
}

int main()
{
  ifstream f("rectangles.in");
  ofstream g("rectangles.out");
  f>>n;
  for(int i=0; i<n; ++i) {
    int a1,b1,a2,b2,x1,y1,x2,y2;
    f>>a1>>b1>>a2>>b2;
    x1=min(a1,a2); x2=max(a1,a2);
    y1=min(b1,b2); y2=max(b1,b2);
    v.push_back(seg(x1,y1,x2,y1));
    v.push_back(seg(x2,y1,x2,y2));
    v.push_back(seg(x1,y2,x2,y2));
    v.push_back(seg(x1,y1,x1,y2));
  }
  for(int i=0; i<v.size(); ++i) for(int j=0; j<v.size(); ++j) if(is(v[i],v[j])!=mp(-1,-1)) {
    //cerr<<v[i].x1<<' '<<v[i].y1<<' ' <<v[i].x2<<' '<<v[i].y2<<'\n';
    //cerr<<v[j].x1<<' '<<v[j].y1<<' ' <<v[j].x2<<' '<<v[j].y2<<"\n\n";
    ma[i][j]=ma[j][i]=1;
    gr[i].push_back(j);
    gr[j].push_back(i);
  }
  int r=0;
  set<pair<per,per> > s;
  for(int i=0; i<v.size(); ++i) for(int j=i+1; j<v.size(); ++j) if(!ma[i][j])
    for(int k=0; k<gr[i].size(); ++k) for(int l=k+1; l<gr[i].size(); ++l) {
      int a=gr[i][k],b=gr[i][l];
      if(!ma[j][a] || !ma[j][b]) continue;
      per sj=min(min(is(v[i],v[a]),is(v[j],v[a])),min(is(v[i],v[b]),is(v[j],v[b])));
      per ds=max(max(is(v[i],v[a]),is(v[j],v[a])),max(is(v[i],v[b]),is(v[j],v[b])));
      if(abs(sj.x-ds.x)==abs(sj.y-ds.y)) s.insert(mp(sj,ds));
    }
  g<<s.size();
  return 0;
}
