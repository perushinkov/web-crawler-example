#include "HttpClient.h"
#include "ResponseParser.h"
using namespace spider;

#include <iostream>
using namespace std;


void main() {
	HttpClient client(80, "127.0.0.1");
	ResponseParser harper;

	if (client.error()) goto FAIL;

	int sent = client.request("/iisstart.htm", "127.0.0.1");
	if (sent <= 0) goto FAIL;
	
	char * text = client.getResponse();
	
	printf(text);
	return;
FAIL:
	printf("FAIL");
}