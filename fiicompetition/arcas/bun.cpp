#include <cstdio>
int arcasi[2][100005];
int ord[200005];
 
int main (){
        int n,tu,r,i,poz,ok=0,j,t,aux,tintaf,tintac,pozf;
	freopen("arcas.in","r",stdin);
	freopen("arcas.out","w",stdout);
        scanf("%d %d",&n,&r);
        tintaf=n;
        scanf("%d",&tu);
        for(i=1;i<=2*n-1;++i)scanf("%d",&ord[i]);
        if(tu==1){
                printf("%d",n);
                return 0;
        }
        if(tu>n+1){
                for(i=3;ord[i]>tu;){
                        i+=2;
                        
                }
                tintac=(i+1)/2;
                tintaf=tintac;
                //printf("%d ",tintaf);
                for(i=tintac*2+1;ord[i]>tu;){
                        tintaf=(i+1)/2;
                        //printf("i=%d ",i);
                        //printf("%d",tintaf);
                        i+=2;
                }
                
                printf("%d",tintaf);
                return 0;
        }
        
}
