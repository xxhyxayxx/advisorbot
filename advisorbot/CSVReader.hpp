#ifndef CSVReader_hpp
#define CSVReader_hpp
#pragma once
#include "OrderBookEntry.hpp"
#include <vector>
#include <string>

#include <stdio.h>

using namespace std;

class CSVReader{
    public:
        CSVReader();

        static vector<OrderBookEntry> readCSV2();
        static vector<std::string> tokenise(string csvLine, char separator);
        static OrderBookEntry stringsToOBE(string priceString, string amountString, string timestamp, string product, OrderBookType orderType);
        static double getLowPrice(vector<OrderBookEntry>& orders);
    
    private:
        static OrderBookEntry stringsToOBE(vector<string> strings);
    
        
    
};

#endif /* CSVReader_hpp */
