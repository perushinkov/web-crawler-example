#include "Posting.h"

Posting::Posting(int docId) {
	this->docId = docId;
	this->occurences = 0;
}

void Posting::increment() {
	this->occurences++;
}
/**
 * Two postings are considered equal if their docIds are equal.
 * That is so that they are sorted by docIds in binary tree.
 */
bool Posting::equals(Posting t) {
	if (t.getDocId() == this->docId) {
		return true; 
	}
	return false;
}

/**
 *
 */

int Posting::hasKey(void * ptr) {
	if (docId == *((char*)ptr)) {
		return 0;
	}
	if (docId > *((char*)ptr)) {
		return 1;
	}
	return -1;
}
int Posting::equals(void * object) {
	if (this->docId > ((Posting*)object)->getDocId()) {
		return 1;
	}
	if (this->docId < ((Posting*)object)->getDocId()) {
		return -1;
	}
	return 0;
}


int Posting::getDocId() {
	return docId;
}

int Posting::getOccurences() {
	return occurences;
}