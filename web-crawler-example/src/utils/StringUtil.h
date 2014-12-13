#ifndef __STRINGUTIL_H
#define __STRINGUTIL_H 1
#include <string.h>

namespace stringUtil {
	int compare(char * a, char * b);
	bool contains(char * subject, char containee);
	void copy(char * from, char * to, int numberOfChars);
	int findAinB(char * a, char * b);
	int length(char * a);

	char * substring(char * text, int len);
	void toLower(char * text);
}

#endif