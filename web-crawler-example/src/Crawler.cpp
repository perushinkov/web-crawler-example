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
		char *page = httpClient::trimToPage(response);
		if (page == nullptr) {
			continue;
		}
		HtmlParser parser;
		parser.parse(page, url);

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
			InvertedIndexValue* result = index.searchWord(word);
			BinNode<Posting>* postings = result->getPostings();
			do {
				if (postings->getContent() != nullptr)
					printf("\t%d\t\t%s\n", postings->getContent()->getOccurences(), siteMap.getUrlById(postings->getContent()->getDocId()));
			} while (postings->next() != nullptr);
			system("pause");
			break;
		}
		case 3:
			return;
		};
	} while (true);


}