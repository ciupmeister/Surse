#include <cstdio>
#include <cmath>
int main () {
        double t,p,b,d;
        double s,k;
        freopen("video.in","r",stdin);
        freopen("video.out","w",stdout);
        scanf("%lf %lf %lf %lf",&d,&b,&t,&p);
        //fprintf(stderr,"%lf",(double)(b*t-t*d)/(d*p));
        k=(double)(b*t-t*d)/(d*p);
        //fprintf(stderr,"%lf\n",k);
        int a=k;
        if(a<k)k=a+1;
        //fprintf(stderr,"%lf",k);
        s=(double)(b-d)*t/k;
        ceil(s);
        int aux=s;
        if(aux<s)++aux;
        printf("%d",aux);
        return 0;
}
