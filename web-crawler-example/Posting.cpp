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

int Posting::getDocId() {
	return docId;
}

int Posting::getOccurences() {
	return occurences;
}