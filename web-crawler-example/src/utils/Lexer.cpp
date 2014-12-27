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
	this->rem = text + pos;
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

	char * remaining = text + pos;
	char current = text[pos];
	for (int i = 0; i < len; i++) {
		if (current != txt[i]) {
			throw new MatchException;
		}
		current = nextChar();
	}
}
/**
 * Matches text until it meets a certain expression txt. 
 * Does not match this expression.
 * 
 * Example:
 * TextRemaining: "we are! They are, you are!"
 *	matchUntil("are,");
 * TextRemaining after call: "are, you are!"
 */
void Lexer::matchUntil(char * txt) {
	pos += stringUtil::findAinB(txt, text + pos);
}


bool Lexer::isNext(char * txt) {
	int relPos = stringUtil::findAinB(txt, text + pos);
	if (relPos == 0) {
		return true;
	}
	return false;
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
/**
 * Matches word containing English letters.
 * Words are reduced to lowerCase.
 */
char * Lexer::matchWord() {
	int startPos = pos;
	char current = text[pos];
	while((current >= 'A' && current <= 'Z')
		  || (current >= 'a' && current <= 'z')) {
		current = this->nextChar();
	}
	if (current == 0 || startPos == pos) {
		throw new MatchException;
	}


	char * word = stringUtil::substring(text + startPos, pos - startPos);
	stringUtil::toLower(word);
	return word;
}
char Lexer::lookahead(int howmuch) {
	return *(text + pos + howmuch);
}
