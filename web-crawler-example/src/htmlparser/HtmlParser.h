#ifndef __HTMLPARSER_H
#define __HTMLPARSER_H 1
#include "..\utils\BinNode.h"
#include "..\utils\Lexer.h"
#include "StraightIndexValue.h"
/*
 * XHTML parser.
 * Note: it currently doesn't support some misformed tags that
 * HTML supports. (missing closing tags, etc)
 */
class HtmlParser {
private:
	enum rules_ {ATTRIBUTE, BEGINTAG, CHAR, CHARDATA, COMMENT, COMPOUNDTAGFINISH, CONTENT, 
		DIGIT, DOCTYPEDECL, DOCUMENT, EQ, FINISHTAG, ELEMENT, EMPTYTAGFINISH, ETAG, 
		LETTER, MISC, NAME, NAMECHAR, PI_enum, REFERENCE, S_enum, SYSTEMLITERAL, WORD};

	BinNode<StraightIndexValue> * index_;
	BinNode<StraightIndexValue> * links_;
	Lexer * lexer_;

	bool isLink_;
	char * link_;

	void updateIndex(BinNode<StraightIndexValue> * anyIndex, char * word);
	bool follows(rules_ rule);
public:
	HtmlParser();

	//Getters for results
	BinNode<StraightIndexValue> * getWords();
	BinNode<StraightIndexValue> * getLinks();


	void parse(char * page);

	//Attribute ::= Name Eq SystemLiteral
	void Attribute();
	//beginTag ::= '<' Name (S Attribute)*
	void beginTag();
	//Char ::= <CR> | <LineFeed> | <tab> | <space>..(255)
	//			lexer->nextChar();
	//CharData ::= [^<&]* - ([^<&]* ']]>' [^<&]*)
	void CharData();
	//Comment ::= '<!--' ((Char - '-') | ('-' (Char - '-')))* '-->'
	void Comment();
	//compoundTagFinish ::= '>' content ETag
	void compoundTagFinish();
	//content ::= (element | CharData | Reference | PI | Comment)*
	void content();
	//Digit ::= '0'..'9'
	//			lexer->nextChar();
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
	char * Name();
	//NameChar ::= Letter | Digit | '.' | '-' | '_' | ':';
	//		lexer->nextChar();
	//PI ::= '<?' <^[?]> '?>'
	void PI();
	//Reference ::= '&' Name ';' | '&#' [0-9]+ ';' | '&#x' [0-9a-fA-F]+ ';'
	void Reference();
	//S ::= (<space>(32) | <tab>(9) | <CR>(13) | <LF>(10))+
	//		lexer->nextChar();
	//SystemLiteral	::=	('"' [^"]* '"') | ("'" [^']* "'")
	char * SystemLiteral();
};

#endif
