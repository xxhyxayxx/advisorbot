#ifndef Validation_hpp
#define Validation_hpp

#include <stdio.h>
#include <string>
#include "OrderBook.hpp"

#endif /* Validation_hpp */

using namespace std;

class Validation{
    public:
        Validation();
        bool valMenu(const string& menu);
        bool valProd(const string& prod, vector<string>& prod_token);
        bool valType(const string& type);
        bool isNumber(const string& str);
};
