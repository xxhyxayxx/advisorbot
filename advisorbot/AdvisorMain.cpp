#include "AdvisorMain.hpp"
#include <iostream>
#include <iomanip>

using namespace std;

AdvisorMain::AdvisorMain(){
    
}

void AdvisorMain::init(){
    string input;
    currentTime = orderBook.getEarliestTime(); //return orders[0].timestamp
    
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
    
    vector<string> tokens = CSVReader::tokenise(helpInput, ' ');
    
    
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
    vector<string> prod = orderBook.getKnownProducts();
    for(string& e : prod)
       cout << e << endl;
}

void AdvisorMain::printMin(){
    cout << "min - enter the amount: min product ask/bid, eg min ETH/BTC ask " << endl;
    string input;
    getline(cin, input);
    
    vector<string> tokens = CSVReader::tokenise(input, ' ');
    
    if(tokens.size() == 3 && tokens[0] == "min" && valProd(tokens[1]) && valType(tokens[2])){
        vector<OrderBookEntry> entries = orderBook.getOrders(OrderBookEntry::stringToOrderBookType(tokens[2]), tokens[1], currentTime);
        
        lowPrice = OrderBook::getLowPrice(entries);
        cout << "The min " << tokens[2] << " for " << tokens[1] << " is " << fixed << setprecision(8) << lowPrice << endl;

    }else{
        cout << "Bad Input" << endl;
    }
}

void AdvisorMain::printMax(){
    cout << "max - enter the amount: max product ask/bid, eg max ETH/BTC ask " << endl;
    string input;
    getline(cin, input);
    
    vector<string> tokens = CSVReader::tokenise(input, ' ');
    
    if(tokens.size() == 3 && tokens[0] == "max" && valProd(tokens[1]) && valType(tokens[2])){
        vector<OrderBookEntry> entries = orderBook.getOrders(OrderBookEntry::stringToOrderBookType(tokens[2]), tokens[1], currentTime);
        highPrice = OrderBook::getHighPrice(entries);
        
        cout << "The max " << tokens[2] << " for " << tokens[1] << " is " << fixed << setprecision(8) << highPrice << endl;
    }else{
        cout << "Bad Input" << endl;
    }
}

void AdvisorMain::printAvg(){
    cout << "avg - enter the amount: avg product ask/bid number of timesteps, eg avg ETH/BTC ask 10" << endl;
    string input;
    getline(cin, input);
    
    vector<string> tokens = CSVReader::tokenise(input, ' ');
    
    if(tokens.size() == 4 && tokens[0] == "avg" && valProd(tokens[1]) && valType(tokens[2]) && isNumber(tokens[3])){
        vector<OrderBookEntry> entries = orderBook.getOrders(OrderBookEntry::stringToOrderBookType(tokens[2]), tokens[1], currentTime);
        
        avgPrice = OrderBook::getAvg(entries, stoi(tokens[3]));
        
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
    cout << "now at " << currentTime << endl;
}

void AdvisorMain::printPredict(){
    cout << "predict - enter the amount: predict max/min price product ask/bid, eg predict max ETH/BTC bid" << endl;
    string input;
    getline(cin, input);
    
    vector<string> tokens = CSVReader::tokenise(input, ' ');
    
    vector<double> list;
    int num = 3;
    string time = currentTime;
    
    
    if(tokens.size() == 4 && tokens[0] == "predict" && (tokens[1] == "min" || tokens[1] == "max") && valProd(tokens[2]) && valType(tokens[3])){
        for (int i = 0; i < num; i++) {
            vector<OrderBookEntry> entries = orderBook.getOrders(OrderBookEntry::stringToOrderBookType(tokens[3]), tokens[2], time);
            if(tokens[1] == "max"){
                list.push_back(OrderBook::getHighPrice(entries));
            }else if(tokens[1] == "min"){
                list.push_back(OrderBook::getLowPrice(entries));
            }
            time = orderBook.getNextTime(time);
            cout << list[i] << endl;
        };
        
        double predValue = orderBook.getPredict(list, num);

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
    
    if(tokens.size() == 2 && tokens[0] == "spread" && valProd(tokens[1])){
        vector<OrderBookEntry> entriesAsk = orderBook.getOrders(OrderBookEntry::stringToOrderBookType("ask"), tokens[1], currentTime);
        vector<OrderBookEntry> entriesBid = orderBook.getOrders(OrderBookEntry::stringToOrderBookType("bid"), tokens[1], currentTime);
        
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
    if(!valMenu(userOption)){
        cout << "Bad Input" << endl;
    }
}

bool AdvisorMain::valMenu(const string& menu){
    vector<string> menuList{"help", "prod", "min", "max", "avg", "time", "step", "predict", "spread"};
    
    bool val = false;
    
    for(string& e : menuList){
        if(menu == e){
            val = true;
        }
    }
    
    return val;
}

bool AdvisorMain::valProd(const string& prod){
    bool val = false;
    
    vector<string> prod_token = orderBook.getKnownProducts();
    
    for(string& e : prod_token){
        if(e == prod){
            val = true;
        }
    }
    
    return val;
}

bool AdvisorMain::valType(const string& type){
    bool val = false;
    
    if(type == "ask" || type == "bid"){
        val = true;
    }
    
    return val;
}

bool AdvisorMain::isNumber(const string& str){
    for (char const &c : str) {
        if (isdigit(c) == 0) return false;
    }
    return true;
}


