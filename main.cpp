#include "MarkovChain.h"

int main(){
	
    MarkovChain chain("test.txt");
    chain.hashTable->printInventory();
    chain.generateString(10);
    return 0;
}
