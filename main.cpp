#include "MarkovChain.h"

int main()
{
    /* Equivalent to:
        Because the boolean flag is true by default, the below line is equivalent to:
        MarkovChain c("hemingway_test.txt", true);
        This means that a filename is passed in instead of a string.
    */


    //DEFAULT: MarkovChain c("filename.txt");
    //IN ORDER TO READ FROM STRING RATHER THAN FILE: MarkovChain c("string to read in", true);
    //IN ORDER TO ENABLE VERBOSE MODE (Lots of info will be printed out): MarkovChain c("string or filename.txt", bool, true); (note that the bool must be false if it's a filename and true if it's a string)

    MarkovChain c("this is is is a test it is is old is this is ind???!!eed a test. \n hellow this is a new line line is \n a new line yes it is hellow. \n hello bitches \n bitches be cray \n jacob you are a bitch don't lie is is a test.", true);

    std::string output = c.generateString(100);
    std::cout << output << std::endl;
    output = c.generateNextWord();
    std::cout << output << std::endl;
    output = c.generateNextWord();
    std::cout << output << std::endl;
    output = c.generateNextWord();
    std::cout << output << std::endl;

    return 0;
}
