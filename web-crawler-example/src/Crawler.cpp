#include "Crawler.h"
#include "utils\StringUtil.h"
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdio.h>
#include <windows.h>
#include <iostream>
using namespace std;

Crawler::Crawler(char * startingAddress) {
	siteMap_ = new SiteMap(startingAddress);
	htmlParser_ = new HtmlParser();
	invertedIndex_ = new InvertedIndex();
}
void Crawler::crawl() {
	/*while (siteMap_->hasNextUrl()) {
		client_ = new HttpClient();
		char * url = siteMap_->getNextUrl();
		int questionMarkLocation = stringUtil::findAinB("?", url);
		if (questionMarkLocation != -1)
			url = stringUtil::substring(url, questionMarkLocation);
		client_->init(HttpClient::getHostFromUrl(url));
		client_->request(HttpClient::getUriFromUrl(url), HttpClient::getHostFromUrl(url));

		char * page = client_->getPage();
		printf(page);
		htmlParser_ = new HtmlParser();
		htmlParser_->parse(page, url);

		htmlParser_->getLinks()->print();
		htmlParser_->getWords()->print();

		siteMap_->updateMap(htmlParser_->getLinks(), url);
		invertedIndex_->updateIndex(htmlParser_->getWords(), siteMap_->getDocId(url));
		
		siteMap_->printPrettyPicture();
	}*/
}
void main() {
	httpClient::init(); // WSASTARTUP
	
	SiteMap siteMap("crawlertest.cs.tu-varna.bg");
	InvertedIndex index;

	while (siteMap.hasNextUrl()) {
		char* url = siteMap.getNextUrl();
		char *response = httpClient::getResponse(url);
		if (response == nullptr) {
			continue;
		}
		char *page = httpClient::trimToPage(response);
		if (page == nullptr) {
			continue;
		}
		HtmlParser parser;
		parser.parse(page, url);

		siteMap.updateMap(parser.getLinks(), url);
		index.updateIndex(parser.getWords(), siteMap.getDocId(url));

		siteMap.printPrettyPicture();
	}
}


/*
const char *getPage(char *ip, char *relativePath)
{
	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
	int *p_int = (int*)malloc(sizeof(int));
	*p_int = 1;

	if ((setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, (char*)p_int, sizeof(int)) == -1) ||
		(setsockopt(sockfd, SOL_SOCKET, SO_KEEPALIVE, (char*)p_int, sizeof(int)) == -1)){
		printf("Error in setsockopt.\n");
		free(p_int);
		exit(1);
	}

	sockaddr_in myaddress;

	myaddress.sin_family = AF_INET;
	myaddress.sin_port = htons(SERVER_PORT);
	memset(&(myaddress.sin_zero), 0, 8);	// fill with zeros
	myaddress.sin_addr.s_addr = inet_addr(ip);

	if (connect(sockfd, (struct sockaddr*)&myaddress, sizeof(myaddress)) == SOCKET_ERROR){
		printf("Error in connect.\n");
		free(p_int);
		exit(1);
	}


	//------------ Generate request message -------------
	char request[100] = "GET /";
	strcat(request, relativePath);
	strcat(request, " HTTP/1.1\nhost:");
	strcat(request, ip);
	strcat(request, "\n\n\0");

	send(sockfd, request, sizeof(request), 0);


	//-------------- Get response message ---------------

	char * text = (char *)malloc(RESPONSE_MAX_LENGTH);			// A huge container for the response

	int received = recv(sockfd, text, RESPONSE_MAX_LENGTH, 0);
	char * returnText = (char *)malloc(received + 1);				// A normal container for the exact size response

	// Copy the huge response into it
	*(text + received*sizeof(char)) = '\0';
	strcpy(returnText, text);

	free(text);					// Free the huge container	

	return getOnlyContent(returnText, received);
}

*/


/*


errorCode_ = 0;
unsigned short wVersionRequested;
WSADATA wsaData;
int err;

// PART ONE: Initiating use of Winsock DLL
// Winsock may have already been initialized, if
// a call to getIpByHost has already been made.
if (!WinsockInitialized()) {
	wVersionRequested = MAKEWORD(2, 3);
	err = WSAStartup(wVersionRequested, &wsaData);

	if (err != 0 || (LOBYTE(wsaData.wVersion) != 2 || HIBYTE(wsaData.wVersion) != 2)) {
		errorCode_ = 1;
		exit(errorCode_);
	}
}

int* p_int;
if (sock_ != 0) closesocket(sock_);
sock_ = socket(AF_INET, SOCK_STREAM, 0);
p_int = (int *)malloc(sizeof(int));
*p_int = 1;

//Setting some standard options, recommended by our lecturer
int opt1 = setsockopt(sock_, SOL_SOCKET, SO_REUSEADDR, (char *)p_int, sizeof(int));
int opt2 = setsockopt(sock_, SOL_SOCKET, SO_KEEPALIVE, (char *)p_int, sizeof(int));

if (opt1 == -1 || opt2 == -1) {
	errorCode_ = 2;
	exit(errorCode_);
}

struct sockaddr_in my_addr;
my_addr.sin_family = AF_INET;
my_addr.sin_port = htons(serverPort_);

memset(&(my_addr.sin_zero), 0, 8);
my_addr.sin_addr.s_addr = getIpByHost(domainName);

serverIp_ = inet_ntoa(my_addr.sin_addr);

if (connect(sock_, (sockaddr *)&my_addr, sizeof(my_addr))) {
	errorCode_ = 4;
	exit(errorCode_);
}*/

