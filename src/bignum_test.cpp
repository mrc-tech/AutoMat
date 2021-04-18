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


	system("pause");
	

	// calcola Fibonacci:	
//	Bignum temp;
//	Bignum n1 = 1;
//	Bignum n2 = 1;
//	for(int i=0;i<1000;i++){
//		cout << n2 << endl;
//		temp = n2;
//		n2 = n2 + n1; //aggiorna 
//		n1 = temp;
//	}

	
	return 0;
}
