#ifndef __RESPONSEPARSER_H
#define __RESPONSEPARSER_H 1
#include "ResponseLexer.h"
namespace spider {
	enum Errors { OK, NOTFOUND, REDIRECT, ANOTHER};

	class ResponseParser{
	private:
		ResponseLexer* lexer;

		void parseStatusLine();
	public:
		ResponseParser(){}
		Errors parse(char * t);
	};
}
#endif