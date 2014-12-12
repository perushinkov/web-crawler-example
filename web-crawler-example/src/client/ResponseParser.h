#ifndef __RESPONSEPARSER_H
#define __RESPONSEPARSER_H 1
#include "ResponseLexer.h"

class ResponseParser{
private:
	long statusCode;
	char * pageContent;
	ResponseLexer* lexer;


	void parseStatusLine();
	void parseHeaders();
public:
	ResponseParser();
	void parse(char * t);

	char * getPageContent() {
		return pageContent;
	}
};

#endif