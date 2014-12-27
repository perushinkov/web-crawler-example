#include "StraightIndexValue.h"
#include "string.h"
StraightIndexValue::StraightIndexValue(char * word) {
	word_ = word;
	occurences_ = 1;
}

void StraightIndexValue::increment() {
	occurences_++;
}

int StraightIndexValue::hasKey(void * ptr) {
	int comparison = strcmp(word_, (char*)ptr); 
	if (comparison == 0) {
		return 0;
	}
	if (comparison > 0) {
		return 1;
	}
	return -1;
}




/**
 * Two SIVs are considered equal if their words are equal.
 * That is so that they are sorted by words in the binary tree.
 */
int StraightIndexValue::equals(void * object) {
	char * objectWord = ((StraightIndexValue*)object)->getWord();
	return this->hasKey((void *) objectWord);
}


char * StraightIndexValue::getWord() {
	return word_;
}

int StraightIndexValue::getOccurences() {
	return occurences_;
}