#ifndef __SITEMAP_H
#define __SITEMAP_H 1
#include "../utils/BinNode.h"
#include "../htmlparser/StraightIndexValue.h"
#include <vector>
#include <map>
using namespace std;
/*
 * TODO: Finish this
 */
class SiteMap {
private:
	int current_;
	vector<string> linksToBeCrawled_;
	
	map<string, int> urlIds_;
	map<int, string> idUrls_;


	map<int, vector<int>> urlGraph_;
public:

	SiteMap(char * startingAddress);
	char* getNextUrl(); 
	bool hasNextUrl();

	string getUrlById(int id);
	int getDocId(char * url);
	void updateMap(BinNode<StraightIndexValue> * links_, char* parentUrl); 
	void printPrettyPicture();
};

#endif
