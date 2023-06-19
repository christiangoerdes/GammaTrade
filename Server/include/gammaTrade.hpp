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

        bool sign_up(std::string name, std::string password);

    private: 
        std::vector<Item> items_for_sale; 
        std::vector<Account> accounts; 
};
