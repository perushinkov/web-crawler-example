#ifndef __RESPONSELEXER_H
#define __RESPONSELEXER_H 1

class ResponseLexer{
private:
	char * text;
	int pos;
	char nextChar();
	void match(char * txt);
public:
	static enum lexemeType {SP, HTTPVERSION};
	ResponseLexer(char * text); 

	char * getLine();
		
	void matchSpace();
	void matchHttpVersion();
		
	char * getRemainingText();
	long matchNumber();
};

#endif