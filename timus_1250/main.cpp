#include <iostream>
#define DN 505
#pragma comment(linker, "/STACK:16777216")
using namespace std;

int n,m,sx,sy,rez;
char mp[DN][DN];
int st[DN][DN],dr[DN][DN],sus[DN][DN],jos[DN][DN],viz[DN][DN],ret[DN][DN];
const int dx[]={1, 0,-1, 0,-1,-1,1, 1};
const int dy[]={0,-1, 0, 1,-1, 1,1,-1};

bool check(int a, int b) {
    return (a>0 && b>0 && a<=n && b<=m);
}

void sacru(int x, int y) {
    mp[x][y]=1;
    for(int d=0; d<8; ++d) {
        int ii=x+dx[d],jj=y+dy[d];
        if(check(ii,jj) && '.'==mp[ii][jj]) sacru(ii,jj);
    }
}

int fill(int i, int j) {
    ret[i][j]=1;
    if(viz[i][j]) return ret[i][j];
    viz[i][j]=1;
    if(!(st[i][j]&dr[i][j]&sus[i][j]&jos[i][j])) {
        ret[i][j]=0;
        return 0;
    }
    int ok=1;
    for(int d=0; d<4; ++d) {
        int ii=i+dx[d],jj=j+dy[d];
        if(check(ii,jj) && '#'==mp[ii][jj]) ok&=fill(ii,jj);
    }
    ret[i][j]=ok;
    return ok;
}

int main()
{
    cin>>m>>n>>sx>>sy;
    for(int i=1; i<=n; ++i) cin>>mp[i]+1;
    swap(sx,sy);
    //if('#')
    sacru(sx,sy);
    for(int i=1; i<=n; ++i) for(int j=1; j<=m; ++j) if(1==mp[i][j]) {
        for(int k=j+1;k<m && !st[i][k];st[i][k]=1,++k);
        for(int k=j-1;k>1 && !dr[i][k];dr[i][k]=1,--k);
        for(int k=i+1;k<n && !sus[k][j];sus[k][j]=1,++k);
        for(int k=i-1;k>1 && !jos[k][j];jos[k][j]=1,--k);
    }
    for(int i=2; i<n; ++i)
        for(int j=2; j<m; ++j) if(!viz[i][j] && '#'==mp[i][j]) {
            //cout<<i<<' '<<j<<' '<<fill(i,j)<<":::::\n";
            rez+=fill(i,j);
        }
    /*for(int i=1; i<=n; ++i) {
        for(int j=1; j<=m; ++j) cout<<ret[i][j];
        cout<<'\n';
    }*/
    cout<<rez;
    return 0;
}
