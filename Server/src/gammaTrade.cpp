#include "../include/gammaTrade.hpp"
#include "../include/account.hpp"
#include "../include/item.hpp"

// Implementation for the GammaTrade class

GammaTrade::GammaTrade() {

}

bool GammaTrade::sign_up(std::string name, std::string password) {
    // Check if an account with this name already exists
    for(Account account : accounts) {
        if(account.name == name) {
            return false; 
        }
    }
    accounts.push_back(Account(name, password)); 
    return true; 
}

int GammaTrade::login(std::string name, std::string password) {
    for(Account account : accounts) {
        // If the login is possible return 0 
        if(account.name == name && account.password == password) {
            return 0; 
        // If the login failed because of a wrong password reutrn 1 
        }else if (account.name == name && account.password != password) {
            return 1; 
        }
    }
    // return 2 which means account not found 
    return 2; 
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
