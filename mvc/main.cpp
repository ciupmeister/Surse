#include <iostream>
#include <fstream>
#include <queue>
#include <bitset>
#define DN 100005
using namespace std;

typedef vector<int>::iterator it;

int n,m,cst[DN],pre[DN],cs,cd;
bitset<DN> viz;
vector<int> gr[DN];
queue<int> c;

void bfs(int s) {
  for(c.push(s);c.size(); c.pop()){
    int fr=c.front();
    viz[fr]=1;
    for(it i=gr[fr].begin(); i!=gr[fr].end(); ++i)
      if(!viz[*i]) {
        c.push(*i);
        pre[*i]=fr;
      }else if(pre[fr]!=*i) cs=fr,cd=*i;
  }
  cout<<cs<<' '<<cd;
}

int main()
{
    ifstream f("mvc.in");
    ofstream g("mvc.out");
    f>>n;
    for(int i=1; i<=n; ++i) f>>cst[i];
    for(int i=0; i<n; ++i) {
      int a,b;
      f>>a>>b;
      gr[a].push_back(b);
      gr[b].push_back(a);
    }
    bfs(1);
    return 0;
}
