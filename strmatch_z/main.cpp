#include <fstream>
#include <algorithm>
#include <string>
using namespace std;

string a,b;
int z[4000000],l,r,k,m,poz[1005],sz;

int main()
{
    ifstream f("strmatch.in");
    ofstream g("strmatch.out");
    f>>a>>b;
    m=a.size();
    a+='$'; a.append(b);
    int n=a.size();
    for(int i=1; i<n; ++i) {
      if(i>r) {
        l=r=i;
        for(;r<n && a[r-l]==a[r];++r);
        z[i]=r-l; --r;
      }else {
        int k=i-l;
        if(z[k]<r-i+1) z[i]=z[k];
        else {
          l=i;
          for(;r<n && a[r-l]==a[r];++r);
          z[i]=r-l; --r;
        }
      }
      if(z[i]==m) {
        ++sz;
        if(sz<=1000) poz[sz]=i-m-1;
      }
    }
    g<<sz<<'\n';
    for(int i=1; i<=min(sz,1000); ++i) g<<poz[i]<<' ';
    return 0;
}
