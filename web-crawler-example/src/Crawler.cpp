#include "client\HttpClient.h"
#include "sitemap\SiteMap.h"
#include "htmlparser\HtmlParser.h"
#include "invertedIndex\InvertedIndex.h"
#include "utils\BinNode.h"
#include "utils\StringUtil.h"
#include <winsock2.h>
#include <ws2tcpip.h>
#include <windows.h>
#include <iostream>
#include <map>
using namespace std;

void main() {
	httpClient::init(); // WSASTARTUP

	SiteMap siteMap("crawlertest.cs.tu-varna.bg");
	InvertedIndex index;

	while (siteMap.hasNextUrl()) {
		char* url = siteMap.getNextUrl();

		printf("\nFetching page %s. Please wait...\n", url);

		char *response = httpClient::getResponse(url);
		if (response == nullptr) {
			printf("Page %s was not found!\n", url);
			continue;
		}
		// Fetching actual htmlPage from response
		char *page = httpClient::trimToPage(response);
		if (page == nullptr) {
			continue;
		}
		HtmlParser parser;
		// Parser parses page and...
		parser.parse(page, url);
		// ...produces the two indexes that the siteMap and the InvertedIndex need

		siteMap.updateMap(parser.getLinks(), url);
		index.updateIndex(parser.getWords(), siteMap.getDocId(url));
	}
	system("pause");
	do {
		system("cls");
		printf("%c", 201);
		for (int i = 0; i < 30; i++) printf("%c", 205);
		printf("%c\n", 187);
		printf("%c 1. Print the graph           %c\n", 186, 186);
		printf("%c 2. Search for a word         %c\n", 186, 186);
		printf("%c 3. Exit                      %c\n", 186, 186);
		printf("%c", 200);
		for (int i = 0; i < 30; i++) printf("%c", 205);
		printf("%c\n\n Type your choice: ", 188);

		int choice;
		cin >> choice;
		std::string s;
		switch (choice) {
		case 1:
			system("cls");
			siteMap.printPrettyPicture();
			printf("\n");
			system("pause");
			break;
		case 2: {
			system("cls");
			printf("Type in a single word: ");
			char word[30];
			scanf("%s", word);
			// Fetching result from invertedIndex
			InvertedIndexValue* result = index.searchWord(word);
			BinNode<Posting>* postings = result->getPostings();

			// Will use map to sort result by number of word occurences
			map<int, string> searchResults;
			do {
				if (postings->getContent() != nullptr) {
					searchResults[postings->getContent()->getOccurences()] = siteMap.getUrlById(postings->getContent()->getDocId());
				}
				postings = postings->next();
			} while (postings != nullptr);

			printf("\n");
			
			for (map<int, string>::reverse_iterator it = searchResults.rbegin(); it != searchResults.rend(); it++) {
				printf("%d -> %s\n", it->first, it->second.c_str());
			}
			system("pause");
			break;
		}
		case 3:
			return;
		};
	} while (true);
}