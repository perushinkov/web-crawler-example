#ifndef __POSTING_H
#define __POSTING_H 1
/*
 * Holds document id, and number of occurences in the document id.
 * Must implement 
 *		int hasKey(void * ptr);
 *		int equals(void * object);
 */

class Posting {
private:
	int docId;
	int occurences;
public:
	Posting(int docId);
	void increment();

	int hasKey(void * ptr);
	int equals(void * object);

	//Getters and Setters
	int getDocId();
	int getOccurences();
	
};

#endif
