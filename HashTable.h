#ifndef HASHTABLE_H
#define HASHTABLE_H
#import <iostream>
#include <string>
struct Movie{
    std::string title;
    int year;
    Movie *next;
    Movie(){next = NULL; title=""; };
    Movie(std::string in_title, int in_year)
    {
        title = in_title;
        year = in_year;
        next= NULL;
    }
};

class HashTable
{
    public:
        HashTable(int);
        ~HashTable();
        void insertMovie(std::string in_title, int in_year);
        Movie* findMovie(std::string searchTitle, bool del);
        void deleteMovie(std::string searchTitle);
        void printInventory();
        int hashSum(std::string);
    protected:
    private:
        Movie *hashTable;
        int arraySize;
};

#endif // HASHTABLE_H
