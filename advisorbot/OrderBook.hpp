#pragma once
#ifndef OrderBook_hpp
#define OrderBook_hpp

#include <stdio.h>
#include "OrderBookEntry.hpp"
#include "CSVReader.hpp"
#include <string>
#include <vector>

using namespace std;

class OrderBook{
    public:
        /** construct, reading a csv data file**/
        OrderBook(string filename);
        /**return  vector of all know products in the dataset*/
        vector<string> getKnownProducts();
        /**return vector of Orders according to the sent filters*/
        vector<OrderBookEntry> getOrders(OrderBookType type, string product, string timestamp);
        
        /**return the earliest time in the orderbook*/
        string getEarliestTime();
        /**return the next time after the sent time in the order book. If there is no next timestamp, wraps around to the start*/
        string getNextTime(string timestamp);
    
        void insertOrder(OrderBookEntry& order);
    
        vector<OrderBookEntry> matchAsksToBids(string product, string timestamp);
        
        static double getHighPrice(vector<OrderBookEntry>& orders);
        static double getLowPrice(vector<OrderBookEntry>& orders);
        double getSpread(double highPrice, double lowPrice);
    
    private:
        vector<OrderBookEntry> orders;
    
    
};

#endif /* OrderBook_hpp */
