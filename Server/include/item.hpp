#pragma once 

#include "accont.hpp"
#include <iostream>

// Item class 
class Item {
    public: 
        // Constructor 
        Item(std::string name, Account owner); 
        Item(std::string name, Account owner, double price);
        
        // Attributes 
        std::string name; 
        Account owner; 
        double price; 
}; 