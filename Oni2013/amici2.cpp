//#include <fstream>
//#include <vector>
//#include <queue>
//#include <cmath>
//#define DN 21005
//using namespace std;
//
//typedef vector<int>::iterator it;
//int t,n,m,d[DN];
//vector<int> gr[DN];
//
//void bfs(int s) {
//  queue<int> c;
//  for(int i=1; i<=n; ++i) d[i]=(1<<30);
//  d[s]=0;
//  for(c.push(s);!c.empty(); c.pop()) {
//    int fr=c.front();
//    for(it i=gr[fr].begin(); i!=gr[fr].end(); ++i) if(d[*i]==(1<<30)) {
//      d[*i]=d[fr]+1;
//      c.push(*i);
//    }
//  }
//}
//
//int main() {
//  ifstream f("amici2.in");
//  ofstream g("amici2.out");
//  for(f>>t;t--;) {
//    f>>n>>m;
//    for(int i=1; i<=n; ++i) gr[i].clear();
//    for(;m--;) {
//      int a,b;f>>a>>b;
//      gr[a].push_back(b);
//      gr[b].push_back(a);
//    }
//    bfs(1);
//    int nmax=-1,dmax=-1;
//    for(int i=1; i<=n; ++i) if(dmax<d[i]) {
//      dmax=d[i];
//      nmax=i;
//    }
//    bfs(nmax);
//    dmax=-1;
//    for(int i=1; i<=n; ++i) dmax=max(dmax,d[i]);
//    g<<ceil(log2(dmax))<<'\n';
//  }
//}
