#ifndef __HTTPCLIENT_H
#define __HTTPCLIENT_H 1
#include "ResponseParser.h"
#include <iostream>
using namespace std;

#include <winsock2.h>

#define RESPONSE_MAX_LENGTH 100000

class HttpClient {
private:
	char text_[RESPONSE_MAX_LENGTH];
	int errorCode_; // Negative for errors, 0 for no errors 
	int sock_;

	u_short serverPort_;
	char * serverIp_;

	ResponseParser * parser_;

	//Methods
	char * getResponse();
public:

	HttpClient();
	void init(char * domainName);
	int request(char * requestUri, char * host);

	//symbol by symbol request will be parsed. Reading lots of it and caching will be done later.
	char * getPage();
	char * getIp();
	//Utility methods
	int error() {return errorCode_;}

	// Static util functions
	static u_long getIpByHost(char *host_name);
	static bool WinsockInitialized();
	static char* getHostFromUrl(char* url); 
	static char* getUriFromUrl(char* url); 
};

#endif


