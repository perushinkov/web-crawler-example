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

	//temporary method
	char * getAThousandSymbols();

	//Utility methods
	int error() {return errorCode;}
};


