#ifndef MARKOVCHAIN_H
#define MARKOVCHAIN_H
#include "HashTable.h"

class MarkovChain
{
private:
	Word * currentWord;
	Word * previousWord;
	void addWord(std::string name);
	void addEdge(std::string next);
    bool checkForExistingEdge(Word *current, std::string next)
	HashTable hashTable(10);
    int hashTableSize=10;
public:
    //add options to change hashTableSize? -Izaak
	MarkovChain(std::string); // build markov from string
	MarkovChain(std::string filename); //build markov from text file
    std::string generateString(int length);
};


#endif // MARKOVCHAIN_H
