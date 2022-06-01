#ifndef AdvisorMain_hpp
#define AdvisorMain_hpp

#include <stdio.h>
#include <iostream>
#include "OrderBook.hpp"

using namespace std;

class AdvisorMain{
    public:
        AdvisorMain();
        /** Call this to start the sim */
        void init();
    
    private:
        void printMenu();
        void printHelp();
        void printProd();
        string getUserOption();
        void processUserOption(string userOption);
    
        OrderBook orderBook{"/Users/nakamurahigeri/Downloads/20200317.csv"};
};

#endif /* AdvisorMain_hpp */
