#include <fstream>
#include <iostream>
#include <set>
#define DN 1000005
using namespace std;

int n,k,ssol,pt,rez,bst;
int p[DN],c[DN];
multiset<int> rst;

int main()
{
    ifstream f("ephie.in");
    ifstream g("ephie.out");
    f>>n>>k;
    for(int i=1; i<=n; ++i) f>>p[i]>>c[i];
    for(int i=1; i<=k; ++i) {
        pt+=p[i];
        rst.insert(p[i]+c[i]);
    }
    rez=max(rez,pt);
    for(int i=k+1; i<=n; ++i) {
        pt+=p[i];
        rst.insert(p[i]+c[i]);
        ssol+=*rst.begin();
        rst.erase(rst.begin());
        bst=pt-ssol;
        rez=max(rez,bst);
    }
	int rraz;
	g>>rraz;
    if(rraz!=rez) {
		cout<<rraz<<' '<<rez<<"gresit";
		cout.flush();
		while(1);
	}else cout<<"Bun\n";
    return 0;
}
