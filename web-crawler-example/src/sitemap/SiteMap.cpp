#include "SiteMap.h"

#include "../utils/StringUtil.h"
SiteMap::SiteMap(char * startingAddress) {
	linksToBeCrawled_.push_back(startingAddress);
	current_ = 0;
}

char* SiteMap::getNextUrl() {
	if (current_ >= linksToBeCrawled_.size())
		return nullptr;
	
	string nextUrl = linksToBeCrawled_.at(current_);
	current_++;
	return stringUtil::concat(nextUrl.c_str(), "");
}

bool SiteMap::hasNextUrl() {
	if (current_ >= linksToBeCrawled_.size())
		return false;
	return true;
}

void SiteMap::updateMap(BinNode<StraightIndexValue> * links, char* parentUrl) {
	static int id = 0;
	vector<int> outcoming;
	do {
		StraightIndexValue* link = links->getContent();

		char* url = link->getWord();
		if (!stringUtil::compare(url, "_")) {
			links = links->next();
			continue;
		}
		if (urlIds_.find(url) == urlIds_.end()) {
			urlIds_[url] = id;
			idUrls_[id] = url;
			outcoming.push_back(id);
			id++;
			linksToBeCrawled_.push_back(url);
		}
		links = links->next();
	} while (links != nullptr);
	urlGraph_[urlIds_[parentUrl]] = outcoming;
}

int SiteMap::getDocId(char * url) {
	return urlIds_[url];
}

void SiteMap::printPrettyPicture() {
	printf("Legend:\n");
	for (int i = 0;; i++) {
		if (urlGraph_.find(i) != urlGraph_.end()) {
			printf("%c -> %s \n", char('A' + i), idUrls_[i].c_str());
		}
		else {
			break;
		}
	}
	
}