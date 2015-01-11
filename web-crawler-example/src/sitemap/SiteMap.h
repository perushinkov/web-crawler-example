#ifndef __SITEMAP_H
#define __SITEMAP_H 1
#include <vector>
using namespace std;
/*
 * TODO: Finish this
 */
class SiteMap {
private:
	vector<string> links;
public:
	SiteMap(char * startingAddress);
	char* getNextUrl(); //TODO: Implement
};

#endif
