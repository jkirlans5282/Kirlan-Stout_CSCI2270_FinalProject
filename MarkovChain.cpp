#include "MarkovChain.h"
#include <random>
#include <time.h>
#include <sstream>

MarkovChain::MarkovChain(std::string filename) //Untested, written
{
    std::ifstream inFile(filename);
    std::string input;
    while(!inFile.eof()){
        getline(inFile, input); //read-in one line at a time
        //WARNING THIS LINE MIGHT THROUGH ERRORS LATER
        std::cout<<"Before: " <<input<<std::endl;
        std::replace_if(input.begin(), input.end(), isNotAlpha, ''); //replace all non alpha with nothing
        std::cout<<"After: "<<input<<std::endl;
        std::istringstream ss(input); //create string stream
        std::string parsedWord;
        while(std::getline(ss, parsedWord, ' ')) {
            addWord(parsedWord);
        }
    }
    std::cout<<"finished reading in file\n";
}
//checks for edge from (currentWord)->next word
//if edge is found increments and returns true if edge not found returns false
bool MarkovChain::checkForExistingEdge(Word *current, std::string next) //Untested, written
{
    bool flag = false;
    for(Edge i:current.edges){
        if(!i->next.word.compare(next)){
            flag = true;
            i.occurences+=1;
        }
        return flag;
    }
}
// Keep this just as a accessor method so the user 
// is never accessing the hash table directly
void MarkovChain::addWord(std::string name){
    //add word to hash table with name value
    hashTable.insertWord(name);
}

void MarkovChain::addEdge(std::string next) //Untested, written
{
    if(!checkForExistingEdge(currentWord, next)){
        Word * destination = hashTable.findWord(next, false);
        if(destination == NULL) //if no next word is found
        {
            destination = hashTable.insertWord(next); //create a new word
        }
        Edge e = new Edge(destination)  //declare new edge to word
        current.edges.push_back(e)//append edge into current word edge vector
    }
}
std::string MarkovChain::generateString(int length) //Untested, written
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
        random_device generator; //this seems excessive? but whatever.
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
