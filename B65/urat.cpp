//cat de slab :))
#include <cstdio>
#include <cstdlib>
#define DN 500005
#define MOD 543217
#define deb(n) fprintf(stderr,"%d ",(n));
#define debnl fprintf(stderr,"\n");

int n,f[DN],rez[DN],ptr=1;
long long g[DN];

int main()
{
    freopen("urat.in","r",stdin);
    freopen("urat.out","w",stdout);
    scanf("%d",&n);
    g[1]=0; f[1]=1;
    g[2]=1; f[2]=2;
    for(int i=3; i<=n; ++i) {
        if(i&1) {
            g[i]=g[i-1]+i-1;
            f[i]=(f[i-1]*1LL*(i-1))%MOD;
        }else {
            g[i]=g[i-1]+i;
            f[i]=(f[i-2]*1LL*(ptr*1LL*ptr)%MOD)%MOD;
            ++ptr;
        }
        //deb(g[i]) deb(f[i]) debnl
    }
    rez[1]=n/2; rez[n]=n/2+1;
    printf("%lld\n%d\n",g[n],f[n]);
    if(n>3) {
        int cnt=0;
        for(int i=3; i<n; i+=2) rez[i]=++cnt;
        cnt=n/2+1;
        for(int i=2; i<n; i+=2) rez[i]=++cnt;
    }else {
        if(n==3) printf("1 3 2");
        else if(n==2) printf("1 2");
        return 0;
    }
    for(int i=1; i<=n; ++i) printf("%d ",rez[i]);
    //debug
    /*int sdif=0;
    for(int i=2; i<=n; ++i) sdif+=abs(rez[i]-rez[i-1]);
    if(sdif!=g[n]) {
        fprintf(stderr,"eroare!!!!!%d %d",sdif,g[n]);
        while(1);
    }*/
    return 0;
}
