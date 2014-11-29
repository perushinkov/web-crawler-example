#ifndef __RESPONSELEXER_H
#define __RESPONSELEXER_H 1

namespace spider {
	class ResponseLexer{
	private:
		char * text;
		int pos;
		char nextChar();
		void match(char * txt);
	public:
		enum lexemeType {SP, HTTPVERSION};
		ResponseLexer(char * text); 

		char * getLine();
		void rewind();
		char * getLexeme(lexemeType type);
		long matchNumber();
	};
}
#endif