#include <fstream>
#include <cstdlib>
#include <ctime>
#define DN 32
using namespace std;

int n;

int main()
{
	srand(time(NULL));
	ofstream g("joc.in");
	n=rand()%DN+1;
	g<<n<<'\n';
	for(int i=1; i<=n; ++i) 
		if(i==1) g<<0<<' '<<rand()%101<<'\n';
		else g<<rand()%101<<' '<<rand()%101<<'\n';
	return 0;
}
