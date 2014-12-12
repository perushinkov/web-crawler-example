#include "Posting.h"

Posting::Posting(int docId) {
	this->docId = docId;
	this->occurences = 0;
}

void Posting::increment() {
	this->occurences++;
}

int Posting::hasKey(void * ptr) {
	if (docId == *((int*)ptr)) {
		return 0;
	}
	if (docId > *((int*)ptr)) {
		return 1;
	}
	return -1;
}
/**
 * Two postings are considered equal if their docIds are equal.
 * That is so that they are sorted by docIds in binary tree.
 */
int Posting::equals(void * object) {

	int objectDocId = ((Posting*)object)->getDocId();
	void * p_int = &objectDocId; 
	return this->hasKey(p_int);
}


int Posting::getDocId() {
	return docId;
}

int Posting::getOccurences() {
	return occurences;
}