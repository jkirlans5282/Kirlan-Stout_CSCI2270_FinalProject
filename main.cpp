#include "MarkovChain.h"

int main()
{
    /* Equivalent to:
        Because the boolean flag is true by default, the below line is equivalent to:
        MarkovChain c("hemingway_test.txt", true);
        This means that a filename is passed in instead of a string.
    */
    MarkovChain c("this is is is a test it is is old is this is indeed a test. \n hellow this is a new line line is \n a new line yes it is hellow.", false);
    //MarkovChain c("hemingway_test.txt");
    std::string empty;
    std::cin >> empty;

    c.print();
    c.print("old");

    std::cin >> empty;

    std::string output = c.generateString(100);
    std::cout << output << std::endl;

    return 0;
}
