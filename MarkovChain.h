#ifndef MARKOVCHAIN_H
#define MARKOVCHAIN_H
#include "HashTable.h"

class MarkovChain
{
private:
    HashTable *hashTable = new HashTable(10);
    bool isVerbose;

	Word *currentWord;
	Word *addWordToHashtable(std::string name);
	void addEdge(Word * next);
	int hashTableSize=10; // Is this variable needed? We have it in the hashTable.h too. -Jacob
	Word * nextWord(Word * current);
	bool checkForExistingEdge(Word *next);
    Word * randomWord();
public:
    //Add options to change hashTableSize? -Izaak
	MarkovChain(bool v = false);
	MarkovChain(std::string textIn, bool flag = false, bool v = false); //If true, a filename is passed. If false a string of text is passed. (Written untested) -Jacob
    std::string generateString(int length);
    std::string generateNextWord();
    void print();
    void print(std::string);
    void verbose(bool set);
    void verbose();
    void add(std::string textIn, bool flag = false);
};

#endif // MARKOVCHAIN_H
