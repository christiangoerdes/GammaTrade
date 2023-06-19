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

        int login(std::string name, std::string password);

        bool deposit(std::string name, std::string password, int amount);

        bool withdraw(std::string name, std::string password, int amount);

    private: 
        std::vector<Item> items_for_sale; 
        std::vector<Account> accounts; 
};
