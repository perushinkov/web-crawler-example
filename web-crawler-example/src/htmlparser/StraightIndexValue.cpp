#include "StraightIndexValue.h"
#include "string.h"
StraightIndexValue::StraightIndexValue(char * word) {
	this->word = word;
	this->occurences = 0;
}

void StraightIndexValue::increment() {
	this->occurences++;
}

int StraightIndexValue::hasKey(void * ptr) {
	int comparison = strcmp(word, (char*)ptr); 
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
	return word;
}

int StraightIndexValue::getOccurences() {
	return occurences;
}