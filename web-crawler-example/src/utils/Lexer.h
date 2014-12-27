#ifndef __LEXER_H
#define __LEXER_H 1

class Lexer{
private:
	char * text;
	int pos;
	char * rem;
	
	
public:
	char nextChar();
	static enum lexemeType {SP, HTTPVERSION};
	Lexer(char * text); 

	char * getLine();
	
	void match(char * txt);
	void matchUntil(char * txt);

	bool isNext(char * txt);
	void matchSpace();
	void matchHttpVersion();
		
	char * getRemainingText();
	long matchNumber();
	char * matchWord();
	char lookahead(int howmuch);
};

#endif