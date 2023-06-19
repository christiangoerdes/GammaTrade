#include "../include/gammaTrade.hpp"
#include "../include/account.hpp"

// Implementation for the GammaTrade class

GammaTrade::GammaTrade(const int timespan) : _timespan(timespan) {
    // initialize all stocks
    stocks = {
        {"DogeCoin", Stock("DogeCoin", 1000.00, 50.00, 10.00, _timespan)},
        {"TechFlair Corp", Stock("TechFlair Corp", 200.00, 5.00, 15.00, _timespan)},
        {"GreenWorld Energy", Stock("GreenWorld Energy", 75.00, 2.00, 10.00, _timespan)},
        {"BlueChip Trust", Stock("BlueChip Trust", 500.00, 1.00, 5.00, _timespan)},
        {"Quantum Computing Inc", Stock("Quantum Computing Inc", 50.00, 10.00, 30.00, _timespan)},
        {"SafeHaven Insurance", Stock("SafeHaven Insurance", 300.00, 3.00, 8.00, _timespan)},
        {"RedPanda Retail", Stock("RedPanda Retail", 100.00, 5.00, 20.00, _timespan)},
        {"HyperAuto Cars", Stock("HyperAuto Cars", 200.00, 2.00, 25.00, _timespan)},
        {"GoldenHorizon Investments", Stock("GoldenHorizon Investments", 450.00, 4.00, 12.00, _timespan)},
        {"MediTech Health", Stock("MediTech Health", 150.00, 7.00, 18.00, _timespan)},
        {"CrystalClear Water", Stock("CrystalClear Water", 80.00, 2.00, 15.00, _timespan)},
        {"Falcon Aerospace", Stock("Falcon Aerospace", 120.00, 8.00, 30.00, _timespan)},
        {"NanoInnovations Ltd", Stock("NanoInnovations Ltd", 70.00, 6.00, 20.00, _timespan)},
        {"ArcticMining Co", Stock("ArcticMining Co", 250.00, 3.00, 20.00, _timespan)},
        {"Evergreen Real Estate", Stock("Evergreen Real Estate", 350.00, 4.00, 10.00, _timespan)},
        {"BrightFutures Education", Stock("BrightFutures Education", 100.00, 5.00, 15.00, _timespan)},
    };

    price_thread = std::thread(&GammaTrade::update_prices, this, 1000);
}

GammaTrade::~GammaTrade() {
        if (stop == false) {
            stop_updates();
        }
        if (price_thread.joinable()) {
            price_thread.join();
        }
    }

// Stops the price updating thread
void GammaTrade::stop_updates() {
    stop = true;
}

void GammaTrade::update_prices(const int dt) {

    while (!stop) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        std::lock_guard<std::mutex> lock(mtx);
        // Update the price here
        for (auto& [key, stock] : stocks) {
            stock.update(dt);
        }
    }
}

// Create a new account
bool GammaTrade::sign_up(std::string name, std::string password) {
    // Check if an account with this name already exists
    for(Account& account : accounts) {
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
    for(Account& account : accounts) {
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
    for(Account& account : accounts) {
        if(account.get_name() == name && account.get_password() == password) {
            return account.add_to_balance(amount);
        }
    }
    return false;
}

// Withdraw money from your account 
bool GammaTrade::withdraw(std::string name, std::string password, int amount) {
    for(Account& account : accounts) {
        if(account.get_name() == name && account.get_password() == password) {
            return account.take_from_balance(amount);
        }
    }
    return false;
}

bool GammaTrade::buy_stocks(std::string name, std::string password, std::string stock, int quantity) {
    for(Account& account : accounts) {
        if(account.get_name() == name && account.get_password() == password) {
            if(stocks.find(stock) != stocks.end()) {
                std::lock_guard<std::mutex> lock(mtx);
                return account.buy_stock(stock, quantity, stocks[stock].getPrice()*quantity); 
            }
        }
    }
    return false;
}

bool GammaTrade::sell_stocks(std::string name, std::string password, std::string stock, int quantity) {
    for(Account& account : accounts) {
        if(account.get_name() == name && account.get_password() == password) {
            if(stocks.find(stock) != stocks.end()) {
                std::lock_guard<std::mutex> lock(mtx);
                return account.sell_stock(stock, quantity, stocks[stock].getPrice()*quantity); 
            }
        }
    }
    return false;
}


std::vector<Stock> GammaTrade::get_stocks() {
    std::vector<Stock> result;
    
    for (const auto& pair : stocks) {
        result.push_back(pair.second);
    }
    
    return result;
}