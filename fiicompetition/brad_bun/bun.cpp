#include <iostream>
#include <fstream>
using namespace std;

int n;

int count(int n) {
	int num=0;
	do {
		++num;
	}while(n&=(n-1));
	return num;
}

int main()
{
    ifstream f("brad.in");
    ifstream g("brad.out");
    f>>n;
    int nrb=count(n)-1;
    int rc=(1<<nrb),rb;
    g>>rb;
    if(rc!=rb) {
        cout<<"gresit"<<rb<<' '<<rc;
        cout.flush();
        while(1);
    }
    cout<<"corect\n";
    return 0;
}
