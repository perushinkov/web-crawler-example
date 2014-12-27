#include "HtmlParser.h"
#include "../utils/StringUtil.h"
#include "../utils/MatchException.h"
#include <iostream>
using namespace std;
HtmlParser::HtmlParser() {
	this->lexer = nullptr;
	this->index = nullptr;
}

void HtmlParser::parse(char * t) {
	lexer = new Lexer(t);
	document();
}


//Attribute ::= Name Eq SystemLiteral
void HtmlParser::Attribute() {
	Name();
	if (follows(rules::EQ)) {
		lexer->nextChar();
	}
	SystemLiteral();
}
//beginTag ::= '<' Name (S Attribute)* S?
void HtmlParser::beginTag() {
	char current;
	lexer->match("<");
	Name();
	while (follows(rules::S_enum)) {
		lexer->nextChar();
		if (follows(rules::ATTRIBUTE)) {
			Attribute();		
		}
	}
}
//Char ::= <CR> | <LineFeed> | <tab> | <space>..(255)
//lexer->nextChar();	

//CharData ::= [^<&]* - ([^<&]* ']]>' [^<&]*)
// OR
//CharData ::= (Word | [^<&A-Za-z])*
void HtmlParser::CharData() {
	while (follows(rules::CHARDATA)) {
		if (follows(rules::WORD)) {
			cout<<lexer->matchWord()<<endl;
		} else {
			lexer->nextChar();
		}
	}
}
//Comment ::= '<!--' ((Char - '-') | ('-' (Char - '-')))* '-->'
void HtmlParser::Comment() {
	lexer->match("<!--");
	lexer->matchUntil("-->");
	lexer->match("-->");
}
//compoundTagFinish ::= '>' content ETag
void HtmlParser::compoundTagFinish() {
	lexer->match(">");
	content();
	ETag();
}
//content ::= (element | CharData | Reference | PI | Comment)*
void HtmlParser::content() {
	while(true) {
		if (follows(rules::ELEMENT)) {
			element();
		} else if (follows(rules::CHARDATA)) {
			CharData();
		} else if (follows(rules::REFERENCE)) {
			Reference();
		} else if (follows(rules::PI_enum)) {
			PI();
		} else if (follows(rules::COMMENT)) {
			Comment();
		} else {
			break;
		}
	}
}
//doctypedecl ::= '<!DOCTYPE' <^[>]> '>'
void HtmlParser::doctypedecl() {
	lexer->match("<!DOCTYPE");
	lexer->matchUntil(">");
	lexer->match(">");
}
//document ::= Misc* (doctypedecl Misc*)? element Misc* 
void HtmlParser::document() {
	while (follows(rules::MISC)) {
		Misc();
	}
	if (follows(rules::DOCTYPEDECL)) {
		doctypedecl();
		while (follows(rules::MISC)) {
			Misc();
		}
	}
	
	element();

	while (follows(rules::MISC)) {
		Misc();
	}
}
//Eq ::= S? '=' S?
void HtmlParser::Eq() {
	if (follows(rules::S_enum)) {
		lexer->nextChar();
	}
	lexer->match("=");
	if (follows(rules::S_enum)) {
		lexer->nextChar();
	}
}
//finishTag ::= emptyTagFinish | compoundTagFinish
void HtmlParser::finishTag() {
	if (follows(rules::EMPTYTAGFINISH)) {
		emptyTagFinish();
	} else if(follows(rules::COMPOUNDTAGFINISH)) {
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
	lexer->match("/>");
}
//ETag ::= '</' Name S? '>'
void HtmlParser::ETag() {
	lexer->match("</");
	Name();
	if (follows(rules::S_enum)) {
		lexer->nextChar();
	}
	lexer->match(">");
}
//Letter ::= [A-Za-z]
//lexer->nextChar();

//Misc ::= Comment | PI |  S
void HtmlParser::Misc() {
	if (follows(rules::S_enum)) {
		lexer->nextChar();
	} else if (follows(rules::COMMENT)) {
		Comment();
	} else {
		PI();
	}
}

//Name ::= (Letter | '_' | ':') (NameChar)*
void HtmlParser::Name() {
	lexer->nextChar();
	while (follows(rules::NAMECHAR)) {
		lexer->nextChar();
	}
}
//NameChar ::= Letter | Digit | '.' | '-' | '_' | ':';
//lexer->nextChar();

//PI ::= '<?' <^[?]> '?>'
void HtmlParser::PI() {
	lexer->match("<?");
	lexer->matchUntil("?>");
	lexer->match("?>");
}
//Reference ::= ('&' Name | '&#' [0-9]+ | '&#x' [0-9a-fA-F]+) ';'
void HtmlParser::Reference() {
	lexer->match("&");
	if (follows(rules::NAME)) {
		Name();
	} else {
		lexer->match("#");
		if (lexer->lookahead(0) == 'x') {
			lexer->match("x");
		}
		lexer->matchUntil(";");
	}
	lexer->match(";");
}
//S ::= (<space>(32) | <tab>(9) | <CR>(13) | <LF>(10))+
//lexer->nextChar();
			
//SystemLiteral	::=	('"' [^"]* '"') | ("'" [^']* "'")
void HtmlParser::SystemLiteral() {
	char current = lexer->lookahead(0);
	if (current == '"') {
		lexer->nextChar();
		lexer->matchUntil("\"");
		lexer->match("\"");
	} else if (current == '\'') {
		lexer->nextChar();
		lexer->matchUntil("'");
		lexer->match("'");
	} else {
		throw new MatchException();
	}
}

/**
 * Takes a look at the following symbol (or symbols where needed), 
 * and returns true if is unambiguously certain that the given rule 
 * is the one that follows .
 */
bool HtmlParser::follows(rules rule) {
	char val = lexer->lookahead(0);

	switch(rule) {
	case rules::ATTRIBUTE: //[_:A-Za-z]
		return follows(rules::NAME);
		break;
	case rules::BEGINTAG: //[<]
		if (val == '<') {
			return true;
		}
		break;
	case rules::CHAR: // <CR>,<tab>,<LF>,[<space>-255]
		if (stringUtil::contains("\r\t\n ", val)
			|| val > ' ') {
			return true;
		}
		break;
	case rules::CHARDATA: // [^<&]
		if (!stringUtil::contains("<&", val)) {
			return true;
		}
		break;
	case rules::COMMENT: // Must differentiate from PI
		if (lexer->isNext("<!-")) {
			return true;
		}
		break;
	case rules::COMPOUNDTAGFINISH: // [>]
		if ('>') {
			return true;
		}
		break;
	case rules::DIGIT: // [0-9]
		if (val >= '0' && val <= '9') {
			return true;
		}
		break;
	case rules::DOCTYPEDECL: // Must differentiate from element
		if (lexer->isNext("<!D")) {
			return true;
		}
		break;
	case rules::EQ: // [ \t\r\n=]
		if (stringUtil::contains(" \t\r\n=", val)) {
			return true;
		}
		break;
	case rules::FINISHTAG: // [/>]
		if (stringUtil::contains("/>", val)) {
			return true;
		}
		break;
	case rules::ELEMENT: // <[_:A-Za-z]
	{
		char val2 = lexer->lookahead(1);
		if (val == '<' 
			&& (val2 == '_' 
				|| val2 == ':'
				|| (val2 >= 'A' && val2 <= 'Z')
				|| (val2 >= 'a' && val2 <= 'z'))) {
			return true;
		}
		break;
	}
	case rules::EMPTYTAGFINISH: // [/]
		if (val == '/') {
			return true;
		}
		break;
	case rules::ETAG: // [/]
		if (val == '/') {
			return true;
		}
		break;
	case rules::LETTER: // [A-Za-z]
		if ((val>='A' && val <='Z') 
			|| (val>='a' && val <='z') ){
			return true;
		}
		break;
	case rules::MISC:
		// NonTrivial. Needs to return true only when what 
		// follows is just Misc and not doctypedecl or element
		// because of document rule:
		if (follows(rules::S_enum) || lexer->isNext("<?") || lexer->isNext("<!--")) {
			return true;
		}
		break;
	case rules::NAME: //[_:A-Za-z]
		if (stringUtil::contains("_:", val) 
			|| (val>='A' && val <='Z') 
			|| (val>='a' && val <='z') ){
			return true;
		}
		break;
	case rules::NAMECHAR: // [.-_:A-Za-z0-9]
		if (stringUtil::contains(".-_:", val)
			|| (val>='A' && val <='Z')
			|| (val>='a' && val <='z') 
			|| (val>='0' && val <='9') ) {
			return true;
		}
		break;
	case rules::PI_enum: // <?
		if (lexer->isNext("<?")) {
			return true;
		}
		break;
	case rules::REFERENCE: // [&]
		if (val == '&') {
			return true;
		}
		break;
	case rules::S_enum: // [\r\n\t ]
		if (stringUtil::contains("\r\n\t ", val)) {
			return true;
		}
		break;
	case rules::SYSTEMLITERAL: // ["']
		if (stringUtil::contains("\"'", val)) {
			return true;
		}
		break;
	case rules::WORD: // [A-Za-z]
		if ((val >= 'a' && val <= 'z')
			|| (val >= 'A' && val <= 'Z')) {
			return true;
		}
	}
	return false;
}

