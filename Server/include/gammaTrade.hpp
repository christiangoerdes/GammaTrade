#pragma once 

#include "account.hpp"
#include <iostream>
#include <vector>
#include <thread>
#include <chrono>
#include <future>

// GammaTrade class 
class GammaTrade {
    public:
        // Constructor 
        GammaTrade(const int timespan);

        void run_market(const int dt);

        bool sign_up(std::string name, std::string password);

        int login(std::string name, std::string password);

        bool deposit(std::string name, std::string password, int amount);

        bool withdraw(std::string name, std::string password, int amount);

        bool buy_stocks(std::string name, std::string password, std::string stock, int quantity);

        bool sell_stocks(std::string name, std::string password, std::string stock, int quantity);

        std::unordered_map<std::string, Stock> get_stocks(); 

    private: 
        std::vector<Account> accounts; 
        std::unordered_map<std::string, Stock> stocks;
        const int _timespan;
};
