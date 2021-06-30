#include <iostream>

#include "../include/Bignum.h"

using namespace std;

const int N = 10000; //index of Fibonacci number


int main()
{
	Bignum a = 1; // Fib(0)
	Bignum b = 1; // Fib(1)
	Bignum temp;
	
	cout << "Calculating...";
	
	for(int i=1; i<N; i++){
		temp = b;
		b = b + a; //update
		a = temp;
	}
	
	cout << "\rFib(" << N << ") = " << b << endl;
	
	system("pause");
	
	return 0;
}

/*
 - fare in modo tale da far inserire N all'utente?
*/
