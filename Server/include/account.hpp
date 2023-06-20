#pragma once 

#include <iostream>
#include <unordered_map>
#include <string>
#include "stock.hpp"

/**
 * @brief Represents a user account with a balance and stock holdings.
 */
class Account {
public:
    /**
     * @brief Constructs an Account object.
     * @param name The name of the account.
     * @param password The password for the account.
     */
    Account(std::string name, std::string password);

    /**
     * @brief Adds the specified amount to the account balance.
     * @param amount The amount to add to the balance.
     * @return True if the balance was successfully updated, false otherwise.
     */
    bool add_to_balance(int amount);

    /**
     * @brief Subtracts the specified amount from the account balance.
     * @param amount The amount to subtract from the balance.
     * @return True if the balance was successfully updated, false otherwise.
     */
    bool take_from_balance(int amount);

    /**
     * @brief Buys the specified quantity of a stock at the given price.
     * @param stock The name of the stock to buy.
     * @param quantity The quantity of stock to buy.
     * @param price The price of the stocks.
     * @return True if the stock purchase was successful, false otherwise.
     */
    bool buy_stock(std::string stock, int quantity, double price);

    /**
     * @brief Sells the specified quantity of a stock at the given price.
     * @param stock The name of the stock to sell.
     * @param quantity The quantity of stock to sell.
     * @param price The price of the stocks.
     * @return True if the stock sale was successful, false otherwise.
     */
    bool sell_stock(std::string stock, int quantity, double price);

    /**
     * @brief Retrieves the name of the account.
     * @return A reference to the account name.
     */
    std::string& get_name();

    /**
     * @brief Retrieves the password of the account.
     * @return A reference to the account password.
     */
    std::string& get_password();

    /**
     * @brief Retrieves the balance of the account.
     * @return A reference to the account balance.
     */
    double& get_balance();

    /**
     * @brief Retrieves the stock holdings of the account.
     * @return A reference to the account's stock holdings.
     */
    std::unordered_map<std::string, int>& get_stocks();

private:
    std::string _name;                                      /**< The name of the account. */
    std::string _password;                                  /**< The password for the account. */
    double _balance;                                        /**< The balance of the account. */
    std::unordered_map<std::string, int> _stocks;           /**< The stock holdings of the account. */
};