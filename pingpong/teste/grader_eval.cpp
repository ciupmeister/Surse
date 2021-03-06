#include <cstdio>
#include <stdlib.h>


bool equals (double a, double b) {
	
	long long x, y;
	x = (long long) ( a * 1000.0);
	y = (long long) ( b * 1000.0 );

	//printf ("%lld %lld\n", x, y);
	return abs(x - y) <= 1;
}

int main () {                                
	
	FILE * out = fopen ("pingpong.out", "r");
	FILE * ok  = fopen ("pingpong.ok", "r");

	double outVal, okVal;
	fscanf (out, "%lf", &outVal);
	fscanf (ok, "%lf", &okVal);

	if (!equals (outVal, okVal)) {
		fprintf (stderr,"WRONG ANSWER!");
		printf("0");
	}
	else {
		fprintf (stderr,"OK!");
		printf("10");
	}

	return 0;
}
