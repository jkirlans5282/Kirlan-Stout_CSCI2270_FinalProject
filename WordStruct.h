#ifndef WORDSTRUCT_H
#define WORDSTRUCT_H
#include <iostream> //used for print statement
#include <string> //used for strings
#include <vector> //used to store edges.

/*
 This document specifies the basic structs we used to create a directed graph.
 */

struct Word; //This is defined here so that Edge can point to a word.

struct Edge
{
    /*
     This struct is a one-way edge with a weight.
     The word pointer "next" points to a word that, in the analyzed word document, came after the word that this edge is stored in.
     The int "occurences" is the number of times that this word has followed the original word.
     The constructor sets occurences to 1 because the first time it is added, it has only occured 1 time.
     */
    Word * next;
    int occurences;
    Edge(Word * n) //constructor
    {
        next = n;
        occurences = 1;
    }
};

struct Word{
    /*
     This struct is both used for items in the directed graph, and as the item in the hash table we use to store all of the words.
     We decided to use a hash table to store the words because we feared that using a linked list to store hundreds if not thousands of words would take too long to search.
     */
    std::string word; //This variable contains the word we are storing.
    Word *next; //This is the pointer we are using to implement the linked list in the hash table.
    std::vector<Edge> edges = {}; //This is the vector of Edge structs we are using to implement the directed graph.
    int edgeSize = 0; //This stores the size of the edge variable for easy access.
    Word() //This constructor is only used for the empty words that are the head of the linked list.
    {
        word ="";
        next=NULL;
    }
    Word(std::string in_word) //This is the default constructor. The next value is set when a new word comes after it.
    {
       word = in_word;
       next = NULL;
    }
    void printWord() //This is a simple function that prints the word and all of it's edges.
    {
        std::cout << word << std::endl;
        std::cout << edgeSize <<std::endl;
        for(int i = 0; i < edgeSize; i++)
        {
            std::cout << "Edge " << i << ": " << edges[i].next->word << std::endl;
        }
    }
};

#endif // WORDSTRUCT_H
