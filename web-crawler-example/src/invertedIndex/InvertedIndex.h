#ifndef __INVERTEDINDEX_H
#define __INVERTEDINDEX_H 1

#include "../utils/BinNode.h"
#include "../htmlparser/StraightIndexValue.h"
#include "InvertedIndexValue.h"
/*
	This class holds the words that have been found.
	Each InvertedIndexValue has a word key, and a tree of postings.
	Each Posting has a docId and number of occurences.
 */
class InvertedIndex {
private:
	BinNode<InvertedIndexValue>* wordIndex_;
public:
	InvertedIndex();
	/*
		This method is used to update the inverted index with straight index information.
	*/
	void updateIndex(BinNode<StraightIndexValue> * links_, int docId);
	void printIndex();
	/*
		Returns a pointer to the InvertedIndexValue that represents the search results for this word.
	*/
	InvertedIndexValue* searchWord(char * word);
};

#endif
