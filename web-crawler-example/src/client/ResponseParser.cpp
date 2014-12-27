#include "ResponseParser.h"
#include "../utils/Lexer.h"
#include <iostream>
using namespace std;

ResponseParser::ResponseParser() {
	lexer_ = nullptr;
}
/*
Response =	Status-Line 
			headers
			[ message-body ]	
*/
void ResponseParser::parse(char * t) {
	if (lexer_ != nullptr) {
		delete lexer_;
	}
	statusCode_ = 0;
	lexer_ = new Lexer(t);
		
	parseStatusLine();
	parseHeaders();
	pageContent_ = lexer_->getRemainingText();
}

/*
	headers = *( anyheader CRLF ) CRLF 
*/
void ResponseParser::parseHeaders() {
	char * line;
	int lengthOfLine;
	do {
		line = lexer_->getLine();
		lengthOfLine = strlen(line);
	} while (lengthOfLine > 1);
}



//Status-Line = HTTP-Version SP Status-Code SP Reason-Phrase CRLF
void ResponseParser::parseStatusLine() {
	lexer_->matchHttpVersion();
	lexer_->matchSpace();
	statusCode_ = lexer_->matchNumber();

	if (statusCode_/100 != 2) {
		throw new exception;
	}
	//We don't need the rest of the line
	lexer_->getLine();
}