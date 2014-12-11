#include "HttpClient.h"
#include "ResponseParser.h"
#include "BinNode.h"

#include <iostream>
using namespace std;


void main() {
	HttpClient client(80, "127.0.0.1");
	ResponseParser harper;

	if (client.error()) goto FAIL;

	int sent = client.request("/iisstart.htm", "127.0.0.1");
	if (sent <= 0) goto FAIL;
	
	char * text = client.getResponse();
	harper.parse(text);
	printf("%s", harper.getPageContent());
	return;
FAIL:
	printf("FAIL");
}