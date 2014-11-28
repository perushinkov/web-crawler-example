#include <iostream>
#include <string>
#include <fstream>
#include <winsock2.h>
#include <windows.h>
#include <fcntl.h>
#include <stdlib.h>
#include <errno.h>
#include <stdio.h>
#include <conio.h>

#include <string>
#include<time.h>

using namespace std;

struct value {
	string word;
	int occurences;
};

struct tree {
	value * element;
	tree * parent;
	tree * leftChild;
	tree * rightChild;
};


#define PREORDER 0
#define INORDER 1
#define POSTORDER 2

void addToTree(tree * root, value * node);
void printTree(tree * root, int method);

void addToTree(tree * root, string * word){

	if(root->element == nullptr) {
		value * node;
		node = new value;
		node->occurences = 1;
		node->word = *word;
		root->element = node;
		root->leftChild = nullptr;
		root->rightChild = nullptr;
		return;
	}

	string val = root->element->word;
	int comparison = strcmp((*word).c_str(), val.c_str());
	if(comparison > 0) {
		if(root->rightChild != nullptr) {
			addToTree(root->rightChild, word);
		} else {
			root->rightChild = new tree;
			tree * temp = root->rightChild;
			value * node = new value;
			node->occurences = 1;
			node->word = *word;
			temp->element = node;
			temp->leftChild = nullptr;
			temp->rightChild = nullptr;
		}
	} else if(comparison < 0) {
		if(root->leftChild != nullptr) {
			addToTree(root->leftChild, word);
		} else {
			root->leftChild = new tree;
			tree * temp = root->leftChild;
			value * node = new value;
			node->occurences = 1;
			node->word = *word;
			temp->element = node;
			temp->leftChild = nullptr;
			temp->rightChild = nullptr;
		}
	} else {
		root->element->occurences++;
	}
}

void printTree(tree * root, int method){
	if(method == PREORDER) {
		cout<<root->element->occurences<<"\t\t"<<root->element->word<<endl;
	}
	if(root->leftChild != nullptr) {
		printTree(root->leftChild, method);
	}
	if(method == INORDER) {
		cout<<root->element->occurences<<"\t\t"<<root->element->word<<endl;
	}
	if(root->rightChild != nullptr) {
		printTree(root->rightChild, method);
	}
	if(method == POSTORDER) {
		cout<<root->element->occurences<<"\t\t"<<root->element->word<<endl;
	}
}


bool addSymbol(tree * existing);
bool isSeparator(char sep);
void nextch();
char ch;

std::ifstream ifs;
std::ofstream ofs;
void main() {
	tree * myTree = new tree;
	myTree->element = nullptr;

	ifs.open("primeren.txt", std::ifstream::in);
	ofs.open("primeren_out.txt", std::ofstream::out);
	
	nextch();
	for(;;) {
		if(ch==0) break;
		addSymbol(myTree);
	}	
	
	printTree(myTree, INORDER);
	ifs.close();
	ofs.close();
}

void nextch(){
	ch = ifs.get();
	if(ifs.eof()) ch = 0;
}
bool addSymbol(tree * existing) {
	string symbol = "";
	while(true) {
		switch(ch) {
		case ' ': case '\n': case '.': case ';': 
		case '-': case '=': case '(': case ')':
		case '{': case '}': case '[': case ']':
		case ',': case '>': case '<':
			nextch();
			continue;
		case 0:
			return false;
		default:
			char d[2];
			d[1] = '\0';
			
			while(!isSeparator(ch)) {
				ch = tolower(ch);
				d[0] = ch;
				symbol.append(d);
				nextch();
			}
			
			addToTree(existing, &symbol);
			return true;
		}
	}
}
bool isSeparator(char sep) {
	switch(sep) {
		case ' ': case '\n': case '.': case ';': 
		case '-': case '=': case '(': case ')':
		case '{': case '}': case '[': case ']':
		case ',': case '>': case '<':
			return true;
		default:
			return false;
	}
}
