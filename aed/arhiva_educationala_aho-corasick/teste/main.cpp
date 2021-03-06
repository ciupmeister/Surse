#include <cstdio>
#include <cstring>
#include <cctype>
#include <vector>
#define DL 1000005
#define DN 10005
#define DA 26
using namespace std;

int lg,n,l,final[DN],ic,sc;
char tx[DL],c[DN];

struct ac {
    vector<int> nd;
    int n0;
    ac *f[DA],*dl;
    ac() {
        n0=0;
        dl=NULL;
        memset(f,0,sizeof(f));
    }
} *q[DN*DN],*t,*p;


void ins(ac *t,char *p,int i) {
    if(!isalpha(*p)) {
        t->nd.push_back(i);
        return;
    }
    int urm=*p-'a';
    if(0==t->f[urm]) t->f[urm]=new ac;
    ins(t->f[urm],p+1,i);
}

void bfs(ac *t) {
    ac *dolar;
    t->dl=t;
    for(q[ic=sc=1]=t;ic<=sc;++ic) {
        ac *fr=q[ic];
        for(int i=0; i<DA; ++i) if(fr->f[i]!=NULL) {
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

int main(int argc,char *argv[])
{	int z;
	sscanf(argv[1],"%d",&z);
	fprintf(stderr,"%d",z);
	char fisin[50],fisout[50];
	sprintf(fisin,"grader_test%d.in",z);
	sprintf(fisout,"grader_test%d.ok",z);
    freopen(fisin,"r",stdin);
    freopen(fisout,"w",stdout);
    scanf("%s",tx);
    scanf("%d",&n);
    t=new ac;
    for(int i=1; i<=n; ++i) {
        scanf("%s",c);
        ins(t,c,i);
    }
    bfs(t);
    p=t;
    lg=strlen(tx);
    for(int i=0; i<lg; ++i) {
        int urm=tx[i]-'a';
        for(;p->f[urm]==NULL && p!=t;p=p->dl);
        if(p->f[urm]!=NULL) p=p->f[urm];
        ++p->n0;
    }
    antibfs(t);
    for(int i=1; i<=n; ++i) printf("%d\n",final[i]);
    return 0;
}
