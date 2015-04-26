#include "MarkovChain.h"
#include <random>
#include <time.h>
#include <stdio.h>
#include <fstream>
#include <sstream>
#include <algorithm>

bool isNotAlpha(char x)
{
    bool b = isalpha(x);
    return !b;
}

/* If flag is true, textIn is a file name. If false, it's just a string of text. */
MarkovChain::MarkovChain(std::string textIn, bool flag)
{
    if(flag)
    {
        std::ifstream inFile(textIn); //Variable fileName changed to textIn, as it was not always a filename. -Alex
        std::string input;
        std::string parsedWord;
        Word *w;
        while(!inFile.eof())
        {
            getline(inFile, input);
            //std::cout << input << std::endl; TEST OUTPUT
            std::replace_if(input.begin(), input.end(), isNotAlpha, ' '); //Replaces all non alphabetical characters with nothing
            std::istringstream ss(input);
            while(std::getline(ss, parsedWord, ' '))
            {
                std::cout << parsedWord << std::endl;// TEST OUTPUT
                if(parsedWord.compare(""))
                {
                    std::cout<<"one"<<std::endl;
                    w = addWord(parsedWord);
                    currentWord = addWord(parsedWord);
                    std::cout<<"two"<<std::endl;
                    addEdge(w); //THE BAD ALLOC IS HERE.
                    std::cout<<"three"<<std::endl;
                    currentWord = w;
                    std::cout<<"four"<<std::endl;
                }
            }
        }

        std::cout << "Finished reading in file" << std::endl;
    }
    else
    {
        std::replace_if(textIn.begin(), textIn.end(), isNotAlpha, ' '); //Replace all non alpha characters with nothing
        std::istringstream ss(textIn);
        std::string parsedWord;
        while(std::getline(ss, parsedWord, ' '))
        {
            currentWord = addWord(parsedWord);
        }
    }
}

// Keep this just as a accessor method
Word * MarkovChain::addWord(std::string name)
{
    //std::cout << name << std::endl;TEST OUTPUT
    //hashTable->printInventory(); TEST OUTPUT
    Word * found = hashTable->findWord(name, false);
    //std::cout << "test" << std::endl; TEST OUTPUT
    if(!found)
    {
        return hashTable->insertWord(name);
    }

    return found;
}

void MarkovChain::addEdge(Word * next) //Untested
{
    std::cout<<currentWord<<std::endl;
    currentWord->edges.push_back(next);
    std::cout<<"four"<<std::endl;
    currentWord->edgeSize++;
}

Word * MarkovChain::nextWord(Word * current)
{
    std::random_device generator;
    std::uniform_int_distribution<int> randomindex (1,current->edgeSize);
    int inx = randomindex(generator);
    Word * next = current->edges[inx-1].next;
    return next;
}

std::string MarkovChain::generateString(int length)
{
    std::string output;
    std::random_device generator;
    std::uniform_int_distribution<int> randomindex (0,hashTableSize-1);
    int inx = randomindex(generator);
    Word current = *(hashTable->hashTable[inx].next); //Segfault
    output.append(current.word);
    output.append(" ");
    for(int l = 0; l < length; l++)
    {
        current.printWord();
        current = *nextWord(&current);
        output.append(current.word);
        output.append(" ");
    }
    output.append(".");
    //std::cout << output << std::endl; TEST OUTPUT
    return output;
}
