#ifndef __STRINGUTIL_H
#define __STRINGUTIL_H 1
#include <string.h>

namespace stringUtil {
	/*
		compares a to b. Works just as strcmp does.
	*/
	int compare(char * a, char * b);
	/*
		Concatenates a to b and returns the new char*.
		Does not change the parameters.
	*/
	char * concat(const char * a, const char * b);
	/* 
		Tells if a string contains a char
	*/
	bool contains(char * subject, char containee);
	/*
		A copy that copies from first param to second a certain amount of chars.
	*/
	void copy(const char * from, char * to, int numberOfChars);
	/*
		Returns position of string a in string b, or -1.
	*/
	int findAinB(char * a, char * b);
	/*
		Equivalent of strlen
	*/
	int length(const char * a);
	/*
		Equivalent of substring
	*/
	char * substring(char * text, int len);
	/*
		Changes param to lowercase
	*/
	void toLower(char * text);
}

#endif