#ifndef MRC_AUTOMAT_IDENTITY
#define MRC_AUTOMAT_IDENTITY

#include <iostream>
#include <cstdlib>
#include <complex>

//classes:
template <class T> T zero(T) 
{
	static const T z = T() - T(); //la classe T deve avere il costruttore e la sottrazione
	return z;
}

template <class T> T one(T)
{
	static T z(zero(T()));
	static const T o = ++z; //la classe T deve avere l'operatore ++
	return o;
}

//standard types:
template<> char zero(char) { return (char) 0; }
template<> char one(char)  { return (char) 1; }
template<> short zero(short) { return (short) 0; }
template<> short one(short)  { return (short) 1; }
template<> int zero(int) { return (int) 0; }
template<> int one(int)  { return (int) 1; }
template<> long zero(long) { return (long) 0; }
template<> long one(long)  { return (long) 1; }
template<> float zero(float) { return (float) 0.0; }
template<> float one(float)  { return (float) 1.0; }
template<> double zero(double) { return (double) 0.0; }
template<> double one(double)  { return (double) 1.0; }

//nested typedefs:
template<class T> std::complex<T> zero(std::complex<T>) { return std::complex<T>(zero(T())); }
template<class T> std::complex<T> one(std::complex<T>)  { return std::complex<T>(one(T()));  }


#endif
