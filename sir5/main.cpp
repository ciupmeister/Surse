#include <iostream>
#include <fstream>
#include <cstring>
#define DN 105
#define MOD 666013
using namespace std;

int n,l,a,mt[DN][DN],rez[DN][DN],aux[DN][DN],pot[DN][DN],v[DN]={1},lst=1,vr[DN],anxt,tot;
int as[DN],tp[DN],sz;

ifstream f("sir5.in");
ofstream g("sir5.out");

void preproc() {
  for(int i=1; i<=n; ++i) {
    f>>a;
    for(;a && tot<l; ++tot,--a) {
      v[tot+1]=vr[tot+1]=v[tot];
      if(tot+1==l && (i&1)) ++v[tot+1],++vr[tot+1];
    }
    if(a) {
      as[++sz]=a;
      tp[sz]=i&1;
    }
  }
}

void inm(int a[DN][DN],int b[DN][DN],int r[DN][DN]) {
    for(int i=1; i<=l; ++i) for(int j=1; j<=l; ++j) {
        int c=0;
        for(int k=1; k<=l; ++k) c=(c+1LL*a[i][k]*b[k][j])%MOD;
        r[i][j]=c;
    }
}

void lgput(int e) {
    int c[DN][DN];
    e=max(0,e);
    memset(rez,0,sizeof(rez));
    memcpy(c,pot,sizeof(pot));
    for(int i=1; i<=l; ++i) rez[i][i]=1;
    for(int i=0; (1<<i)<=e; ++i) {
        if((1<<i)&e) {
            inm(rez,c,aux);
            memcpy(rez,aux,sizeof(rez));
        }
        inm(c,c,aux);
        memcpy(c,aux,sizeof(aux));
    }
}

void inmv(){
  memset(vr,0,sizeof(vr));
  for(int i=1; i<=l; ++i) for(int j=1; j<=l; ++j) vr[i]=(vr[i]+1LL*v[j]*rez[i][j])%MOD;
}

int main()
{
    f>>n>>l;

    preproc();
    for(int i=1; i<l; ++i) pot[i][i+1]=1;
    pot[l][1]=pot[l][l]=1;

    for(int i=1; i<=sz; ++i) {
      a=as[i];
      if(tp[i]&1){
        lgput(a);
        inmv();
        for(int k=1; k<=l; ++k) v[k]=vr[k];
      }else {
        int ultPoz=min(l-1,a);
        for(int j=1; j<=ultPoz; ++j) v[l+j]=(v[l+j-1]+v[j])%MOD;
        for(int j=1; j<=l; ++j) v[j]=v[j+ultPoz];
        int ram=a-ultPoz,li=1;
        for(int j=1; j<=l; ++j)
          if(j+ram<=l) v[j]=v[j+ram];
          else v[j]=v[l];
      }
    }
    g<<v[l];
    return 0;
}
