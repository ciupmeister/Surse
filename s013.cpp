#include <fstream>
#include <vector>
#include <bitset>
#define DN 2505
using namespace std;

typedef vector<int>::iterator it;

int n,m,l[DN],r[DN],ve[55][55],oz[55][55],cv,co;
char mt[55][55];
vector<int> gr[DN];
bitset<DN> viz;

int cupl(int s) {
	if(viz[s]) return 0;
	viz[s]=1;
	for(it i=gr[s].begin(); i!=gr[s].end(); ++i) if(r[*i]==0 || cupl(r[*i])) {
		l[s]=*i; r[*i]=s;
		return 1;
	}
	return 0;
}

int main() {
	ifstream f("s013.in");
	ofstream g("s013.out");
	f>>n>>m;
	for(int i=1; i<=n; ++i) for(int j=1; j<=m; ++j) f>>mt[i][j];
	for(int i=1; i<=n; ++i) for(int j=1; j<=m; ++j) if(mt[i][j]=='*')
		if(mt[i][j-1]=='*') oz[i][j]=co;
		else oz[i][j]=++co;
	for(int j=1; j<=m; ++j) for(int i=1; i<=n; ++i) {
		if(mt[i-1][j]!='*') ++cv;
		gr[oz[i][j]].push_back(cv);
	}
	
	for(int ok=1;ok;) {
		ok=0; viz&=0;
		for(int i=1; i<=co; ++i) if(!l[i]) ok|=cupl(i);
	}
	int r=0;
	for(int i=1; i<=co; ++i) r+=(l[i]>0);
	g<<r;
	return 0;
}