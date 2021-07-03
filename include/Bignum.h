/**********************************
TODO:
- migliorare la gestione del segno negli operatori
- fare il controllo delle cifre in ingresso
- inserire le funzioni ausiliarie (sqrt, pow, etc.)





***********************************/




//#include <iostream>
#include <cstring>
#include <string> //salva i dati in una stringa (un char occupa il doppio rispetto a 4 bit, che è più compatto)


class Bignum 
{
	std::string value; //valore del numero salvato in vettore di char
	bool negativo = false; //segno: 0 = positivo; 1 = negativo
	
public:
	Bignum();
	Bignum(long int);
	Bignum(const std::string&); //NON SONO SICURO DEL PERCHè COME REFERENCE.... (forse risparmio memoria??)
	
	inline std::string getValue() const { return value; };
	inline bool getSign() const { return negativo; };
	inline unsigned long length() const { if (value == "0") return 0; else return value.length(); };
	
	const Bignum & operator=(const long long&);
	const Bignum & operator=(const Bignum&);
	
	Bignum operator - () const;     // negate  operator
	Bignum operator ++ ();          // prefix  increment operator
	Bignum operator ++ (int);       // postfix increment operator
	Bignum operator -- ();          // prefix  decrement operator
	Bignum operator -- (int);       // postfix decrement operator
	
	Bignum operator += (const Bignum&);
	Bignum operator -= (const Bignum&);
	Bignum operator *= (const Bignum&);
	Bignum operator /= (const Bignum&);
	Bignum operator %= (const Bignum&);
	
	friend Bignum operator + (const Bignum&,const Bignum&);
	friend Bignum operator - (const Bignum&,const Bignum&);
	friend Bignum operator * (const Bignum&,const Bignum&);
	friend Bignum operator / (const Bignum&,const Bignum&);
	friend Bignum operator % (const Bignum&,const Bignum&);
	
	friend bool operator == (const Bignum&,const Bignum&);
	friend bool operator != (const Bignum&,const Bignum&);
	friend bool operator <  (const Bignum&,const Bignum&);
	friend bool operator <= (const Bignum&,const Bignum&);
	friend bool operator >  (const Bignum&,const Bignum&);
	friend bool operator >= (const Bignum&,const Bignum&);
	
	// funzioni aggiuntive
	friend Bignum abs(const Bignum&);
	friend Bignum sqrt(const Bignum&);
	friend Bignum pow(const Bignum&,const Bignum&);
	friend double div(const Bignum&,const Bignum&);
	
	// Class Data
	static const Bignum zero;
	static const Bignum one;
	static const Bignum two;
	
    // I/O stream functions
	friend std::ostream & operator << (std::ostream&,const Bignum&);
	friend std::istream & operator >> (std::istream&,Bignum&);
	
private:
	inline void setNegative(const bool s) { negativo = s; };
	Bignum multdigit(int) const; //motliplica ogni cifra per un numero
	Bignum mult10(int) const; //moltiplica per 10^x
	
	
	
	
};


// Class Data

const Bignum Bignum::zero = Bignum(0);

const Bignum Bignum::one  = Bignum(1);

const Bignum Bignum::two  = Bignum(2);



Bignum::Bignum()
{
	value = "0"; //azzera il valore
	negativo = false; //lo zero è considerato positivo
}


Bignum::Bignum(long int a)
{
	negativo = false; //di default è positivo
	if(a < 0){
		negativo = true;
		a = (-a); //il valore nella stringa è comunque positivo (modulo)
	}
	if(a == 0){
		value = "0";
	    return;
	}
	
//	value = "";
//	while(a > 0){
//		value += (a % 10) + '0';
//		a /= 10;
//	}
	value = std::to_string(a); //converte l'intero in una stringa
}


Bignum::Bignum(const std::string & str)
{
	std::string s = (str == "") ? "0" : str;
	
	negativo = (s[0] == '-') ? true : false; //vede se il numero è negativo
	
	unsigned long start = s.find_first_not_of("0-");
	if(start > s.length()){
		s = "0"; //ha trovato solo zeri
	}else{
		s = s.substr(start,s.length()-start); //elimina eventuali zeri e segni iniziali
	}
	
	value = s;
	
//	if(ispunct(s[0]))                    // if the first character
//		value = s.substr(1,s.length()-1);  // is a punctuation mark. (NON è DETTO! potrebbe essere '+')
//	else value = s;
}




// Bignum = long long
const Bignum & Bignum::operator = (const long long& num)  //QUESTA VERSIONE PARE FUNZIONARE...
{
	Bignum temp(num);
	value = temp.getValue();
	negativo = temp.getSign();
	
	return *this;
}


// Bignum = Bignum
const Bignum & Bignum::operator = (const Bignum &rhs)
{
   if(this == &rhs) return *this;

   value = rhs.value;
   negativo = rhs.negativo;

   return *this;
}


bool operator == (const Bignum & x,const Bignum & y)
{ return ((x.negativo == y.negativo) && (x.value == y.value)); }


bool operator != (const Bignum & x,const Bignum & y)  
{ return !(x == y); }


bool operator < (const Bignum & x,const Bignum & y)
{
	//controlla i segni relativi
	if     (x.negativo < y.negativo) return false;
	else if(x.negativo > y.negativo) return true;
	// exclusive or (^) to determine sign
	if     (x.value.length() < y.value.length()) return (1^x.negativo);
	else if(x.value.length() > y.value.length()) return (0^x.negativo);
	return (x.value < y.value && !x.negativo) || (x.value > y.value && x.negativo);
}


bool operator <= (const Bignum & x,const Bignum & y)
{ return (x<y || x==y); }


bool operator > (const Bignum & x,const Bignum & y)
{ return (!(x<y) && x!=y); }


bool operator >= (const Bignum & x,const Bignum & y)
{ return (x>y || x==y); }






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
	char d1, d2; //cifre dei due numeri da sommare
	char digitsum; //somma temporanea delle cifre
	char carry = 0; //riporto (se eccede 9) sommando due interi il riporto può essere massimo 1
	std::string::const_reverse_iterator i, j; //iteratori delle stringhe (contrario perchè la cifra meno significativa è l'ultimo elemento delal stringa, quindi deve cominciare dalla fine)
	std::string temp = ""; //variabile di appoggio per calcolare il risultato
	
	if(x.negativo ^ y.negativo){ // ^ = XOR (bitwise)
		//se c'è un solo segno negativo fa la sottrazione
		if(x.negativo) return y-abs(x); //x è negativo, y è positivo
		else           return x-abs(y); //x è positivo, y è negativo
	}
	
	i = x.value.rbegin();
	j = y.value.rbegin();
	while(i!=x.value.rend() || j!=y.value.rend()){
		d1 = (i == x.value.rend()) ? 0 : *(i++) - '0'; // get digit
		d2 = (j == y.value.rend()) ? 0 : *(j++) - '0'; // get digit
		digitsum = d1 + d2 + carry; //somma le cifre
		carry = (digitsum >= 10) ? 1 : 0; //imposta il riporto, se cè
		digitsum -= 10*carry; //se c'è il riporto ovviamente lo detrae dalla cifra
		temp = char(digitsum+'0') + temp; //aggiunge la cifra trovata a temp
	}
	if(carry) temp = '1' + temp;  //se, alla fine, è rimasto ancora del resto aggiunge una cifra significativa
	if(x.negativo) temp = '-' + temp; //aggiunge il meno se il numero è negativo
	
	return Bignum(temp);
}


// sottrazione
Bignum operator - (const Bignum & x, const Bignum & y)
{
	char d1, d2; //cifre dei due numeri da sottrarre
	char digitsub; //valore temporanea delle cifre
	char borrow = 0; //quanto prendo dalla cifra superiore
	bool is_negative;
	std::string::const_reverse_iterator i, j; //iteratori delle stringhe (contrario perchè la cifra meno significativa è l'ultimo elemento delal stringa, quindi deve cominciare dalla fine)
	std::string temp = ""; //variabile di appoggio per calcolare il risultato
	
	if(x.negativo ^ y.negativo){ // ^ = XOR (bitwise)
		//se c'è un solo segno negativo fa l'addizione
		if(x.negativo) return -(y+abs(x)); //è negativo il primo termine
		else           return   x+abs(y);  //è negativo il secondo termine
	}
	

// AGGIUSTARE I SEGNI PER I CASI NEGATIVI!!! (magari senza utilizzare troppe risorse)	
	Bignum u, v;
	if(x.negativo) // both u,v are negative
		if(x<y) { u=x; v=y; is_negative=true;}
		else    { u=y; v=x; is_negative=false;}
	else           // both u,v are positive
		if(x<y) { u=y; v=x; is_negative=true;}
		else    { u=x; v=y; is_negative=false;}
//	//controlla se il risultato è positivo o negativo (il calcolo lo fa in modo tale che il risultato è sempre positivo)
//	Bignum u=x,v=y; //variabili temporanee CERCARE DI ELIMINARE QUESTO USO ECCESSIVO DI RISORSE!!!!!!!!!!!!
//	if(!x.negativo && x<y){ u=y; v=x; is_negative = true;  } else is_negative = false; //x e y sono entrambi positivi: x è più grande di y
//	if( x.negativo && x>y){ u=y; v=x; is_negative = false; } else is_negative = true;  //x e y sono entrambi negativi: y è più negativo di x
//	//NON FUNZIONA QUESTA SECONDA VERSIONE....
	
	i = u.value.rbegin();
	j = v.value.rbegin();
	while(i!=u.value.rend() || j!=v.value.rend()){
		d1 = (i == u.value.rend()) ? 0 : *(i++) - '0'; // get digit
		d2 = (j == v.value.rend()) ? 0 : *(j++) - '0'; // get digit
		digitsub = d1 - d2 - borrow; //sottrae le cifre
		borrow = (digitsub < 0) ? 1 : 0; //imposta il prestito, se cè
		digitsub += 10*borrow; //se c'è il prestito ovviamente lo aggiunge dalla cifra
		temp = char(digitsub+'0') + temp; //aggiunge la cifra trovata a temp
	}
	while(temp[0] == '0') temp = temp.substr(1); //elimina eventuali zeri iniziali
	if(is_negative) temp = '-' + temp; //se è negativo il risultato aggiunge il meno
	
	return Bignum(temp);
}


// moltiplicazione
Bignum operator * (const Bignum & x, const Bignum & y)
{
	Bignum pprod(1);
	Bignum tempsum(0);
	std::string::const_reverse_iterator r = y.value.rbegin();
	
	for(unsigned long i=0;r!=y.value.rend();i++,r++){
		int digit = *r - '0'; //estrae una cifra
		pprod = x.multdigit(digit); //poltiplica il valore per la cifra
		pprod = pprod.mult10(i); //aggiunge gli zeri
		tempsum = tempsum + pprod; //aggiunge i prodotti fatti alla somma
	}
	tempsum.negativo = x.negativo ^ y.negativo; //determina il segno del risultato
	
	return tempsum;
}


// divisione
Bignum operator / (const Bignum & x, const Bignum & y)
{
	int len = x.value.length() - y.value.length();
	std::string temp;
	Bignum u,v,b,c,d,quotient=Bignum::zero;
	
	if(y == Bignum::zero) {
		std::cerr << "Error : division by zero" << std::endl;
		return Bignum::zero;
	}
	
	u = abs(x); v = abs(y);
	if(u < v) return Bignum::zero;
	c = Bignum(u.value.substr(0,u.value.length()-len));
	
	for(int i=0;i<=len;i++){
		quotient = quotient.mult10(1);
		b = d = Bignum::zero; // initialize b and d to 0
		while(b < c) { b = b + v; d = d + Bignum::one; }
		if(c < b){// if b>c, then
			// we have added one count too many 
			b = b - v; 
			d = d - Bignum::one;
		}
		quotient = quotient + d; // add to the quotient
		if(i < len){
			// partial remainder * 10 and add to next digit
			c = (c-b).mult10(1);
			c += Bignum(u.value[u.value.length()-len+i]-'0');
		}
	}
	quotient.negativo = x.negativo ^ y.negativo; // to determine sign
	return quotient;
}


// modulo
Bignum operator % (const Bignum & x, const Bignum & y)
{
	return (x - y*(x/y));
}



Bignum Bignum::operator += (const Bignum &x)
{  return *this = *this + x; }

Bignum Bignum::operator -= (const Bignum &x)
{  return *this = *this - x; }

Bignum Bignum::operator *= (const Bignum &x)
{  return *this = *this * x; }

Bignum Bignum::operator /= (const Bignum &x)
{  return *this = *this / x; }

Bignum Bignum::operator %= (const Bignum &x)
{  return *this = *this % x; }




// Prefix increment operator
Bignum Bignum::operator ++ ()
{ return *this = *this + one; }

// Postfix increment operator
Bignum Bignum::operator ++ (int)
{
   Bignum result(*this);
   *this = *this + one;
   return result;
}

// Prefix decrement operator
Bignum Bignum::operator -- ()
{ return *this = *this - one; }

// Postfix decrement operator
Bignum Bignum::operator -- (int)
{
   Bignum result(*this);
   *this = *this - one;
   return result;
}









// moltiplica ogni cifra del Bignum per un numero
Bignum Bignum::multdigit(int num) const
{
	short carry = 0;
	std::string::const_reverse_iterator r;
	
	if(num){
		std::string temp;
		for(r=value.rbegin();r!=value.rend();r++){
			short d1 = *r - '0';              // get digit and multiplied by
			short digitprod = d1*num + carry; // that digit plus carry
			if(digitprod >= 10){              // if there's a new carry,
				carry = digitprod/10;         // carry is high digit
				digitprod -= carry*10;        // result is low digit
			}
			else carry = 0;                   // otherwise carry is 0
			temp = char(digitprod + '0') + temp;   // insert char in string
		}
		if(carry) temp = char(carry + '0') + temp; // if carry at end,
		Bignum result(temp);
		return result;
	}
	else return zero;
}



// moltiplica Bignum per 10^num
Bignum Bignum::mult10(int num) const
{
	if(*this != zero){
		std::string temp;
		for(int j=0;j<num;j++) temp = temp + '0';
		Bignum result(value+temp);
		if(negativo) result = -result;
		return result;
    }
    else return zero;
}











// ################ FUNZIONI FRIEND ################

// abs(Bignum)
Bignum abs(const Bignum & x)
{
	Bignum res(x);
	if(res.negativo) res.setNegative(false); //ha accesso perché è una funzione "friend"
	return res;
}


// scambia due Bignum
void swap(Bignum & x, Bignum & y)
{
	Bignum temp = x;
	x = y;
	y = temp;
}








std::ostream& operator << (std::ostream& os, const Bignum& n)
{
	//stampa il valore dell'intero sullo stream di output (console, file o altro)
	if(n.negativo) os << '-'; //aggiunge il segno (solo se è negativo)
	os << n.value; //aggiunge il valore
	return os; //ritorna lo stream
}



std::istream & operator >> (std::istream & s, Bignum & v)
{
//   std::string temp(10000, ' '); //MASSIMO 10000 CIFRE?????
   std::string temp;
   s >> temp;
   v = Bignum(temp);
   return s;
}





// ################ FUNZIONI AGGIUNTIVE ################

////somma con un int
//Bignum operator + (const int a, const Bignum x) { return Bignum(a) + x; }
//Bignum operator + (const Bignum x, const int a) { return Bignum(a) + x; }
////sottrazione con un int
//Bignum operator - (const int a, const Bignum x) { return Bignum(a) - x; }
//Bignum operator - (const Bignum x, const int a) { return Bignum(a) - x; }
////moltiplicazione per un int
//Bignum operator * (const int a, const Bignum x) { return Bignum(a) * x; }
//Bignum operator * (const Bignum x, const int a) { return Bignum(a) * x; }
// MI SA CHE è INUTILE CHE IL C++ FA AUTOMATICAMENTE IL CASTING....



// DA IMPLEMENTARE !!!!!!!!!!!!!

//
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
//
//BigInt lcm(BigInt a, BigInt b) {
//    return (a*b/gcd(a,b));
//}
//
//// Calculate the integer square root of a number
//// based on the formula (a+b)^2 = a^2 + 2ab + b^2
//Verylong sqrt(const Verylong &v)
//{
//   // if v is negative, error is reported
//   if(v.vlsign) {cerr << "NaN" << endl; return Verylong::zero; }
//
//   int j, k = v.vlstr.length()+1, num = k >> 1;
//   Verylong y, z, sum, tempsum, digitsum;
//   string temp, w(v.vlstr);
//
//   k = 0;
//   j = 1;
//
//   // segment the number 2 digits by 2 digits
//   if(v.vlstr.length() % 2) digitsum = Verylong(w[k++] - '0');
//   else            
//   { 
//     digitsum = Verylong((w[k] - '0')*10 + w[k+1] - '0'); 
//     k += 2;
//   }
//
//   // find the first digit of the integer square root
//   sum = z = Verylong(int(sqrt(double(digitsum))));
//   // store partial result
//   temp = char(int(z) + '0');
//   digitsum = digitsum - z*z;
//
//   for(;j<num;j++)
//   {
//     // get next digit from the number
//     digitsum = digitsum.mult10(1) + Verylong(w[k++] - '0');
//     y = z + z;        // 2*a
//     z = digitsum/y;
//     tempsum = digitsum.mult10(1) + Verylong(w[k++] - '0');
//     digitsum = -y*z.mult10(1) + tempsum - z*z;
//     // decrease z by 1 and re-calculate when it is over-estimated.
//     while(digitsum < Verylong::zero)
//     {
//       --z;
//       digitsum = -y*z.mult10(1) + tempsum - z*z;
//     }
//     temp = temp + char(int(z) + '0');// store partial result
//     z = sum = sum.mult10(1) + z;     // update value of the partial result
//   }
//   Verylong result(temp);
//   return result;
//}
//
//// Raise a number X to a power of degree
//Verylong pow(const Verylong &X,const Verylong &degree)
//{
//   Verylong N(degree), Y("1"), x(X);
//
//   if(N == Verylong::zero) return Verylong::one;
//   if(N < Verylong::zero) return Verylong::zero;
//
//   while(1)
//   {
//     if(N%Verylong::two != Verylong::zero)
//     {
//       Y = Y * x;
//       N = N / Verylong::two;
//       if(N == Verylong::zero) return Y;
//     }
//     else  N = N / Verylong::two;
//     x = x * x;
//   }
//}
//
//// Double division function
//double div(const Verylong &u,const Verylong &v)
//{
//   double qq = 0.0, qqscale = 1.0;
//   Verylong w,y,b,c;
//   int d, count;
//   // number of significant digits
//   int decno = numeric_limits<double>::digits;
//
//   if(v == Verylong::zero) 
//   {
//     cerr << "ERROR : Division by zero" << endl;
//     return 0.0;
//   }
//   if(u == Verylong::zero) return 0.0;
//
//   w=abs(u); y=abs(v);
//   while(w<y) { w = w.mult10(1); qqscale *= 0.1; }
//
//   int len = w.vlstr.length() - y.vlstr.length();
//   string temp = w.vlstr.substr(0,w.vlstr.length()-len);
//   c = Verylong(temp);
//
//   for(int i=0;i<=len;i++)
//   {
//     qq *= 10.0;
//     b = Verylong::zero; d = 0;   // initialize b and d to 0
//     while(b < c) { b += y; d += 1;}
//
//     if(c < b) { b -= y; d -= 1;} // if b>c, then we have added one too many
//     qq += double(d);             // add to the quotient
//     c = (c-b).mult10(1);         // the partial remainder * 10
//     if(i < len)                  // and add to next digit
//        c += Verylong(w.vlstr[w.vlstr.length()-len+i]-'0');
//   }
//   qq *= qqscale; count = 0;
//
//   while(c != Verylong::zero && count < decno)
//   {
//     qqscale *= 0.1;
//     b = Verylong::zero; d = 0;   // initialize b and d to 0
//     while(b < c) { b += y; d += 1;}
//     if(c < b) { b -= y; d -= 1;} // if b>c, then we have added one too many
//     qq += double(d)*qqscale;
//     c = (c-b).mult10(1);
//     count++;
//   }
//   if(u.vlsign^v.vlsign) qq *= (-1.0); // check for the sign
//   return qq;
//}
