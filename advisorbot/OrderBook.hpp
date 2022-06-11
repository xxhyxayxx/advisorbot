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
        OrderBook();
        /**return  vector of all know products in the dataset*/
        vector<string> getKnownProducts();
        /**return vector of Orders according to the sent filters*/
        vector<OrderBookEntry> getOrders(OrderBookType type, string product, string timestamp);
        vector<OrderBookEntry> getOrdersCurrentTime(string timestamp);
        
        /**return the earliest time in the orderbook*/
        string getEarliestTime();
        /**return the next time after the sent time in the order book. If there is no next timestamp, wraps around to the start*/
        string getNextTime(string timestamp);
        
        static double getHighPrice(vector<double>& list);
        static double getLowPrice(vector<double>& list);
        static double getAvg(vector<double>& list);
        double getSpread(double askPrice, double bidPrice);
    
    private:
        vector<OrderBookEntry> orders;
        vector<double> list;
    
    
};

#endif /* OrderBook_hpp */
