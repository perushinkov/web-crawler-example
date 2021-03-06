#include "Posting.h"
#include <iostream>
using namespace std;
Posting::Posting(int docId) {
	docId_ = docId;
	occurences_ = 0;
}

void Posting::increment(int howMany) {
	occurences_ += howMany;
}

int Posting::hasKey(void * ptr) {
	if (docId_ == *((int*)ptr)) {
		return 0;
	}
	if (docId_ > *((int*)ptr)) {
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
	return hasKey(p_int);
	return 0;
}


void Posting::print() {
	printf("%d\t - \t%s\n", occurences_, docId_);
}


int Posting::getDocId() {
	return docId_;
}

int Posting::getOccurences() {
	return occurences_;
}