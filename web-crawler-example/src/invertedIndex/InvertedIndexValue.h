#ifndef __INVERTEDINDEXVALUE_H
#define __INVERTEDINDEXVALUE_H 1
#include "Posting.h"
#include "../utils/BinNode.h"
/*
	A word and a tree of Postings.
	Each Posting holds a document and a number of occurences.
*/

class InvertedIndexValue {
private:
	char * word_;
	BinNode<Posting> * posts_;
public:
	InvertedIndexValue(char * word);
	void addOccurence(int docId, int howMany);

	int hasKey(void * ptr);
	int equals(void * object);
	void print();
	char * getWord();

	BinNode<Posting> * getPostings();
};

#endif
