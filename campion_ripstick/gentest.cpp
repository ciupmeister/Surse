#include <fstream>
#include <algorithm>
#include <ctime>
#include <cstdlib>
#define DN 10000
#define DV 1000000000
using namespace std;

int main()
{
	ofstream g("ripstick.in");
	srand(time(NULL));
	/*int n=rand()%DN+1;
	int a=rand()%DV+1;
	int b=rand()%DV+1;
	if(a>b) swap(a,b);
	g<<n<<' '<<a<<' '<<b<<'\n';
	for(int i=1; i<=n; ++i) g<<rand()%20001-10000<<' ';*/
	g<<"100000 1 1000000000\n";
	for(int i=1; i<=100000; ++i) g<<"10000 ";
	return 0;
}

