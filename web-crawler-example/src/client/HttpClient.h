#ifndef __HTTPCLIENT_H
#define __HTTPCLIENT_H 1
#include <iostream>
using namespace std;
#include <winsock2.h>
#include "../utils/StringUtil.h"

#define RESPONSE_MAX_LENGTH 40000

namespace httpClient {
	/*
		These functions are used to extract the different parts of the url.
		URL = <host>/<URI>
		USAGE:
			dnslookup requires just the host part of the url
			HTTP request formation requires just uri
	*/
	char* getHostFromUrl(char* url);
	char* getUriFromUrl(char* url);

	/*
		Called just once for the initialization of the WinSock dll
	*/
	void init();

	/*
		Performs an http request and receives a response from server.
		Represents the main delay in the execution of the program.
	*/
	char * getResponse(char * url);

	/*
		Uses gethostbyname() to extract ip address
	*/
	char* getIpByHost(char *host_name);

	/*
		Trims http response and leaves just html content
	*/
	char* trimToPage(char *response);
};

#endif


