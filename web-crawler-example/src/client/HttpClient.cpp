#include "HttpClient.h"

#define RESPONSE_MAX_LENGTH 20000

HttpClient::HttpClient(){
	this->serverIp = "127.0.0.1";
	this->serverPort = 80;
	this->parser = new ResponseParser();
}

void HttpClient::init(char * serverIp){
	this->serverIp = serverIp;
	
	errorCode = 0;
	unsigned short wVersionRequested;
	WSADATA wsaData;
	int err;
	
	// PART ONE: Initiating use of Winsock DLL
	wVersionRequested = MAKEWORD(2, 3);
	err = WSAStartup(wVersionRequested, &wsaData);

	if (err != 0 || (LOBYTE(wsaData.wVersion) != 2 || HIBYTE(wsaData.wVersion) != 2) ) {
		errorCode = 1;
		return;
	}

	int* p_int;

	sock = socket(AF_INET, SOCK_STREAM, 0);
	p_int = (int *)malloc(sizeof(int));
	*p_int = 1;

	//Setting some standard options, recommended by our lecturer
	int opt1 = setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, (char *)p_int, sizeof(int));
	int opt2 = setsockopt(sock, SOL_SOCKET, SO_KEEPALIVE, (char *)p_int, sizeof(int));

	if (opt1 == -1 || opt2 == -1) {
		errorCode = 2;
		return;
	}

	struct sockaddr_in my_addr;
	my_addr.sin_family = AF_INET;
	my_addr.sin_port = htons(serverPort);

	memset(&(my_addr.sin_zero), 0, 8);
	my_addr.sin_addr.s_addr = inet_addr(serverIp);

	if (connect(sock, (sockaddr *)&my_addr, sizeof(my_addr))) {
		errorCode = 3;
		return;
	}
}


/**
 *	Performs a standard HTTP request, filling in 
 *	the requestUri and the host name, as shown below:
 *	
 *	GET <requestUri> HTTP/1.1<CRLF>
 *	host: <host><CRLF>
 *  <CRLF>
 *
 *	The last empty line matters! It signifies the end of the HTTP request.
 */
int HttpClient::request(char * requestUri, char * host) {
	char * query = (char *)malloc(100);
	query[0] = '\0';
	strcat(query, "GET ");
	strcat(query, requestUri);
	strcat(query, " HTTP/1.1\nhost:");
	strcat(query, host);
	strcat(query, "\n\n");
	return send(sock, query, strlen(query), 0);
}
/**
 * Fetches HTTP response.
 */
char * HttpClient::getResponse() {
	// Holder to contain the response. It is created huge,
	// as we cannot tell beforehand what the size of the response is
	char * text = (char *)malloc(RESPONSE_MAX_LENGTH);

	// Assuming the response does not exceed the set maximum length,
	// we get the response text into the char*text holder
	int received = recv(sock, text, RESPONSE_MAX_LENGTH, 0);
	
	// Once we know the length of the received text, we allocate
	// a holder just big enough to contain it
	char * returnText = (char *)malloc(received+1);
	// and copy the response text into it
	*(text + received*sizeof(char)) = '\0';
	strcpy(returnText, text);
	
	//Then we free the originally allocated memory, which we no longer need.
	free(text);
	return returnText;
}

/**
 * Fetches Html page
 */
char * HttpClient::getPage() {
	char * response = getResponse();
	parser->parse(response);
	return parser->getPageContent();
}