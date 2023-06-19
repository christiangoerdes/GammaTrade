#pragma once 

#include <iostream>

// Item class 
class Item {
    public: 
        // Constructor 
        Item(std::string name, double price, std::string owner);
        
        // Attributes 
        std::string name; 
        double price; 
}; 