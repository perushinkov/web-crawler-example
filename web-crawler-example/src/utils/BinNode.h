#ifndef __BINNODE_H
#define __BINNODE_H 1

/*
 * TODO: Finish this
 */
template <class T>
class BinNode {
private:
	BinNode * parent_;
	BinNode * leftChild_;
	BinNode * rightChild_;
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
};

#endif
