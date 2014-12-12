#include "ResponseParser.h"
#include "ResponseLexer.h"
#include <iostream>
using namespace std;

ResponseParser::ResponseParser() {
	lexer = nullptr;
}
/*
Response =	Status-Line 
			headers
			[ message-body ]	
*/
void ResponseParser::parse(char * t) {
	if (lexer != nullptr) {
		delete lexer;
	}
	statusCode = 0;
	lexer = new ResponseLexer(t);
		
	parseStatusLine();
	parseHeaders();
	this->pageContent = lexer->getRemainingText();
}

/*
	headers = *( anyheader CRLF ) CRLF 
*/
void ResponseParser::parseHeaders() {
	char * line;
	int lengthOfLine;
	do {
		line = lexer->getLine();
		lengthOfLine = strlen(line);
	} while (lengthOfLine > 1);
}



//Status-Line = HTTP-Version SP Status-Code SP Reason-Phrase CRLF
void ResponseParser::parseStatusLine() {
	lexer->matchHttpVersion();
	lexer->matchSpace();
	statusCode = lexer->matchNumber();

	if (statusCode/100 != 2) {
		throw new exception;
	}
	//We don't need the rest of the line
	lexer->getLine();
}