#pragma GCC optimize("O3","unroll-loops","omit-frame-pointer","inline") //Optimization flags
#pragma GCC option("arch=native","tune=native","no-zeroupper") //Enable SSE
#pragma GCC target("sse")  //Enable SSE

#include <immintrin.h>
#include <iostream>
#include <cmath>

#include "vec128f.h"


class v4f
{
	private:
		vec128f * v; //data vector
		unsigned _size; //vector size
		float * remain; //remained data FARE CON UN ALTRO CHUNK MEZZO VUOTO????
	public:
		v4f();
		v4f(unsigned size);
		v4f(unsigned size, float value);
		~v4f();
		
		//element access
		const float operator [] (const unsigned& index) const; //getter
		float& operator [] (const unsigned& index); //setter
		
		//getters
		inline unsigned size() { return _size; }
		
	private:
		inline unsigned chunk_size() const { return std::floor(_size/NVARS); }
		inline unsigned remaining_size() const { return _size - chunk_size()*NVARS; }
};



v4f::v4f(unsigned size, float value)
{
	_size = size; //salva la dimensione del vettore
	v = new vec128f[chunk_size()]; //alloca la memoria
	for(int i=0;i<chunk_size();i++) v[i] = vec128f(value); //setta il valore iniziale
	remain = new float[remaining_size()]; //alloca la memoria per i dati rimanenti
	for(int i=0;i<remaining_size();i++) remain[i] = value; //salva i dati rimanenti in un array standard CAMBIARE??
}



v4f::~v4f()
{
	if(v) delete [] v;
	if(remain) delete [] remain;
}




const float v4f::operator [] (const unsigned& index) const
{
	int i = std::floor(index/NVARS);
	int j = index % NVARS;
	if(i >= chunk_size()) return remain[index-(chunk_size()*NVARS)];
	
	return v[i][j];
}

float& v4f::operator [] (const unsigned& index)
{
	int i = std::floor(index/NVARS);
	int j = index % NVARS;
	if(i >= chunk_size()) return remain[index-(chunk_size()*NVARS)];
	
	return v[i][j];
}




