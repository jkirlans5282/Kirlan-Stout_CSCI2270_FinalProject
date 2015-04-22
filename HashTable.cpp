#include "HashTable.h"

using namespace std;


//x is the string to hash, s is the array size
int HashTable::hashSum(std::string str, int s) //Done
{
	return 0;
}
void HashTable::insertWord(std::string in_word) //Done
{
	Word *m = new Word(in_word);
	int location = hashSum(in_word, arraySize);

	//cout<<location<<" : "<<in_word<<endl;
	Word *currentWord = &(hashTable[location]);
	Word *previousWord = &(hashTable[location]);

	if(currentWord->next==NULL){
		//cout<<"here\n";
		currentWord->next = m;
	}
	else{
		while(true)
		{
			//cout<<"comparing "<<currentWord->word<<" : "<<in_word<<" : ";
			//cout<<in_word.compare(currentWord->word)<<endl;
			if(in_word.compare(currentWord->word)<0)
			{
				//cout<<"<0\n";
				previousWord->next = m;
				m->next = currentWord;
				break;
			}
			else{
				//cout<<">0\n";
				if(currentWord->next != NULL){
					//cout<<"not null\n";
					previousWord = currentWord;
					currentWord = currentWord->next;
				}
				else{
					//cout<<"null\n";
					currentWord->next = m;
					break;
				}
			}
		}
	}
}
void HashTable::printInventory() //Done
{
	bool empty = true;
	for(int i = 0; i<10; i++){
		cout<<"["<<i<<"]"<<" : ";
		Word currentWord = hashTable[i];
		while(currentWord.next!=NULL){
			cout<<" ("<<currentWord.next->word<<")->";
			currentWord=*(currentWord.next);
			if(empty){empty = false;}
		}
		cout<<"\n";
	}
	if(empty){cout<<"Hash table is empty"<<endl;}

}
HashTable::HashTable(int size) //Done
{
	hashTable = new Word[size];
	arraySize = size;
}
Word* HashTable::findWord(string searchTitle, bool del) //Done
{
	int index = hashSum(searchTitle, arraySize);
	Word * currentWord = &(hashTable[index]);
	Word * previousWord = &(hashTable[index]);

	while(true){
		if(!currentWord->word.compare(searchTitle)){
			if(del){return previousWord;}
			else{return currentWord;}
		}else if(searchTitle.compare(currentWord->word)<0||currentWord->next==NULL){
			cout<<"Word Not found"<<endl;
			return NULL;
		}else{
			previousWord = currentWord;
			currentWord=currentWord->next;
		}
	}
}
void HashTable::deleteWord(string searchTitle) //done
{
	Word * previous = findWord(searchTitle, true);
	Word * temp = previous->next;
	delete previous->next;
	previous->next = temp->next;
}
