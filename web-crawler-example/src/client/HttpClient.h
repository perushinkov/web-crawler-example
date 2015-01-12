#ifndef __HTTPCLIENT_H
#define __HTTPCLIENT_H 1
#include <iostream>
using namespace std;
#include <winsock2.h>
#include "../utils/StringUtil.h"

#define RESPONSE_MAX_LENGTH 30000

namespace httpClient {

	char* getHostFromUrl(char* url);
	char* getUriFromUrl(char* url);

	void init();
	char * getResponse(char * url);
	char* getIpByHost(char *host_name);
	char* trimToPage(char *response);
};

#endif


