#include <fstream>
#include <ctime>
#include <cstdlib>
#define N 20000
using namespace std;

int main()
{
	ofstream g("ripstick.in");
	srand(time(NULL));
	g<<N<<" 1 1000000000\n";
	for(int i=1; i<=N; ++i) g<<rand()%20001-10000<<' ';
	return 0;
}

