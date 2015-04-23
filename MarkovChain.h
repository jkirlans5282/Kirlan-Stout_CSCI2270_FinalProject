#ifndef MARKOVCHAIN_H
#define MARKOVCHAIN_H
#include "HashTable.h"

class MarkovChain
{
private:
	Word * currentWord;
	Word * previousWord; //This is unnessecary, hashtable find word method written to find previous and current w/ flag -Jacob
	void addWord(std::string name);
	void addEdge(std::string next);
    bool checkForExistingEdge(Word *current, std::string next)
	HashTable hashTable(10); //hashtable constructor
    int hashTableSize=10; // is this variable needed we have it in the hashTable.h too. -Jacob
public:
    //add options to change hashTableSize? -Izaak
	MarkovChain(std::string); // build markov from string
	MarkovChain(std::string filename); //build markov from text file (Written untested) -Jacob
    std::string generateString(int length);
};

#endif // MARKOVCHAIN_H
