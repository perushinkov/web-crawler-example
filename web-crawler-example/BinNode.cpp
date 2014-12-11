#include "BinNode.h"

template <class T>
BinNode<T>::BinNode() {
	this->parent = nullptr;
	this->leftChild = nullptr;
	this->rightChild = nullptr;
	this->content = nullptr;
}

