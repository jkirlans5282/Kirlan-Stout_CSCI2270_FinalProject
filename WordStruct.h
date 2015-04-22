#ifndef WORDSTRUCT_H
#define WORDSTRUCT_H
#import <iostream>
#include <string>
#import <vector>

struct Edge{
    Word * next;
    int occurences;
};

struct Word{
    std::string word;
    Word *next;
    std::vector<Edge> edges;
    Word(std::string in_word)
    {
       std:: string word = in_word;
       next = NULL;
    }
};
#endif // WORDSTRUCT_H
