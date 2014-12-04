#include "ResponseParser.h";
#include "ResponseLexer.h";
#include <iostream>;
using namespace std;

namespace spider {
	Errors ResponseParser::parse(char * t) {
		statusCode = 0;
		lexer = new ResponseLexer(t);
		
		parseStatusLine();

		char * line;
		int mint;
		do {
			line = lexer->getLine();
			mint = strlen(line);
			printf("%s %d\n", line, mint);
		} while(mint != 1);
		return OK;
	}
	//Status-Line = HTTP-Version SP Status-Code SP Reason-Phrase CRLF
	void ResponseParser::parseStatusLine() {
		lexer->getLexeme(lexer->HTTPVERSION);
		lexer->getLexeme(lexer->SP);
		statusCode = lexer->matchNumber();

		if (statusCode/100 != 2) {
			throw new exception;
		}
		//We don't need the rest of the line
		lexer->getLine();
	}
}