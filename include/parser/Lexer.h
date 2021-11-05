/*
	LEXER
	convert a math formatted string into a sequence of tokens
	
	(c) 2021 Marchi Technology
*/
#ifndef MRC_AUTOMAT_LEXER
#define MRC_AUTOMAT_LEXER

#include <vector>
#include <string>

#include "Token.h"



class Lexer
{
	private:
		std::vector<Token> tokens;
		
		const std::string whiteSpaces = " \t\n"; // characters to be ignored
		const std::string numbers = "0123456789"; // numbers
		const std::string specialChars = "+-*/()[]{}"; // special characters
		
	public:
		Lexer();
		Lexer(std::string str);
		
		inline std::vector<Token> getTokens() { return tokens; }
		
		
		inline void print() { for(auto x : tokens) x.print(); } // for Debug
		
		
	private:
		// auxiliary functions:
		std::vector<Token> tokenizer(std::string str);
		inline bool isContained(std::string str, char c) { for(int i=0; i<str.length(); i++) if(str[i] == c) return true; return false; } // check if a character is contained into a string

};


// ########################################################################################################


Lexer::Lexer(std::string str)
{
	tokens = tokenizer(str);
}



std::vector<Token> Lexer::tokenizer(std::string str)
{
	// MI SA CHE QUESTA FUNZIONE NON HA SENSO DI ESISTERE...
	// non faccio altro che occupare piu` RAM
	std::vector<Token> res;
	int index = 0; // index for the current char of the string
	
	for(int i=0; i<str.length(); i++){
//		if(isContained(whiteSpaces, str[i])) std::cout << "Ignora" << std::endl;
//		else if(isContained(numbers, str[i])) std::cout << "Numero" << std::endl;
//		else if(isContained(specialChars, str[i])) std::cout << "Speciale" << std::endl;
//		else std::cout << "Lettera" << std::endl;
		
		
//		if(isContained(whiteSpaces, str[index])) index++; // skip ignored characters
		
		if(str[i] == '+') res.push_back(Token(ADD, 0));
		if(str[i] == '-') res.push_back(Token(SUB, 0));
		if(str[i] == '*') res.push_back(Token(MUL, 0));
		if(str[i] == '/') res.push_back(Token(DIV, 0));
		
		if(str[i] == '(') res.push_back(Token(Lpar, 0));
		if(str[i] == ')') res.push_back(Token(Rpar, 0));
		
		if(isContained(numbers, str[i])){
			std::string temp = "";
			while((isContained(numbers, str[i]) || str[i] == '.') && i < str.length()){
				temp += str[i];
				i++;
			}
			i--; // reduce index due to overshoot
			res.push_back(Token(NUMBER, atof(temp.c_str())));
		}
		
	}
	
	return res;
}







#endif
