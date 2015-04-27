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

/* If flag is true, textIn is a file name. If false, it's passed as a string. Flag is default TRUE. */
MarkovChain::MarkovChain(std::string textIn, bool flag)
{
    if(flag) //If a filename is passed and a file needs to be read.
    {
        bool firstword = true;
        std::ifstream inFile(textIn);

        std::string line;
        std::string parsedWord;

        Word *w;
        std::cout << "This is a test statement" << std::endl;
        while(!inFile.eof())
        {
            getline(inFile, line);

            //std::cout << line << std::endl; //TEST OUTPUT

            std::replace_if(line.begin(), line.end(), isNotAlpha, ' '); //Replaces all non alphabetical characters with spaces.
            std::istringstream ss(line);

            while(std::getline(ss, parsedWord, ' ')) //Parses lines into individual words.
            {
                //std::cout << parsedWord << std::endl;// TEST OUTPUT

                if(parsedWord.compare(""))
                {
                    w = addWordToHashtable(parsedWord);

                    if(!firstword)
                    {
                        addEdge(w);
                    }

                    firstword = false;
                    currentWord = w;
                }
            }
        }

        std::cout << "Finished reading in file" << std::endl;
    }
    else //THIS IS REALLY OLD AND UNTESTED I DON'T THINK IT WORKS
    {
        std::replace_if(textIn.begin(), textIn.end(), isNotAlpha, ' ');
        std::istringstream ss(textIn);
        std::string parsedWord;
        while(std::getline(ss, parsedWord, ' '))
        {
            currentWord = addWordToHashtable(parsedWord);
        }
    }
}

Word * MarkovChain::addWordToHashtable(std::string name)
{
    Word * found = hashTable->findWord(name, false);

    if(!found)
    {
        return hashTable->insertWord(name);
    }

    return found;
}
bool MarkovChain::checkForExistingEdge(Word * next){
    if(currentWord->edgeSize>=1){
        for(int i = 0 ; i<currentWord->edgeSize; i++){
            if(currentWord->edges[i].next->word.compare(next->word)==0){
                currentWord->edges[i].occurrences+=1;
                return true;
            }
        }
        return false;
    }
    else{
        return false;
    }
}
void MarkovChain::addEdge(Word * next) //Untested
{
    //std::cout<<"Current Word in addEdge is: "<<currentWord<<std::endl; //TEST OUTPUT
    if(!checkForExistingEdge(next)){ //edge incremented in check sloppy but simple way to do it
        currentWord->edges.push_back(next);
        currentWord->edgeSize++;
    }
}

Word * MarkovChain::nextWord(Word * current)
{
    int totalWeight = 0;
    for(int i = 0; i < current->edgeSize; i++)
    {
        totalWeight++;
    }
    std::random_device generator;
    std::uniform_int_distribution<int> randomweight (0,totalWeight-1);
    int random = randomweight(generator);
    Word * next = new Word;
    if(current->edges.size() > 0)
    {
        int j = 0;
        while(true)
        {
            random -= current->edges[j].occurrences;
            if(random < 0)
            {
                next = current->edges[j].next;
                break;
            }
            j++;
        }
    }
    else
    {
        next = randomWord();
    }
    return next;
}

Word * MarkovChain::randomWord()
{
    std::random_device generator; //This doesn't work on Windows machines.
    std::uniform_int_distribution<int> randomindex (0,hashTableSize-1);
    int random = randomindex(generator);
    while(hashTable->hashTable[random].next == NULL) //In case it picks a hash with no values assigned to it.
    {
        random = randomindex(generator);
    }
    std::uniform_int_distribution<int> randomdistance (0,hashTable->linkedListLength[random]-1);
    int distance = randomdistance(generator);
    Word * current = hashTable->hashTable[random].next;
    for(int i = 0; i < distance; i++)
    {
        current = current->next;
    }
    return current;
}

std::string MarkovChain::generateString(int length)
{
    std::string output;
    Word * current = randomWord();
    output.append(current->word);
    output.append(" ");
    for(int l = 0; l < length; l++)
    {
        if(current->edges.size() > 0)
        {
            current->printWord();
            current = nextWord(current);
            output.append(current->word);
            output.append(" ");
        }
    }
    output.append(".");
    //std::cout << output << std::endl; TEST OUTPUT
    return output;
}
