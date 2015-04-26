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

MarkovChain::MarkovChain(std::string fileName, bool flag) //If flag is true, fileName is a filename. If false, it's just a string.
{   
    if(flag){
        std::ifstream inFile(fileName);
        std::string input;
        std::string parsedWord;
        Word * w;
        while(!inFile.eof()){
            getline(inFile, input); //read-in one line at a time
            std::cout<<input<<std::endl;
            std::replace_if(input.begin(), input.end(), isNotAlpha, ' '); //replace all non alphabetical words with nothing
            std::istringstream ss(input); //create string stream
            while(std::getline(ss, parsedWord, ' ')) {
                if(parsedWord.compare("")){
                    w = addWord(parsedWord);
                    addEdge(parsedWord);
                    currentWord = w;
                }
            }
        }
        std::cout<<"finished reading in file\n";
    }else{
        std::replace_if(fileName.begin(), fileName.end(), isNotAlpha, ' '); //replace all non alpha with nothing
        std::istringstream ss(fileName); //create string stream, text
        std::string parsedWord;
        while(std::getline(ss, parsedWord, ' ')) {
            currentWord = addWord(parsedWord);
        }
    }
}

//checks for edge from (currentWord)->next word
//if edge is found increments and returns true if edge not found returns false
bool MarkovChain::checkForExistingEdge(Word *current, std::string nextWord) //Untested, written
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

void MarkovChain::addEdge(std::string next) //Untested, written
{
    if(!currentWord)
    {
        if(!checkForExistingEdge(currentWord, next)){
            Word * destination = hashTable->findWord(next, false);
            if(destination == NULL) //if no next word is found
            {
                destination = hashTable->insertWord(next); //create a new word
            }
            Edge *e = new Edge(destination);  //declare new edge to word
            currentWord->edges.push_back(*e);//append edge into current word edge vector
        }
    }
}

std::string MarkovChain::generateString(int length) //Untested, written
{
    std::string output;
    std::random_device generator; //this seems excessive? but whatever.
    std::uniform_int_distribution<int> randomindex (0,hashTableSize-1);
    int inx = randomindex(generator);
    std::cout << inx << std::endl;
    Word current = *(hashTable->hashTable[inx].next);//random word in table
    output.append(current.word);
    output.append(" ");
    for(int l = 0; l < length; l++)
    {
        int totalWeight = 0;
        for(int i = 0; i < current.edges.size(); i++)
        {
            totalWeight += current.edges[i].occurences;
        }
        std::random_device generator; //this seems excessive? but whatever.
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
