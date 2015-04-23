#include "MarkovChain.h"
#include <random>
#include <time.h>
#include <stdio.h>
#include <fstream>
#include <sstream>

bool isNotAlpha(char x)
{
    bool b = isalpha(x);
    return !b;
}

MarkovChain::MarkovChain(std::string fileName, bool flag=true) //Untested, needs cleaning
{   if(flag){
        std::ifstream inFile(fileName);
        std::string input;
        while(!inFile.eof()){
            getline(inFile, input); //read-in one line at a time
            //WARNING THIS LINE MIGHT THROUGH ERRORS LATER
            std::cout<<"Before: " <<input<<std::endl;
            std::replace_if(input.begin(), input.end(), isNotAlpha, ' '); //replace all non alpha with nothing
            std::cout<<"After: "<<input<<std::endl;
            std::istringstream ss(input); //create string stream
            std::string parsedWord;
            while(std::getline(ss, parsedWord, ' ')) {
                addWord(parsedWord);
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
    //add word to hash table with name value
    Word * w = hashTable->insertWord(name);
    return w;
}

void MarkovChain::addEdge(std::string next) //Untested, written
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
std::string MarkovChain::generateString(int length) //Untested, written
{
    std::string output;
    Word * current = NULL;//random word in table
    output.append(current->word);
    output.append(" ");
    for(int l = 0; l < length; l++)
    {
        int totalWeight = 0;
        for(int i = 0; i < current->edges.size(); i++)
        {
            totalWeight += current->edges[i].occurences;
        }
        std::random_device generator; //this seems excessive? but whatever.
        std::uniform_real_distribution<int> distribution (0,totalWeight);
        int randint = distribution(generator);
        int j = 0;
        while(true)
        {
            randint -= current->edges[j].occurences;
            if(randint<0)
            {
                current = current->edges[j].next;
            }
        }
        output.append(current->word);
        output.append(" ");
    }
    output.append(".");
    return output;
}
