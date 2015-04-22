#include "MarkovChain.h"
Bool checkForExistingEdge(Word *current, std::string next){ //checks for matching edge if edge is found increments and returns true if edge not found returns false
    bool flag = false;
    for(Edge i:current.edges){
        if(!i->next.word.compare(next)){
            flag = true;
            i.occurences+=1;
        }
        return flag;
}
void MarkovChain::addWord(std::string name){
//add word to hash table with name value
}

void MarkovChain::addEdge(std::string next){
    if(!checkForExistingEdge(currentWord, next)){
        //check for existing word
        //if not, create new word
        Edge e = new Edge()  //declare new edge to word
        current.edges.push_back()//append edge into current word edge vector
    }
}
