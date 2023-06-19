#include "../include/account.hpp"

Account::Account(std::string name, std::string password) {
    _name = name;
    _password = password;
    _balance = 0;
}

// Update the account balance
bool Account::add_to_balance(int amount) {
    if(amount < 0) {
        return false;
    }
    _balance += amount;
    return true;
}
bool Account::take_from_balance(int amount) {
    if(amount > _balance || amount < 0) {
        return false;
    }
    _balance -= amount;
    return true;
}
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

bool Account::sell_stock(std::string stock, int quantity, double price) {
    if(_stocks.find(stock) == _stocks.end() || quantity > _stocks[stock]) {
        return false;
    }
    _stocks[stock] -= quantity;
    _balance += price;
    return true;

}

// Getter 
std::string& Account::get_name() {
    return _name;
}
std::string& Account::get_password() {
    return _password;
}
double& Account::get_balance() {
    return _balance;
}
std::unordered_map<std::string, int>& Account::get_stocks() {
    return _stocks;
}