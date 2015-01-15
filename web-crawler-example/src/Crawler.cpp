#include "client\HttpClient.h"
#include "sitemap\SiteMap.h"
#include "htmlparser\HtmlParser.h"
#include "invertedIndex\InvertedIndex.h"
#include "utils\BinNode.h"
#include "utils\StringUtil.h"
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdio.h>
#include <windows.h>
#include <iostream>
using namespace std;

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