#ifndef __LEXER_H
#define __LEXER_H 1

class Lexer{
private:
	char * text_;
	int pos_;
	char * rem_;
	
	
public:
	char nextChar();
	static enum lexemeType {SP, HTTPVERSION};
	Lexer(char * text); 

	char * getLine();
	
	void match(char * txt);
	int matchUntil(char * txt);

	bool isNext(char * txt);
	void matchSpace();
	void matchHttpVersion();
		
	char * getRemainingText();
	long matchNumber();
	char * matchWord();
	char lookahead(int howmuch);
	char * fetchLastNChars(int n);
};

#endif