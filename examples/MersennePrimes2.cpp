/********************************************************
Mersenne prime numbers:
M(n) = 2^n - i   where M(n) is prime
https://en.wikipedia.org/wiki/Mersenne_prime

for determining if is a Mersenne primes use the 
Lucas–Lehmer primality test:
https://en.wikipedia.org/wiki/Lucas-Lehmer_primality_test
********************************************************/
#include <iostream>
#include "../include/Bignum.h"
using namespace std;
typedef unsigned long long ulong64;

bool isPrime(Bignum);
bool LucasLehmerTest(Bignum);
Bignum pow2(Bignum);
void MersennePrimes(ulong64);


int main()
{
	MersennePrimes(1000);
	
	return 0;
}




bool isPrime(Bignum n) // function determines if the number n is prime.
{
    for(Bignum i=2; i*i<n; i++) if(n % i == 0) return false;
    return true;
}



bool LucasLehmerTest(Bignum p)
{
	// Determine if Mp = 2p - 1 is prime for p > 2
	if(p<=2) return isPrime(pow2(p)-1);
	Bignum s = 4;
	Bignum M = pow2(p) - 1;
	for(Bignum i=0; i<p-2; i++) s = ((s*s)-2) % M;
	if(s==0) return true; else return false;
}



Bignum pow2(Bignum n) // function returns 2 raised to power of n
{
    Bignum square=1;
    for(Bignum i=0; i<n; i++) square *= 2;
    return square;
}



void MersennePrimes(ulong64 Nmax)
{
    Bignum i;
    Bignum n;
	
    for(n=2; n<=Nmax; n++){
    	cout << "\rAnalyzing: n = " << n;
        if(isPrime(n)){
        	//exponent must be prime (can be demostrated)
            if(LucasLehmerTest(n)){
                // he found a Mersenne prime number
                cout << "\rM_{" << n << "} = " << pow2(n) - 1 << "                    " << endl;
            }
        }
    }
}


