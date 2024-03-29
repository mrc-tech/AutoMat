/**********************************
TODO:
- 

***********************************/
#include <iostream>
#include <iomanip> //per setfill() e setw()
#include <vector>
//#include <cstring>
//#include <string> //salva i dati in una stringa (un char occupa il doppio rispetto a 4 bit, che � pi� compatto)
#include <limits>
#include <cmath>

//#include "identity.h"

using namespace std; //TEMPORANEO PER IL DEBUG

typedef unsigned long long ulong64;


class Bignum 
{
	vector<ulong64> data; //valore del numero salvato in vettore ulong64
	bool negativo = false; //segno: 0 = positivo; 1 = negativo
	
	const unsigned int chunkSize = 13; //numero di cifre che ogni elemento del vettore descrive (costante per tutti)
	
public:
	Bignum();
	Bignum(ulong64);
	Bignum(const Bignum&); //copy constructor
//	Bignum(const std::string&); //NON SONO SICURO DEL PERCH� COME REFERENCE.... (forse risparmio memoria??)
	
//	inline std::string getValue() const { return value; };
	inline bool getSign() const { return negativo ? -1 : 1; };
	inline ulong64 length() const { return data.size() * chunkSize; }; //L'ULTIMO ELEMENTO POTREBBE AVERE UN NUMERO DI CIFRE MINORI DI Ncifre
	
	const Bignum & operator=(const long long&);
	const Bignum & operator=(const Bignum&);
	
	Bignum operator - () const;     // negate  operator
//	Bignum operator ++ (int);       // postfix increment operator
//	Bignum operator -- (int);       // postfix decrement operator
//	Bignum operator ++ ();          // prefix  increment operator
//	Bignum operator -- ();          // prefix  decrement operator
	
	friend Bignum operator + (const Bignum&,const Bignum&);
//	friend Bignum operator - (const Bignum&,const Bignum&);
//	friend Bignum operator * (const Bignum&,const Bignum&);
//	friend Bignum operator / (const Bignum&,const Bignum&);
//	friend Bignum operator % (const Bignum&,const Bignum&);
	
	inline Bignum operator += (const Bignum &x) { return *this = *this + x; };
//	inline Bignum operator -= (const Bignum &x) { return *this = *this - x; };
//	inline Bignum operator *= (const Bignum &x) { return *this = *this * x; };
//	inline Bignum operator /= (const Bignum &x) { return *this = *this / x; };
//	inline Bignum operator %= (const Bignum &x) { return *this = *this % x; };
	
	friend bool operator == (const Bignum&,const Bignum&);
	friend bool operator != (const Bignum&,const Bignum&);
//	friend bool operator <  (const Bignum&,const Bignum&);
//	friend bool operator <= (const Bignum&,const Bignum&);
//	friend bool operator >  (const Bignum&,const Bignum&);
//	friend bool operator >= (const Bignum&,const Bignum&);
	
	// funzioni aggiuntive PERCH� METTERLE FRIEND? 
	friend Bignum abs(const Bignum&);
//	friend Bignum sqrt(const Bignum&);
//	friend Bignum pow(const Bignum&,const Bignum&);
//	friend double div(const Bignum&,const Bignum&);
	
	// Class Data
	static const Bignum zero;
	static const Bignum one;
	static const Bignum two;
	
	// Conversion operators
	operator int () const;
	operator double () const;
//	operator std::string () const;
	
    // I/O stream functions
	friend std::ostream & operator << (std::ostream&,const Bignum&);
//	friend std::istream & operator >> (std::istream&,Bignum&);
	
private:
//	inline void setNegative(const bool s) { negativo = s; };
//	Bignum multdigit(int) const; //motliplica ogni cifra per un numero
//	Bignum mult10(int) const; //moltiplica per 10^x
	
	
	
	
};


// Class Data
const Bignum Bignum::zero = Bignum(0); //INCLUDERE NELLA DEFINIZIONE "identity.h" ???
const Bignum Bignum::one  = Bignum(1); //INCLUDERE NELLA DEFINIZIONE "identity.h" ???
const Bignum Bignum::two  = Bignum(2);



Bignum::Bignum()
{
	data.push_back(0); //azzera il valore
	negativo = false; //lo zero � considerato positivo
}


Bignum::Bignum(ulong64 a)
{
	negativo = false; //di default � positivo
	if(a < 0){
		negativo = true;
		a = (-a); //il valore nella stringa � comunque positivo (modulo)
	}
	data.push_back(a);
}


// Copy Constructor
Bignum::Bignum(const Bignum& n)
{
	data = n.data;
	negativo = n.negativo;
}


//Bignum::Bignum(const std::string & str)
//{
//	std::string s = (str == "") ? "0" : str;
//	
//	negativo = (s[0] == '-') ? true : false; //vede se il numero � negativo
//	
//	unsigned long start = s.find_first_not_of("0-");
//	if(start > s.length()){
//		s = "0"; //ha trovato solo zeri
//	}else{
//		s = s.substr(start,s.length()-start); //elimina eventuali zeri e segni iniziali
//	}
//	
//	value = s;
//	
////	if(ispunct(s[0]))                    // if the first character
////		value = s.substr(1,s.length()-1);  // is a punctuation mark. (NON � DETTO! potrebbe essere '+')
////	else value = s;
//}


//Bignum::Bignum(const char* number)
//{
//	string value(number);
//	if(value[0]=='-'){
//		sign = -1;
//		value = value.substr(1,value.size()-1);
//	}
//	else sign = 1;
//
//	value = removeFrontZeros(value);
//	check(value,number);
//	integer = str_to_chunk(value,8);
//}
//
//Bignum::Bignum(string value)
//{
//	string original_form = value;
//	if(value[0]=='-'){
//		sign = -1;
//		value = value.substr(1,value.size()-1);
//	}
//	else sign = 1;
//
//	value = removeFrontZeros(value);
//	check(value,original_form);
//	integer = str_to_chunk(value,8);
//}







// Bignum = long long
const Bignum & Bignum::operator = (const long long& num)
{
	Bignum temp(num);
	data = temp.data;
	negativo = temp.negativo;
	
	return *this;
}


// Bignum = Bignum
const Bignum & Bignum::operator = (const Bignum &rhs)
{
	if(this == &rhs) return *this;
	
	data = rhs.data;
	negativo = rhs.negativo;
	
	return *this;
}


bool operator == (const Bignum & x,const Bignum & y)
{
	if(x.data.size() != y.data.size()) return false; //devono avere lo stesso numero di chunks
	for(int i=0;i<x.data.size();i++) if(x.data[i] != y.data[i]) return false; //i chunks devono avere lo stesso valore
	if(x.negativo != y.negativo) return false; //devono avere lo stesso segno
	return true;
}


bool operator != (const Bignum & x,const Bignum & y)  
{ return !(x == y); }


//bool operator < (const Bignum & x,const Bignum & y)
//{
//	//controlla i segni relativi
//	if     (x.negativo < y.negativo) return false;
//	else if(x.negativo > y.negativo) return true;
//	//controlla il numero di chunks
//	if     (x.data.size() < y.data.size()) return (1^x.negativo);
//	else if(x.data.size() > y.data.size()) return (0^x.negativo);
//	return ((x.value < y.value && !x.negativo) || (x.value > y.value && x.negativo);
//}


//bool operator <= (const Bignum & x,const Bignum & y)
//{ return (x<y || x==y); }


//bool operator > (const Bignum & x,const Bignum & y)
//{ return (!(x<y) && x!=y); }


//bool operator >= (const Bignum & x,const Bignum & y)
//{ return (x>y || x==y); }






// Unary - operator
Bignum Bignum::operator -() const
{
    Bignum temp(*this);
    if(temp != zero) temp.negativo = !negativo;
    return temp;
}







// addizione
Bignum operator + (const Bignum & x, const Bignum & y)
{
	// funzione esterna definita "friend" in modo tale da esplicitare x e y
	ulong64 d1, d2; //cifre dei due numeri da sommare
	ulong64 digitsum; //somma temporanea delle cifre
	ulong64 carry = 0; //riporto (se eccede 9) sommando due interi il riporto pu� essere massimo 1
	std::vector<ulong64> temp;
	Bignum res;
	
//	if(x.negativo ^ y.negativo){ // ^ = XOR (bitwise)
//		//se c'� un solo segno negativo fa la sottrazione
//		if(x.negativo) return y-abs(x); //x � negativo, y � positivo
//		else           return x-abs(y); //x � positivo, y � negativo
//	}
	
	
//	cout << "x.len=" << x.len << "  y.len:" << x.len << endl;
	
	int i = 0;
	int j = 0;
	while(i<x.data.size() || j<y.data.size()){
		d1 = (i == x.data.size()) ? 0 : x.data[i++]; // get digit
		d2 = (j == y.data.size()) ? 0 : y.data[j++]; // get digit
		digitsum = d1 + d2 + carry; //somma le cifre
//		std::cout << "Step1:  " << d1 << " " << d2 << "  " << digitsum << " " << carry << std::endl;
//		if(digitsum < pow(10,x.Ncifre)) carry = 0; else carry = digitsum / (ulong64)pow(10,x.Ncifre); //imposta il riporto, se c�
			carry = digitsum / (ulong64)pow(10,x.chunkSize); //imposta il riporto, se c�
		digitsum -= pow(10,x.chunkSize) * carry; //se c'� il riporto ovviamente lo detrae dalla cifra
		temp.push_back(digitsum); //aggiunge la cifra trovata a temp
//		std::cout << "Step2:  " << d1 << " " << d2 << "  " << digitsum << " " << carry << std::endl;
	}
	if(carry>0) temp.push_back(carry);  //se, alla fine, � rimasto ancora del resto aggiunge una cifra significativa
	if(x.negativo) res.negativo = true;
	res.data = temp;
//	std::cout << "pollo" << res.len << std::endl;
	
	return res;
}


// sottrazione
//Bignum operator - (const Bignum & x, const Bignum & y)
//{
//	char d1, d2; //cifre dei due numeri da sottrarre
//	char digitsub; //valore temporanea delle cifre
//	char borrow = 0; //quanto prendo dalla cifra superiore
//	bool is_negative;
//	std::string::const_reverse_iterator i, j; //iteratori delle stringhe (contrario perch� la cifra meno significativa � l'ultimo elemento delal stringa, quindi deve cominciare dalla fine)
//	std::string temp = ""; //variabile di appoggio per calcolare il risultato
//	
//	if(x.negativo ^ y.negativo){ // ^ = XOR (bitwise)
//		//se c'� un solo segno negativo fa l'addizione
//		if(x.negativo) return -(y+abs(x)); //� negativo il primo termine
//		else           return   x+abs(y);  //� negativo il secondo termine
//	}
//	
//
//// AGGIUSTARE I SEGNI PER I CASI NEGATIVI!!! (magari senza utilizzare troppe risorse)	
//	Bignum u, v;
//	if(x.negativo) // both u,v are negative
//		if(x<y) { u=x; v=y; is_negative=true;}
//		else    { u=y; v=x; is_negative=false;}
//	else           // both u,v are positive
//		if(x<y) { u=y; v=x; is_negative=true;}
//		else    { u=x; v=y; is_negative=false;}
////	//controlla se il risultato � positivo o negativo (il calcolo lo fa in modo tale che il risultato � sempre positivo)
////	Bignum u=x,v=y; //variabili temporanee CERCARE DI ELIMINARE QUESTO USO ECCESSIVO DI RISORSE!!!!!!!!!!!!
////	if(!x.negativo && x<y){ u=y; v=x; is_negative = true;  } else is_negative = false; //x e y sono entrambi positivi: x � pi� grande di y
////	if( x.negativo && x>y){ u=y; v=x; is_negative = false; } else is_negative = true;  //x e y sono entrambi negativi: y � pi� negativo di x
////	//NON FUNZIONA QUESTA SECONDA VERSIONE....
//	
//	i = u.value.rbegin();
//	j = v.value.rbegin();
//	while(i!=u.value.rend() || j!=v.value.rend()){
//		d1 = (i == u.value.rend()) ? 0 : *(i++) - '0'; // get digit
//		d2 = (j == v.value.rend()) ? 0 : *(j++) - '0'; // get digit
//		digitsub = d1 - d2 - borrow; //sottrae le cifre
//		borrow = (digitsub < 0) ? 1 : 0; //imposta il prestito, se c�
//		digitsub += 10*borrow; //se c'� il prestito ovviamente lo aggiunge dalla cifra
//		temp = char(digitsub+'0') + temp; //aggiunge la cifra trovata a temp
//	}
//	while(temp[0] == '0') temp = temp.substr(1); //elimina eventuali zeri iniziali
//	if(is_negative) temp = '-' + temp; //se � negativo il risultato aggiunge il meno
//	
//	return Bignum(temp);
//}


// moltiplicazione
//Bignum operator * (const Bignum & x, const Bignum & y)
//{
//	Bignum pprod(1);
//	Bignum tempsum(0);
//	std::string::const_reverse_iterator r = y.value.rbegin();
//	
//	for(unsigned long i=0;r!=y.value.rend();i++,r++){
//		int digit = *r - '0'; //estrae una cifra
//		pprod = x.multdigit(digit); //poltiplica il valore per la cifra
//		pprod = pprod.mult10(i); //aggiunge gli zeri
//		tempsum = tempsum + pprod; //aggiunge i prodotti fatti alla somma
//	}
//	tempsum.negativo = x.negativo ^ y.negativo; //determina il segno del risultato
//	
//	return tempsum;
//}


// divisione
//Bignum operator / (const Bignum & x, const Bignum & y)
//{
//	int len = x.value.length() - y.value.length();
//	std::string temp;
//	Bignum u,v,b,c,d,quotient=Bignum::zero;
//	
//	if(y == Bignum::zero) {
//		std::cerr << "Error : division by zero" << std::endl;
//		return Bignum::zero;
//	}
//	
//	u = abs(x); v = abs(y);
//	if(u < v) return Bignum::zero;
//	c = Bignum(u.value.substr(0,u.value.length()-len));
//	
//	for(int i=0;i<=len;i++){
//		quotient = quotient.mult10(1);
//		b = d = Bignum::zero; // initialize b and d to 0
//		while(b < c) { b = b + v; d = d + Bignum::one; }
//		if(c < b){// if b>c, then
//			// we have added one count too many 
//			b = b - v; 
//			d = d - Bignum::one;
//		}
//		quotient = quotient + d; // add to the quotient
//		if(i < len){
//			// partial remainder * 10 and add to next digit
//			c = (c-b).mult10(1);
//			c += Bignum(u.value[u.value.length()-len+i]-'0');
//		}
//	}
//	quotient.negativo = x.negativo ^ y.negativo; // to determine sign
//	return quotient;
//}


// modulo
//Bignum operator % (const Bignum & x, const Bignum & y)
//{
//	return (x - y*(x/y));
//}





// Prefix increment operator
//Bignum Bignum::operator ++ ()
//{ return *this = *this + one; }

// Postfix increment operator
//Bignum Bignum::operator ++ (int)
//{
//   Bignum result(*this);
//   *this = *this + one;
//   return result;
//}

// Prefix decrement operator
//Bignum Bignum::operator -- ()
//{ return *this = *this - one; }

// Postfix decrement operator
//Bignum Bignum::operator -- (int)
//{
//   Bignum result(*this);
//   *this = *this - one;
//   return result;
//}








//Bignum::operator int() const
//{
//	int number, factor = 1;
//	static Bignum max0(std::numeric_limits<int>::max());
//	static Bignum min0(std::numeric_limits<int>::min()+1);
//	std::string::const_reverse_iterator j=value.rbegin();
//	
//	if(*this > max0){
//		std::cerr << "Error: Conversion Verylong->integer is not possible" << std::endl;
//		return std::numeric_limits<int>::max();
//	}else if(*this < min0){
//		std::cerr << "Error: Conversion Verylong->integer is not possible" << std::endl;
//		return std::numeric_limits<int>::min();
//	}
//	
//	number = *j - '0';
//	
//	for(j++;j!=value.rend();j++){
//		factor *= 10;
//		number += (*j-'0') * factor;
//	}
//	
//	if(negativo) return -number;
//	return number;
//}
//   
//Bignum::operator double() const
//{
//	double sum, factor = 1.0;
//	std::string::const_reverse_iterator i = value.rbegin();
//	
//	sum = double(*i) - '0';
//	for(i++;i!=value.rend();i++){
//		factor *= 10.0;
//		sum += double(*i-'0') * factor;
//	}
//	if(negativo) return -sum;
//	return sum;
//}
//
//Bignum::operator std::string () const
//{
//	if(value.length() == 0) return std::string("0");
//	return value;
//}










// moltiplica ogni cifra del Bignum per un numero
//Bignum Bignum::multdigit(int num) const
//{
//	short carry = 0;
//	std::string::const_reverse_iterator r;
//	
//	if(num){
//		std::string temp;
//		for(r=value.rbegin();r!=value.rend();r++){
//			short d1 = *r - '0';              // get digit and multiplied by
//			short digitprod = d1*num + carry; // that digit plus carry
//			if(digitprod >= 10){              // if there's a new carry,
//				carry = digitprod/10;         // carry is high digit
//				digitprod -= carry*10;        // result is low digit
//			}
//			else carry = 0;                   // otherwise carry is 0
//			temp = char(digitprod + '0') + temp;   // insert char in string
//		}
//		if(carry) temp = char(carry + '0') + temp; // if carry at end,
//		Bignum result(temp);
//		return result;
//	}
//	else return zero;
//}



// moltiplica Bignum per 10^num
//Bignum Bignum::mult10(int num) const
//{
//	if(*this != zero){
//		std::string temp;
//		for(int j=0;j<num;j++) temp = temp + '0';
//		Bignum result(value+temp);
//		if(negativo) result = -result;
//		return result;
//    }
//    else return zero;
//}











// FUNZIONI FRIEND ===================================================================================================

// abs(Bignum)
Bignum abs(const Bignum & x)
{
	Bignum res(x);
	if(res.negativo) res.negativo = false; //ha accesso perch� � una funzione "friend"
	return res;
}


// scambia due Bignum
//void swap(Bignum & x, Bignum & y)
//{
//	Bignum temp = x;
//	x = y;
//	y = temp;
//}








std::ostream& operator << (std::ostream& os, const Bignum& n)
{
	//stampa il valore dell'intero sullo stream di output (console, file o altro)
	if(n.negativo) os << '-'; //aggiunge il segno (solo se � negativo)
	for(int i=n.data.size()-1;i>=0;i--){
		//aggiunge il valore n-esimo MIGLIORARE USANDO GLI ITERATOR
		if(i == n.data.size()-1) os << n.data[i]; //� l'ultimo chunk
		else os << std::setfill('0') << std::setw(n.chunkSize) << n.data[i];
	}
	return os; //ritorna lo stream
}

//ostream& operator<<(ostream &out, const bint& value)
//{
//    string outputstring = value.string_form();
//    out << outputstring;
//    return out;
//}



//std::istream & operator >> (std::istream & s, Bignum & v)
//{
////   std::string temp(10000, ' '); //MASSIMO 10000 CIFRE?????
//   std::string temp;
//   s >> temp;
//   v = Bignum(temp);
//   return s;
//}

//istream& operator>>(istream &in, bint &value) {
//    string input;
//	in >> input;
//    check(input,input);
//    if(input[0]=='-'){
//		value.set_sign(-1);
//		input[0] = '0';
//	}
//	else
//		value.set_sign(1);
//    value.set_bint_field(str_part_by(8,input));
//	return in;
//}





// FUNZIONI AGGIUNTIVE ===================================================================================================

////somma con un int
//Bignum operator + (const int a, const Bignum x) { return Bignum(a) + x; }
//Bignum operator + (const Bignum x, const int a) { return Bignum(a) + x; }
////sottrazione con un int
//Bignum operator - (const int a, const Bignum x) { return Bignum(a) - x; }
//Bignum operator - (const Bignum x, const int a) { return Bignum(a) - x; }
////moltiplicazione per un int
//Bignum operator * (const int a, const Bignum x) { return Bignum(a) * x; }
//Bignum operator * (const Bignum x, const int a) { return Bignum(a) * x; }
// MI SA CHE � INUTILE CHE IL C++ FA AUTOMATICAMENTE IL CASTING....



// DA IMPLEMENTARE !!!!!!!!!!!!!


//BigInt gcd(BigInt a, BigInt b) {
//    Set(a);
//    Set(b);
//    while (b > Integer(0)) {
//        BigInt r = a%b;
//        a = b;
//        b = r;
//    }
//    Set(a);
//    return a;
//}


//BigInt lcm(BigInt a, BigInt b) {
//    return (a*b/gcd(a,b));
//}


// Raise a number X to a power of degree
//Bignum pow(const Bignum& X, const Bignum& degree)
//{
//	Bignum N(degree), Y("1"), x(X);
//	
//	if(N == Bignum::zero) return Bignum::one;
//	if(N <  Bignum::zero) return Bignum::zero;
//	
//	while(true){
//		if(N % Bignum::two != Bignum::zero){
//			Y = Y * x;
//			N = N / Bignum::two;
//			if(N == Bignum::zero) return Y;
//		} else N = N / Bignum::two;
//		x = x * x;
//	}
//}
//
//
//// Double division function
//double div(const Bignum& x, const Bignum& y)
//{
//	double qq = 0.0, qqscale = 1.0;
//	Bignum u,v,b,c;
//	int d, count;
//	// number of significant digits
//	int decno = std::numeric_limits<double>::digits;
//	
//	if(x == Bignum::zero) {
//		std::cerr << "ERROR : Division by zero" << std::endl;
//		return 0.0;
//	}
//	if(x == Bignum::zero) return 0.0;
//	
//	u=abs(x); v=abs(y);
//	while(u<v) { u = u.mult10(1); qqscale *= 0.1; }
//	
//	int len = u.value.length() - v.value.length();
//	std::string temp = u.value.substr(0,u.value.length()-len);
//	c = Bignum(temp);
//	
//	for(int i=0;i<=len;i++){
//		qq *= 10.0;
//		b = Bignum::zero; d = 0; // initialize b and d to 0
//		while(b < c) { b += v; d += 1; }
//		
//		if(c < b) { b -= v; d -= 1;} // if b>c, then we have added one too many
//		qq += double(d); // add to the quotient
//		c = (c-b).mult10(1); // the partial remainder * 10
//		if(i < len) c += Bignum(u.value[u.value.length()-len+i]-'0'); // and add to next digit
//	}
//	qq *= qqscale; count = 0;
//	
//	while(c != Bignum::zero && count < decno){
//		qqscale *= 0.1;
//		b = Bignum::zero; d = 0; // initialize b and d to 0
//		while(b < c) { b += v; d += 1; }
//		if(c < b) { b -= v; d -= 1; } // if b>c, then we have added one too many
//		qq += double(d)*qqscale;
//		c = (c-b).mult10(1);
//		count++;
//	}
//	if(v.negativo ^ y.negativo) qq *= (-1.0); // check for the sign
//	
//	return qq;
//}

// FUNZIONI AUSILIARIE ===================================================================================================

vector<ulong64> get_chunk_subset(const vector<ulong64>& set, size_t istart, size_t iend)
{
	vector<ulong64> newset;
	newset.reserve(iend-istart+1);
	newset.insert(newset.end(),set.begin()+istart,set.begin()+iend+1);
	return newset;
}

vector<ulong64> join_chunks(const vector<ulong64>& left, const vector<ulong64>& right)
{
	vector<ulong64> joinedfield;
	joinedfield.reserve(left.size() + right.size());
	joinedfield.insert(joinedfield.end(), left.begin(), left.end());
	joinedfield.insert(joinedfield.end(), right.begin(), right.end());
	return joinedfield;
}


/// @return a std::string with no sequential zeroes in the front
std::string removeFrontZeros(const std::string& str)
{
	size_t str_len = str.size();
	size_t zero_indecies = 0;
	
	for(size_t i=0; i<str_len-1; ++i){
		if(str[i]!='0') break;
		++zero_indecies;
    }
	
	return str.substr(zero_indecies,str_len-zero_indecies);
}

/// @return a std::string number representation of the array
std::string chunk_to_str(const std::vector<ulong64>& arr_chunks,const unsigned int chunkSize)
{
	size_t n = arr_chunks.size();
	std::string carried_answer="", current_index;
	
	for(size_t i=0ll;i<n;++i){
		current_index = std::to_string(arr_chunks[i]);
		std::string front_zeros(chunkSize-current_index.size(),'0');
        carried_answer += (front_zeros + current_index);
    }

    return removeFrontZeros(carried_answer);
}

vector<ulong64> str_to_chunk(const string& number, ulong64 length)
{
	vector<string> str_partition;
	vector<ulong64> long_partition;
	
	string str_temp(length,'0');
	size_t num_size = number.size();
	
	long long int memreserve = ((long long int)num_size/(long long int)length)+1;
	str_partition.reserve(memreserve);
	long_partition.reserve(memreserve);
	
	for(size_t i=0, str_i; i<num_size;++i){
		if(i==0 or i%length==0){
			str_i = length;
			str_partition.push_back(str_temp);
		}
		str_partition.back()[str_i-1] = number[num_size-1-i];
		--str_i;
	}
	
	size_t str_size = str_partition.size();
	for(size_t i=0; i<str_size; ++i) long_partition.push_back(stoll(str_partition[str_size-1-i]));
	
	return long_partition;
}

void check(const string& value, const string original_form)
{
	try
	{
		size_t value_size = value.size(); 
		if(value_size<=0) throw value_size;
		for(size_t i=0; i<value_size; ++i) if(value[i]<'0'^value[i]>'9') throw value;
	}
	catch(size_t NO_VALUE_ERROR)
	{
		cerr<<"\n\x1B[31mbint ERROR\033[0m [check] : NUMBER HAS NO VALUE\n";
		exit(1);
	}
	catch(string VALUE_ERROR)
	{
		if(VALUE_ERROR[0]=='-') cerr<<"\n\x1B[31mbint ERROR\033[0m [check] : YOU ASSIGNED AN INVALID BIG \"INTEGER\" NUMBER : (-"<<original_form<<")\n"; // error for double negative signs
		cerr<<"\n\x1B[31mbint ERROR\033[0m [check] : YOU ASSIGNED AN INVALID BIG \"INTEGER\" NUMBER : ("<<original_form<<")\n";
		exit(2);
	}
}

