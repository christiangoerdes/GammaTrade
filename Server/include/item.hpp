#pragma once 

#include "account.hpp"
#include <iostream>

// Item class 
class Item {
    public:
        // Constructor 
        Item(std::string name, int quantity) {
            _name = name;
            _quantity = quantity;
        }

        int getQuantity() const {
            return _quantity;
        }

        void changeQuantity(int change) {
            _quantity += change;
        }

    private:
        // Attributes 
        std::string _name;
        int _quantity;

};