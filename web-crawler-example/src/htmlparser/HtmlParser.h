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
	enum rules_ {ANYTAG, ATTRIBUTE, CHAR, CHARDATA, NAME, NAMECHAR, REFERENCE, S_enum, SYSTEMLITERAL, WORD};

	BinNode<StraightIndexValue> * index_;
	BinNode<StraightIndexValue> * links_;
	Lexer * lexer_;

	char* urlBase_;
	
	char* attrName_;
	char* attrValue_;

	void updateIndex(BinNode<StraightIndexValue> * anyIndex, char * word);
	bool follows(rules_ rule);
	char* processLink(char* link);
	char* getBaseFromUrl(char* url);
public:
	HtmlParser();

	//Getters for results
	BinNode<StraightIndexValue> * getWords();
	BinNode<StraightIndexValue> * getLinks();

	void parse(char * page, char * url);

	
	void Attribute();	
	void anyTag();
	void CharData();
	void content();
	char * Name();
	void Reference();
	char * SystemLiteral();
};

#endif
