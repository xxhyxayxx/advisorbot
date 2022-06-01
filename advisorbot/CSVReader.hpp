#ifndef CSVReader_hpp
#define CSVReader_hpp
#pragma once
#include "OrderBookEntry.hpp"
#include <vector>
#include <string>

#include <stdio.h>

class CSVReader{
    public:
        CSVReader();
    
        static std::vector<OrderBookEntry> readCSV(std::string csvFile);
        static std::vector<std::string> tokenise(std::string csvLine, char separator);
        static OrderBookEntry stringsToOBE(std::string priceString, std::string amountString, std::string timestamp, std::string product, OrderBookType orderType);
    
    private:
        static OrderBookEntry stringsToOBE(std::vector<std::string> strings);
    
        
    
};

#endif /* CSVReader_hpp */
