#include <iostream>
#include <chrono>

#include "Bignum_fast.h"

using namespace std;

const int N = 10000;



int main()
{
	Bignum n1 = 0; // Fib(0)
	Bignum n2 = 1; // Fib(1)
	Bignum temp;
	
	chrono::high_resolution_clock::time_point now = chrono::high_resolution_clock::now();
	
	for(int i=2; i<=N; i++){
		temp = n2;
		n2 = n1 + n2;
		n1 = temp;
	}
	
	double time = chrono::duration_cast<chrono::duration<double>>(chrono::high_resolution_clock::now() - now).count();
	
	cout << "Fib("<<N<<") = " << n2 << "\n[time: "<<time<<" s]";
	
	cin.get();
	
	return 0;
}
