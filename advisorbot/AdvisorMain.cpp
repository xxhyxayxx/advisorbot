#include "AdvisorMain.hpp"
#include <iostream>

using namespace std;

AdvisorMain::AdvisorMain(){
    
}

void AdvisorMain::init(){
    string input;
//    currentTime = orderBook.getEarliestTime(); //return orders[0].timestamp
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
       std::cout << products.at(i) << ' ';
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
}
