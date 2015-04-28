#include "MarkovChain.h"

int main()
{
    
    MarkovChain example1("hemingway_test.txt"); //This is the default constructor; it creates a markov chain via a file, the name of which is passed as the first argument.
    
    MarkovChain example2("one one two one two three one two three four one two three four five", true); //This constructor constructs a markov chain directly from the string that is passed in, not from a file.
    
    MarkovChain example3(); //A markov chain can also be created with no arguments; this can't generate anything, it's just an empty chain.
    
    //These four have all have been initialized in non-verbose mode. In order to set the markov chain into verbose mode, you can either construct it as verbose during construction; turning the above three ito the following examples.
    //Objects in verbose mode will print out /a lot/ of information to the command line

    //THIS IS COMMENTED OUT BECAUSE IT PRINTS WAY TOO MUCH: MarkovChain example1verbose("hemingway_test.txt", false, true);
    
    MarkovChain example2verbose("one one two one two three one two three four one two three four five", true, true);
    
    MarkovChain example3verbose(true); //This constructor doesn't do anything requiring verbose mode to print stuff
    
    //You can also change the mode of an object after creation:
    
    example1.verbose(false); //this sets verbose to false, regardless of previous state
    example2.verbose(true); //this sets verbose to true, regardless of previous state
    example3.verbose(); //this changes verbose to the opposite of the previous state
    
    //To generate strings, we use the generateString function:
    
    std::string output = example1.generateString(100); //100 is the length of the string in words
    std::cout << output << std::endl;
    
    //This is an example of how generation works if verbose mode is enabled:
    
    output = example2.generateString(100);
    //NO COUT IS NEEDED HERE BECAUSE VERBOSE MODE WILL PRINT ENOUGH
    
    //Each generation resets the start point; if you want to generate the word that would be after the last generation, you can use this function:
    
    output = example2.generateNextWord();
    std::cout << output << std::endl;
    output = example2.generateNextWord();
    std::cout << output << std::endl;
    output = example2.generateNextWord();
    std::cout << output << std::endl;
    
    //To add more text to your markov chain, you can use:
    
    example1.add("HungerGames.txt");
    
    //or

    example1.add("hello isn't this a fine addition to this example?", true)
    
    //And to print information from the objects, you can use:
    
    example1.print() //This prints the hashtable used to store all the words
    
    example1.primt("old") //This prints the information pertaining to the word "old" in the hashtable
    
    
    return 0;
}
