/**********************************
TODO:
- mettere la possibilità di immettere il valore con std::cin





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

const Bignum Bignum::one = Bignum(1);

const Bignum Bignum::two = Bignum(2);



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

   negativo = (s[0] == '-') ? true : false;        // check for negative sign
   if(ispunct(s[0]))                    // if the first character
     value = s.substr(1,s.length()-1);  // is a punctuation mark.
   else value = s;
}
//Bignum::Bignum(const std::string &s)
//{ VERSIONE MIGLIORE: MA NON FUNZIONA AL 100%!!!!!!!!!!!!!
//	unsigned long start = s.find_first_not_of("0-");
//	
//	if(!std::strcmp(&s[start],"")){
//		std::strcpy(&value[0], "0");
//	}
//	
//	if(s[0] == '-') negativo = true;
//	
//	value = &s[start];
//}



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
		if(x.negativo == false) return x-abs(y); //x è positivo, y è negativo
		else                    return y-abs(x); //x è negativo, y è positivo
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
	std::string::const_reverse_iterator i, j; //iteratori delle stringhe (contrario perchè la cifra meno significativa è l'ultimo elemento delal stringa, quindi deve cominciare dalla fine)
	std::string temp = ""; //variabile di appoggio per calcolare il risultato
	
	if(x.negativo ^ y.negativo){ // ^ = XOR (bitwise)
		//se c'è un solo segno negativo fa l'addizione
		if(x.negativo == false) return x+abs(y); //è negativo il secondo termine
		else                    return y+abs(x); //è negativo il primo termine
	}
	

// AGGIUSTARE I SEGNI PER I CASI NEGATIVI!!! (magari senza utilizzare troppe risorse)	
//Verylong w, y;
//if(u.vlsign == 0)  // both u,v are positive
// if(u<v) { w=v; y=u; negative=1;}
// else    { w=u; y=v; negative=0;}
//else               // both u,v are negative
// if(u<v) { w=u; y=v; negative=1;}
// else    { w=v; y=u; negative=0;}
	
	i = x.value.rbegin();
	j = y.value.rbegin();
	while(i!=x.value.rend() || j!=y.value.rend()){
		d1 = (i == x.value.rend()) ? 0 : *(i++) - '0'; // get digit
		d2 = (j == y.value.rend()) ? 0 : *(j++) - '0'; // get digit
		digitsub = d1 - d2 - borrow; //sottrae le cifre
		borrow = (digitsub < 0) ? 1 : 0; //imposta il prestito, se cè
		digitsub += 10*borrow; //se c'è il prestito ovviamente lo aggiunge dalla cifra
		temp = char(digitsub+'0') + temp; //aggiunge la cifra trovata a temp
	}
	while(temp[0] == '0') temp = temp.substr(1); //elimina eventuali zeri iniziali

	
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
