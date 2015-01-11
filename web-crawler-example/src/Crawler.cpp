#include "Crawler.h"
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdio.h>
#include <windows.h>
#include <iostream>
using namespace std;

Crawler::Crawler(char * startingAddress) {
	client_ = new HttpClient();
	siteMap_ = new SiteMap(startingAddress);
	htmlParser_ = new HtmlParser();
	invertedIndex_ = new InvertedIndex();
}
void Crawler::crawl() {
	while (siteMap_->hasNextUrl()) {
		client_ = new HttpClient();
		char * url = siteMap_->getNextUrl();
		client_->init(HttpClient::getHostFromUrl(url));
		client_->request(HttpClient::getUriFromUrl(url), client_->getIp());
		char * page = client_->getPage();
		htmlParser_ = new HtmlParser();
		htmlParser_->parse(page, url);
		siteMap_->updateMap(htmlParser_->getLinks(), url);
		invertedIndex_->updateIndex(htmlParser_->getWords(), siteMap_->getDocId(url));
		
		siteMap_->printPrettyPicture();
	}
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
	Crawler myCrawler("new.tu-varna.bg/index.php/bg/");
	myCrawler.crawl();
}
