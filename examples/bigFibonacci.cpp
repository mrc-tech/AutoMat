/*********************************************
Fibonacci number: Fib(N) = Fib(N-1) + Fib(N-2)
		  with: Fib(0) = 0 & Fib(1) = 1
*********************************************/
#include <iostream>
#include <chrono>

#include "../include/Bignum.h"

using namespace std;

const int N = 10000; //index of Fibonacci number


int main()
{
	Bignum a = 0; // Fib(0)
	Bignum b = 1; // Fib(1)
	Bignum temp;
	
	cout << "Calculating...";
	
	chrono::high_resolution_clock::time_point now = chrono::high_resolution_clock::now();
	
	for(int i=2; i<=N; i++){
		temp = b;
		b = b + a; //update
		a = temp;
	}
	
	double time = chrono::duration_cast<chrono::duration<double>>(chrono::high_resolution_clock::now() - now).count();
	
	cout << "\rFib(" << N << ") = " << b << "\n[time: "<<time<<" s]" << endl;
	
	system("pause");
	
	return 0;
}

/*
 - fare in modo tale da far inserire N all'utente?
*/
