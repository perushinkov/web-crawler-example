#ifndef __BINNODE_H
#define __BINNODE_H 1

/*
	The binary tree which this project uses.
	It supports basic search, add, delete and iteration functionality.
	Some of its methods have requirements of T.
	For instance T must implement
		bool hasKey(void* key)
	to use findByKey(void* key);
	and print() to use the BinNode print() method;
*/
template <class T>
class BinNode {
private:
	BinNode<T> * parent_;
	BinNode<T> * leftChild_;
	BinNode<T> * rightChild_;
	T * content_;
public:
	BinNode() {
		parent_ = nullptr;
		content_ = nullptr;
		leftChild_ = nullptr;
		rightChild_ = nullptr;
	}

	BinNode(BinNode * parent, T * content) {
		parent_ = parent;
		content_ = content;
		leftChild_ = nullptr;
		rightChild_ = nullptr;
	}

	/**
	 * T must have a method hasKey(void * key)
	 */
	T * findByKey(void * key) {
		if (content_ == nullptr) {
			return nullptr;
		}

		int comparison = content_->hasKey(key);
	
		if (comparison == 0) {
			return content_;
		}
		if (comparison > 0 && rightChild_ != nullptr) {
			return rightChild_->findByKey(key);
		}
		if(comparison < 0 && leftChild_ != nullptr) {
			return leftChild_->findByKey(key);
		}
		return nullptr;
	}



	/**
	*	Returns true if no content was overridden
	*/
	bool add(T * entry) {
		if (content_ == nullptr) {
			content_ = entry;
			return true;
		}

		int comparison = content_->equals((void *)entry);
		if (comparison == 0) {
			content_ = entry;
			return false;
		}

		if (comparison > 0) {
			if (rightChild_ != nullptr) {
				return rightChild_->add(entry);
			}
			rightChild_ = new BinNode<T>(this, entry);
		}
		if(comparison < 0) {
			if (leftChild_ != nullptr) {
				return leftChild_->add(entry);
			}
			leftChild_ = new BinNode<T>(this, entry);
		}
		return true;
	}

	/*
	Some memory management
	*/
	void deleteAll() {
		delete content_;
		if (leftChild_ != nullptr) {
			leftChild_->deleteAll();
		}
		if (rightChild_ != nullptr) {
			rightChild_->deleteAll();
		}
	}

	/*
		Printer
	*/
	void print() {
		
		if (leftChild_ != nullptr) {
			leftChild_->print();
		}
		if (content_ != nullptr)
			content_->print();
		if (rightChild_ != nullptr) {
			rightChild_->print();
		}
	}
	/*
		Forward Iterator functionality
	*/
	BinNode<T>* next() {
		if (leftChild_ != nullptr) return leftChild_;
		if (rightChild_ != nullptr) return rightChild_;

		BinNode<T>* lastOne = this;
		while (lastOne->parent_ != nullptr) {
			if (lastOne->parent_->leftChild_ == lastOne && lastOne->parent_->rightChild_ != nullptr) {
				return lastOne->parent_->rightChild_;
			}
			lastOne = lastOne->parent_;
			continue;
		}
		return nullptr;
	}

	T* getContent() {
		return content_;
	}
};

#endif
