#ifndef __CRAWLER_H
#define __CRAWLER_H 1
#include "client\HttpClient.h"
#include "sitemap\SiteMap.h"
#include "htmlparser\HtmlParser.h"
#include "invertedIndex\InvertedIndex.h"
#include "utils\BinNode.h"
/*
 * TODO: Finish this
 */
class Crawler {
private:
	HttpClient * client;
	SiteMap * siteMap;
	HtmlParser * htmlParser;
	InvertedIndex * invertedIndex;
public:
	Crawler();
	void crawl(char * startingAddress);
};

#endif
