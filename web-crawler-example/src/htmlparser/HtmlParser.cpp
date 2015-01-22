#include "HtmlParser.h"
#include "../utils/StringUtil.h"
#include "../utils/MatchException.h"
#include <iostream>
using namespace std;

/**
 * Updates index with new word.
 *
 * If wordIndex exists, updates it,
 * else creates it.
 */
void HtmlParser::updateIndex(BinNode<StraightIndexValue> * targetIndex, char * word) {
	StraightIndexValue * wordIndex;
	wordIndex = targetIndex->findByKey((void *)word);
	if (wordIndex != nullptr) {
		wordIndex->increment();
	} else {
		targetIndex->add(new StraightIndexValue(word));
	}
}

char* HtmlParser::processLink(char* link) {
	//REMOVE VARIABLES
	int questionMarkLocation = stringUtil::findAinB("?", link);
	if (questionMarkLocation != -1)
		link = stringUtil::substring(link, questionMarkLocation);
	int len = stringUtil::length(link);
	// IF ABSOLUTE URL
	if (stringUtil::findAinB("http://", link) == 0 &&
		(stringUtil::findAinB(".htm", link) == len - 4 ||
		stringUtil::findAinB(".html", link) == len - 5)) {
		return link + 7;
	}
	

	// IF RELATIVE PATH TO A FILE
	if ( (stringUtil::findAinB(".htm", link) == len - 4 || 
		stringUtil::findAinB(".html", link) == len - 5) &&
		stringUtil::findAinB("http://", link) == -1) {
		return stringUtil::concat(urlBase_, link);
	}

	// No other hrefs supported!
	return nullptr;
}

char* HtmlParser::getBaseFromUrl(char* url) {
	if (stringUtil::findAinB("/", url) == -1) {
		return stringUtil::concat(url, "/");
	}
	else {
		for (int i = stringUtil::length(url) - 1; i > 0; i--) {
			if (*(url + i) == '/') {
				return stringUtil::substring(url, i + 1);
			}
		}
	}
	throw new exception("Base url not formed correctly!");
	return nullptr;
}

//PUBLIC

HtmlParser::HtmlParser() {
	lexer_ = nullptr;
	index_ = nullptr;
	links_ = nullptr;
}

BinNode<StraightIndexValue> * HtmlParser::getWords() {
	return index_;
}

BinNode<StraightIndexValue> * HtmlParser::getLinks() {
	return links_;
}

void HtmlParser::parse(char* t, char* url) {
	urlBase_ = getBaseFromUrl(url);
	if (index_ != nullptr) {
		delete index_;
	}
	index_ = new BinNode<StraightIndexValue>(nullptr, nullptr);

	if (links_ != nullptr) {
		delete links_;
	}
	links_ = new BinNode<StraightIndexValue>(nullptr, new StraightIndexValue("_"));
	
	lexer_ = new Lexer(t);
	content();
}


void HtmlParser::Attribute() {
	bool isHref = false;
	attrName_ = Name();
	while (lexer_->lookahead(0) != '=') {
		lexer_->nextChar();
	}
	lexer_->nextChar();
	while (lexer_->lookahead(0) != '"' && lexer_->lookahead(0) != '\'') {
		lexer_->nextChar();
	}
	attrValue_ = SystemLiteral();
}

void HtmlParser::anyTag() {
	lexer_->match("<");
	if (lexer_->isNext("!--")) {
		lexer_->matchUntil("-->");
		lexer_->match("-->");
		return;
	}
	if (lexer_->isNext("/")) lexer_->nextChar();
	char* tagName = Name();
	
	char * metaName = nullptr;   //Used only for metas
	char * metaContent = nullptr;

	while (follows(S_enum)) {
		lexer_->nextChar();
		if (follows(ATTRIBUTE)) {
			Attribute();
		}
		if (/*(!stringUtil::compare(tagName, "a") || !stringUtil::compare(tagName, "area")) &&
			*/!stringUtil::compare(attrName_, "href")) {
			char* mylink = processLink(attrValue_);
			if (mylink != nullptr) {
				updateIndex(links_, mylink);
			}
		}
		if (!stringUtil::compare(tagName, "meta")) {
			if (!stringUtil::compare(attrName_, "name")) {
				metaName = attrValue_;
			}
			if (!stringUtil::compare(attrName_, "content")) {
				metaContent = attrValue_;
			}
		}
	}
	if (metaName != nullptr && (!stringUtil::compare(metaName, "description") ||			
		!stringUtil::compare(metaName, "keywords"))) {

		Lexer lexer(attrValue_);
		char* word = lexer.findWord();
		while (word != nullptr) {
			stringUtil::toLower(word);
			updateIndex(index_, word);
			word = lexer.findWord();
		}
	}

	if (lexer_->isNext("/")) lexer_->nextChar();
	if (lexer_->matchUntil(">") != -1) {
		lexer_->match(">");
	}
	else {
		lexer_->getRemainingText();
	}	
}

void HtmlParser::CharData() {
	while (lexer_->lookahead(0) != '<') {
		if (follows(WORD)) {
			updateIndex(index_, lexer_->matchWord()); //Here is where word extraction takes place
		} else {
			if (lexer_->lookahead(0) == '\0') return;
			lexer_->nextChar(); //Can be made a bit safer here!
		}
	}
}
//content ::= (anyTag | CharData | Reference)*
void HtmlParser::content() {
	while(true) {
		if (lexer_->lookahead(0) == '\0') break;

		if (lexer_->lookahead(0) == '<'){
			anyTag();
		} else if (follows(REFERENCE)) {
			Reference();
		} else {
			CharData();
		}
	}
}

//Name ::= (Letter | '_' | ':') (NameChar)*
char * HtmlParser::Name() {
	int i = 0;

	lexer_->nextChar();
	i++;
	while (follows(NAMECHAR)) {
		lexer_->nextChar();
		i++;
	}
	return lexer_->fetchLastNChars(i);	
}

//Reference ::= ('&' Name | '&#' [0-9]+ | '&#x' [0-9a-fA-F]+) ';'
void HtmlParser::Reference() {
	lexer_->match("&");
	if (follows(NAME)) {
		Name();
	} else {
		lexer_->match("#");
		if (lexer_->lookahead(0) == 'x') {
			lexer_->match("x");
		}
		lexer_->matchUntil(";");
	}
	lexer_->match(";");
}
//S ::= (<space>(32) | <tab>(9) | <CR>(13) | <LF>(10))+
//lexer->nextChar();
			
//SystemLiteral	::=	('"' [^"]* '"') | ("'" [^']* "'")
char * HtmlParser::SystemLiteral() {
	char * retVal;
	char current = lexer_->lookahead(0);
	if (current == '"') {
		lexer_->nextChar();
		retVal = lexer_->fetchLastNChars(lexer_->matchUntil("\""));
		lexer_->match("\"");
	} else if (current == '\'') {
		lexer_->nextChar();
		retVal = lexer_->fetchLastNChars(lexer_->matchUntil("'"));
		lexer_->match("'");
	} else {
		throw new MatchException();
	}
	return retVal;
}

/**
 * Takes a look at the following symbol (or symbols where needed), 
 * and returns true if is unambiguously certain that the given rule 
 * is the one that follows .
 */
bool HtmlParser::follows(rules_ rule) {
	char val = lexer_->lookahead(0);

	switch(rule) {
	case ATTRIBUTE: //[_:A-Za-z]
		return follows(NAME);
		break;
	case ANYTAG: // <[_:A-Za-z/]
	{
		char val2 = lexer_->lookahead(1);
		if (val == '<'
			&& (val2 == '_'
			|| val2 == ':' || val2 == '/'
			|| (val2 >= 'A' && val2 <= 'Z')
			|| (val2 >= 'a' && val2 <= 'z'))) {
			return true;
		}
		break;
	}
	case NAME: //[_:A-Za-z]
		if (stringUtil::contains("_:", val) 
			|| (val>='A' && val <='Z') 
			|| (val>='a' && val <='z') ){
			return true;
		}
		break;
	case NAMECHAR: // [.-_:A-Za-z0-9]
		if (stringUtil::contains(".-_:", val)
			|| (val>='A' && val <='Z')
			|| (val>='a' && val <='z') 
			|| (val>='0' && val <='9') ) {
			return true;
		}
		break;
	case REFERENCE: // [&]
		if (val == '&') {
			return true;
		}
		break;
	case S_enum: // [\r\n\t ]
		if (stringUtil::contains("\r\n\t ", val)) {
			return true;
		}
		break;
	case SYSTEMLITERAL: // ["']
		if (stringUtil::contains("\"'", val)) {
			return true;
		}
		break;
	case WORD: // [A-Za-z]
		if ((val >= 'a' && val <= 'z')
			|| (val >= 'A' && val <= 'Z')) {
			return true;
		}
	}
	return false;
}

