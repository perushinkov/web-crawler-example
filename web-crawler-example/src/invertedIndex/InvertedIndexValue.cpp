#include "InvertedIndexValue.h"
#include "../utils/StringUtil.h"

int InvertedIndexValue::hasKey(void * key) {
	return strcmp((char *)key, word_);
}

int InvertedIndexValue::equals(void * object) {
	return strcmp(word_, ((InvertedIndexValue *)object)->getWord());
}

InvertedIndexValue::InvertedIndexValue(char * word) {
	word_ = word;
}

void InvertedIndexValue::addOccurence(int docId) {
	//TODO
}
char * InvertedIndexValue::getWord() {
	return word_;
}