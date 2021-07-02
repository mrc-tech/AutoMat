#include <iostream>
#include <string>

#include "Bignum.h"
#include "Ratio.h"

using namespace std;



int main()
{
	Ratio<short> r(4,3);
	
	cout << r << endl;
	if(r.den()!=0) cout << (double)r.num()/r.den() << endl;
	cout << (double)r << endl;
	
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
	
	cout << (double)(a*b)-b << endl;
	
	Ratio<Bignum> big(2725466,382672);
	using std::operator<<; //LEZZATA CAUSATA DALL'OVERLOAD DELL'OPERATORE<< (per la classe Ratio)
	cout << "gcd(" << big << ") = " << gcd(big.num(), big.den()) << endl;
	big.normalize();
	cout << big << endl;
	
	Ratio<Bignum> veryBig = Ratio<Bignum>(Bignum("2349023749283492376492374923"),Bignum("4823492384923"));
	cout << veryBig << endl;
	cout << veryBig * veryBig << endl;
	
	return 0;
}
