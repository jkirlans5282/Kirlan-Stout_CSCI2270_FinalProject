#ifndef WORDSTRUCT_H
#define WORDSTRUCT_H
#include <iostream> //used for print statements
#include <string> //used for strings
#include <vector> //used to store edges

/*
 This document specifies the basic structs we used to create a directed graph.
 */

struct Word; /* This is defined here so that Edge can point to a word. */


struct Edge
{
    Word * next;
    int occurrences;
    Edge(Word * n) //constructor
    {
        next = n;
        occurrences = 1;
    }
};

struct Word{
    /*
     This struct is both used for items in the directed graph and as the item in the hash table we use to store all of the words.
     We decided to use a hash table to store the words for speed when reading them in.
     If the words were only stored in a graph, the entire graph would need to be searched every time a word is added.
     THE SAME STRUCTS are used in both. There are not two sets of objects, instead each one is BOTH an element in the graph and the hashtable.
    */
    std::string word; //The word we are storing.
    Word *next; //Using to implement the linked list in the hash table.
    std::vector<Edge> edges = {}; //Vector of Edge structs used to implement the directed graph.
    int edgeSize = 0; //This stores the size of the edge variable for easy access.

    Word() //Only used for the empty words that are the head of the hashtable's linked list.
    {
        word = "";
        next = NULL;
    }

    Word(std::string in_word) //Used for all elements in the hashtable after the first.
    {
       word = in_word;
       next = NULL;
    }

    void printWord() //Prints the word AND all of it's edges.
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
