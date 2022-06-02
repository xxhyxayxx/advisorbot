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
    cout << "avg - enter the amount: avg product ask/bid, eg avg ETH/BTC ask " << endl;
    string input;
    getline(cin, input);
    
    vector<string> tokens = CSVReader::tokenise(input, ' ');
    
    vector<OrderBookEntry> entries = orderBook.getOrders(OrderBookEntry::stringToOrderBookType(tokens[2]), tokens[1], currentTime);
    avgPrice = OrderBook::getAvg(entries);
    
    cout << "The average " << tokens[2] << " for " << tokens[1] << " is " << avgPrice << endl;
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
}
