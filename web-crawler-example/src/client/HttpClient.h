#ifndef __HTTPCLIENT_H
#define __HTTPCLIENT_H 1
#include "ResponseParser.h"
#include <iostream>
using namespace std;

#include <winsock2.h>

class HttpClient {
private:
	int errorCode; // Negative for errors, 0 for no errors 
	int sock;

	long serverPort;
	char * serverIp;
	char * getResponse();

	ResponseParser * parser;
public:
	HttpClient();
	void init(char * serverIp);
	int request(char * requestUri, char * host);

	//symbol by symbol request will be parsed. Reading lots of it and caching will be done later.
	char * getPage();
	//Utility methods
	int error() {return errorCode;}
};

#endif
