/**********************************************
TODO:
- fare la classe "template"


*************************************************/
#ifndef MRC_AUTOMAT_RATIO
#define MRC_AUTOMAT_RATIO

#include "identity.h "//per one()
#include <string>

template <typename T>
class Ratio
{
	private:
		T _num; //numeratore
		T _den; //denominatore
		
	public:
		Ratio() : _num(0), _den(1) {};
		Ratio(const T num) : _num(num), _den(1) {};
		Ratio(const T num,const T den) : _num(num), _den(den) {};
		
		//getters:
		inline T num() { return _num; };
		inline T den() { return _den; };
		//setters:
		inline void setNum(T num) { _num = num; };
		inline void setDen(T den) { _den = den; };
		
		//arithmetic and relational operators:
		const Ratio<T>& operator = (const Ratio<T>&);
		Ratio<T> operator - () const;
		
		Ratio<T> operator + (const Ratio<T>&) const;
		Ratio<T> operator - (const Ratio<T>&) const;
		Ratio<T> operator * (const Ratio<T>&) const;
		Ratio<T> operator / (const Ratio<T>&) const;
		
		inline const Ratio<T>& operator += (const Ratio<T>& r) { return *this = *this + r; };
		inline const Ratio<T>& operator -= (const Ratio<T>& r) { return *this = *this - r; };
		inline const Ratio<T>& operator *= (const Ratio<T>& r) { return *this = *this * r; };
		inline const Ratio<T>& operator /= (const Ratio<T>& r) { return *this = *this / r; };
		
		inline bool operator == (const Ratio<T>& r) const { return (_num * r._den) == (_den * r._num); };
		inline bool operator != (const Ratio<T>& r) const { return !(*this == r); };
		inline bool operator >  (const Ratio<T>& r) const { return (_num*r._den - _den*r._num > zero(T())); };
		inline bool operator <  (const Ratio<T>& r) const { return (_num*r._den - _den*r._num < zero(T())); };
		inline bool operator >= (const Ratio<T>& r) const { return (*this>r) || (*this==r); };
		inline bool operator <= (const Ratio<T>& r) const { return (*this<r) || (*this==r); };
		
		
		//output functions:
		std::ostream& output(std::ostream&) const;
};




template<typename T> Ratio<T> Ratio<T>::operator + (const Ratio<T> &rhs) const
{ return Ratio<T>(_num * rhs._den + _den * rhs._num, _den * rhs._den); }

template<typename T> Ratio<T> Ratio<T>::operator - (const Ratio<T> &rhs) const
{ return Ratio<T>(_num * rhs._den - _den * rhs._num, _den * rhs._den); }

template<typename T> Ratio<T> Ratio<T>::operator * (const Ratio<T> &rhs) const
{ return Ratio<T>(_num * rhs._num, _den * rhs._den); }

template<typename T> Ratio<T> Ratio<T>::operator / (const Ratio<T> &rhs) const
{ return Ratio<T>(_num * rhs._den, _den * rhs._num); }




template<typename T> std::ostream& Ratio<T>::output(std::ostream& s) const
{
	using std::operator<<; //dice al compilatore di usare l'operatore << standard
	if(_den == one(T())) return s << _num;
	return s << _num << "/" << _den;
}



// FUNZIONI AUSILIARIE ==================================================================================================

template<typename T> std::ostream& operator << (std::ostream& s,const T r)
{
	return r.output(s);
}

#endif
