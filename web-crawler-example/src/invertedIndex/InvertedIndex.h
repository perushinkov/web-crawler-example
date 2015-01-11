#ifndef __INVERTEDINDEX_H
#define __INVERTEDINDEX_H 1

#include "../utils/BinNode.h"
#include "../htmlparser/StraightIndexValue.h"
#include "InvertedIndexValue.h"
/*
 * TODO: Finish this
 */
class InvertedIndex {
private:
	BinNode<InvertedIndexValue>* wordIndex_;
public:
	InvertedIndex();
	void updateIndex(BinNode<StraightIndexValue> * links_, int docId); // TODO
};

#endif
