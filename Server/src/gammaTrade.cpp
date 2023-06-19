#include "../include/gammaTrade.hpp"
#include "../include/account.hpp"

// Implementation for the GammaTrade class

GammaTrade::GammaTrade() {

}

// Create a new account
bool GammaTrade::sign_up(std::string name, std::string password) {
    // Check if an account with this name already exists
    for(Account account : accounts) {
        if(account.get_name() == name) {
            // If an account with this name already exists, return false
            return false; 
        }
    }
    // Create new account with the given name 
    accounts.push_back(Account(name, password)); 
    return true; 
}

// Check if login is valid
int GammaTrade::login(std::string name, std::string password) {
    for(Account account : accounts) {
        // If the login is possible return 0 
        if(account.get_name() == name && account.get_password() == password) {
            return 0; 
        // If the login failed because of a wrong password reutrn 1 
        }else if (account.get_name() == name && account.get_password() != password) {
            return 1; 
        }
    }
    // return 2 which means account not found 
    return 2; 
}

// Deposit money into your account
bool GammaTrade::deposit(std::string name, std::string password, int amount) {
    for(Account account : accounts) {
        if(account.get_name() == name && account.get_password() == password) {
            return account.add_to_balance(amount);
        }
    }
    return false;
}

// Withdraw money from your account 
bool GammaTrade::withdraw(std::string name, std::string password, int amount) {
    for(Account account : accounts) {
        if(account.get_name() == name && account.get_password() == password) {
            return account.take_from_balance(amount);
        }
    }
    return false;
}