#include "ResponseLexer.h"
#include "StringUtil.h"
#include "MatchException.h"

#include <stdlib.h>
#include <string.h>
#include "StringUtil.h"
namespace spider{
	
	ResponseLexer::ResponseLexer(char * text) {
		this->text = text;
		pos = 0;
	}

	char * ResponseLexer::getLine() {
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
	char ResponseLexer::nextChar() {
		pos++;
		return text[pos];
	}

	void ResponseLexer::rewind() {
		this->pos = 0;
	}

	char * ResponseLexer::getLexeme(lexemeType type) {
		switch(type) {
		case SP:
			nextChar();
			return nullptr;
		case HTTPVERSION:
			//HTTP-Version   = "HTTP" "/" 1*DIGIT "." 1*DIGIT
			match("HTTP/");
			matchNumber();
			match(".");
			matchNumber();
			return nullptr;
		}
	}
	/**
	 * Reads from the text the text that is sent as parameter.
	 * If it is not the same function returns false.
	 */
	void ResponseLexer::match(char * txt) {
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
	long ResponseLexer::matchNumber() {
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
}
