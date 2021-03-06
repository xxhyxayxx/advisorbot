#include "AdvisorMain.hpp"
#include <iostream>
#include <iomanip>

using namespace std;

AdvisorMain::AdvisorMain(){
    
}

void AdvisorMain::init(){
    string input;
    currentTime = orderBook.getEarliestTime(); //return orders[0].timestamp
    entries = orderBook.getOrdersCurrentTime(currentTime); //get the curennt time orderBookEntry data
    prod = orderBook.getKnownProducts(); //get the product list
    
    
    while(true){
        printMenu();
        input = getUserOption();
        processUserOption(input); //change display contents according to input
    }
}


void AdvisorMain::printMenu(){
    cout << "Please enter a command, or help for a list of commands " << endl;
}

void AdvisorMain::printHelp(){
    cout << "The available commands are help, help <cmd>, prod, min, max, avg, time, step, predict, spread (etc. list all commands)" << endl;
    
    string helpInput;
    helpInput = getUserOption();
    
    vector<string> tokens = CSVReader::tokenise(helpInput, ' '); //split the words from the user input
    
    
    if(helpInput == "help avg"){
        cout << "avg ETH/BTC bid 10 -> average ETH/BTC bid over last 10 time steps" << endl;
    }
    if(helpInput == "help prod"){
        cout << "print all products that you can manage" << endl;
    }
    if(helpInput == "help min"){
        cout << "min ETH/BTC ask -> minimum ETH/BTC ask at the current time" << endl;
    }
    if(helpInput == "help max"){
        cout << "mxn ETH/BTC ask -> max ETH/BTC ask at the current time" << endl;
    }
    if(helpInput == "help time"){
        cout << "print current timestamp" << endl;
    }
    if(helpInput == "help step"){
        cout << "move and print next timestamp" << endl;
    }
    if(helpInput == "help predict"){
        cout << "predict max ETH/BTC bid" << endl;
    }
    if(helpInput == "help spread"){
        cout << "spread ETH/BTC" << endl;
    }

}

void AdvisorMain::printProd(){
    for(string& e : prod)
       cout << e << endl;
}

void AdvisorMain::printMin(){
    cout << "min - enter the amount: min product ask/bid, eg min ETH/BTC ask " << endl;
    string input;
    getline(cin, input);
    
    vector<string> tokens = CSVReader::tokenise(input, ' '); //split the words from the user input
    
    
    //validate
    if(tokens.size() == 3 && tokens[0] == "min" && val.valProd(tokens[1], prod) && val.valType(tokens[2])){
        
        vector<double> priceList;
        
        //only the price data is extracted and stored in vector
        for(OrderBookEntry& e : entries){
            if(e.orderType == OrderBookEntry::stringToOrderBookType(tokens[2]) && e.product == tokens[1]){
                priceList.push_back(e.price);
            }
        }
        
        lowPrice = OrderBook::getLowPrice(priceList);
        cout << "The min " << tokens[2] << " for " << tokens[1] << " is " << fixed << setprecision(8) << lowPrice << endl;
    }else{
        cout << "Bad Input" << endl;
    }
}

void AdvisorMain::printMax(){
    cout << "max - enter the amount: max product ask/bid, eg max ETH/BTC ask " << endl;
    string input;
    getline(cin, input);
    
    vector<string> tokens = CSVReader::tokenise(input, ' '); //split the words from the user input
    
    //validate
    if(tokens.size() == 3 && tokens[0] == "max" && val.valProd(tokens[1], prod) && val.valType(tokens[2])){
        vector<double> priceList;
        
        //only the price data is extracted and stored in vector
        for(OrderBookEntry& e : entries){
            if(e.orderType == OrderBookEntry::stringToOrderBookType(tokens[2]) && e.product == tokens[1]){
                priceList.push_back(e.price);
            }
        }
        
        highPrice = OrderBook::getHighPrice(priceList);
        
        cout << "The max " << tokens[2] << " for " << tokens[1] << " is " << fixed << setprecision(8) << highPrice << endl;
    }else{
        cout << "Bad Input" << endl;
    }
}

void AdvisorMain::printAvg(){
    cout << "avg - enter the amount: avg product ask/bid number of timesteps, eg avg ETH/BTC ask 10" << endl;
    string input;
    getline(cin, input);
    
    vector<string> tokens = CSVReader::tokenise(input, ' '); //split the words from the user input
    
    //validate
    if(tokens.size() == 4 && tokens[0] == "avg" && val.valProd(tokens[1], prod) && val.valType(tokens[2]) && val.isNumber(tokens[3])){
        
        vector<double> list;
        vector<OrderBookEntry> orders;
        vector<double> avgList;
        string timestamp = currentTime;
        
        for(int i = 1; i <= stoi(tokens[3]); i++){
            orders = orderBook.getOrdersCurrentTime(timestamp);
            for(OrderBookEntry& e : orders){
                if(e.orderType == OrderBookEntry::stringToOrderBookType(tokens[2]) && e.product == tokens[1]){
                    list.push_back(e.price);
                }
            }
            timestamp = orderBook.getNextTime(timestamp);
        }
        
        avgPrice = OrderBook::getAvg(list);
        
        cout << "The average " << tokens[1] << " " << tokens[2] << " price over the last " << tokens[3] << " timesteps was " << fixed << setprecision(8) << avgPrice << endl;
    }else{
        cout << "Bad Input" << endl;
    }
}

void AdvisorMain::printTime(){
    cout << currentTime << endl;
}

void AdvisorMain::printStep(){
    currentTime = orderBook.getNextTime(currentTime);
    entries = orderBook.getOrdersCurrentTime(currentTime); //update the curennt time orderBookEntry data
    cout << "now at " << currentTime << endl;
}

void AdvisorMain::printPredict(){
    cout << "predict - enter the amount: predict max/min price product ask/bid, eg predict max ETH/BTC bid" << endl;
    string input;
    getline(cin, input);
    
    vector<string> tokens = CSVReader::tokenise(input, ' '); //split the words from the user input
    
    vector<double> list;
    vector<double> avgList;
    int num = 5;
    string time = currentTime;
    vector<OrderBookEntry> orders;
    double predValue;
    
    //validate
    if(tokens.size() == 4 && tokens[0] == "predict" && (tokens[1] == "min" || tokens[1] == "max") && val.valProd(tokens[2], prod) && val.valType(tokens[3])){
        //Extract the relevant data and obtain the highest or lowest price
        for (int i = 1; i <= num; i++) {
            orders = orderBook.getOrdersCurrentTime(time);
            for(OrderBookEntry& e : orders){
                if(e.orderType == OrderBookEntry::stringToOrderBookType(tokens[3]) && e.product == tokens[2]){
                    list.push_back(e.price);
                }
            }
            if(tokens[1] == "max"){
                avgList.push_back(OrderBook::getHighPrice(list));
            }else if(tokens[1] == "min"){
                avgList.push_back(OrderBook::getLowPrice(list));
            }
            list.clear();
            time = orderBook.getNextTime(time);
        };
        
        //EMA - An exponential smooth moving average is an exponentially weighted average that is closer to the most recent closing price.
        predValue = orderBook.getPredict(list, num);

        cout << "The predict " << tokens[1] << " " << tokens[2] << " " << tokens[3] << " is " << predValue << endl;
    }else{
        cout << "Bad Input" << endl;
    }
}

void AdvisorMain::printSpread(){
    cout << "spread - enter the amount: spread product, eg spread ETH/BTC" << endl;
    string input;
    getline(cin, input);
    
    vector<string> tokens = CSVReader::tokenise(input, ' ');
    
    //validate
    if(tokens.size() == 2 && tokens[0] == "spread" && val.valProd(tokens[1], prod)){
        vector<double> entriesAsk;
        vector<double> entriesBid;
        
        for(OrderBookEntry& e : entries){
            if(e.orderType == OrderBookEntry::stringToOrderBookType("ask") && e.product == tokens[1]){
                entriesAsk.push_back(e.price);
            }
            if(e.orderType == OrderBookEntry::stringToOrderBookType("bid") && e.product == tokens[1]){
                entriesBid.push_back(e.price);
            }
        }
        
        //show as percentage
        spreadPrice = orderBook.getSpread(OrderBook::getLowPrice(entriesAsk), OrderBook::getHighPrice(entriesBid)) * 100;
        
        cout << "The spread " << tokens[1]  << " is " << spreadPrice << "% " << endl;
    }else{
        cout << "Bad Input" << endl;
    }
}

string AdvisorMain::getUserOption(){
    string userOption;
    string line;
    
    getline(cin, line);
    userOption = line;
    
    return userOption;
}

void AdvisorMain::processUserOption(string userOption){

    if(userOption == "help"){
        printHelp();
    }
    if(userOption == "prod"){
        printProd();
    }
    if(userOption == "min"){
        printMin();
    }
    if(userOption == "max"){
        printMax();
    }
    if(userOption == "avg"){
        printAvg();
    }
    if(userOption == "time"){
        printTime();
    }
    if(userOption == "step"){
        printStep();
    }
    if(userOption == "predict"){
        printPredict();
    }
    if(userOption == "spread"){
        printSpread();
    }
    if(!val.valMenu(userOption)){
        cout << "Bad Input" << endl;
    }
}
