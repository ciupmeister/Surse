/*
    Se da o stiva.
    Fiecare element are asociat un profit si un cost de a fi scos din stiva si nefolosit.
    Sa se determine profitul maxim de a alege k elemente

*/

#include <iostream>
#include <fstream>
#include <set>
#define DN 1000005
using namespace std;

int n,k,p[DN],c[DN],bst[DN],ssol,pt,rez;
multiset<int> sol,rst;

int main()
{
    ifstream f("ephie.in");
    ofstream g("ephie.out");
    f>>n>>k;
    for(int i=1; i<=n; ++i) f>>p[i]>>c[i];
    for(int i=1; i<=k; ++i) {
        pt+=p[i];
        rst.insert(p[i]+c[i]);
    }
    for(int i=k+1; i<=n; ++i) {
        pt+=p[i];
        rst.insert(p[i]+c[i]);
        ssol+=*rst.begin();
        sol.insert(*rst.begin());
        rst.erase(rst.begin());
        bst[i]=pt-ssol;
        rez=max(rez,bst[i]);
    }
    g<<rez;
    return 0;
}
