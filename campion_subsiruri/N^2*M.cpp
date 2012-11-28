#include <cstdio>
#include <fstream>
#define DN 1005
#define MOD 666013
#define deb(n) fprintf(stderr,"%d ",(n));
#define debnl fprintf(stderr,"\n");
using namespace std;

int n,m,a,b,v[DN],dp[DN][DN],rez;

bool cmp(const int &a, const int &b) {
    return v[a]<v[b];
}

int main()
{
    freopen("subsiruri.in","r",stdin);
    ifstream f("subsiruri.out");
    scanf("%d %d %d %d",&n,&m,&a,&b);
    for(int i=1; i<=n; ++i) {
        scanf("%d",&v[i]);
        ++dp[i][v[i]%m];
    }
    for(int i=1; i<=n; ++i) for(int mod=0; mod<m; ++mod) {
        for(int j=1; j<i; ++j) if(v[i]>=v[j]) {
		dp[i][(mod+v[i])%m]+=dp[j][mod];
		if(dp[i][(mod+v[i])%m]>=MOD) dp[i][(mod+v[i])%m]-=MOD;
	}
    }
    for(int i=1; i<=n; ++i) for(int mod=a; mod<=b; ++mod) {
	rez+=dp[i][mod];
	if(rez>=MOD) rez-=MOD;
    }
	int rf;
    f>>rf;
	if(rf!=rez) {
		printf("EROARE!\n%d %d\n",rf,rez);
		while(1);
	}else printf("OK\n");
    //deb(rez)
    return 0;
}
