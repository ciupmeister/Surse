#include <fstream>
#include <iostream>
#include <set>
#include <tr1/unordered_map>
#include <algorithm>
#define DN 2005
#define V 10000
#define x first
#define y second
using namespace std;
using namespace tr1;

unordered_map<int,int> mp;
set<int> s;
typedef pair<int,int> per;
pair<per,per> v[DN];
unordered_map<int,int> bst;
int n,fst[4*DN],lst[4*DN],cnt;

bool cmp(pair<per,per> a,pair<per,per> b) {
    if(a.x.x==b.x.x) return a.y.y<b.y.y;
    return a.x.x<b.x.x;
}

int fa(int a,int b) {return cnt*a+b;}

inline int memo(int &a,int &b) {
    if(a>=b) return 0;
    //cout<<a<<' '<<b<<'\n';cout.flush();
    if(bst.find(fa(a,b))!=bst.end()) return bst[fa(a,b)];
    int r=0,z=0;
    for(int i=fst[a]; i<=n; ++i) if(v[i].x.x>=a && v[i].y.y<=b) {
        ++z;
        r=max(r,memo(v[i].x.y,v[i].y.x)+memo(v[i].y.y,b)+1);
        if(z>100)break;
    }
    bst[fa(a,b)]=r;
    return r;
}

int main() {
    ifstream f("intfm.in");
    ofstream g("intfm.out");
    f>>n;
    for(int i=1; i<=n; ++i) {
        int a,b,lg;
        f>>a>>b;
        lg=(b-a)/5;
        v[i].x.x=a; s.insert(a);
        v[i].x.y=a+2*lg; s.insert(a+2*lg);
        v[i].y.x=a+3*lg; s.insert(a+3*lg);
        v[i].y.y=b; s.insert(b);
    }
    for(set<int>::iterator is=s.begin(); is!=s.end(); ++is) mp[*is]=++cnt;
    for(int i=1; i<=n; ++i) {
        v[i].x.x=mp[v[i].x.x];
        v[i].x.y=mp[v[i].x.y];
        v[i].y.x=mp[v[i].y.x];
        v[i].y.y=mp[v[i].y.y];
    }
    int a=1,b=1;
    for(int i=1; i<=cnt; ++i) {
        for(;v[a].x.x<i && a<=n;++a);
    }
    sort(v+1,v+n+1);
    g<<memo(v[1].x.x,cnt);
    return 0;
}
