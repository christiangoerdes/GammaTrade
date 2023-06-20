#pragma once

#include "account.hpp"
#include <iostream>
#include <vector>
#include <thread>
#include <chrono>
#include <mutex>
#include <atomic>

// GammaTrade class 
class GammaTrade {
    public:
        // Constructor 
        GammaTrade(const int timespan);

        ~GammaTrade();

        void update_prices();

        void stop_updates();

        bool sign_up(std::string name, std::string password);

        int login(std::string name, std::string password);

        bool deposit(std::string name, std::string password, int amount);

        bool withdraw(std::string name, std::string password, int amount);

        bool buy_stocks(std::string name, std::string password, std::string stock, int quantity);

        bool sell_stocks(std::string name, std::string password, std::string stock, int quantity);

        std::vector<Stock> get_stocks(); 

        std::unordered_map<std::string, int> get_stocks_for(std::string name, std::string password); 

    private: 
        std::vector<Account> accounts; 
        std::unordered_map<std::string, Stock> stocks;
        const int _timespan;
        std::atomic<bool> stop{false};  // flag to stop the thread when we're done
        std::mutex mtx;
        std::thread price_thread;
};
