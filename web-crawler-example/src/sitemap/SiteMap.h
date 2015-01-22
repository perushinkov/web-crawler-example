#ifndef __SITEMAP_H
#define __SITEMAP_H 1
#include "../utils/BinNode.h"
#include "../htmlparser/StraightIndexValue.h"
#include <vector>
#include <map>
using namespace std;
/*
	SiteMap has several responsibilities:
	- it holds the links that will be crawled by the crawler and is responsible
		for delivering them one by one.
	- it maintains mapping between docids and docUrls
	- It holds information about the connnections between the different urls
		and can draw a graph.
*/
class SiteMap {
private:
	// Current linkToBeCrawled
	int current_;

	//New linksToBeCrawled are added here
	vector<string> linksToBeCrawled_;
	
	//URL to ID and ID to URL maps
	map<string, int> urlIds_;
	map<int, string> idUrls_;

	// Holds graph information. Works just with docIds
	map<int, vector<int>> urlGraph_;
public:

	SiteMap(char * startingAddress);
	
	// Delivers next url to be crawled
	char* getNextUrl(); 

	// Tells if there are still urls to be crawled
	bool hasNextUrl();

	// Interface to private Id to URL map
	string getUrlById(int id);

	// Interface to private URL to Id maps
	int getDocId(char * url);

	/*
		Takes a straight index tree and the url of the page and updates sitemap state
		that includes all of the above (Links to be crawled, <docId, docUrl> maps, graph).
	*/
	void updateMap(BinNode<StraightIndexValue> * links_, char* parentUrl); 

	/*
		Uses a layered approach to paint a "graph" representation on the console
		The representation shows which page points to which pages. Neighbour lists.
	*/
	void printPrettyPicture();
};

#endif
