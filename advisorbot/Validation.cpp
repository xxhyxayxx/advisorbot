#include "Validation.hpp"
#include <iostream>
#include <string>

using namespace std;

Validation::Validation(){
    
}

bool Validation::valMenu(const string& menu){
    vector<string> menuList{"help", "prod", "min", "max", "avg", "time", "step", "predict", "spread"};
    
    bool val = false;
    
    for(string& e : menuList){
        if(menu == e){
            val = true;
        }
    }
    
    return val;
}

bool Validation::valProd(const string& prod, vector<string>& prod_token){
    bool val = false;
    
    for(string& e : prod_token){
        if(e == prod){
            val = true;
        }
    }
    
    return val;
}

bool Validation::valType(const string& type){
    bool val = false;
    
    if(type == "ask" || type == "bid"){
        val = true;
    }
    
    return val;
}

bool Validation::isNumber(const string& str){
    for (char const &c : str) {
        if (isdigit(c) == 0) return false;
    }
    return true;
}





