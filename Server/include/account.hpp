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
        bool buy_stock(std::string stock, int quantity, int price) {
            if(price > _balance) {
                return false;
            }
            if(_stocks.find(stock) != _stocks.end()) {
                _stocks[stock] += quantity;
            }else{
                _stocks[stock] = quantity;
            }
            _balance -= price;
            return true;
        }

        bool sell_stock(std::string stock, int quantity, int price) {

            if(_stocks.find(stock) == _stocks.end() || quantity > _stocks[stock]) {
                return false;
            }

            _stocks[stock] -= quantity;
            _balance += price;
            return true;

        }

        // Getter 
        std::string& get_name() {
            return _name;
        }
        std::string& get_password() {
            return _password;
        }
        double& get_balance() {
            return _balance;
        }

    private: 
        // Attributes 
        std::string _name; 
        std::string _password; 
        double _balance; 
        std::map<std::string, int> _stocks; 
}; 