#include "HttpClient.h"
#include <Winsock2.h>
#include "../utils/StringUtil.h"

char* httpClient::getHostFromUrl(char* url) {
	int pos = stringUtil::findAinB("/", url);
	if (pos == -1) {
		return url;
	}
	return stringUtil::substring(url, pos);
}
char* httpClient::getUriFromUrl(char* url) {
	int pos = stringUtil::findAinB("/", url);
	if (pos == -1) {
		return "/";
	}
	int len = stringUtil::length(url);
	return stringUtil::substring(url + pos, len - pos);
}

char * httpClient::getResponse(char * url) {

	char* ip = getIpByHost(getHostFromUrl(url));
	if (ip == nullptr) return nullptr;

	int sock_ = socket(AF_INET, SOCK_STREAM, 0);
	int *p_int = (int*)malloc(sizeof(int));
	*p_int = 1;

	int opt1 = setsockopt(sock_, SOL_SOCKET, SO_REUSEADDR, (char *)p_int, sizeof(int));
	int opt2 = setsockopt(sock_, SOL_SOCKET, SO_KEEPALIVE, (char *)p_int, sizeof(int));

	if (opt1 == -1 || opt2 == -1) {
		exit(2);
	}
	struct sockaddr_in my_addr;

	my_addr.sin_family = AF_INET;
	my_addr.sin_port = htons(80);
	memset(&(my_addr.sin_zero), 0, 8);
	my_addr.sin_addr.s_addr = inet_addr(ip);

	if (connect(sock_, (struct sockaddr*)&my_addr, sizeof(my_addr)) != 0){
		exit(4);
	}


	char* query = (char *)malloc(150);
	query[0] = '\0';
	query = stringUtil::concat(query, "GET ");
	query = stringUtil::concat(query, getUriFromUrl(url));
	query = stringUtil::concat(query, " HTTP/1.1\nHost:");
	query = stringUtil::concat(query, ip);
	query = stringUtil::concat(query, "\n\n\0");
	send(sock_, query, stringUtil::length(query), 0);

	char * text = (char *)malloc(RESPONSE_MAX_LENGTH);	// A huge container for the response
	// MUST WAIT FOR ALL DATA. without flag it loads around 3-4000 symbols...

	int received = 0;
	int newAmount = 0;

	received += recv(sock_, text + received, 100, 0);
	if (text[9] != '2') //Checking status code 
		return nullptr;
	do {
		newAmount = recv(sock_, text+received, 7000, 0);
		received += newAmount;
	} while (newAmount > 0);
	
	
	char * returnText = (char *)malloc(received + 1);// A normal container for the exact size response

	// Copy the huge response into it
	*(text + received*sizeof(char)) = '\0';
	stringUtil::copy(text, returnText, stringUtil::length(text));
	int a = strlen(text);
	int b = strlen(returnText);
	free(text);
	return returnText;
}

 void httpClient::init() {
	 unsigned short wVersionRequested;
	 WSADATA wsaData;
	 int err;

	 // PART ONE: Initiating use of Winsock DLL
	 // Winsock may have already been initialized, if
	 // a call to getIpByHost has already been made.

	 wVersionRequested = MAKEWORD(2, 2);
	 err = WSAStartup(wVersionRequested, &wsaData);

	 if (err != 0 || (LOBYTE(wsaData.wVersion) != 2 || HIBYTE(wsaData.wVersion) != 2)) {
		 exit(1);
	 }
 }
 char* httpClient::trimToPage(char* response) {
	 int k = strlen(response);
	 int pos = stringUtil::findAinB("HTTP/1.1 ", response);

	 response += stringUtil::findAinB("<html", response); // Moving pointer to start of html body
	 return response;
 }

char* httpClient::getIpByHost(char *host_name) {
	int iResult;
	struct hostent *remoteHost;
	remoteHost = gethostbyname(host_name);
	if (remoteHost == nullptr) {
		return 0;
	}
	if (remoteHost->h_addrtype == AF_INET)
	{
		if (remoteHost->h_addr_list[0] != 0) {
			return inet_ntoa(*(struct in_addr *)*remoteHost->h_addr_list);
		}
	}
	return 0;
}