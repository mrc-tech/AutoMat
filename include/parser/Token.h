#ifndef MRC_AUTOMAT_TOKEN
#define MRC_AUTOMAT_TOKEN

#include <iostream>


enum TokenType{
	NUMBER,
	ADD, // (a + b)
	SUB, // (a - b)
	MUL, // (a * b)
	DIV, // (a / b)
	NEG, // -(a)
	Lpar, // left parenthesis
	Rpar, // right parenthesis
};


class Token
{
	private:
		TokenType type;
		double value; // ERRATISSIMO!!! dovrebbe essere un numero razionale di bignum, o meglio un raizonale di complessi...
	
	public:
		Token();
		Token(TokenType type, double value) : type(type), value(value) {}
		
		inline TokenType getType() { return type; }
		inline double getValue() { return value; }
		
		void print(); // for Debug purposes
};


// #############################################################################################################


void Token::print()
{
	if(type == ADD)		std::cout << "ADD" << std::endl;
	if(type == SUB)		std::cout << "SUB" << std::endl;
	if(type == MUL)		std::cout << "MUL" << std::endl;
	if(type == DIV)		std::cout << "DIV" << std::endl;
	if(type == NEG)		std::cout << "NEG" << std::endl;
	if(type == Lpar)	std::cout << "Lpar" << std::endl;
	if(type == Rpar)	std::cout << "Rpar" << std::endl;
	if(type == NUMBER)	std::cout << "NUM: " << value << std::endl;
}



#endif
