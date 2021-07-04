/******************************************
Logistic map:
x_(n+1) = r * x_n *(1 - x_n)
x_n: ratio of existing population to the
maximum possible population
if r = 4 it's a nonlinear transformation
if r > 4 x_n is unbounded (exceed 1)
https://en.wikipedia.org/wiki/Logistic_map
******************************************/
#include <iostream>

#include "../include/Bignum.h"
#include "../include/Ratio.h"

using namespace std;

const int Nmax = 6;


int main()
{
	Ratio<Bignum> r(4), a(1); //constants
	Ratio<Bignum> x0(1,3); //initial value x0 = 1/3
	
	for(int i=0; i<Nmax; i++){
		cout << "x[" << i << "] = " << x0 << " or " << double(x0) << endl;
		x0 = r*x0*(a - x0); //update population size
	}
	cout << "x[" << Nmax << "] = " << x0 << " or " << double(x0) << endl;
	
	system("pause");
	
	return 0;
}
