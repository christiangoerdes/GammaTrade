#pragma once 
#include "item.hpp"
#include <iostream>
#include <vector>

// Account class 
class Account {
    public: 
        // Constructor 
        Account(std::string password, std::string owner, double balance);
        
        // Attributes 
        std::string name; 
        std::string password; 
        double balance; 
        std::vector<Item> goods; 
}; 