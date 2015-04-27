# CSCI2270_FinalProject
### Alex Curtiss, Audrey Randall, Izaak Weiss, Jacob Kirlan-Stout

Contributers:
  None.
  
Project description:

A Markov chain is a way of generating random strings of words based off of a text file. It chooses a random word from the file to start and choses each subsequent word based off the probability that it follows the previous one. For example, if building from the string "two three one two four two four" a Markov chain might start with "two" and have a 67% change to become "two four" and a 33% change to become "two three", because "four" follows "two" two times out the three. If it becomes "two three" it has a 100% chance to become "two three one" because "one" follows "three" every time, and so on.

Our program allows for a file to be read in, or a string passed in, and will generate a Markov chain of the desired length based off of it.

How to run:
  A driver file (main.cpp) is included which demonstrates the basic program functionality. The code in documented in-line.

Dependencies:
  None.
  
System requirements:
  As of 4/26/2015 the random numbers are not correctly generated for WINDOWS machines, although the program otherwise runs fine. The program works correctly on Mac and Ubuntu Linux systems.

Known issues:
  Random numbers aren't correctly generated on computers runnng Windows.
