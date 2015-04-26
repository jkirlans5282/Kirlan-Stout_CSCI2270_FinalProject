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
            std::cout << input << std::endl;
            std::replace_if(input.begin(), input.end(), isNotAlpha, ' '); //Replaces all non alphabetical characters with nothing
            std::istringstream ss(input);
            while(std::getline(ss, parsedWord, ' '))
            {
                if(parsedWord.compare(""))
                {
                    w = addWord(parsedWord);
                    addEdge(parsedWord);
                    currentWord = w;
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

/* If edge is found increments and returns true if edge not found returns false */
//Would anyone mind if I combined this method with addEdge? Currently its name is disassociated with its functionality. -Alex
bool MarkovChain::checkForExistingEdge(Word *current, std::string nextWord) //Untested
{
    bool flag = false;
    for(Edge i:current->edges){
        if(!i.next->word.compare(nextWord)){
            flag = true;
            i.occurences+=1;
        }
    }
    return flag;
}
// Keep this just as a accessor method
Word * MarkovChain::addWord(std::string name)
{
    Word * found = hashTable->findWord(name, false);
    if(!found)
    {
        return hashTable->insertWord(name);
    }
    return found;
}

void MarkovChain::addEdge(std::string next) //Untested
{
    if(!currentWord)
    {
        //This previously printed out "yes". Perhaps making our test prints more meaningful might help others debug? -Alex
        std::cout << "MarkovChain::addEdge - currentWord is false" << std::endl;
        if(!checkForExistingEdge(currentWord, next)){
            std::cout << "MarkovChain::addEdge - There is no existing edge" << std::endl; //This printed out "yes!!". See above.

            Word * destination = hashTable->findWord(next, false);
            Edge *e = new Edge(destination);
            currentWord->edges.push_back(*e);
        }
        else
        {

        }
    }
}

std::string MarkovChain::generateString(int length) //Untested
{
    std::string output;
    std::random_device generator; //This seems excessive. Is it alright to replace it with a more simple random number generator? -Jacob
    std::uniform_int_distribution<int> randomindex (0,hashTableSize-1);
    int inx = randomindex(generator);
    std::cout << inx << std::endl;
    Word current = *(hashTable->hashTable[inx].next); //Not actually random- can only be one of the
    output.append(current.word);
    output.append(" ");
    current.printWord();
    for(int l = 0; l < length; l++)
    {
        int totalWeight = 0;
        std::cout << current.edges.size() << std::endl;
        for(int i = 0; i < current.edges.size(); i++)
        {
            totalWeight += current.edges[i].occurences;
            std::cout << totalWeight << std::endl;
        }
        std::random_device generator; //See note on whether we need this or not, above.
        std::uniform_int_distribution<int> distribution (0,totalWeight);
        int randint = distribution(generator);
        int j = 0;
        while(true)
        {
            randint -= current.edges[j].occurences;
            if(randint<0)
            {
                current = *(current.edges[j].next);
            }
        }
        output.append(current.word);
        output.append(" ");
    }
    output.append(".");
    return output;
}
