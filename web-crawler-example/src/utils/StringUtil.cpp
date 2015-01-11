#include "StringUtil.h"
#include "MatchException.h"
/*
	standard:
	0 for equality
	-1 or 1 respectively for other results
*/
int stringUtil::compare(char * a, char * b) {
	int pos = 0;
	char a_cur, b_cur;

	while (true) {
		a_cur = *(a + pos);
		b_cur = *(b + pos);

		if (a_cur == b_cur) {
			if (a_cur != '\0') {
				pos++;
				continue;
			}
			return 0;
		}
		if (a_cur == '\0') {
			return -1;
		}
		if (b_cur == '\0') {
			return 1;
		}
		if (a_cur > b_cur) {
			return 1;
		}
		if (a_cur < b_cur) {
			return 1;
		}
		throw new MatchException();
	}
}

char * stringUtil::concat(const char * a, const char * b) {
	char * c;
	int len_a, len_b, len_c;

	len_a = length(a);
	len_b = length(b);
	len_c = len_a + len_b;

	c = (char *) malloc(len_c + 1);
	c[len_c] = '\0';

	copy(a, c, len_a);
	copy(b, c + len_a, len_b);

	return c;
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
		pos++;
	}
	return false;
}

void stringUtil::copy(const char * from, char * to, int numberOfChars) {
	for (int i = 0; i < numberOfChars; i++) {
		to[i] = from[i];
	}
}

/**
 * A naive simple algorithm due to time constraints
 */
int stringUtil::findAinB(char * a, char * b) {
	int a_len = length(a);
	int b_len = length(b);
	bool match = false;
	for (int i = 0; i <= b_len -a_len; i++) {
		match = true;
		for (int j = 0; j < a_len; j++) {
			if (a[j] != b[j + i]) {
				match = false;
				break;
			}
		}
		if (match) {
			return i;
		}
	}
	return -1;
}

int stringUtil::length(const char * a) {
	int pos = 0;
	while (1) {
		if (a[pos] == '\0') break;
		pos++;
	}
	return pos;
}

char * stringUtil::substring(char * text, int len) {
	char * newString = (char *)malloc(len+1);
	newString[len] = '\0';
	copy(text, newString, len);
	return newString;
}

void stringUtil::toLower(char * text) {
	int pos = 0;
	while (1) {
		if (text[pos] == '\0') break;
		if (text[pos] > 'A' && text[pos] < 'Z') {
			text[pos] += 'a' - 'A';		
		}
		pos++;
	}
}



