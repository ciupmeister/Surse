#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>
using namespace std;

char in[55],ou[55];
string s1,s2,rez;
int n;

int main() {
	srand(time(NULL));
	for(int i=1; i<=10; ++i) {
		sprintf(in,"grader_test%d.in",i);
		sprintf(ou,"grader_test%d.ok",i);
		n=i*10;
		s1.clear(); s2.clear(); rez.clear();
		for(int i=0; i<n; ++i) {
			s1+=rand()%2+'0';
			s2+=rand()%2+'0';
			rez+=((s1[i]-'0')^(s2[i]-'0'))+'0';
		}
		
		ofstream f(in);
		ofstream g(ou);
		f<<s1<<'\n'<<s2;
		g<<rez;
	}
}
