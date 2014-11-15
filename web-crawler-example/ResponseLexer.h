#ifndef __RESPONSELEXER_H
#define __RESPONSELEXER_H 1

namespace spider {
	class ResponseLexer{
	private:
		char * text;
		int pos;
	public:
		ResponseLexer(char * text); 
	};
}
#endif