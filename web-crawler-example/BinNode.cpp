#include "BinNode.h"

template <class T>
BinNode<T>::BinNode() {
	this->parent = nullptr;
	this->leftChild = nullptr;
	this->rightChild = nullptr;
	this->content = nullptr;
}

template <class T>
BinNode<T>::BinNode(BinNode * parent, T * content) {
	this->parent = parent;
	this->content = content;
}
/**
 * T must have a method hasKey(void * key)
 */
template <class T>
T * BinNode<T>::findByKey(void * key) {
	int comparison = this->content->hasKey(key);
	
	if (comparison == 0) {
		return this->content;
	}
	if (comparison > 0 && this->rightChild != nullptr) {
		return this->leftChild->findByKey(key);
	}
	if(comparison < 0 && this->leftChild != nullptr) {
		return this->rightChild->findByKey(key);
	}
	return nullptr;
}
/**
 *	Returns true if no content was overridden
 */
template <class T>
bool BinNode<T>::add(T * entry) {
	if (content == nullptr) {
		content = entry;
		return true;
	}

	int comparison = content->equals((void *)entry);
	if (comparison == 0) {
		content = entry;
		return false;
	}

	if (comparison > 0 && this->rightChild != nullptr) {
		return this->leftChild->findByKey(key);
	}
	if(comparison < 0 && this->leftChild != nullptr) {
		return this->rightChild->findByKey(key);
	}
	return nullptr;
}