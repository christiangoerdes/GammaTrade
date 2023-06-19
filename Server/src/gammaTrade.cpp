#include "../include/gammaTrade.hpp"
#include "../include/account.hpp"
#include "../include/item.hpp"

// Implementation for the GammaTrade class

GammaTrade::GammaTrade() {

}

// Implementation for the Item class

/*
Item::Item(std::string name, double price) {
    this->name = name;
}
*/

// Implementation for the Account class

Account::Account(std::string name, std::string password) {
    this->name = name;
    this->password = password;
    balance = 0;
}