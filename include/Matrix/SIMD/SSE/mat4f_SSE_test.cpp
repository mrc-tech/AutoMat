#pragma GCC optimize("O3","unroll-loops","omit-frame-pointer","inline") //Optimization flags
#pragma GCC option("arch=native","tune=native","no-zeroupper") //Enable SSE
#pragma GCC target("sse")  //Enable SSE

#include <immintrin.h>
#include <iostream>

#include "mat4f_SSE.hpp"

using namespace std;



int main()
{
	Matrix A(4,4);
	
	return 0;
}
