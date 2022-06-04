#include "AdvisorMain.hpp"
#include <iostream>

using namespace std;

AdvisorMain::AdvisorMain(){
    
}

void AdvisorMain::init(){
    string input;
    currentTime = orderBook.getEarliestTime(); //return orders[0].timestamp
//    wallet.insertCurrency("BTC", 10); //deposit 10 BTC in Wallet
    
    while(true){
        printMenu();
        input = getUserOption();
        processUserOption(input);//change display contents according to input
    }
}


void AdvisorMain::printMenu(){
    cout << "Please enter a command, or help for a list of commands " << endl;
    
//    //1 print help
//    std::cout << "1: Print help " << std::endl;
//
//    //2 print exchange stats
//    std::cout << "2: Print exchange stats " << std::endl;
//
//    //3 make an offer
//    std::cout << "3: Make an offer " << std::endl;
//
//    //4 make a bid
//    std::cout << "4: Make a bid " << std::endl;
//
//    //5 print wallet
//    std::cout << "5: Print wallet " << std::endl;
//
//    //6 continue
//    std::cout << "6: Continue " << std::endl;
//
//    std::cout << "================" << std::endl;
    
//    std::cout << "Current Time is : " << currentTime << std::endl;
}

void AdvisorMain::printHelp(){
    cout << "The available commands are help, help <cmd>, avg, time, (etc. list all commands)" << endl;
    
    string helpInput;
    helpInput = getUserOption();
    if(helpInput == "help avg"){
        cout << "avg ETH/BTC bid 10 -> average ETH/BTC bid over last 10 time steps" << endl;
    }

}

void AdvisorMain::printProd(){
    vector<string> products = orderBook.getKnownProducts();
    
    for(int i=0; i < products.size(); i++)
       cout << products.at(i) << endl;
}

void AdvisorMain::printMin(){
    cout << "min - enter the amount: min product ask/bid, eg min ETH/BTC ask " << endl;
    string input;
    getline(cin, input);
    
    vector<string> tokens = CSVReader::tokenise(input, ' ');
    
    vector<OrderBookEntry> entries = orderBook.getOrders(OrderBookEntry::stringToOrderBookType(tokens[2]), tokens[1], currentTime);
    lowPrice = OrderBook::getLowPrice(entries);
    
    cout << "The min " << tokens[2] << " for " << tokens[1] << " is " << lowPrice << endl;
}

void AdvisorMain::printMax(){
    cout << "max - enter the amount: max product ask/bid, eg max ETH/BTC ask " << endl;
    string input;
    getline(cin, input);
    
    vector<string> tokens = CSVReader::tokenise(input, ' ');
    
    vector<OrderBookEntry> entries = orderBook.getOrders(OrderBookEntry::stringToOrderBookType(tokens[2]), tokens[1], currentTime);
    highPrice = OrderBook::getHighPrice(entries);
    
    cout << "The max " << tokens[2] << " for " << tokens[1] << " is " << highPrice << endl;
}

void AdvisorMain::printAvg(){
    cout << "avg - enter the amount: avg product ask/bid number of timesteps, eg avg ETH/BTC ask 10" << endl;
    string input;
    getline(cin, input);
    
    vector<string> tokens = CSVReader::tokenise(input, ' ');
    
    vector<OrderBookEntry> entries = orderBook.getOrders(OrderBookEntry::stringToOrderBookType(tokens[2]), tokens[1], currentTime);
    
    avgPrice = OrderBook::getAvg(entries, stoi(tokens[3]));
    
    cout << "The average " << tokens[1] << " " << tokens[2] << " price over the last " << tokens[3] << " timesteps was " << avgPrice << endl;
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
    
//    for(string& e : tokens){
//        cout << e << endl;
//    }
//
//    cout << tokens[1] << endl;
    
    vector<double> list;
    int num = 3;
    string time = currentTime;
    
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
}

void AdvisorMain::printSpread(){
    cout << "spread - enter the amount: spread product, eg spread ETH/BTC" << endl;
    string input;
    getline(cin, input);
    
    vector<string> tokens = CSVReader::tokenise(input, ' ');
    
    vector<OrderBookEntry> entriesAsk = orderBook.getOrders(OrderBookEntry::stringToOrderBookType("ask"), tokens[1], currentTime);
    vector<OrderBookEntry> entriesBid = orderBook.getOrders(OrderBookEntry::stringToOrderBookType("bid"), tokens[1], currentTime);
    
    spreadPrice = orderBook.getSpread(OrderBook::getLowPrice(entriesAsk), OrderBook::getHighPrice(entriesBid)) * 100;
    
    cout << "The spread " << tokens[1]  << " is " << spreadPrice << "% " << endl;
}

string AdvisorMain::getUserOption(){
    
    string userOption;
    string line;
    
//    cout << "Type commands " << std::endl;
    std::getline(std::cin, line);
    userOption = line;
//    try{
//        userOption = std::stoi(line);
//    }catch(const std::exception& e){
//
//    }
//    std::cout << "You chose: " << userOption << std::endl;
    
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
}
