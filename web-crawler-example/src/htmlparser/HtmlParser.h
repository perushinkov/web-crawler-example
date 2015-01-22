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
	// Used to identify different NonTerminals in grammar
	enum rules_ {ANYTAG, ATTRIBUTE, CHAR, CHARDATA, NAME, NAMECHAR, REFERENCE, S_enum, SYSTEMLITERAL, WORD};

	// Two binary trees that hold words and links respectively
	BinNode<StraightIndexValue> * index_;
	BinNode<StraightIndexValue> * links_;

	// A helper that holds text and walks it via helpful methods
	Lexer * lexer_;

	/*
		This is the url of the current page minus the filename of the page
		It is used to form relative links.
	*/
	char* urlBase_;
	
	/*
		These private variables are used to keep state as the parser parses
		the text. More specifically they hold the attribute name and the attribute
		value of the currently parsed attribute. Used for analysis of metadata
		and links.
	*/
	char* attrName_;
	char* attrValue_;

	/*
		A function that updates a given index with an entry that is either
		a link or a word. If an entry already exists in the index, its occurences
		are incremented, else a new entry is created.
	*/
	void updateIndex(BinNode<StraightIndexValue> * anyIndex, char * word);
	/*
		Takes a look at the following symbol (or symbols where needed),
		and returns true if is unambiguously certain that the given rule
		is the one that follows .
	*/
	bool follows(rules_ rule);

	/*
		It proccesses links:
		1. Removes variables in url
		2. Makes sure only .html and .htm urls are processed.
		3. Handles both absolute and relative urls.

		If the result is not null, then it is a new crawlable url.
	*/
	char* processLink(char* link);

	/*
		Used to form urlBase_. See urlBase_ description.
	*/
	char* getBaseFromUrl(char* url);
public:
	HtmlParser();

	//Getters for results
	BinNode<StraightIndexValue> * getWords();
	BinNode<StraightIndexValue> * getLinks();

	/*
		These parse functions represent a highly simplified parser, based on
		the XHTML EBNF grammar.

		CONTENT: (anyTag | reference | charData)*

		ANYTAG: "<" ["/"]  (attribute)* ["/"] ">"

		ATTRIBUTE: Name "=" "\"" SystemLiteral "\""

		NAME: (Letter | '_' | ':') (NameChar)*

		SYSTEM_LITERAL: ('"' [^"]* '"') | ("'" [^']* "'")

		REFERENCE: ('&' Name | '&#' [0-9]+ | '&#x' [0-9a-fA-F]+) ';'

		CHARDATA: ([^<a-zA-Z_]*  | WORD )*

	*/

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
