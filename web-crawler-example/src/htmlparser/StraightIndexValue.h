#ifndef __STRAIGHTINDEXVALUE_H
#define __STRAIGHTINDEXVALUE_H 1
/*
 * TODO: Finish this
 */

class StraightIndexValue {
private:
	char * word;
	int occurences;
public:
	StraightIndexValue(char * word);

	void increment();

	int hasKey(void * ptr);
	int equals(void * object);

	//Getters and setters
	char * getWord();
	int getOccurences();
};

#endif
