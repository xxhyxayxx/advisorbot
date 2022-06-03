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
        void printMin();
        void printMax();
        void printAvg();
        void printTime();
        void printStep();
        string getUserOption();
        void processUserOption(string userOption);
        string currentTime;
        double highPrice;
        double lowPrice;
        double avgPrice;
    
        OrderBook orderBook{"/Users/nakamurahigeri/Documents/advisorbot/advisorbot/test.csv"};
};

#endif /* AdvisorMain_hpp */
