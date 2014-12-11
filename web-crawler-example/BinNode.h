#ifndef __BINNODE_H
#define __BINNODE_H 1

/*
 * TODO: Finish this
 */
template <class T>
class BinNode {
private:
	BinNode * parent;
	BinNode * leftChild;
	BinNode * rightChild;
	T * content;
public:
	BinNode();
	BinNode(BinNode * parent, T * content);
	bool find(T);

};

#endif
