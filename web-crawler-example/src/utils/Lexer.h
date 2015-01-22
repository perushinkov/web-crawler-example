#ifndef __LEXER_H
#define __LEXER_H 1

/*
	A utility class that is initialized with a text, which it then
	walks via its helpful methods.
*/
class Lexer{
private:
	char * text_;
	int pos_;
	char * rem_;
	
	
public:
	/*
		Reads a char. Exceptionn if end of text.
	*/
	char nextChar();
	static enum lexemeType {SP, HTTPVERSION};
	Lexer(char * text); 

	/*
		Reads a line from the text and returns it
	*/
	char * getLine();
	
	/*
		Matches text. This means that it reads this text from the current position.
		If this teext does not follow, an exception is thrown.
	*/
	void match(char * txt);

	/*
		Matches until it meets a certain text. Note that it does not read this text.
	*/
	int matchUntil(char * txt);

	/*
		Returns true if parameter text follows.
	*/
	bool isNext(char * txt);
	/*
		Reads and returns remaining text.
	*/
	char * getRemainingText();
	/*
		Reads a word. Words are reduced to lowercase. IF no word follows, returns nullptr.
	*/
	char * matchWord();
	/*
		Finds next word and returns it or returns nullptr.
	*/
	char * findWord();
	/*
		Returns a character ahead of current position, without moving the current position.
	*/
	char lookahead(int howmuch);
	/*
		Fetches last n characters from current position. Does not move read pointer.
	*/
	char * fetchLastNChars(int n);
};

#endif