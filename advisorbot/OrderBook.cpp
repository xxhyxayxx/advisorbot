#include "OrderBook.hpp"
#include "CSVReader.hpp"
#include <map>
#include <iostream>

using namespace std;

/** construct, reading a csv data file**/
OrderBook::OrderBook(){
    orders = CSVReader::readCSV();
}
/**return  vector of all know products in the dataset*/
vector<string> OrderBook::getKnownProducts(){
    
    vector<string> products;
    map<string, bool> prodMap;
    for(OrderBookEntry& e : orders){
        prodMap[e.product] = true;
    }
    for(auto const& e : prodMap){
        products.push_back(e.first);
    }
    return products;
}
/**return vector of Orders according to the sent filters*/
vector<OrderBookEntry> OrderBook::getOrdersCurrentTime(string timestamp){

    vector<OrderBookEntry> orders_sub;
    
    for(OrderBookEntry& e : orders){
        if(e.timestamp == timestamp){
            orders_sub.push_back(e);
        }
    }
    
    return orders_sub;
}

double OrderBook::getHighPrice(vector<double>& list){
    double max = list[0];
    for(double& e : list){
        if(e > max) max = e;
    }
    return max;
}

double OrderBook::getLowPrice(vector<double>& list){
    double min = list[0];
    for(double& e : list){
        if(e < min) min = e;
    }
    return min;
}

double OrderBook::getAvg(vector<double>& list){
    double price = 0;
    double avg = 0;
    int counter = 0;
    for(double& e : list){
        price += e;
        counter++;
    }
    
    avg = price / counter;
    return avg;
}

string OrderBook::getEarliestTime(){
        return orders[0].timestamp;
}

string OrderBook::getNextTime(string timestamp){
    string next_timestamp = "";
    for(OrderBookEntry& e: orders){
        if(e.timestamp > timestamp){
            next_timestamp = e.timestamp;
            break;
        }
    }
    if(next_timestamp == ""){
        next_timestamp = orders[0].timestamp;
    }
    
    return next_timestamp;
}

double OrderBook::getSpread(double askPrice, double bidPrice) {
    double spread;
    
    spread = askPrice - bidPrice;

    return spread;
}
