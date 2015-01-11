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
	posts_ = new BinNode<Posting>(nullptr, nullptr);
}

void InvertedIndexValue::addOccurence(int docId, int howMany) {
	Posting* posting = posts_->findByKey((void *)&docId);
	if (posting == nullptr) {
		posting = new Posting(docId);
		posts_->add(posting);
	}
	else {
		posting->increment(howMany);
	}	
}
char * InvertedIndexValue::getWord() {
	return word_;
}