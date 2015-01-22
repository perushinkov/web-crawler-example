#include "InvertedIndex.h"

InvertedIndex::InvertedIndex() {
	wordIndex_ = new BinNode<InvertedIndexValue>(nullptr, new InvertedIndexValue("_"));
}

void InvertedIndex::updateIndex(BinNode<StraightIndexValue> * words, int docId) {
	do {
		StraightIndexValue* docWithWords = words->getContent();
		if (docWithWords == nullptr) {
			words = words->next();
			continue;
		}
		char* word = docWithWords->getWord();
		int occurence = docWithWords->getOccurences();

		InvertedIndexValue* wordWithPostings = wordIndex_->findByKey((void*)word);
		if (wordWithPostings != nullptr) {
			wordWithPostings->addOccurence(docId, occurence);
		}
		else {
			wordWithPostings = new InvertedIndexValue(word);
			wordWithPostings->addOccurence(docId, occurence);
			wordIndex_->add(wordWithPostings);
		}
		words = words->next();
	} while (words != nullptr);
}

 InvertedIndexValue* InvertedIndex::searchWord(char * word) {
	return wordIndex_->findByKey((void *)word);
}

void InvertedIndex::printIndex() {
	wordIndex_->print();
}