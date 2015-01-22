#ifndef __POSTING_H
#define __POSTING_H 1
#include "../sitemap/SiteMap.h"
/*
	Holds document id, and number of occurences in this document.
 */

class Posting {
private:
	int docId_;
	int occurences_;
public:
	Posting(int docId);
	void increment(int howMany);

	int hasKey(void * ptr);
	int equals(void * object);

	void print();
	//Getters and Setters
	int getDocId();
	int getOccurences();
	
};

#endif
