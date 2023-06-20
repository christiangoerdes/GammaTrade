#include "../include/account.hpp"

// Implementation for the Account class

/**
 * @brief Constructs an Account object with the specified name and password.
 * 
 * @param name The name of the account.
 * @param password The password of the account.
 */
Account::Account(std::string name, std::string password) {
    _name = name;
    _password = password;
    _balance = 0;
}

/**
 * @brief Adds the specified amount to the account balance.
 * 
 * @param amount The amount to add to the balance.
 * @return True if the balance was successfully updated, false otherwise.
 */
bool Account::add_to_balance(int amount) {
    if(amount < 0) {
        return false;
    }
    _balance += amount;
    return true;
}

/**
 * @brief Takes the specified amount from the account balance.
 * 
 * @param amount The amount to deduct from the balance.
 * @return True if the balance was successfully updated, false otherwise.
 */
bool Account::take_from_balance(int amount) {
    if(amount > _balance || amount < 0) {
        return false;
    }
    _balance -= amount;
    return true;
}

/**
 * @brief Buys stocks with the specified quantity and price.
 * 
 * @param stock The name of the stock to buy.
 * @param quantity The quantity of stocks to buy.
 * @param price The total price of the stocks.
 * @return True if the stocks were successfully bought, false otherwise.
 */
bool Account::buy_stock(std::string stock, int quantity, double price) {
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

/**
 * @brief Sells stocks with the specified quantity and price.
 * 
 * @param stock The name of the stock to sell.
 * @param quantity The quantity of stocks to sell.
 * @param price The total price of the stocks.
 * @return True if the stocks were successfully sold, false otherwise.
 */
bool Account::sell_stock(std::string stock, int quantity, double price) {
    if(_stocks.find(stock) == _stocks.end() || quantity > _stocks[stock]) {
        return false;
    }
    _stocks[stock] -= quantity;
    _balance += price;
    return true;

}

/**
 * @brief Returns the name of the account.
 * 
 * @return The name of the account.
 */
std::string& Account::get_name() {
    return _name;
}

/**
 * @brief Returns the password of the account.
 * 
 * @return The password of the account.
 */
std::string& Account::get_password() {
    return _password;
}

/**
 * @brief Returns the balance of the account.
 * 
 * @return The balance of the account.
 */
double& Account::get_balance() {
    return _balance;
}

/**
 * @brief Returns the map of stocks owned by the account.
 * 
 * @return A reference to the map of stocks owned by the account.
 */
std::unordered_map<std::string, int>& Account::get_stocks() {
    return _stocks;
}