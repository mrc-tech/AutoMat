#pragma GCC optimize("O3","unroll-loops","omit-frame-pointer","inline") //Optimization flags
#pragma GCC option("arch=native","tune=native","no-zeroupper") //Enable SSE
#pragma GCC target("sse")  //Enable SSE

#include <immintrin.h>
#include <iostream>

#include "vec128f.h" // 128-bit packed 32-bit float numbers class
#include "vec128d.h" // 128-bit packed 64-bit double numbers class
//ATTENZIONE! RIDEFINIIZONE DI NBITS E NVARS PER I VETTORI DI DIFFERENTI VARIABILI!!!!


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
	
	
	
	vec128d A(2.0);
	vec128d B(-12.5, 7.9);
	
	cout << "A    = " << A << endl;
	cout << "B    = " << B << endl;
	cout << "B[1] = " << B[1] << endl;
	cout << "A+B  = " << A+B << endl;
	cout << "A-B  = " << A-B << endl;
	cout << "A*B  = " << A*B << endl;
	cout << "A/B  = " << A/B << endl;
	
	cout << "round(B)    = " << round(B)    << endl;
	cout << "truncate(B) = " << truncate(B) << endl;
	cout << "floor(B)    = " << floor(B)    << endl;
	cout << "ceil(B)     = " << ceil(B)     << endl;
	
	
	return 0;
}
