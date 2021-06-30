/*******************************************
Mersenne prime numbers:
M(n) = 2^n - i   where M(n) is prime
https://en.wikipedia.org/wiki/Mersenne_prime
*******************************************/
#include <iostream>
#include "../include/Bignum.h"
using namespace std;
typedef unsigned long long ulong64;

bool isPrime(Bignum);
Bignum pow2(Bignum);
void MersennePrimes(ulong64);


int main()
{
	MersennePrimes(1000);
	
	return 0;
}




bool isPrime(Bignum n) // function determines if the number n is prime. (IT TAKES TOO LONG!!)
{
    for(Bignum i=2; i*i<n; i++) if(n % i == 0) return false;
    return true;
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
            i = pow2(n) - 1;
            if(isPrime(i)){
                // he found a Mersenne prime number
                cout << "\rM_{" << n << "} = " << i << "                    " << endl;
            }
        }
    }
}


