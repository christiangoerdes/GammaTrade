#pragma once 
#include <iostream>
#include <unordered_map>
#include <string>
#include <stock.hpp>

// Account class 
class Account {
    public: 
        // Constructor 
        Account(std::string name, std::string password);
        
        // Attributes 
        std::string name; 
        std::string password; 
        double balance; 
        std::unordered_map<std::string, int> stocks; 
}; 