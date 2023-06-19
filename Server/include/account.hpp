#pragma once 

#include <iostream>
#include <map>
#include <string>
#include <stock.hpp>

// Account class 
class Account {
    public: 
        // Constructor 
        Account(std::string name, std::string password);
        
        // Update the account balance
        bool add_to_balance(int amount);
        bool take_from_balance(int amount);
        bool buy_stock(std::string stock, int quantity, int price);

        bool sell_stock(std::string stock, int quantity, int price);

        // Getter 
        std::string& get_name();
        std::string& get_password();
        double& get_balance();

    private: 
        // Attributes 
        std::string _name; 
        std::string _password; 
        double _balance; 
        std::map<std::string, int> _stocks; 
}; 