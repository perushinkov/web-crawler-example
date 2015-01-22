#ifndef __STRAIGHTINDEXVALUE_H
#define __STRAIGHTINDEXVALUE_H 1
/*
	This is a class that holds a string and the number of its occurences.
	It implements all it needs to become binary tree content.
	USAGE:
		It is the value by which the number of occurences of a link or a word are stored.
*/
class StraightIndexValue {
private:
	char * word_;
	int occurences_;
public:
	StraightIndexValue(char * word);

	void increment();

	/*
		BinNode compatibility
	*/
	int hasKey(void * ptr);
	int equals(void * object);

	void print();
	//Getters and setters
	char * getWord();
	int getOccurences();
};

#endif
