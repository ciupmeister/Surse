//Normalizare + 2 caractere
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#define DN 10005
#define x first
#define y second
using namespace std;

int n,m,k;
long long rez;
string cc,cnou,s[DN];
pair<int,pair<char,char> > fin[DN];

int main()
{
    ifstream f("lexic.in");
    ofstream g("lexic.out");
    f>>n>>m>>k;
    int N=0;
    for(int i=0; i<=k; ++i) s[0]+='-';
    for(int i=1; i<=n; ++i) {
        f>>cc;
        cnou.clear();
        if(cc.size()<k) continue;
        for(int i=0; i<k; ++i) cnou+=cc[i];
        for(int i=cc.size()-1; i>=cc.size()-k; --i) cnou+=cc[i];
        if(cc.size()>k) {
            cnou+=cc[k];
            cnou+=cc[cc.size()-k-1];
        }
        s[++N]=cnou;
    }
    n=N;
    sort(s+1,s+n+1);
    for(int i=1; i<=n; ++i) {
        fin[i].x=fin[i-1].x;
        string s1,s2;
        for(int j=0; j<2*k; ++j) s1+=s[i][j],s2+=s[i-1][j];
        if(s1.compare(s2)) ++fin[i].x;

        if(s[i].size()>k) {
            fin[i].y.x=s[i][s[i].size()-2];
            fin[i].y.y=s[i][s[i].size()-1];
        }else fin[i].y.x=fin[i].y.y=-1;
    }
    long long nrf=1;//cate familii am
    int dim=0,nrg=1;//cate am in fiecare familie si cate am gresite
    for(int i=2; i<=n; ++i) {
        if(fin[i].x!=fin[i-1].x) {
            nrf*=1LL*nrg;
            if(dim)rez+=nrf;
            dim=0; nrf=nrg=1;
            continue;
        }
        if(fin[i].y.x==-1 || fin[i-1].y.x==-1 || fin[i].y.x!=fin[i-1].y.x || fin[i].y.y!=fin[i-1].y.y) {
               ++dim;
               nrf*=nrg;
               nrg=1;
        } else ++nrg;
    }
    if(dim) {
        nrf*=1LL*nrg;
        rez+=nrf;
    }
    g<<rez;
    return 0;
}
