#ifndef MARKOVCHAIN_H
#define MARKOVCHAIN_H
#include "HashTable.h"

class MarkovChain
{
private:
    int hashTableSize=10;
    HashTable *hashTable = new HashTable(hashTableSize);
    bool isVerbose;
    bool punctuation;
    int sentenceLength = 0;
    Word *currentWord;
    int period[20] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    int comma[20] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

	Word *addWordToHashtable(std::string name);
	void addEdge(Word * next);
    bool addPunctuation(char);
	Word * nextWord(Word * current);
	bool checkForExistingEdge(Word *next);
    Word * randomWord();
    std::string generatePunctuation(std::string output);
public:
    /*
        For MarkovChain constructors, if v is true, verbose mode is true. See main.cpp for more information on verbose mode.
        In the constructors, if flag is false it assumes the argument is a filename that needs to be read. If it's true, it assumes it's just a string.
        If no flag is passed, it assumes the string is a filename. If no verbose flag is passed, it is set to false by default.
        In the add() method, flag acts the same way but is default false, meaning that add("filename") is valid syntax and won't throw an error.
    */
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
