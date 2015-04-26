#include "HashTable.h"

int HashTable::hashSum(std::string str, int s)
{
	int hash = str[0];
	for (int i = 1 ; i < str.length(); i++)
		hash = ((hash * 33) + str[i]);
	return abs(hash%arraySize);
}

Word *HashTable::insertWord(std::string in_word) //Modified untested
{
	Word *m = new Word(in_word);
	int location = hashSum(in_word, arraySize);
	std::cout << in_word << ":" << m->word << ":" << location << std::endl;
	//std::cout << location << " : " << in_word << std::endl;
	Word *currentWord = &(hashTable[location]); //Can we just make the hashTable an array of pointers instead of having to dereference the first element?
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
    return m; //Now returns the word for later use
}

void HashTable::printInventory()
{
	bool empty = true;
	for(int i = 0; i < 10; i++)
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
}

/* Bool flag returns PREVIOUS word if true and the CURRENT word if false */
Word* HashTable::findWord(std::string searchTitle, bool returningPrev)
{
	int index = hashSum(searchTitle, arraySize);
	Word *currentWord = &(hashTable[index]);
	Word *previousWord = &(hashTable[index]);

	while(true)
    {
		if(!currentWord->word.compare(searchTitle))
		{
			if(returningPrev)
			{
			    return previousWord;
            }
			else
            {
                return currentWord;
            }
		}
		else if(searchTitle.compare(currentWord->word) < 0 || currentWord->next == NULL)
        {
			return NULL;
		}
		else
        {
			previousWord = currentWord;
			currentWord = currentWord->next;
		}
	}
}

void HashTable::deleteWord(std::string searchTitle)
{
	Word *previous = findWord(searchTitle, true);
	Word *temp = previous->next;
	previous->next = temp->next;
	delete temp;
}
