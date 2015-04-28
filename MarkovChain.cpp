#include "MarkovChain.h"
#include <random>
#include <time.h>
#include <stdio.h>
#include <fstream>
#include <sstream>
#include <algorithm>

//Determines if a character is alphabetical
bool isNotAlpha(char x)
{
    if(x == ' ')
    {
        return false;
    }
    bool b = isalpha(x);
    return !b;
}

MarkovChain::MarkovChain()
{
    isVerbose = false;
    hashTable->isVerbose = false;
}

MarkovChain::MarkovChain(std::string textIn)
{
    isVerbose = false;
    hashTable->isVerbose = false;
    add(textIn, false);
}

MarkovChain::MarkovChain(std::string textIn, bool flag)
{
    isVerbose = false;
    hashTable->isVerbose = false;
    add(textIn, flag);
}

/* If flag is true, textIn is a file name. If false, it's passed as a string. */
MarkovChain::MarkovChain(std::string textIn, bool flag, bool v)
{
    isVerbose = v;
    hashTable->isVerbose = v;
    add(textIn, flag);
}

void MarkovChain::add(std::string textIn, bool flag)
{
    if(!flag) //If a filename is passed and a file needs to be read.
    {
        //The first word shouldn't be given an edge to itself, this bool allows it not to.
        bool firstword = true;
        Word *w;
        std::ifstream inFile(textIn);
        std::string line;
        std::string parsedWord;

        //Reads in the file line by line, and an inner getline() reads the line in word by word.
        while(getline(inFile, line))
        {
            if(isVerbose)
            {
                std::cout << "line: " << std::endl;
                std::cout << line << std::endl;
            }
            std::replace_if(line.begin(), line.end(), isNotAlpha, ' '); //Replaces all non alphabetical characters with spaces.
            std::istringstream ss(line);
            while(std::getline(ss, parsedWord, ' ')) //Parses lines into individual words.
            {
                //If word is not a space (resolved issue with seg fault on double spaces)
                if(parsedWord.compare(""))
                {
                    w = addWordToHashtable(parsedWord);
                    if(!firstword)
                    {
                        addEdge(w);
                    }
                    else
                    {
                        firstword = false;
                    }
                    currentWord = w;
                }
            }
        }

        if(isVerbose)
        {
            std::cout << "Finished reading in string" << std::endl;
        }
    }
    else
    {
        //The first word shouldn't be given an edge to itself, this bool allows it not to.
        bool firstword = true;
        Word *w;
        std::string line;
        std::string parsedWord;
        std::istringstream ss1(textIn);
        int i = 0;

        //Reads in the file line by line, and an inner getline() reads the line in word by word.
        while(std::getline(ss1, line, '\n'))
        {
            if(isVerbose)
            {
                std::cout << "Line: " << line << std::endl;
            }
            std::replace_if(line.begin(), line.end(), isNotAlpha, ' '); //Replaces all non alphabetical characters with spaces.
            std::istringstream ss2(line);
            while(std::getline(ss2, parsedWord, ' ')) //Parses lines into individual words.
            {
                //If word is not a space (resolved issue with seg fault on double spaces)
                if(parsedWord.compare(""))
                {
                    w = addWordToHashtable(parsedWord);

                    if(!firstword)
                    {
                        addEdge(w);
                    }
                    else
                    {
                        firstword = false;
                    }
                    currentWord = w;
                }
            }
        }
        if(isVerbose)
        {
            std::cout << "Finished reading in string" << std::endl;
        }
    }
}


//Adds word to hash table if it isn't already there
Word * MarkovChain::addWordToHashtable(std::string name)
{
    Word * found = hashTable->findWord(name, false); //The boolean flag in findWord returns the current word in the hash table if true, the previous word if false
    //The above line is determining if name exists in the hash table. If not, it returns null. If so, it returns the word right before name.

    //If name isn't already part of the table, insert it:
    if(!found)
    {
        return hashTable->insertWord(name);
    }
    //If name is part of hash table, return null
    return found;
}


bool MarkovChain::checkForExistingEdge(Word * next){
    //currentWord is a private variable in class MarkovChain
    if(currentWord->edgeSize>=1){
        for(int i = 0 ; i<currentWord->edgeSize; i++){
            //if an edge exists, increment its weight by one. If not, return false.
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
    if(!checkForExistingEdge(next)){ //The weight of the edge is already incremented in checkForExistingEdge() if said function returns true.
        //If edge doesn't exist, add it. Also increment the variable used to keep track of the size of the vector of adjacent edges
        currentWord->edges.push_back(next);
        currentWord->edgeSize++;
    }
}

/*
    Picks a new word based off the probability that it would follow the current word.

*/
Word * MarkovChain::nextWord(Word * current)
{
    int totalWeight = 0; //stores the sum of all the weights of all the edges of Word* current
    for(int i = 0; i < current->edgeSize; i++)
    {
        totalWeight+= current->edges[i].occurrences;
    }
    std::random_device generator;
    std::uniform_int_distribution<int> randomweight (0,totalWeight-1);
    //Generate a random number between 0 and totalWeight-1
    int random = randomweight(generator);
    Word * next = new Word;
    if(current->edges.size() > 0)
    {
        int j = 0;
        //Iterate through current's edges by subtracting each edge's weight one at a time until random is less than zero.
        //Whatever edge you're on then, that word becomes the next word.
        //This allows for the probabilities explained in the README (not yet described at the time this comment was written) to be true.
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

/*
    Chooses a word randomly from the pool of everything that it has read in. It sets current* to be this word.
    If verbose is true (see below) it prints the index where the word was chosen from.

    Preconditions:
    Some text has been added to the hashtable.
    At the moment, this function doesn't appear to work on at least some Windows machines. The random numbers are not, in fact, random.

    Postconditions:
    Current* changes to some word that is likely to follow it.
*/
Word * MarkovChain::randomWord()
{
    std::random_device generator;
    std::uniform_int_distribution<int> randomindex (0,hashTableSize-1);
    int random = randomindex(generator);

    //If random (which will be an index in the hash table) is a number with no values assigned to it, re-pick it.
    while(hashTable->hashTable[random].next == NULL)
    {
        random = randomindex(generator);
    }

    if(isVerbose)
    {
        std::cout << "Random index:" << random << std::endl;
    }

    //Distance is the distance along the linked list that the random word is found.
    std::uniform_int_distribution<int> randomdistance (0,hashTable->linkedListLength[random]-1);
    int distance = randomdistance(generator);

    if(isVerbose)
    {
        std::cout << "Random distance:" << distance << std::endl;
    }

    Word * current = hashTable->hashTable[random].next;
    for(int i = 0; i < distance; i++)
    {
        current = current->next;
    }
    return current;
}

/*
    GenerateString() makes a string of words, the length of which is passed in as an argument. This is printed to the console.
    It does this by selecting a random word from everything that it has read in.
    Every subsequent word is based off the probability that it would follow the previous word.

    Preconditions:
    Some text has been added to the Markov chain.
    Length is greater than zero.
*/
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
            if(isVerbose)
            {
                current->printWord();
            }
            current = nextWord(current);
            output.append(current->word);
            output.append(" ");
        }
    }
    output.append("\b" ".");
    if(isVerbose)
    {
        std::cout << output << std::endl;
    }
    currentWord = current;
    return output;
}

/*
    GenerateNextWord() prints one word based off the last one that was printed.

    Preconditions:
    At least one chain should have been generated before this. This fact may change in later patches.
*/
std::string MarkovChain::generateNextWord()
{
    currentWord = nextWord(currentWord);
    std::string output = currentWord->word;
    return output;
}

/*
    Print() when called with a string shows each edge from the chosen word to all words that can follow it, including weights.

    Preconditions:
    The word should exist, or it won't be printed.
*/
void MarkovChain::print(std::string name)
{
	Word * found = hashTable->findWord(name, false);
	if(found != NULL)
    {
        found->printWord();
	}
	else
    {
        std::cout<<"Word not found!"<<std::endl;
    }


}

/*
    Print() with no arguments will display the hashtable in a visual format, even if it's empty.
    This is hard to read for large hashtables.
*/
void MarkovChain::print()
{
	hashTable->printInventory();
}

/*
    The verbose feature is useful for debugging, as it prints out much of what goes on behind the scenes.
    This includes lines when reading in, and edges when generating a string.

    Postconditions:
    The verbose() method flips whatever verbose is at the moment. If it's true it becomes false and vice versa.
*/
void MarkovChain::verbose()
{
    isVerbose = !isVerbose;
    hashTable->isVerbose = !(hashTable->isVerbose);
}

/*
    The verbose method can be called with a boolean argument, which sets verbose to be that regardless of what it was before.

    Postconditions:
    The verbose boolean is set equal to the boolean passed as an argument
*/
void MarkovChain::verbose(bool set)
{
    isVerbose = set;
    hashTable->isVerbose = set;
}
