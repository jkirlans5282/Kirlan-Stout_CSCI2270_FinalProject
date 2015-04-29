#include "HashTable.h"
#include <stdlib.h>

int HashTable::hashSum(std::string str, int s)
{
	int hash = str[0];

	for (int i = 1 ; i < str.length(); i++)
		hash = ((hash * 33) + str[i]);

	return abs(hash%arraySize);
}

//Inserts word into hash table. Pre-conditions: in_word is not "".
//Post condition: hasTable has one more word in it.
Word *HashTable::insertWord(std::string in_word)
{
	Word *m = new Word(in_word);

	int location = hashSum(in_word, arraySize);
	linkedListLength[location]++; //Used when choosing the random word to start the chain.

	Word *currentWord = &(hashTable[location]);
	Word *previousWord = &(hashTable[location]);

	if(currentWord->next == NULL)
    {
		currentWord->next = m;
	}
	else
    {
		while(true)
		{
			if(in_word.compare(currentWord->word) < 0)
			{
				previousWord->next = m;
				m->next = currentWord;
				break;
			}
			else{
				if(currentWord->next != NULL)
                {
					previousWord = currentWord;
					currentWord = currentWord->next;
				}
				else
                {
					currentWord->next = m;
					break;
				}
			}
		}
	}
	if(isVerbose)
    {
        std::cout<<"Word added: " << m->word << std::endl;
    }

    return m; //Now returns the word for later use
}

void HashTable::printInventory()
{
	bool empty = true;
	for(int i = 0; i < arraySize; i++)
    {
		std::cout << "[" << i << "]" << " : ";
		Word currentWord = hashTable[i];
		while(currentWord.next != NULL)
		{
			std::cout << " (" << currentWord.next->word << ")->";
			currentWord = *(currentWord.next);
			if(empty) empty = false;
		}
		std::cout << std::endl;
	}
	if(empty) std::cout << "Hash table is empty" << std::endl;
}

HashTable::HashTable(int size)
{
	hashTable = new Word[size];
	arraySize = size;
	linkedListLength = new int[size];

	for(int i = 0; i<size; i++){
		linkedListLength[i]=0;
	}
}

/*
    Bool flag returns PREVIOUS word if true and the CURRENT word if false.
*/
Word* HashTable::findWord(std::string searchTitle, bool returningPrev)
{
    int location = hashSum(searchTitle, arraySize);
	Word *currentWord = &(hashTable[location]);

    if(hashTable[location].next == NULL) return NULL;

	while(true)
    {
		if(!currentWord->next->word.compare(searchTitle))
		{
			if(returningPrev)
			{
			    return currentWord;
            }
			else
            {
                return currentWord->next;
            }
		}
		else if(searchTitle.compare(currentWord->next->word) < 0 || currentWord->next->next == NULL)
        {
			return NULL;
		}

        currentWord = currentWord->next;
	}
}

void HashTable::deleteWord(std::string searchTitle)
{
	Word *previous = findWord(searchTitle, true);
	Word *temp = previous->next;
	previous->next = temp->next;
	delete temp;
}
