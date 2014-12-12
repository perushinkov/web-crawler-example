#include "IndexValue.h"
#include "StringUtil.h"

int IndexValue::hasKey(void * key) {
	return strcmp((char *)key, this->word);
}

int IndexValue::equals(void * object) {
	return strcmp(word, ((IndexValue *)object)->getWord());
}

IndexValue::IndexValue(char * word) {
	this->word = word;
}

void IndexValue::addOccurence(int docId) {
	//TODO
}
char * IndexValue::getWord() {
	return word;
}