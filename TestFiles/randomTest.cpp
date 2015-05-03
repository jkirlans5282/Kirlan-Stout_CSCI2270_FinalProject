#include <iostream>
#include <unistd.h>
#include <cstdlib>
#include <time.h>
#include <random>
#include <stdio.h>
#include <fstream>
#include <sstream>
#include <algorithm>

int test() {

    srand(time(NULL));

    int zero = 0, one = 0, two = 0, three = 0, four = 0, five = 0, six = 0, seven = 0, eight = 0, nine = 0;
    int i;
    
    std::cout<<"srand:"<<'\n';
    for(int j = 0; j < 100000; j++) {
        i = rand()%10;
        if(i==0)
        {
            zero++;
        }
        else if(i==1)
        {
            one++;
        }
        else if(i==2)
        {
            two++;
        }
        else if(i==3)
        {
            three++;
        }
        else if(i==4)
        {
            four++;
        }
        else if(i==5)
        {
            five++;
        }
        else if(i==6)
        {
            six++;
        }
        else if(i==7)
        {
            seven++;
        }
        else if(i==8)
        {
            eight++;
        }
        else if(i==9)
        {
            nine++;
        }
    }
    
    std::cout << "1:" << one << std::endl;
    std::cout << "2:" << two << std::endl;
    std::cout << "3:" << three << std::endl;
    std::cout << "4:" << four << std::endl;
    std::cout << "5:" << five << std::endl;
    std::cout << "6:" << six << std::endl;
    std::cout << "7:" << seven << std::endl;
    std::cout << "8:" << eight << std::endl;
    std::cout << "9:" << nine << std::endl;
    
    zero = 0, one = 0, two = 0, three = 0, four = 0, five = 0, six = 0, seven = 0, eight = 0, nine = 0;
    
    std::cout<<'\n'<<"generator:"<<'\n';
    for(int j = 0; j < 100000; j++) {
        std::random_device generator;
        std::uniform_int_distribution<int> randomindex (0,9);
        i = randomindex(generator);
        if(i==0)
        {
            zero++;
        }
        else if(i==1)
        {
            one++;
        }
        else if(i==2)
        {
            two++;
        }
        else if(i==3)
        {
            three++;
        }
        else if(i==4)
        {
            four++;
        }
        else if(i==5)
        {
            five++;
        }
        else if(i==6)
        {
            six++;
        }
        else if(i==7)
        {
            seven++;
        }
        else if(i==8)
        {
            eight++;
        }
        else if(i==9)
        {
            nine++;
        }
        
    }
    
    std::cout << "1:" << one << std::endl;
    std::cout << "2:" << two << std::endl;
    std::cout << "3:" << three << std::endl;
    std::cout << "4:" << four << std::endl;
    std::cout << "5:" << five << std::endl;
    std::cout << "6:" << six << std::endl;
    std::cout << "7:" << seven << std::endl;
    std::cout << "8:" << eight << std::endl;
    std::cout << "9:" << nine << std::endl;
    
    return 0;
}
