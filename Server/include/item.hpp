#pragma once 

#include "account.hpp"
#include <iostream>

// Item class 
class Item {
    public: 
        // Constructor 
        Item(std::string name, double price);
        
        // Attributes 
        std::string name; 
};