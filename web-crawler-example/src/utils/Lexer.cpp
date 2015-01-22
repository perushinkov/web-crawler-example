#include "Lexer.h"
#include "StringUtil.h"
#include "MatchException.h"

#include <iostream>
using namespace std;
#include <stdlib.h>
#include <string.h>
#include "StringUtil.h"

Lexer::Lexer(char * text) {
	text_ = text;
	int endOfFilePosition = stringUtil::findAinB("</html>", text_);
	if (endOfFilePosition != -1)
		*(text_ + endOfFilePosition + 7) = '\0';
	char* test = text_ + endOfFilePosition;
	pos_ = 0;
}

char * Lexer::getLine() {
	int startPosition = pos_;
	char current = text_[pos_];
	while(current != '\n' && current != '\0') {
		current = nextChar();
	} 
	char * line = (char *)malloc(pos_ - startPosition + 1);
	line[pos_ - startPosition] = '\0';
	stringUtil::copy(text_ + startPosition, line, pos_ - startPosition);

	current = nextChar();
	return line;
}
/**
 * Returns '\0' upon reaching end of string.
 * Caller is responsible for not calling nextChar() when there is no next char.
 */
char Lexer::nextChar() {
	pos_++;
	rem_ = text_ + pos_;
	return text_[pos_];
}

char * Lexer::getRemainingText() {
	int charsRemaining = strlen(text_ + pos_);
	char * remainder = (char *)malloc(charsRemaining + 1);
	remainder[charsRemaining] = '\0';
	stringUtil::copy(text_ + pos_, remainder, charsRemaining);
	return remainder;
}

/**
 * Reads from the text the text that is sent as parameter.
 * If it is not the same function returns false.
 */
void Lexer::match(char * txt) {
	int len = strlen(txt);

	char * remaining = text_ + pos_;
	char current = text_[pos_];
	for (int i = 0; i < len; i++) {
		if (current != txt[i]) {
			throw new MatchException;
		}
		current = nextChar();
	}
}
/**
 * Matches text until it meets a certain expression txt. 
 * Does not match the txt expression.
 * Returns number of matched characters.
 * 
 * Example:
 * TextRemaining: "we are! They are, you are!"
 *	matchUntil("are,");
 * TextRemaining after call: "are, you are!"
 */
int Lexer::matchUntil(char * txt) {
	int displacement = stringUtil::findAinB(txt, text_ + pos_);
	if (displacement != -1)
		pos_ += displacement;
	return displacement;
}


bool Lexer::isNext(char * txt) {
	int relPos = stringUtil::findAinB(txt, text_ + pos_);
	if (relPos == 0) {
		return true;
	}
	return false;
}

/**
* Matches word containing English letters.
* Words are reduced to lowerCase.
*/
char * Lexer::matchWord() {
	int startPos = pos_;
	char current = text_[pos_];
	while ((current >= 'A' && current <= 'Z')
		|| (current >= 'a' && current <= 'z')) {
		current = nextChar();
	}
	if (/*current == 0 || */startPos == pos_) {
		return nullptr;
	}


	char * word = stringUtil::substring(text_ + startPos, pos_ - startPos);
	stringUtil::toLower(word);
	return word;
}

/**
* Finds next word and returns it or returns nullptr.
*/
char * Lexer::findWord() {
	char current = text_[pos_];
	while (!((current >= 'A' && current <= 'Z')
		|| (current >= 'a' && current <= 'z')) && 
		current != '\0') {
		current = nextChar();
	}
	if (current != '\0') return matchWord();
	return nullptr;
}

char Lexer::lookahead(int howmuch) {
	return *(text_ + pos_ + howmuch);
}

char * Lexer::fetchLastNChars(int n) {
	char * retVal = (char *)malloc(n + 1);
	retVal[n] = '\0';
	stringUtil::copy(text_ + pos_ - n, retVal, n);
	return retVal;
}