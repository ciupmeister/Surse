#include <cstdio>
#include <cstring>
#include <iostream>
#define DN 100005
using namespace std;

char tx[DN];
int t,dp[DN],tip[DN];

int main()
{
	scanf("%d\n",&t);
		scanf("%s",tx);
		printf("%s",tx);
		int n=strlen(tx);
		int ns,cont,lst,d,twalk;
		ns=cont=0;
		for(int i=0; i<n; ++i) if('<'==tx[i]) {
			++cont;
			if(0==ns) {
				tip[0]=1;
				dp[0]=i;
				++ns;
				lst=i;
			}else {
				d=i-lst-1;
				lst=i;
				if(cont==i+1) continue;
				twalk=0;
				for(;0<ns && 0<d;) {
					if(1==tip[ns-1]) {
						twalk+=dp[ns-1];
						--ns;
					}else if(dp[ns-1]<=d) {
						twalk+=dp[ns-1];
						d-=dp[ns-1];
						--ns;
					}else {
						twalk+=d;
						dp[ns-1]-=d;
						d=0;
					}
				}
				if(0==d) {
					if(0<ns && 0==dp[ns-1]) ++dp[ns-1];
					else {
						tip[ns]=0;
						dp[ns]=1;
						++ns;
					}
				}
				twalk+=d;
				if(0<twalk) {
					tip[ns]=1;
					dp[ns]=twalk;
					++ns;
				}

			}
		}
		int rez=0;
		printf("%d\n",ns);
		for(;ns--;) rez+=dp[ns];

	return 0;
}
