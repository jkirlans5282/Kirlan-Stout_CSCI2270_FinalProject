#include "MarkovChain.cpp"

int main()
{
    MarkovChain c("test.txt");

    c.hashTable->printInventory();
    c.generateString(10);

    return 0;
}
