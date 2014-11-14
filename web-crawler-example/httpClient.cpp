#include "httpClient.h"

HttpClient::HttpClient(long serverPort, string serverIp){
	this->serverPort = serverPort;
	this->serverIp = serverIp;
	
	errorCode = 0;
	unsigned short wVersionRequested;
	WSADATA wsaData;
	int err;

	wVersionRequested = MAKEWORD(2, 2);
	err = WSAStartup(wVersionRequested, &wsaData);

	if (err != 0 || (LOBYTE(wsaData.wVersion) != 2 || HIBYTE(wsaData.wVersion) != 2) ) {
		errorCode = 1;
		return;
	}

	int* p_int;

	sock = socket(AF_INET, SOCK_STREAM, 0);
	p_int = (int *)malloc(sizeof(int));
	*p_int = 1;

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
	my_addr.sin_addr.s_addr = inet_addr(serverIp.c_str);

	if (connect(sock, (sockaddr *)&my_addr, sizeof(my_addr))) {
		errorCode = 3;
		return;
	}
}

int HttpClient::request(string requestUri, string host) {
	string queryString = "GET ";
	queryString+= requestUri;
	queryString+= " HTTP/1.1\n";
	queryString+= "host: ";
	queryString+= host;
	queryString+= "\n";
	return send(sock, queryString.c_str, queryString.length, 0);
}

char * HttpClient::getAThousandSymbols() {
	char * text = (char *)malloc(1000);
	int received = recv(sock, text, 1000, 0);
	return text;
}