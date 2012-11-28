#include <fstream>
#include <bitset>
#define DN 260
using namespace std;

int n,m,ramase,
        a[DN][DN],//matricea de adiacenta
        grad[DN],//gradul fiecarui nod
        ntri[DN][DN],//pentru nodurile dominate
	p[DN]
        ;
bitset<DN> out;

void rezolva() {
    int i,j;
    bool ok=true;
    int k,l;
    ramase=n;
    for (i=1;i<=n ;++i)p[i]=i;
	out&=0;
    for(;ramase>1 && ok;) {
        ok=false;
        for (i=1; i<=ramase && !ok; ++i)
        	for (j=1; j<=ramase && !ok ;++j)
                if (i != j && a[p[i]][p[j]])
                    if (ntri[p[i]][p[j]] == grad[p[i]] - 1) {
                        out[p[i]] = 1;//scoatem nodul i daca i este dominat de j
                        ///<actualizari>
                        for (k = 1; k <= ramase; ++k)//si actualizam gradul fiecarui nod
                            if (a[p[k]][p[i]])
                                grad[p[k]]--;
                        for (k = 1; k <= ramase; ++k)
                            for (l = k + 1; l <= ramase; ++l)
                                if (a[p[k]][p[l]] && a[p[k]][p[i]] && a[p[l]][p[i]])
                                    --ntri[p[k]][p[l]], --ntri[p[l]][p[k]];//actualizam nodurile dominate
                        ///</actualizari>
                        ok=true;
                        --ramase;
                        break;
                    }
            for (i = 1,j=0; i <= n; i++)
                if (!out[i])
                    p[++j] = i;
    }

}

int main()
{
    int t,k,i,j;
	ifstream f("tj.in");
	ofstream g("tj.out");
	for(f>>t; t--; ) {
	    f>>n>>m;
	    for(int i=0; i<=n; ++i) {
		for(int j=0; j<=n; ++j) a[i][j]=ntri[i][j]=0;
		grad[i]=0;
	    }
		for(k=1; k<=m; k++) {
		    f>>i>>j;
		    a[i][j]=a[j][i]=1;
		    ++grad[i],++grad[j];
		}
		for (i = 1; i <=n; ++i)
			for (j = 1; j <= n; ++j)
				if (i != j && a[i][j])//avem muchie de la i la j
					for (k = 1; k <= n; ++k)
						if (i != k && j != k && a[i][k] && a[j][k])//i este dominat
							++ntri[i][j];
        rezolva();
        if(ramase>1) g<<"NU\n";
        else g<<"DA\n";
	}
	return 0;
}
