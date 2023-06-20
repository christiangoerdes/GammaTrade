#pragma once

#include "account.hpp"
#include <iostream>
#include <vector>
#include <thread>
#include <chrono>
#include <mutex>
#include <atomic>
#include <condition_variable>

/**
 * @brief Represents a trading platform with user accounts and stocks.
 */
class GammaTrade {
public:
    /**
     * @brief Constructs a GammaTrade object.
     * @param timespan The timespan for stock price updates.
     */
    GammaTrade(const int timespan);

    /**
     * @brief Destructor for GammaTrade.
     */
    ~GammaTrade();

    /**
     * @brief Updates the prices of all stocks.
     */
    void update_prices(const int timespan);


    /**
     * @brief Stops the stock price updates.
     */
    void stop_updates();

    /**
     * @brief Signs up a new user account.
     * @param name The name of the account.
     * @param password The password for the account.
     * @return True if the sign-up was successful, false otherwise.
     */
    bool sign_up(std::string name, std::string password);

    /**
     * @brief Checks if the login is valid.
     * @param name The name of the account.
     * @param password The password for the account.
     * @return  0 if the login is successful, 1 if the password is incorrect, 2 if the account is not found.
     */
    int login(std::string name, std::string password);

    /**
     * @brief Deposits money into a user account.
     * @param name The name of the account.
     * @param password The password for the account.
     * @param amount The amount to deposit.
     * @return True if the deposit was successful, false otherwise.
     */
    bool deposit(std::string name, std::string password, int amount);

    /**
     * @brief Withdraws money from a user account.
     * @param name The name of the account.
     * @param password The password for the account.
     * @param amount The amount to withdraw.
     * @return True if the withdrawal was successful, false otherwise.
     */
    bool withdraw(std::string name, std::string password, int amount);

    /**
     * @brief Buys stocks for a user account.
     * @param name The name of the account.
     * @param password The password for the account.
     * @param stock The name of the stock to buy.
     * @param quantity The quantity of stock to buy.
     * @return True if the stock purchase was successful, false otherwise.
     */
    bool buy_stocks(std::string name, std::string password, std::string stock, int quantity);

    /**
     * @brief Sells stocks from a user account.
     * @param name The name of the account.
     * @param password The password for the account.
     * @param stock The name of the stock to sell.
     * @param quantity The quantity of stock to sell.
     * @return True if the stock sale was successful, false otherwise.
     */
    bool sell_stocks(std::string name, std::string password, std::string stock, int quantity);

    /**
     * @brief Retrieves the list of available stocks.
     * @return A vector of Stock objects.
     */
    std::vector<Stock> get_stocks();

    /**
     * @brief Retrieves the stock holdings for a user account.
     * @param name The name of the account.
     * @param password The password for the account.
     * @return A map of stock names to quantities.
     */
    std::unordered_map<std::string, int> get_stocks_for(std::string name, std::string password);

private:
    std::vector<Account> accounts;                      /**< The user accounts. */
    std::unordered_map<std::string, Stock> stocks;      /**< The available stocks. */
    const int _timespan;                                /**< The timespan for stock price updates. */
    std::atomic<bool> stop{false};                      /**< Flag to stop the update thread. */
    std::mutex mtx;                                     /**< Mutex for thread synchronization. */
    std::thread price_thread;                           /**< Thread for stock price updates. */
    std::condition_variable cv;
};