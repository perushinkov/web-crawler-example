#include "Crawler.h"

#include <iostream>
using namespace std;

Crawler::Crawler() {
	client = new HttpClient();
	siteMap = new SiteMap();
	htmlParser = new HtmlParser();
	invertedIndex = new InvertedIndex();
}
void Crawler::crawl(char * startingAddress) {
	client->init(startingAddress);
	gethostbyname();
	client->request("/iisstart.htm", "127.0.0.1");
	char * page = client->getPage();
	htmlParser->parse(page);
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
	myCrawler.crawl("127.0.0.1");
	
}