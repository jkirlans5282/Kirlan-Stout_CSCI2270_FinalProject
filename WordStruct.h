#ifndef WORDSTRUCT_H
#define WORDSTRUCT_H
#import <iostream>
#include <string>
struct Edge{
};

struct Word{
    std::string word;
    Word *next;
    Word(){next = NULL; word=""; };
    Word(std::string in_word)
    {
       std:: string word = in_word;
       next= NULL;
    }
};
#endif // WORDSTRUCT_H
