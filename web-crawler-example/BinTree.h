#ifndef __BINTREE_H
#define __BINTREE_H 1
#include "BinNode.h"
/**
 * Will try to see if I can make do with BinNode only
 */
template <class T>
class BinTree {
private:
	BinNode<T> * root;
public:
	BinTree();
	bool find(T);


};

#endif
