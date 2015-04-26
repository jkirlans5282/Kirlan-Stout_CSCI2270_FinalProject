#ifndef MARKOVCHAIN_H
#define MARKOVCHAIN_H
#include "HashTable.h"

class MarkovChain
{
private:
	Word * currentWord;
	Word * previousWord; //This is unnecessary, hashtable find word method written to find previous and current w/ flag -Jacob
	Word * addWord(std::string name);
	void addEdge(std::string next);
    bool checkForExistingEdge(Word *current, std::string next);
	HashTable *hashTable = new HashTable(10); //hashtable constructor
    int hashTableSize=10; // is this variable needed we have it in the hashTable.h too. -Jacob
public:
    //add options to change hashTableSize? -Izaak
	MarkovChain(std::string fileName, bool flag=true); //build markov from text file, true filename, false text (Written untested) -Jacob
    std::string generateString(int length);
};

#endif // MARKOVCHAIN_H
