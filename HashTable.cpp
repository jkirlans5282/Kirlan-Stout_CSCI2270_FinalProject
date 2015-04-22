#include "HashTable.h"
#import <iostream>
#include <string>
using namespace std;


//x is the string to hash, s is the array size
int HashTable::hashSum(string x) //Done
{
    int sum = 0;
    for(int i = 1; i<x.length(); i++){
        sum += x[i];  //ascii value of ith character in the string
    }
    sum = sum % arraySize;
    return sum;
}
void HashTable::insertMovie(std::string in_title, int in_year) //Done
{
	Movie *m = new Movie(in_title, in_year);
	int location = hashSum(in_title);

	//cout<<location<<" : "<<in_title<<endl;
	Movie *currentMovie = &(hashTable[location]);
	Movie *previousMovie = &(hashTable[location]);
	
	if(currentMovie->next==NULL){
		//cout<<"here\n";
		currentMovie->next = m;
	}
	else{
		while(true)
		{
			//cout<<"comparing "<<currentMovie->title<<" : "<<in_title<<" : "; 
			//cout<<in_title.compare(currentMovie->title)<<endl;
			if(in_title.compare(currentMovie->title)<0)
			{
				//cout<<"<0\n";
				previousMovie->next = m;
				m->next = currentMovie;
				break;
			}
			else{
				//cout<<">0\n";
				if(currentMovie->next != NULL){
					//cout<<"not null\n";
					previousMovie = currentMovie;
					currentMovie = currentMovie->next;
				}
				else{
					//cout<<"null\n";
					currentMovie->next = m;
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
		Movie currentMovie = hashTable[i];
		while(currentMovie.next!=NULL){
			cout<<"("<<currentMovie.next->title<<", "<<currentMovie.next->year<<") -> ";
			currentMovie=*(currentMovie.next);
			if(empty){empty = false;}
		}
		cout<<"\n";
	}
	if(empty){cout<<"Hash table is empty"<<endl;}

}
HashTable::HashTable(int size) //Done
{
	hashTable = new Movie[size];
	arraySize = size;
}
Movie* HashTable::findMovie(string searchTitle, bool del) //Done
{
	int index = hashSum(searchTitle);
	Movie * currentMovie = &(hashTable[index]);
	Movie * previousMovie = &(hashTable[index]);

	while(true){
		if(!currentMovie->title.compare(searchTitle)){
			if(del){return previousMovie;}
			else{return currentMovie;}
		}else if(searchTitle.compare(currentMovie->title)<0||currentMovie->next==NULL){
			cout<<"Movie Not found"<<endl;
			return NULL;
		}else{
			previousMovie = currentMovie;
			currentMovie=currentMovie->next;
		}
	}
}
void HashTable::deleteMovie(string searchTitle) //done
{
	Movie * previous = findMovie(searchTitle, true);
	Movie * temp = previous->next;
	delete previous->next;
	previous->next = temp->next;
}
