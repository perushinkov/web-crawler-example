#ifndef __POSTING_H
#define __POSTING_H 1
/*
 * Holds document id, and number of occurences in the document id.
 */

class Posting {
private:
	int docId;
	int occurences;
public:
	Posting(int docId);
	void increment();
	bool equals(Posting p);

	//Getters and Setters
	int getDocId();
	int getOccurences();
	
};

#endif
