#pragma GCC optimize("O3","unroll-loops","omit-frame-pointer","inline") //Optimization flags
#pragma GCC option("arch=native","tune=native","no-zeroupper") //Enable AVX
#pragma GCC target("avx")  //Enable AVX

#include <immintrin.h>
#include <iostream>

#include "vec256f.h" // 256-bit packed 32-bit sigle precision floating point numbers class

using namespace std;

int main()
{
	vec256f a;
	vec256f b(2.0f);
	vec256f c(1.4f, 3.3f, -12.5f, -33.4f, 7.9f, -70.2f, 15.1f, 22.6f);
	
	cout << "a    = " << a << endl;
	cout << "b    = " << b << endl;
	cout << "c    = " << c << endl;
	cout << "c[2] = " << c[2] << endl;
	cout << "b+c  = " << b+c << endl;
	cout << "b-c  = " << b-c << endl;
	cout << "b*c  = " << b*c << endl;
	cout << "b/c  = " << b/c << endl;
	
	cout << "round(c)    = " << round(c)    << endl;
	cout << "truncate(c) = " << truncate(c) << endl;
	cout << "floor(c)    = " << floor(c)    << endl;
	cout << "ceil(c)     = " << ceil(c)     << endl;
	
	return 0;
}
