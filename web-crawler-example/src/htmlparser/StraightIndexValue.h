#ifndef __STRAIGHTINDEXVALUE_H
#define __STRAIGHTINDEXVALUE_H 1

class StraightIndexValue {
private:
	char * word_;
	int occurences_;
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
