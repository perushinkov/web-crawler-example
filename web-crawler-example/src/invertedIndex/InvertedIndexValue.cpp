#include "InvertedIndexValue.h"
#include "../utils/StringUtil.h"

int InvertedIndexValue::hasKey(void * key) {
	return strcmp((char *)key, this->word);
}

int InvertedIndexValue::equals(void * object) {
	return strcmp(word, ((InvertedIndexValue *)object)->getWord());
}

InvertedIndexValue::InvertedIndexValue(char * word) {
	this->word = word;
}

void InvertedIndexValue::addOccurence(int docId) {
	//TODO
}
char * InvertedIndexValue::getWord() {
	return word;
}