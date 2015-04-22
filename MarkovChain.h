#ifndef MARKOVCHAIN_H
#define MARKOVCHAIN_H
#include "HashTable.h"

class MarkovChain
{
private:
	std::string currentWord;
	std::string previousWord;
	void addWord(std::string name);
	void addEdge(std::string next);
	HashTable hashTable(10);
public:
	MarkovChain(std::string);
	MarkovChain(std::string filename);
	generateString(int length);
};



#endif // MARKOVCHAIN_H
