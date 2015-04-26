#ifndef MARKOVCHAIN_H
#define MARKOVCHAIN_H
#include "HashTable.cpp"

class MarkovChain
{

private:
	Word *currentWord;
	//Pointer to previousWord was unnecessary and removed. Nice catch, Jacob. -Alex
	Word *addWord(std::string name);
	void addEdge(std::string next);
    bool checkForExistingEdge(Word *current, std::string next);
    int hashTableSize=10; // Is this variable needed? We have it in the hashTable.h too. -Jacob
public:
    //Add options to change hashTableSize? -Izaak
	MarkovChain(std::string textIn, bool flag = true); //If true, a filename is passed. If false a string of text is passed. (Written untested) -Jacob
    std::string generateString(int length);
    HashTable *hashTable = new HashTable(10);

};

#endif // MARKOVCHAIN_H
