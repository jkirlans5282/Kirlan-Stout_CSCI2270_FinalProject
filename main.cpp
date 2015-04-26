#include "MarkovChain.h"

int main(){
	
    MarkovChain chain("test.txt");
    chain.hashTable->printInventory();

    return 0;
}
