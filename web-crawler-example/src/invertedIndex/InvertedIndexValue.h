#ifndef __INDEXVALUE_H
#define __INDEXVALUE_H 1
#include "Posting.h"
#include "BinNode.h"
/*
 * TODO: Finish this
 * Must implement 
 *		int hasKey(void * ptr);
 *		int equals(void * object);
 */

class IndexValue {
private:
	char * word;
	BinNode<Posting> * posts;
public:
	IndexValue(char * word);
	void addOccurence(int docId);

	int hasKey(void * ptr);
	int equals(void * object);

	char * getWord();
};

#endif
