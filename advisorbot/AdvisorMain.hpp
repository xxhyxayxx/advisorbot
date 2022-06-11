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
        void printPredict();
        void printSpread();
        string getUserOption();
        void processUserOption(string userOption);
        bool valMenu(const string& menu);
        bool valProd(const string& prod);
        bool valType(const string& type);
        bool isNumber(const string& str);
        string currentTime;
        double highPrice;
        double lowPrice;
        double avgPrice;
        double predHighPrice;
        double spreadPrice;
    
        vector<OrderBookEntry> entries;
    
        //OrderBook orderBook{"/Users/nakamurahigeri/Documents/advisorbot/advisorbot/test.csv"};
        OrderBook orderBook{"/Users/nakamurahigeri/Downloads/20200601.csv"};
};

#endif /* AdvisorMain_hpp */
