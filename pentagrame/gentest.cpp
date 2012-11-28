#include <fstream>
#include <cstdlib>
#include <ctime>
using namespace std;

int n=50000,m=50000;

int main() {
	srand(time(NULL));
	ofstream g("pentagrame.in");
	g<<n<<' '<<m<<'\n';
	for(int i=1; i<=n; ++i) {
		for(int j=0; j<5; ++j) g<<char(rand()%27+'A');
		g<<'\n';
	}
	for(int i=1; i<=m; ++i) {
		for(int j=0; j<30; ++j) g<<char(rand()%27+'A');
		g<<'\n';
	}
	return 0;
}
