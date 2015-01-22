#include "InvertedIndexValue.h"
#include "../utils/StringUtil.h"
#include <iostream>
using namespace std;
int InvertedIndexValue::hasKey(void * key) {
	return strcmp(word_, (char *)key);
}

int InvertedIndexValue::equals(void * object) {
	return strcmp(word_, ((InvertedIndexValue *)object)->getWord());
}

void InvertedIndexValue::print() {
	printf("Word: %s \n", word_);
	posts_->print();
}

InvertedIndexValue::InvertedIndexValue(char * word) {
	word_ = word;
	posts_ = new BinNode<Posting>(nullptr, nullptr);
}

void InvertedIndexValue::addOccurence(int docId, int howMany) {
	Posting* posting = posts_->findByKey((void *)&docId);
	if (posting == nullptr) {
		posting = new Posting(docId);
		posts_->add(posting);
	}
	posting->increment(howMany);
	
}
char * InvertedIndexValue::getWord() {
	return word_;
}

BinNode<Posting> * InvertedIndexValue::getPostings() {
	return posts_;
}