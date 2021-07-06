#pragma GCC optimize("O3","unroll-loops","omit-frame-pointer","inline") //Optimization flags
//#pragma GCC option("arch=native","tune=native","no-zeroupper") //Enable AVX
#pragma GCC target("avx")  //Enable AVX

#include <immintrin.h>
#include <iostream>
#include <chrono>
#include <vector>

#include "v8f.h" // 256-bit packed 32-bit sigle precision floating point numbers wrapper vector class

using namespace std;

int main()
{
	vector<float> A, B, C;
	v8f a, b, c;
	
	for(int i=0;i<1000;i++) A.push_back(1.0f);
	for(int i=0;i<1000;i++) B.push_back(2.0f);
	
	a = A;
	b = B;
	
	chrono::high_resolution_clock::time_point now = chrono::high_resolution_clock::now();
	//==============================
	for(int i=0;i<A.size();i++) C.push_back(A[i] + B[i]);
	//==============================
	double time = chrono::duration_cast<chrono::duration<double>>(chrono::high_resolution_clock::now() - now).count();
	cout << "LIN time: " << time << endl;
	
	now = chrono::high_resolution_clock::now();
	//==============================
	c = a + b;
	//==============================
	time = chrono::duration_cast<chrono::duration<double>>(chrono::high_resolution_clock::now() - now).count();
	cout << "AVX time: " << time << endl;
	
	
	for(int i=0;i<c.size();i++) cout << c[i]; cout << endl;
	
	return 0;
}
