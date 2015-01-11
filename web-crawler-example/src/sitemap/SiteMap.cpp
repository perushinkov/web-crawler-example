#include "SiteMap.h"
#include "../utils/BinNode.h"
#include "../htmlparser/StraightIndexValue.h"
#include "../utils/StringUtil.h"
SiteMap::SiteMap(char * startingAddress) {
	links_.push_back(startingAddress);
}

char* SiteMap::getNextUrl() {
	string nextUrl = links_.at(links_.size() - 1);
	links_.pop_back();
	return stringUtil::concat(nextUrl.c_str(), "");;
}

bool SiteMap::hasNextUrl() {
	if (links_.size() > 0) {
		return true;
	}
	return false;
}

void SiteMap::updateMap(BinNode<StraightIndexValue> * links_) {

}