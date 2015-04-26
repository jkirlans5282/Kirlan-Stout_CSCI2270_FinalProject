#include <iostream>
#include <unistd.h>
#include <cstdlib>
#include <time.h>
#include <random>
#include <stdio.h>
#include <fstream>
#include <sstream>
#include <algorithm>

int main() {

    srand(time(NULL));

    std::cout<<"srand:"<<'\n';
    for(int i = 0; i < 10; i++) {
        std::cout<<rand()%10<<'\n';
    }
    std::cout<<'\n'<<"generator:"<<'\n';
    for(int i = 0; i < 10; i++) {
        std::random_device generator;
        std::uniform_int_distribution<int> randomindex (0,10);
        std::cout<<randomindex(generator)<<'\n';
    }
}
