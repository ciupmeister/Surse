#include <fstream>
using namespace std;

int main() {
	ofstream g("intfm.in");
	g<<"2000\n";
	for(int i=0; i<2000; ++i) g<<5*i<<' '<<5*(i+1)<<'\n';
}
