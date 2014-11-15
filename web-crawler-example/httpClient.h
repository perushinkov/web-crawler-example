#ifndef __HTTPCLIENT_H
#define __HTTPCLIENT_H 1

#include <iostream>
using namespace std;

#include <winsock2.h>

class HttpClient {
private:
	int errorCode; // Negative for errors, 0 for no errors 
	int sock;

	long serverPort;
	string serverIp;
public:
	HttpClient(long serverPort, string serverIp);

	int request(string requestUri, string host);

	//symbol by symbol request will be parsed. Reading lots of it and caching will be done later.
	char * getResponse();

	//Utility methods
	int error() {return errorCode;}
};

#endif
