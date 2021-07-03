#include <iostream>

#include "Bignum.h"

using namespace std;


int main()
{	
	Bignum x;
	Bignum y(12345);
	Bignum z("31415926500000");
	
	x = 93;
	
	cout << "x     = " << x          << " parsec" << endl;
	cout << "y     = " << y          << " parsec" << endl;
	cout << "z     = " << z          << " parsec" << endl;
	cout << "z.len = " << z.length() << " cifre" << endl;
	cout << "x+y+z = " << x + y + z  << " parsec" << endl;
	cout << "z-x   = " << z - x      << " parsec" << endl;
	cout << "2*y   = " << 2 * y      << " parsec" << endl;
	cout << "y*z   = " << y * z      << " parsec^2" << endl;
	cout << endl;
	cout << div(Bignum("405465165846846984984"), Bignum("27498578684651684798")) << endl;
	cout << pow(Bignum("239462384682"), 64) << endl;
	
	cout << endl;
	cout << "x   = ";
	cin >> x;
	cout << "2*x = " << x + x << endl;
	cout << "x^2 = " << x * x << endl;
	
	cout << endl << endl;
	cout << "x   = ";
	cin >> x;
	cout << "y   = ";
	cin >> y;
	cout << "x+y = " << x+y << endl;
	cout << "x-y = " << x-y << endl;
	cout << "y-x = " << y-x << endl;
	cout << "x<y = " << ((x<y)?"vero":"falso") << endl;
	cout << "x>y = " << ((x>y)?"vero":"falso") << endl;
	cout << "x/y = " << x/y << endl;
	cout << "x%y = " << x%y << endl;
	
	
	
	system("pause");
	
	return 0;
}
