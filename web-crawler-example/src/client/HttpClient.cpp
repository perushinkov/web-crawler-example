#include "HttpClient.h"
#include <ws2tcpip.h>
#include "../utils/StringUtil.h"

#define RESPONSE_MAX_LENGTH 20000

HttpClient::HttpClient(){
	serverIp_ = "127.0.0.1";
	serverPort_ = 80;
	parser_ = new ResponseParser();
}

void HttpClient::init(char * domainName){
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

		if (err != 0 || (LOBYTE(wsaData.wVersion) != 2 || HIBYTE(wsaData.wVersion) != 2) ) {
			errorCode_ = 1;
			exit(errorCode_);
		}
	}

	int* p_int;

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
	query = stringUtil::concat(query, "GET ");
	query = stringUtil::concat(query, requestUri);
	query = stringUtil::concat(query, " HTTP/1.1\nHOST:");
	query = stringUtil::concat(query, host);
	query = stringUtil::concat(query, "\n\n");
	return send(sock_, query, strlen(query), 0);
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
	
	int received = recv(sock_, text, RESPONSE_MAX_LENGTH, 0);
	
	// Once we know the length of the received text, we allocate
	// a holder just big enough to contain it
	char * returnText = (char *)malloc(received+1);
	// and copy the response text into it
	*(text + received*sizeof(char)) = '\0';
	stringUtil::copy(text, returnText, received);
	
	//Then we free the originally allocated memory, which we no longer need.
	free(text);
	//printf("\n\n%s\n\n", returnText);
	return returnText;
}

char * HttpClient::getIp() {
	return serverIp_;
}
/**
 * Fetches Html page
 */
char * HttpClient::getPage() {
	char * response = getResponse();
	parser_->parse(response);
	return parser_->getPageContent();
}


// STATIC FUNCTIONS START HERE:

/**
 * Returns ip as a u_long that can be directly assigned to s_addr.
 */
u_long HttpClient::getIpByHost(char *host_name) {

    //-----------------------------------------
    // Declare and initialize variables
    WSADATA wsaData;
    int iResult;

    int i = 0;
    struct hostent *remoteHost;

    // Initialize Winsock
	if (!WinsockInitialized()) {
		iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
		if (iResult != 0) {
			printf("WSAStartup failed: %d\n", iResult);
			return 0;
		}
	}

    remoteHost = gethostbyname(host_name);
    if (remoteHost == nullptr) {
        return 0;
    }
	
    i = 0;
    if (remoteHost->h_addrtype == AF_INET)
    {
        if (remoteHost->h_addr_list[i] != 0) {
			return *((u_long *) remoteHost->h_addr_list[0]); 
        }
    }
    else {   
		printf("Different from AF_INET!\n");
        return 0;
    } 
	printf("Undiagnosed mistake! DEBUG please!\n");
    return 0;
}

/**
 * This function tests if winsock dll has been initialized.
 * It does that by attempting to create a socket, and checking
 * the error message.
 */
bool HttpClient::WinsockInitialized() {
    SOCKET s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (s == INVALID_SOCKET && WSAGetLastError() == WSANOTINITIALISED){
        return false;
    }
    return true;
}

/**
 * Url must be in the form hostname[/[path]]
 *
 *
 */
char* HttpClient::getHostFromUrl(char* url) {
	int pos = stringUtil::findAinB("/", url);
	if (pos == -1) {
		return url;
	}
	return stringUtil::substring(url, pos);
} 
char* HttpClient::getUriFromUrl(char* url) {
	int pos = stringUtil::findAinB("/", url);
	if (pos == -1) {
		return "/";
	}
	int len = stringUtil::length(url);
	return stringUtil::substring(url + pos, len - pos);
} 