#ifndef __RESPONSEPARSER_H
#define __RESPONSEPARSER_H 1

namespace spider {
	enum Errors { OK, NOTFOUND, REDIRECT, ANOTHER};

	class ResponseParser{
	private:
		ResponseLexer * lexer;
	public:
		ResponseParser(){}
		Errors parse(char * t);
	};
}
#endif