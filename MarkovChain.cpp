#include "MarkovChain.h"
#include <random>
#include <time.h>

MarkovChain::MarkovChain(std::string filename)
{
    
}

bool MarkovChain::checkForExistingEdge(Word *current, std::string next){ //checks for matching edge if edge is found increments and returns true if edge not found returns false
    bool flag = false;
    for(Edge i:current.edges){
        if(!i->next.word.compare(next)){
            flag = true;
            i.occurences+=1;
        }
        return flag;
    }
}

void MarkovChain::addWord(std::string next) //Do we need this? I vote we get rid of it -Izaak
{
    hashTable.addWord(next)
}

void MarkovChain::addEdge(std::string next){
    if(!checkForExistingEdge(currentWord, next)){
        Word * destination = hashTable.findWord(next, false);
        if(destination == 0) //if no next word is found
        {
            destination = hashTable.insertWord(next); //create a new word
        }
        Edge e = new Edge(destination)  //declare new edge to word
        current.edges.push_back()//append edge into current word edge vector
    }
}

std::string MarkovChain::generateString(int length)
{
    std::string output;
    current = 0;//some word in table
    output.append(current.word);
    output.append(" ");
    for(int l = 0; l < length; l++)
    {
        totalWeight = 0;
        for(int i = 0; i < current.edges.size(); i++)
        {
            totalWeight += current.edges[i].occurences;
        }
        random_device generator;
        uniform_real_distribution<int> distribution (0,totalWeight);
        randint = distribution(generator)
        int j = 0;
        while(true)
        {
            randint -= current.edges[j].occurences;
            if(randint<0)
            {
                current = current.edges[j]
            }
        }
        output.append(current.word);
        output.append(" ");
    }
    output.append(".");
    return output;
}
