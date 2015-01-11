#ifndef __SITEMAP_H
#define __SITEMAP_H 1
#include <vector>
using namespace std;
/*
 * TODO: Finish this
 */
class SiteMap {
private:
	vector<string> links_;
public:
	SiteMap(char * startingAddress);
	char* getNextUrl(); 
	bool hasNextUrl(); 
	void updateMap(BinNode<StraightIndexValue> * links_); // TODO
};

#endif
