#ifndef MARKOVCHAIN_H
#define MARKOVCHAIN_H
#include "HashTable.h"

class MarkovChain
{

private:
	Word *currentWord = 0;
	//Pointer to previousWord was unnecessary and removed. Nice catch, Jacob. -Alex
	Word *addWord(std::string name);
	void addEdge(Word * next);
	bool checkForExistingEdge(Word *current, std::string next);
	int hashTableSize=10; // Is this variable needed? We have it in the hashTable.h too. -Jacob
	Word * nextWord(Word * current);
public:
    //Add options to change hashTableSize? -Izaak
	MarkovChain(std::string textIn, bool flag = true); //If true, a filename is passed. If false a string of text is passed. (Written untested) -Jacob
    std::string generateString(int length);
    HashTable *hashTable = new HashTable(10);

};

#endif // MARKOVCHAIN_H