#pragma once 
#include "item.hpp"
#include <iostream>
#include <unordered_map>

// Account class 
class Account {
    public: 
        // Constructor 
        Account(std::string name, std::string password);
        
        // Attributes 
        std::string name; 
        std::string password; 
        double balance; 
        std::unordered_map<Item, int> stocks; 
}; 