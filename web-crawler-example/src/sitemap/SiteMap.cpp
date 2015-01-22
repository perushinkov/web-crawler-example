#include "SiteMap.h"
#include <algorithm>
#include "../utils/StringUtil.h"
#include <string>
using namespace std;
SiteMap::SiteMap(char * startingAddress) {
	linksToBeCrawled_.push_back(startingAddress);
	current_ = 0;
	urlIds_[startingAddress] = 0;
	idUrls_[0] = startingAddress;
}

string SiteMap::getUrlById(int id) {
	if (idUrls_.find(id) != idUrls_.end()) {
		return idUrls_[id];
	}
	return "";
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
	static int id = 1;
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
			id++;
			linksToBeCrawled_.push_back(url);
		}
		outcoming.push_back(urlIds_[url]);
		links = links->next();
	} while (links != nullptr);
	urlGraph_[urlIds_[parentUrl]] = outcoming;
}

int SiteMap::getDocId(char * url) {
	return urlIds_[url];
	return 0;
}

void SiteMap::printPrettyPicture() {
	system("cls");
	
	for (int x = 0; x < 2 + 2 * (urlIds_.size() + 1); x++) {
		for (int y = 0; y < 2 + 3 * (urlIds_.size() + 1); y++) {
			// UI Filters applied here
			if (x == 1 && y % 3 == 0 && y > 1)  printf("%c", 186);
			else if (x == 1 || y == 1) printf("%c", 178);
			else if (x == 0 && y > 1 && y % 3 == 0) printf("%c", (y - 3) / 3 + 'A');
			else if (y == 0 && x > 1 && x % 2 == 0) printf("%c", (x - 2) / 2 + 'A');
			else if (x == 0 && y > 1 && (y+1) % 3 == 0) printf("%c", '/');
			else if (x == 0 && y > 1 && (y-1) % 3 == 0) printf("%c", '\\');
			else {
				if (y % 3 == 0 && y > 1 && urlGraph_.find((y-3)/3) != urlGraph_.end() && urlGraph_[(y-3)/3].size() != 0) {
					int sourceId = (y-3)/3;
					vector<int> targets = urlGraph_[sourceId];
					bool targetHere = false;
					int lastDest = *std::max_element(std::begin(targets), std::end(targets));
					int lastDestX = 2 + 2 * lastDest;
					if (x % 2 == 0 && find(targets.begin(), targets.end(), (x - 2) / 2) != targets.end()) {
						targetHere = true;
					}
					if (x < lastDestX) { 
						if (targetHere) std::printf("%c", 185);
						else std::printf("%c", 186);					
					}
					else if (x == lastDestX) std::printf("%c", 188);
					else std::printf("%c", ' ');

				}
				else if (y % 3 == 2 && y > 1 && urlGraph_.find((y - 2) / 3) != urlGraph_.end() && urlGraph_[(y - 2) / 3].size() != 0) {
					vector<int> targets = urlGraph_[(y - 2) / 3];
					if (x % 2 == 0 && find(targets.begin(), targets.end(), (x - 2) / 2) != targets.end()) std::printf("%c", 205);
					else std::printf(" ");
				} else if (y % 3 == 1 && y > 1 && urlGraph_.find((y - 1) / 3) != urlGraph_.end() && urlGraph_[(y - 1) / 3].size() != 0) {
					vector<int> targets = urlGraph_[(y - 1) / 3];
					if (x % 2 == 0 && find(targets.begin(), targets.end(), (x - 2) / 2) != targets.end()) std::printf("%c", (x - 2) / 2 + 'A');
					else std::printf(" ");
				} else std::printf(" ");
			}
		}
		std::printf("\n");
	}
	

	printf("Legend:\n");
	typedef std::map<int, std::vector<int>>::iterator it_type;

	for (int i = 0; i < urlIds_.size(); i++) {
		printf("%c -> %s \n", 'A' + i, idUrls_[i].c_str());
	}


}