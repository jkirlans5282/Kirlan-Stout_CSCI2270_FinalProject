#include "MarkovChain.h"

int main()
{
    MarkovChain c("hemingway_test.txt");

    c.hashTable->printInventory();
    std::string output = c.generateString(100);
    std::cout << output << std::endl;

    return 0;
}
