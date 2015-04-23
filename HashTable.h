#ifndef HASHTABLE_H
#define HASHTABLE_H
#include "WordStruct.h"

class HashTable
{
    public:
        HashTable(int);
        ~HashTable();
        Word* insertWord(std::string in_word);
        Word* findWord(std::string searchword, bool del);
        void deleteWord(std::string searchword);
        void printInventory();
        int hashSum(std::string, int);
    protected:
    private:
        Word *hashTable;
        int arraySize; // is this needed, we have hashtable size in the markov chain as well -Jacob
};

#endif // HASHTABLE_H
