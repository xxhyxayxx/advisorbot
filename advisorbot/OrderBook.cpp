#include "OrderBook.hpp"
#include "CSVReader.hpp"
#include <map>
#include <iostream>

using namespace std;

/** construct, reading a csv data file**/
OrderBook::OrderBook(string filename){
    orders = CSVReader::readCSV2();
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
vector<OrderBookEntry> OrderBook::getOrders(OrderBookType type, string product, string timestamp){

    vector<OrderBookEntry> orders_sub;
    
    for(OrderBookEntry& e : orders){
        if(e.orderType == type && e.product == product && e.timestamp == timestamp){
            orders_sub.push_back(e);
        }
    }
    
    return orders_sub;
}

double OrderBook::getHighPrice(vector<OrderBookEntry>& orders){
    double max = orders[0].price;
    for(OrderBookEntry& e : orders){
        if(e.price > max) max = e.price;
    }
    return max;
}

double OrderBook::getLowPrice(vector<OrderBookEntry>& orders){
    double min = orders[0].price;
    for(OrderBookEntry& e : orders){
        if(e.price < min) min = e.price;
    }
    return min;
}

double OrderBook::getAvg(vector<OrderBookEntry>& orders, int num){
    double price = 0;
    double avg = 0;
    int length = 0;
    for(OrderBookEntry& e : orders){
        price += e.price;
        length++;
        if(length == num){
            break;
        }
    }
    avg = price / num;
    return avg;
}

double OrderBook::getPredict(vector<double>& list, int num)
{
    double price = 0;
    double avg = 0;
    int length = 0;
    for(double& e : list){
        price += e;
        length++;
        if(length == num){
            break;
        }
    }
    avg = price / num;
    return avg;
}

string OrderBook::getEarliestTime(){
        return orders[0].timestamp;
}

string OrderBook::getNextTime(string timestamp){
    string next_timestamp = "";
    for(OrderBookEntry& e: orders){
        if(e.timestamp > timestamp){
            cout << e.timestamp << endl;
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
