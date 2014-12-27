#include "Crawler.h"
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdio.h>
#include <windows.h>
#include <iostream>
using namespace std;

Crawler::Crawler() {
	client = new HttpClient();
	siteMap = new SiteMap();
	htmlParser = new HtmlParser();
	invertedIndex = new InvertedIndex();
}
void Crawler::crawl(char * domainName) {
	client->init(domainName);
	client->request("/iisstart.htm", client->getIp());
	char * page = client->getPage();
	htmlParser->parse(page);
	cout<<"TheEnd!";
}
	/*

	ResponseParser harper;

	if (client.error()) goto FAIL;

	int sent = client.request("/iisstart.htm", "127.0.0.1");
	if (sent <= 0) goto FAIL;
	
	char * text = client.getResponse();
	harper.parse(text);
	printf("%s", harper.getPageContent());
	return;
FAIL:
	printf("FAIL");*/


void main() {
	Crawler myCrawler;
	myCrawler.crawl("localhost");
}
