#include "SiteMap.h"
#include <algorithm>
#include "../utils/StringUtil.h"
SiteMap::SiteMap(char * startingAddress) {
	linksToBeCrawled_.push_back(startingAddress);
	current_ = 0;
	urlIds_[startingAddress] = 0;
	idUrls_[0] = startingAddress;
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
	system("cls");
	
	/*for (int x = 0; x < 2 + 2 * (urlGraph_.rbegin()->first + 1); x++) {
		for (int y = 0; y < 2 + 3 * (urlGraph_.rbegin()->first + 1); y++) {
			// UI Filters applied here
			if (x == 1 && y % 3 == 0 && y > 1)  printf("%c", 186);
			else if (x == 1 || y == 1) printf("%c", 178);
			else if (x == 0 && y > 1 && y % 3 == 0) printf("%c", (y - 3) / 3 + 'A');
			else if (y == 0 && x > 1 && x % 2 == 0) printf("%c", (x - 2) / 2 + 'A');
			else if (x == 0 && y > 1 && (y+1) % 3 == 0) printf("%c", '/');
			else if (x == 0 && y > 1 && (y-1) % 3 == 0) printf("%c", '\\');
			else {
				if (y % 3 == 0 && y > 1) {
					int source = (y - 3) / 3;
					if (urlGraph_.find(source) != urlGraph_.end() && urlGraph_[source].size() > 0) {
						int lastPower = urlGraph_[source].at(urlGraph_[source].size() - 1);
						int destination = (x - 2) / 2;
						if (destination < lastPower) {
							printf("%c", 186);
						}
						else if (destination == lastPower) {
							printf("%c", 188);
						}
					}
				}
				printf(" ");
			}
		}
		printf("\n");
	}
	*/

	printf("Legend:\n");
	typedef std::map<int, std::vector<int>>::iterator it_type;

	for (it_type iterator = urlGraph_.begin(); iterator != urlGraph_.end(); iterator++) {
		printf("%c -> %s \n", 'A' + iterator->first, idUrls_[iterator->first].c_str());
		for (int x = 0; x < 3; x++) {
			for (int y = 0; y < 79; y++) {
				if (x == 0 && y == 0) printf("%c", 'A' + iterator->first);
				else { 
					int size = iterator->second.size();
					if (size > 0) {
						if (y < *iterator->second.rbegin()) {
							if (find(iterator->second.rbegin(), iterator->second.rend(), (y - 3) / 3) != iterator->second.rend()) { 
								if (x == 0) printf("%c", 203);
								else if (x == 1) printf("%c", 208);
								else printf("%c", 'A' + ((y - 3) / 3));
							} else printf("%c", 205); 
						}
						else if (x == 0 && y == *iterator->second.rbegin()) printf("%c", 187);
					}
					else printf(" ");
				}
			}
			printf("\n");
		}
	}


}