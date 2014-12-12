#ifndef __HTMLPARSER_H
#define __HTMLPARSER_H 1
#include "..\utils\BinNode.h"
#include "..\utils\Lexer.h"
#include "StraightIndexValue.h"
/*
 * TODO: Finish this
 */
class HtmlParser {
private:
	enum rules {ATTRIBUTE, BEGINTAG, CHAR, CHARDATA, COMMENT, COMPOUNDTAGFINISH, CONTENT, 
		DIGIT, DOCTYPEDECL, DOCUMENT, EQ, FINISHTAG, ELEMENT, EMPTYTAGFINISH, ETAG, 
		LETTER, MISC, NAME, NAMECHAR, PI_enum, REFERENCE, S_enum, SYSTEMLITERAL};

	BinNode<StraightIndexValue> * index;
	Lexer * lexer;
public:
	HtmlParser();
	void parse(char * page);
	
	bool follows(rules rule);

	//Attribute ::= Name Eq SystemLiteral
	void Attribute();
	//beginTag ::= '<' Name (S Attribute)*
	void beginTag();
	//Char ::= <CR> | <LineFeed> | <tab> | <space>..(255)
	void Char();
	//CharData ::= [^<&]* - ([^<&]* ']]>' [^<&]*)
	void CharData();
	//Comment ::= '<!--' ((Char - '-') | ('-' (Char - '-')))* '-->'
	void Comment();
	//compoundTagFinish ::= '>' content ETag
	void compoundTagFinish();
	//content ::= (element | CharData | Reference | PI | Comment)*
	void content();
	//Digit ::= '0'..'9'
	void Digit();
	//doctypedecl ::= '<!DOCTYPE' <^[>]> '>'
	void doctypedecl();
	//document ::= Misc* (doctypedecl Misc*)? element Misc* 
	void document();
	//Eq ::= S? '=' S?
	void Eq();
	//finishTag ::= emptyTagFinish | compoundTagFinish
	void finishTag();
	//element ::= beginTag S? finishTag
	void element();
	//emptyTagFinish ::= '/>'
	void emptyTagFinish();
	//ETag ::= '</' Name S? '>'
	void ETag();
	//Letter ::= [A-Za-z]
	void Letter();
	//Misc ::= Comment | PI |  S
	void Misc();
	//Name ::= (Letter | '_' | ':') (NameChar)*
	void Name();
	//NameChar ::= Letter | Digit | '.' | '-' | '_' | ':';
	void NameChar();
	//PI ::= '<?' <^[?]> '?>'
	void PI();
	//Reference ::= '&' Name ';' | '&#' [0-9]+ ';' | '&#x' [0-9a-fA-F]+ ';'
	void Reference();
	//S ::= (<space>(32) | <tab>(9) | <CR>(13) | <LF>(10))+
	void S();
	//SystemLiteral	::=	('"' [^"]* '"') | ("'" [^']* "'")
	void SystemLiteral();
};

#endif
