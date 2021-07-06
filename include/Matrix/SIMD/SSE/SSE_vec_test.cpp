#pragma GCC optimize("O3","unroll-loops","omit-frame-pointer","inline") //Optimization flags
#pragma GCC option("arch=native","tune=native","no-zeroupper") //Enable SSE
#pragma GCC target("sse")  //Enable SSE

#include <immintrin.h>
#include <iostream>

#include "vec128f.h" // 128-bit packed 32-bit float numbers class



using namespace std;

int main()
{
	vec128f a;
	vec128f b(2.0f);
	vec128f c(1.4f, 3.3f, -12.5f, 7.9f);
	
	cout << "a    = " << a << endl;
	cout << "b    = " << b << endl;
	cout << "c    = " << c << endl;
	cout << "c[1] = " << c[1] << endl;
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
