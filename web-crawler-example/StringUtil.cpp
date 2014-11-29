#include "StringUtil.h"

namespace spider {

	void stringUtil::copy(char * from, char * to, int numberOfChars) {
		for (int i = 0; i < numberOfChars; i++) {
			to[i] = from[i];
		}
	}
}