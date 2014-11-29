#include "ResponseParser.h";
#include "ResponseLexer.h";
#include <iostream>;
using namespace std;

namespace spider {
	Errors ResponseParser::parse(char * t) {
		this->lexer = new ResponseLexer(t);
		return OK;
	}
	//Status-Line = HTTP-Version SP Status-Code SP Reason-Phrase CRLF
	void ResponseParser::parseStatusLine() {
	}
}