#include <iostream>

#include "Ratio.h"
//#include "Bignum.h"

using namespace std;



int main()
{
	Ratio<short> r(4,3);
	
	cout << r << endl;
	if(r.den()!=0) cout << (double)r.num()/r.den() << endl;
	
	cout << r + Ratio<short>(2,17) << endl;
	cout << r - Ratio<short>(2,17) << endl;
	cout << r * Ratio<short>(2,17) << endl;
	cout << r / Ratio<short>(2,17) << endl;
	
	Ratio<int> a(2,3), b(1,5);
	
	cout << (a == b) << endl;
	cout << (a != b) << endl;
	cout << (a <  b) << endl;
	cout << (a >  b) << endl;
	cout << (a <= b) << endl;
	cout << (a >= b) << endl;
	
	
	
	return 0;
}
