#ifndef WORDSTRUCT_H
#define WORDSTRUCT_H
#include <iostream>
#include <string>
#include <vector>
struct Word;

struct Edge{
    Word * next;
    int occurences;
};

struct Word{
    std::string word;
    Word *next; //linked list for hashtable
    std::vector<Edge> edges; //graph
    Word(){std::cout<<"hey shithead you initialized it without a value";};
    Word(std::string in_word)
    {
       std:: string word = in_word;
       next = NULL;
    }
};
#endif // WORDSTRUCT_H
