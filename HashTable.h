#ifndef HASHTABLE_H
#define HASHTABLE_H
#include "WordStruct.h"

class HashTable
{
    friend class MarkovChain; //This allows MarkovChain objects to access the private functions and variables of a HashTable object.
private:
    bool verbose;
    int *linkedListLength;
    HashTable(int);
    ~HashTable();
    Word* insertWord(std::string in_word);
    Word* findWord(std::string searchword, bool returningPrev);
    void deleteWord(std::string searchword);
    void printInventory();
    int hashSum(std::string, int);
    Word *hashTable;
    int arraySize;
};

#endif // HASHTABLE_H
