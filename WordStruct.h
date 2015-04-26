#ifndef WORDSTRUCT_H
#define WORDSTRUCT_H
#include <iostream>
#include <string>
#include <vector>
//Word struct is used by both HashTable and MarkovChain

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
    std::vector<Edge> edges; //graph
    Word(){word ="__NULL__"; next=NULL;};
    Word(std::string in_word)
    {
       word = in_word;
       next = NULL;
    }
};
#endif // WORDSTRUCT_H
