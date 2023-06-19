#pragma once 
#include <iostream>
#include <map>
#include <string>
#include <stock.hpp>

// Account class 
class Account {
    public: 
        // Constructor 
        Account(std::string name, std::string password) {
            _name = name;
            _password = password;
            _balance = 0;
        }
        
        // Update the account balance
        bool add_to_balance(int amount) {
            if(amount < 0) {
                return false;
            }
            _balance += amount;
            return true;
        }
        bool take_from_balance(int amount) {
            if(amount > _balance || amount < 0) {
                return false;
            }
            _balance -= amount;
            return true;
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
        std::string name; 
        std::string password; 
        double balance; 
        std::unordered_map<std::string, int> stocks; 
}; 