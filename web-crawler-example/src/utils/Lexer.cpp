#include "Lexer.h"
#include "StringUtil.h"
#include "MatchException.h"

#include <iostream>
using namespace std;
#include <stdlib.h>
#include <string.h>
#include "StringUtil.h"

Lexer::Lexer(char * text) {
	this->text = text;
	pos = 0;
}

char * Lexer::getLine() {
	int startPosition = this->pos;
	char current = text[pos];
	while(current != '\n' && current != '\0') {
		current = this->nextChar();
	} 
	char * line = (char *)malloc(pos - startPosition + 1);
	line[pos - startPosition] = '\0';
	stringUtil::copy(text + startPosition, line, pos - startPosition);

	current = this->nextChar();
	return line;
}
/**
	* Returns '\0' upon reaching end of string.
	* Caller is responsible for not calling nextChar() when there is no next char.
	*/
char Lexer::nextChar() {
	pos++;
	return text[pos];
}

char * Lexer::getRemainingText() {
	int charsRemaining = strlen(text + pos);
	char * remainder = (char *)malloc(charsRemaining + 1);
	remainder[charsRemaining] = '\0';
	stringUtil::copy(text+pos,remainder,charsRemaining);
	return remainder;
}

void Lexer::matchSpace() {
	nextChar();
}
//HTTP-Version   = "HTTP" "/" 1*DIGIT "." 1*DIGIT
void Lexer::matchHttpVersion() {
		match("HTTP/");
		matchNumber();
		match(".");
		matchNumber();
}




/**
	* Reads from the text the text that is sent as parameter.
	* If it is not the same function returns false.
	*/
void Lexer::match(char * txt) {
	int len = strlen(txt);
	char current = text[pos];
	for (int i = 0; i < len; i++) {
		if (current != txt[i]) {
			throw new MatchException;
		}
		current = nextChar();
	}
}

/**
	* Reads from the text a number.
	* If the text does not start with a digit returns false.
	*/
long Lexer::matchNumber() {
	long num = 0;
	char current = text[pos];
	while(current >= '0' && current <= '9') {
		num *= 10;
		num += current - '0';
		current = this->nextChar();
	}
	if (current == 0) {
		throw new MatchException;
	}
	return num;
}


char Lexer::lookahead(int howmuch) {
	return *(text + howmuch);
}
