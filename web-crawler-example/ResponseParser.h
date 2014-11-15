#ifndef __RESPONSEPARSER_H
#define __RESPONSEPARSER_H 1

namespace spider {
	enum Errors { OK, NOTFOUND, REDIRECT, ANOTHER};

	class ResponseParser{
	private:		
		char * fetchHeader(char * text);
		void matchResponse();
		
		void matchStatusLine();
	public:
		ResponseParser(){}
		Errors parse(char * t);
	};
}
#endif