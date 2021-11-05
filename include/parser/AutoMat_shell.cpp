#include <iostream>
#include <string>

#include "Parser.h"

using namespace std;


int main(int argc, char **argv)
{
	string str;
	int index = 0; // counter for the input history
	
	if(argc > 1){
		// user insertedd a string:
		str = "";
		for(int i=1; i<argc; i++) str += string(argv[i]); // don't considerate spaces in CLI parameters
		
		Lexer lex(str); lex.print(); // CODICE DI PROVA DEL LEXER.
		
		return 0;
	}
	
	while(str != "exit" && str != "quit")
	{
		cout << "[" << index << "]>"; // METTERE CHE CI SONO DI DEFAULT 2 CIFRE, TIPO 01 02 03 05 98 99
		getline(cin,str);
		
		Lexer lex(str);
		lex.print();
		
		index++; // IN REALTA` LO INCREMENTA SOLAMENTE SE NON CI SONO ERRORI!!
	}
	
	
	return 0;
}
