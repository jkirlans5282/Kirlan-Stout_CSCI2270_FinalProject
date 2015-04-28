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
	int hashTableSize=10;
	Word * nextWord(Word * current);
	bool checkForExistingEdge(Word *next);
    Word * randomWord();
public:
    //For MarkovChain constructors, if v is true, verbose mode is true. See main.cpp for more information on verbose mode.
    //If flag is false, a filename is passed that needs to be read. If it's true, a string is passed.
    //The variables set here are OPTIONAL, so v or flag do not have to be passed and will just be set to false by default.
    //EX: MarkovChain() and MarkovChain("filename.txt") are VALID constructors.
	MarkovChain();
	MarkovChain(std::string textIn);
	MarkovChain(std::string textIn, bool flag);
	MarkovChain(std::string textIn, bool flag, bool v);
    std::string generateString(int length);
    std::string generateNextWord();
    void print();
    void print(std::string);
    void verbose(bool set);
    void verbose();
    void add(std::string textIn, bool flag = false);
};

#endif // MARKOVCHAIN_H
