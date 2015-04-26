#ifndef HASHTABLE_H
#define HASHTABLE_H
#include "WordStruct.h"

class HashTable
{
private:
    int[] linkedListLengths;
    public:
        HashTable(int);
        ~HashTable();
        Word* insertWord(std::string in_word);
        Word* findWord(std::string searchword, bool returningPrev);
        void deleteWord(std::string searchword);
        void printInventory();
        int hashSum(std::string, int);

        //Why were these made public? -Alex
        Word *hashTable;
        int arraySize; //Is this needed? We have hashtable size in the Markov chain as well. -Jacob
};

#endif // HASHTABLE_H
