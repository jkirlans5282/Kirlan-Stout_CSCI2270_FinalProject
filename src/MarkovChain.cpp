#include "MarkovChain.h"
#include <random>
#include <time.h>
#include <stdio.h>
#include <fstream>
#include <sstream>
#include <algorithm>

/*Determines if a character is alphabetical. Returns true if NOT a letter.
This is so replace_if can be called in the longest constructor to replace all
non alphabetical chars w/ spaces when reading in file.
Pre conditions: none.
Post conditions: none.
*/
bool isNotAlpha(char x)
{
    if(x == ' ')
    {
        return false;
    }
    bool b = isalpha(x);
    return !b;
}

/*Constructor #1: verbose false, no Markov Chain initialized. */
MarkovChain::MarkovChain()
{
    isVerbose = false;
    hashTable->isVerbose = false;
}

/*Constructor #2: verbose false, constructs Markov Chain from string*/
MarkovChain::MarkovChain(std::string textIn)
{
    isVerbose = false;
    hashTable->isVerbose = false;
    add(textIn, false);
}

/* Constructor #3: verbose false, constructs Markov Chain from string if flag is true and file if flag is false. */
MarkovChain::MarkovChain(std::string textIn, bool flag)
{
    isVerbose = false;
    hashTable->isVerbose = false;
    add(textIn, flag);
}

/* If flag is true, textIn is a file name. If false, it's a string variable.
   If v is true, verbose mode will be used. */
MarkovChain::MarkovChain(std::string textIn, bool flag, bool v)
{
    isVerbose = v;
    hashTable->isVerbose = v;
    add(textIn, flag);
}

/*  Constructs both the graph and the hash table. See the readme for a complete description of how this works.
    If flag is true, textIn is the name of a string. If false, it's used as a file name.
    Pre conditions: textIn cannot be "" or, if it's a filename, the name of a nonexistent file. If it is, the code
    will run, but various strange errors occur.
    Post conditions: Graph (not a class, so no name) and hash table (hashTable) constructed.
*/
void MarkovChain::add(std::string textIn, bool flag)
{
    if(!flag) //textIn is a filename
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
    else //textIn is a string
    {
        //The first word shouldn't be given an edge to itself, this bool allows it not to.
        bool firstword = true;
        Word *w;
        std::string line;
        std::string parsedWord;
        std::istringstream ss1(textIn);
        int i = 0;

        //Parses the string line by line (artifact of previous code. We know there's a better way to do this.)
        while(std::getline(ss1, line, '\n'))
        {
            if(isVerbose)
            {
                std::cout << "Line: " << line << std::endl;
            }
            std::replace_if(line.begin(), line.end(), isNotAlpha, ' '); //Replaces all non alphabetical characters with spaces.
            std::istringstream ss2(line);
            //Parses each line word by word
            while(std::getline(ss2, parsedWord, ' '))
            {
                //If word is not a space (resolved issue with seg fault on double spaces)
                if(parsedWord.compare(""))
                {
                    w = addWordToHashtable(parsedWord);

                    if(!firstword)
                    {
                        addEdge(w);
                    }
                    else //change firstWord to false the first time through
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


/*  Adds word to hash table if it isn't already there.
    Pre condition: none
    Post condition: a Word struct has been created and added to the hashTable and the graph.
        It has a Word *next pointer to the next word in the linked list within the hash table,
        and a vector of adjacent vertices that contains pointers to all other words that have
        ever PRECEDED the current one. If the current word has followed one of the words in its edges
        more than once, the weight of that edge has been incremented by one.
*/
Word * MarkovChain::addWordToHashtable(std::string name)
{
    Word * found = hashTable->findWord(name, false); //The boolean flag in findWord returns the current word in the hash table if true, the previous word if false
    //The above line is determining if name exists in the hash table. If not, it returns null. If so, it returns the word right before name.

    //If name isn't already part of the table, then found is the Word struct right before name needs to be inserted, so insert it:
    if(!found)
    {
        return hashTable->insertWord(name);
    }
    //If name is part of hash table, return null
    return found;
}

/*  Checks the graph for an edge between currentWord (which is a private global variable in class MarkovChain) and next.
    Returns true if edge exists, false if not.
    Pre conditions: none.
    Post conditions: none.
*/
bool MarkovChain::checkForExistingEdge(Word * next){
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

/*  Adds an edge if the edge doesn't already exist from current to next.
    The weight of the edge between currentWord (a private global variable) and next is
    already incremented in checkForExistingEdge() if checkForExistingEdge() returns true.
*/
void MarkovChain::addEdge(Word * next)
{
    //If edge doesn't exist, add it. Also increment the variable used to keep track of the size of the vector of adjacent edges
    if(!checkForExistingEdge(next)){
        currentWord->edges.push_back(next);
        currentWord->edgeSize++;
    }
}

/*
    Picks the next word in the Markov chain by choosing a random number between zero and the total weights of all current's edges.
    It then iterates through current's edges by subtracting each edge's weight one at a time until random is less than zero.
    Whatever edge it's on then becomes the next word.

    This effectively chooses a word based on the probability that it follows the current word. This word becomes current.

    Preconditions:
    Some text has been added to the chain.

    Postconditions:
    Current* changes to a new word.
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
        if(isVerbose)
        {
            std::cout << "Random index:" << random << std::endl;
        }
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
    bool empty = true;
    for(int i = 0; i < hashTable->arraySize; i++)
    {
        std::cout << "[" << i << "]" << " : ";
        Word currentWord = hashTable->hashTable[i];
        while(currentWord.next != NULL)
        {
            std::cout << " (" << currentWord.next->word << ")->";
            currentWord = *(currentWord.next);
            if(empty)
            {
                empty = false;
                break;
            }
        }
        if(!empty)
        {
            break;
        }
        std::cout << std::endl;
    }
    if(empty)
    {
        return "";
    }

    std::cout << length << std::endl;
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
