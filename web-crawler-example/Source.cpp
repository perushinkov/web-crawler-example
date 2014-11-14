#include "httpClient.h"

#include <iostream>
using namespace std;


void main() {
	HttpClient client(80, "127.0.0.1");
	if (client.error()) goto FAIL;

	int sent = client.request("/iisstart.htm", "127.0.0.1");
	if (sent <= 0) goto FAIL;

	

	return;
FAIL:
	printf("FAIL");
}