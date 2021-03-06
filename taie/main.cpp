#include <iomanip>
#include <fstream>
#include <algorithm>
#define DN 1005
#define x first
#define y second
using namespace std;

typedef pair<long double,long double> per;
pair<per,per> seg[DN];
per p[DN*2];
int n,sz;

double id(per a, per b, per c) {
  long double p=a.x*b.y+b.x*c.y+c.x*a.y,m=-b.x*a.y-c.x*b.y-a.x*c.y;
  return p+m;
}

int main()
{
    ifstream f("taie.in");
    ofstream g("taie.out");
    f>>n;
    for(int i=1; i<=n; ++i) {
      f>>seg[i].x.x>>seg[i].x.y>>seg[i].y.x>>seg[i].y.y;
      p[++sz]=seg[i].x;
      p[++sz]=seg[i].y;
    }
//optimizari secrete aici
    for(int i=1; i<=sz; ++i)
      for(int j=i+1; j<=sz; ++j) {
        int ok=1;
        for(int k=1; k<=n; ++k) if(!((id(p[i],p[j],seg[k].x)<=0 && id(p[i],p[j],seg[k].y)>=0) ||(id(p[i],p[j],seg[k].x)>=0 && id(p[i],p[j],seg[k].y)<=0) )) {
          ok=0;
          break;
        }
        if(ok) {
          g<<fixed<<setprecision(9)<<p[i].x<<' '<<p[i].y<<' '<<p[j].x<<' '<<p[j].y<<'\n';
          return 0;
        }
      }
    g<<-1;
    return 0;
}
