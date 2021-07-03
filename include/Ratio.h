/**********************************************
TODO:
- fare la classe "template"


*************************************************/
#ifndef MRC_AUTOMAT_RATIO
#define MRC_AUTOMAT_RATIO

#include "identity.h "//per one()
#include <string>


template<typename T> T gcd(T,T);


template <typename T>
class Ratio
{
	private:
		T _num; //numeratore
		T _den; //denominatore
		
	public:
		Ratio() : _num(zero(T())), _den(one(T())) {};
		Ratio(const T num) : _num(num), _den(one(T())) {};
		Ratio(const T,const T);
		
		//getters:
		inline T num() { return _num; };
		inline T den() { return _den; };
		//setters:
		inline void setNum(T num) { _num = num; };
		inline void setDen(T den) { _den = den; };
		
		//arithmetic and relational operators:
		inline const Ratio<T>& operator = (const Ratio<T>& r) { _num = r._num; _den = r._den; return *this; };
		inline Ratio<T> operator - () const { return Ratio<T>(-_num, _den); };
		
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
		
		//conversion:
		inline operator double() const { return double(_num)/double(_den); };
//		inline operator float() const { return float(_num)/float(_den); };
		
		//other:
		void normalize();
		
		//output functions:
		friend std::ostream& operator << (std::ostream& out, const Ratio<T> r) {
			if(r._den == one(T())) return out << r._num;
			return out << r._num << "/" << r._den;
		}
};



template<typename T> Ratio<T>::Ratio(const T num, const T den) : _num(num), _den(den)
{
	if(num==zero(T())){
		using std::operator<<; //dice al compilatore di usare l'operatore << standard
		std::cerr << "Zero denominator in Rational Number " << std::endl;
		return;
	}
	normalize();
}


template<typename T> Ratio<T> Ratio<T>::operator + (const Ratio<T> &rhs) const
{ return Ratio<T>(_num * rhs._den + _den * rhs._num, _den * rhs._den); }

template<typename T> Ratio<T> Ratio<T>::operator - (const Ratio<T> &rhs) const
{ return Ratio<T>(_num * rhs._den - _den * rhs._num, _den * rhs._den); }

template<typename T> Ratio<T> Ratio<T>::operator * (const Ratio<T> &rhs) const
{ return Ratio<T>(_num * rhs._num, _den * rhs._den); }

template<typename T> Ratio<T> Ratio<T>::operator / (const Ratio<T> &rhs) const
{ return Ratio<T>(_num * rhs._den, _den * rhs._num); }






template<typename T> void Ratio<T>::normalize()
{
	T t;
	if(_num < zero(T())) t = -_num; else t = _num; //prende il valore assoulto del numeratore
	t = gcd(t, _den);
	if(t > one(T())){ _num /= t; _den /= t; }
	if(_den < zero(T())) { _num = -_num; _den = -_den; } //il denominatore è sempre positivo
}




// FUNZIONI AUSILIARIE ==================================================================================================


template<typename T> T gcd(T a, T b)
{
	while(b > zero(T())){
		T m = a % b;
		a = b;
		b = m;
	}
	return a;
}

#endif
