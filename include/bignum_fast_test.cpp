#include <iostream>

#include "Bignum_fast.h"

using namespace std;



int main()
{
	Bignum n1 = 0;
	Bignum n2 = 1;
	Bignum temp;
	
	for(int i=0;i<1;i++){
		temp = n2;
		n2 = n1 + n2;
		n1 = temp;
	}
	
	cout << n2 << endl;
	
	return 0;
}
