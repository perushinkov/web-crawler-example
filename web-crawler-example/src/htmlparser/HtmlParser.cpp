#include "HtmlParser.h"
#include "../utils/StringUtil.h"
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
void HtmlParser::CharData() {
	//TODO
}
//Comment ::= '<!--' ((Char - '-') | ('-' (Char - '-')))* '-->'
void HtmlParser::Comment() {
	lexer->match("<!--");
	//TODO
	//lexer->matchUntil("-->");
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
	//TODO
}
//Digit ::= '0'..'9'
//lexer->nextChar();

//doctypedecl ::= '<!DOCTYPE' <^[>]> '>'
void HtmlParser::doctypedecl() {
	lexer->match("<!DOCTYPE");
	//lexer->matchUntil(">");
	lexer->match(">");
}
//document ::= Misc* (doctypedecl Misc*)? element Misc* 
void HtmlParser::document() {
	//TODO
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

}
//Letter ::= [A-Za-z]
//lexer->nextChar();

//Misc ::= Comment | PI |  S
void HtmlParser::Misc() {
	//TODO
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
	//TODO
	//lexer->matchUntil("?");
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
		//TODO
		//lexer->matchUntil(";");
	}
	lexer->match(";");
}
//S ::= (<space>(32) | <tab>(9) | <CR>(13) | <LF>(10))+
//lexer->nextChar();
			
//SystemLiteral	::=	('"' [^"]* '"') | ("'" [^']* "'")
void HtmlParser::SystemLiteral() {
	char current = lexer->lookahead(0);
	if (current == '"') {
		//TODO
		//matchUntil("\"");
	} else if (current == '\'') {
		//TODO
		//matchUntil("'");
	} else {
		//TODO
		//throw something here
	}
}



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
	case rules::COMMENT: // [<]
		if (val == '<') {
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
	case rules::DOCTYPEDECL: // [<]
		if (val == '<') {
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
	case rules::ELEMENT: // [<]
		return follows(rules::BEGINTAG);
		break;
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
	case rules::MISC: // [ \r\t\n<]
		if (stringUtil::contains(" \r\t\n<", val)) {
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
	case rules::PI_enum: // [<]
		if (val == '<') {
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
	}
	return false;
}

