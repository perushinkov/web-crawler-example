#include "HtmlParser.h"
#include "../utils/StringUtil.h"
#include "../utils/MatchException.h"
#include <iostream>
using namespace std;

/**
 * NOTE: Word extraction takes place in CharData parse function
 *		Link extraction takes place in [TODO: find out where and how]
 */

//PRIVATE

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

void HtmlParser::parse(char * t) {
	if (index_ != nullptr) {
		delete index_;
	}
	index_ = new BinNode<StraightIndexValue>(nullptr, nullptr);

	if (links_ != nullptr) {
		delete links_;
	}
	links_ = new BinNode<StraightIndexValue>(nullptr, nullptr);
	
	lexer_ = new Lexer(t);
	document();
}


//Attribute ::= Name Eq SystemLiteral
//
void HtmlParser::Attribute() {
	bool isHref = false;
	char * attrName = Name();
	if (isLink_ && stringUtil::compare(attrName, "href")) {
		isHref = true;
	}
	if (follows(EQ)) {
		lexer_->nextChar();
	}
	if (isHref) {
		link_ = SystemLiteral();
	} else {
		SystemLiteral();
	}
	
}
//beginTag ::= '<' Name (S Attribute)* S?
void HtmlParser::beginTag() {
	isLink_ = false;
	lexer_->match("<");
	char * tagName = Name();
	if (stringUtil::compare(tagName, "a") == 0) {
		isLink_ = true;
	}
	link_ = nullptr; // Is there a memory leak here?? Not sure what happens to old value.
	while (follows(S_enum)) {
		lexer_->nextChar();
		if (follows(ATTRIBUTE)) {
			Attribute();		
		}
	}
	if (link_ != nullptr) {
		updateIndex(links_, link_);
	}
}
//Char ::= <CR> | <LineFeed> | <tab> | <space>..(255)
//lexer->nextChar();	

//CharData ::= [^<&]* - ([^<&]* ']]>' [^<&]*)
// OR
//CharData ::= (Word | [^<&A-Za-z])*
void HtmlParser::CharData() {
	while (follows(CHARDATA)) {
		if (follows(WORD)) {
			updateIndex(index_, lexer_->matchWord()); //Here is where word extraction takes place
		} else {
			lexer_->nextChar(); //Can be made a bit safer here!
		}
	}
}
//Comment ::= '<!--' ((Char - '-') | ('-' (Char - '-')))* '-->'
void HtmlParser::Comment() {
	lexer_->match("<!--");
	lexer_->matchUntil("-->");
	lexer_->match("-->");
}
//compoundTagFinish ::= '>' content ETag
void HtmlParser::compoundTagFinish() {
	lexer_->match(">");
	content();
	ETag();
}
//content ::= (element | CharData | Reference | PI | Comment)*
void HtmlParser::content() {
	while(true) {
		if (follows(ELEMENT)) {
			element();
		} else if (follows(CHARDATA)) {
			CharData();
		} else if (follows(REFERENCE)) {
			Reference();
		} else if (follows(PI_enum)) {
			PI();
		} else if (follows(COMMENT)) {
			Comment();
		} else {
			break;
		}
	}
}
//doctypedecl ::= '<!DOCTYPE' <^[>]> '>'
void HtmlParser::doctypedecl() {
	lexer_->match("<!DOCTYPE");
	lexer_->matchUntil(">");
	lexer_->match(">");
}
//document ::= Misc* (doctypedecl Misc*)? element Misc* 
void HtmlParser::document() {
	while (follows(MISC)) {
		Misc();
	}
	if (follows(DOCTYPEDECL)) {
		doctypedecl();
		while (follows(MISC)) {
			Misc();
		}
	}
	
	element();

	while (follows(MISC)) {
		Misc();
	}
}
//Eq ::= S? '=' S?
void HtmlParser::Eq() {
	if (follows(S_enum)) {
		lexer_->nextChar();
	}
	lexer_->match("=");
	if (follows(S_enum)) {
		lexer_->nextChar();
	}
}
//finishTag ::= emptyTagFinish | compoundTagFinish
void HtmlParser::finishTag() {
	if (follows(EMPTYTAGFINISH)) {
		emptyTagFinish();
	} else if(follows(COMPOUNDTAGFINISH)) {
		compoundTagFinish();
	} else {
		throw new MatchException();
	}
}
//element ::= beginTag finishTag
void HtmlParser::element() {
	beginTag();
	finishTag();
}
//emptyTagFinish ::= '/>'
void HtmlParser::emptyTagFinish() {
	lexer_->match("/>");
}
//ETag ::= '</' Name S? '>'
void HtmlParser::ETag() {
	lexer_->match("</");
	Name();
	if (follows(S_enum)) {
		lexer_->nextChar();
	}
	lexer_->match(">");
}
//Letter ::= [A-Za-z]
//lexer->nextChar();

//Misc ::= Comment | PI |  S
void HtmlParser::Misc() {
	if (follows(S_enum)) {
		lexer_->nextChar();
	} else if (follows(COMMENT)) {
		Comment();
	} else {
		PI();
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
//NameChar ::= Letter | Digit | '.' | '-' | '_' | ':';
//lexer->nextChar();

//PI ::= '<?' <^[?]> '?>'
void HtmlParser::PI() {
	lexer_->match("<?");
	lexer_->matchUntil("?>");
	lexer_->match("?>");
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
	case BEGINTAG: //[<]
		if (val == '<') {
			return true;
		}
		break;
	case CHAR: // <CR>,<tab>,<LF>,[<space>-255]
		if (stringUtil::contains("\r\t\n ", val)
			|| val > ' ') {
			return true;
		}
		break;
	case CHARDATA: // [^<&]
		if (!stringUtil::contains("<&", val)) {
			return true;
		}
		break;
	case COMMENT: // Must differentiate from PI
		if (lexer_->isNext("<!-")) {
			return true;
		}
		break;
	case COMPOUNDTAGFINISH: // [>]
		if ('>') {
			return true;
		}
		break;
	case DIGIT: // [0-9]
		if (val >= '0' && val <= '9') {
			return true;
		}
		break;
	case DOCTYPEDECL: // Must differentiate from element
		if (lexer_->isNext("<!D")) {
			return true;
		}
		break;
	case EQ: // [ \t\r\n=]
		if (stringUtil::contains(" \t\r\n=", val)) {
			return true;
		}
		break;
	case FINISHTAG: // [/>]
		if (stringUtil::contains("/>", val)) {
			return true;
		}
		break;
	case ELEMENT: // <[_:A-Za-z]
	{
		char val2 = lexer_->lookahead(1);
		if (val == '<' 
			&& (val2 == '_' 
				|| val2 == ':'
				|| (val2 >= 'A' && val2 <= 'Z')
				|| (val2 >= 'a' && val2 <= 'z'))) {
			return true;
		}
		break;
	}
	case EMPTYTAGFINISH: // [/]
		if (val == '/') {
			return true;
		}
		break;
	case ETAG: // [/]
		if (val == '/') {
			return true;
		}
		break;
	case LETTER: // [A-Za-z]
		if ((val>='A' && val <='Z') 
			|| (val>='a' && val <='z') ){
			return true;
		}
		break;
	case MISC:
		// NonTrivial. Needs to return true only when what 
		// follows is just Misc and not doctypedecl or element
		// because of document rule:
		if (follows(S_enum) || lexer_->isNext("<?") || lexer_->isNext("<!--")) {
			return true;
		}
		break;
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
	case PI_enum: // <?
		if (lexer_->isNext("<?")) {
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

