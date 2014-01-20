#include <iostream>
#include <fstream>
#include <vector>
using namespace std;
ifstream f("berarii2.in");
ofstream g("berarii2.out");
vector <int> gr[1000005];

int n,m,p,i,j,v[1000005],b[1005],mb,x,y;
void dfs(int k)
{ vector <int> :: iterator ir;
  v[k]=1;

  for(ir=gr[k].begin();ir!=gr[k].end();ir++)
      if(v[*ir]==0)
        dfs(*ir);

}
int main()
{   f>>n>>m>>p;
    for(i=1;i<=m;i++)
        {
          f>>x>>y;
          gr[y].push_back(x);
        }
    for(i=1;i<=p;i++)
        f>>b[i];
    for(i=1;i<=p;i++)
          if(v[b[i]]==0)
            dfs(b[i]);
   mb=0;
    for(i=1;i<=n;i++)
        if(v[i]==0)
            mb++;
    g<<mb<<"\n";
    for(i=1;i<=n;i++)
        if(v[i]==0)
            g<<i<<"\n";
    return 0;
}
