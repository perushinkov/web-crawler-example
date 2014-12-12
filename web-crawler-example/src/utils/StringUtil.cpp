#include "StringUtil.h"

void stringUtil::copy(char * from, char * to, int numberOfChars) {
	for (int i = 0; i < numberOfChars; i++) {
		to[i] = from[i];
	}
}

bool stringUtil::contains(char * subject, char containee) {
	int pos = 0;
	while (true) {
		if (*(subject + pos) == '\0') {
			break;
		}
		if (*(subject + pos) == containee) {
			return true;
		}
	}
	return false;
}