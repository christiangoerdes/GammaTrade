#pragma once 

#include "item.hpp"
#include "account.hpp"
#include <iostream>
#include <vector>

// GammaTrade class 
class GammaTrade {
public:
    // Constructor 
    GammaTrade();


private: 
    std::vector<Item> items_for_sale; 
    std::vector<Account> accounts; 
};
