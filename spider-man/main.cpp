#include <iostream>
#include <iomanip>
#include <fstream>
#include <cmath>
#define x first
#define y second
using namespace std;

typedef pair<double,double> per;

double xc,yc,r;
per a,b,z;

double dist(per a, per b) {
  return (b.x-a.x)*(b.x-a.x)+(b.y-a.y)*(b.y-a.y);
}

double f(double u) {
  per c;
  c.x=r*cos(u); c.y=r*sin(u);
  return dist(a,c)+dist(c,b);
}

int main()
{
    ifstream fi("spider-man.in");
    ofstream g("spider-man.out");
    fi>>xc>>yc>>r;
    fi>>a.x>>a.y>>b.x>>b.y;
    a.x-=xc; a.y-=yc;
    b.x-=xc; b.y-=yc;
    double ls=0.00000000001,ld=2*acos(-1),ts,td;
    for(;fabs(ld-ls)>=0.000001;) {
      ts=(2.0*ls+ld)/3.0;
      td=(ls+2.0*ld)/3.0;
      if(f(ts)<f(td)) ld=td;
      else ls=ts;
    }
    g<<fixed<<setprecision(9)<<f(ts);
    return 0;
}
