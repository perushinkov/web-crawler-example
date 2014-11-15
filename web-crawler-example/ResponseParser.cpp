#include "ResponseParser.h";
#include <iostream>;
using namespace std;

namespace spider {
	Errors ResponseParser::parse(char * t) {
		char * headerText = fetchHeader(t);
		matchResponse();
		return OK;
	}

	char * ResponseParser::fetchHeader(char * text) {
		int pos = 1;
		while (text[pos] != '\n' && text[pos-1] != '\n') {
			pos++;
		} 
		char * retText = (char *)malloc(pos+1);
		for (int i = 0; i < pos+1; i++) {
			retText[i] = text[i];
		}
		return retText;
	}
	
	/** 
	 *	Response =
	 *		Status-Line
     *		*(( general-header 
	 *		 | response-header 
	 *		 | entity-header ) CRLF) 
	 *		 CRLF
	 *		 [ message-body ]
	 *
	 */
	void ResponseParser::matchResponse() {
		matchStatusLine();

	}

	// Status-Line = HTTP-Version SP Status-Code SP Reason-Phrase CRLF
	void ResponseParser::matchStatusLine() {
	}
}