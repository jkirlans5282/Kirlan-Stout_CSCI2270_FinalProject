#include "MarkovChain.h"

int main()
{
    /* Equivalent to:
        Because the boolean flag is true by default, the below line is equivalent to:
        MarkovChain c("hemingway_test.txt", true);
        This means that a filename is passed in instead of a string.
    */
    MarkovChain c("hemingway_test.txt");

    c.hashTable->printInventory();

    std::string output = c.generateString(100);
    std::cout << output << std::endl;

    return 0;
}
