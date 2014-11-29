#include "ResponseLexer.h"
#include "StringUtil.h"
#include "MatchException.h"

#include <stdlib.h>
#include <string.h>
namespace spider{
	
	ResponseLexer::ResponseLexer(char * text) {
		this->text = text;
		pos = 0;
	}

	char * ResponseLexer::getLine() {
		int startPosition = this->pos;
		char current;
		do {
			current = this->nextChar();
		} while(current != '\n' || current != '\0');
		char * line = (char *)malloc(pos - startPosition + 1);
		line[pos - startPosition] = '\0';
		//StringUtil.copy(text, line, current - startPosition);
		return line;
		return nullptr;
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
		for (int i = 0; i < len; i++) {
			if (nextChar() != txt[i]) {
				throw new MatchException;
			}
		}
	}

	/**
	 * Reads from the text a number.
	 * If the text does not start with a digit returns false.
	 */
	long ResponseLexer::matchNumber() {
		long num = 0;
		char current = 0;
		while(current >= '0' && current <= '9') {
			current = this->nextChar();
			num *= 10;
			num += current - '0';
		}
		if (current == 0) {
			throw new MatchException;
		}
		return num;
	}
}
