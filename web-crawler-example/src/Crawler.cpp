#include "Crawler.h"
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdio.h>
#include <windows.h>
#include <iostream>
using namespace std;

Crawler::Crawler() {
	client_ = new HttpClient();
	siteMap_ = new SiteMap();
	htmlParser_ = new HtmlParser();
	invertedIndex_ = new InvertedIndex();
}
void Crawler::crawl(char * domainName) {
	client_->init(domainName);
	client_->request("/iisstart.htm", client_->getIp());
	char * page = client_->getPage();
	htmlParser_->parse(page);
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
