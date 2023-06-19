#pragma once 
#include "item.hpp"
#include <iostream>
#include <map>

// Account class 
class Account {
    public: 
        // Constructor 
        Account(std::string name, std::string password) {
            _name = name;
            _password = password;
            _balance = 0;
        }
        
        // Getter 
        std::string get_name() {
            return _name;
        }
        std::string get_password() {
            return _password;
        }
        double get_balance() {
            return _balance;
        }

    private: 
        // Attributes 
        std::string _name; 
        std::string _password; 
        double _balance; 
        std::map<Item, int> _stocks; 
}; 