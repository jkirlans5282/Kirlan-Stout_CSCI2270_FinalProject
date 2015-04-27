#ifndef HASHTABLE_H
#define HASHTABLE_H
#include "WordStruct.h"

class HashTable
{
    public:
    /*
     What can be private? remember we might need to access things in MarkovChain that the user shouldn't access.
     Is there a way to do that via inheritance or something?
     also, should we rename stuff for consistent naming across cases?
    */
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
