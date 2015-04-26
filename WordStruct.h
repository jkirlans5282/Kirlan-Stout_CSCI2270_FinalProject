#ifndef WORDSTRUCT_H
#define WORDSTRUCT_H
#include <iostream>
#include <string>
#include <vector>

/* Word struct is used by both HashTable and MarkovChain */ //Is this comment necessary to understand it? -Alex
struct Word;

struct Edge{
    Word * next;
    int occurences;
    Edge(Word * n)
    {
        next = n;
        occurences = 1;
    }
};

struct Word{
    std::string word;
    Word *next; //linked list for hashtable
    std::vector<Edge> edges = {}; //graph
    int edgeSize = 0;
    Word()
    {
        word ="";
        next=NULL;
    }
    Word(std::string in_word)
    {
       word = in_word;
       next = NULL;
    }
    void printWord()
    {
        std::cout << word << std::endl;
        for(int i = 0; i < edgeSize; i++)
        {
            std::cout << "Edge " << i << ": " << edges[i].next->word << std::endl;
        }
    }
};

#endif // WORDSTRUCT_H
