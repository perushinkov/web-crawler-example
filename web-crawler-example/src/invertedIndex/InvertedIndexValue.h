#ifndef __INVERTEDINDEXVALUE_H
#define __INVERTEDINDEXVALUE_H 1
#include "Posting.h"
#include "../utils/BinNode.h"
/*
 * TODO: Finish this
 * Must implement 
 *		int hasKey(void * ptr);
 *		int equals(void * object);
 */

class InvertedIndexValue {
private:
	char * word;
	BinNode<Posting> * posts;
public:
	InvertedIndexValue(char * word);
	void addOccurence(int docId);

	int hasKey(void * ptr);
	int equals(void * object);

	char * getWord();
};

#endif
