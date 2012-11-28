#include <cstdio>
#include <cstring>
#include <cctype>
#include <vector>
#define DL 100005
#define DN 1005
using namespace std;

int lg,n,l,final[DN],ic,sc;
char tx[DL],c[DN];

struct ac {
    vector<int> nd;
    int n0;
    ac *f[2],*dl;
    ac() {
        n0=0;
        f[0]=f[1]=dl=NULL;
    }
} *q[DN*DN],*t,*p;


void ins(ac *t,char *p,int i) {
    if(!isdigit(*p)) {
        t->nd.push_back(i);
        return;
    }
    int urm=*p-'0';
    if(0==t->f[urm]) t->f[urm]=new ac;
    ins(t->f[urm],p+1,i);
}

void bfs(ac *t) {
    ac *dolar;
    t->dl=t;
    for(q[ic=sc=1]=t;ic<=sc;++ic) {
        ac *fr=q[ic];
        for(int i=0; i<2; ++i) if(fr->f[i]!=NULL) {
            for(dolar=fr->dl;dolar!=t && dolar->f[i]==NULL;dolar=dolar->dl);
            if(dolar->f[i]!=NULL && dolar->f[i]!=fr->f[i]) dolar=dolar->f[i];
            fr->f[i]->dl=dolar;
            q[++sc]=fr->f[i];
        }
    }
    t->dl=NULL;
}


void antibfs(ac *t) {
    for(int i=sc; i>0; --i) {
        ac *fr=q[i];
        if(fr->dl!=NULL) fr->dl->n0+=fr->n0;
        for(int j=0; j<fr->nd.size(); ++j) final[fr->nd[j]]=fr->n0;
    }
}

int main()
{
    freopen("virus.in","r",stdin);
    freopen("virus.out","w",stdout);
    scanf("%d %d",&lg,&n);
    scanf("%s",tx);
    t=new ac;
    for(int i=1; i<=n; ++i) {
        scanf("%d %s",&l,c);
        ins(t,c,i);
    }
    bfs(t);
    p=t;
    for(int i=0; i<lg; ++i) {
        int urm=tx[i]-'0';
        for(;p->f[urm]==NULL && p!=t;p=p->dl);
        if(p->f[urm]!=NULL) p=p->f[urm];
        ++p->n0;
    }
    antibfs(t);
    for(int i=1; i<=n; ++i) printf("%d\n",final[i]);
    return 0;
}

