#include "../include/gammaTrade.hpp"
#include "../include/account.hpp"

// Implementation for the GammaTrade class

GammaTrade::GammaTrade(const int timespan) : _timespan(timespan), price_thread(&GammaTrade::update_prices, this) {
    // initialize all stocks
    stocks = {
        {"DogeCoin", Stock("DogeCoin", 1000.00, pow(1 + 0.1, 1.0/(365*24)) - 1, 0.2 / sqrt(365*24), _timespan, std::random_device{}())},
        {"TechFlair Corp", Stock("TechFlair Corp", 200.00, pow(1 + 0.02, 1.0/(365*24)) - 1, 0.06 / sqrt(365*24), _timespan, std::random_device{}())},
        {"GreenWorld Energy", Stock("GreenWorld Energy", 75.00, pow(1 - 0.04, 1.0/(365*24)) - 1, 0.1 / sqrt(365*24), _timespan, std::random_device{}())},
        {"BlueChip Trust", Stock("BlueChip Trust", 500.00, pow(1 - 0.01, 1.0/(365*24)) - 1, 0.02 / sqrt(365*24), _timespan, std::random_device{}())},
        {"Quantum Computing Inc", Stock("Quantum Computing Inc", 50.00, pow(1 + 0.04, 1.0/(365*24)) - 1, 0.08 / sqrt(365*24), _timespan, std::random_device{}())},
        {"SafeHaven Insurance", Stock("SafeHaven Insurance", 300.00, pow(1 + 0.03, 1.0/(365*24)) - 1, 0.04 / sqrt(365*24), _timespan, std::random_device{}())},
        {"RedPanda Retail", Stock("RedPanda Retail", 100.00, pow(1 - 0.02, 1.0/(365*24)) - 1, 0.06 / sqrt(365*24), _timespan, std::random_device{}())},
        {"HyperAuto Cars", Stock("HyperAuto Cars", 200.00, pow(1 + 0.02, 1.0/(365*24)) - 1, 0.04 / sqrt(365*24), _timespan, std::random_device{}())},
        {"GoldenHorizon Investments", Stock("GoldenHorizon Investments", 450.00, pow(1 + 0.04, 1.0/(365*24)) - 1, 0.06 / sqrt(365*24), _timespan, std::random_device{}())},
        {"MediTech Health", Stock("MediTech Health", 150.00, pow(1 - 0.03, 1.0/(365*24)) - 1, 0.05 / sqrt(365*24), _timespan, std::random_device{}())},
        {"CrystalClear Water", Stock("CrystalClear Water", 80.00, pow(1 + 0.02, 1.0/(365*24)) - 1, 0.04 / sqrt(365*24), _timespan, std::random_device{}())},
        {"Falcon Aerospace", Stock("Falcon Aerospace", 120.00, pow(1 + 0.04, 1.0/(365*24)) - 1, 0.08 / sqrt(365*24), _timespan, std::random_device{}())},
        {"NanoInnovations Ltd", Stock("NanoInnovations Ltd", 70.00, pow(1 - 0.03, 1.0/(365*24)) - 1, 0.06 / sqrt(365*24), _timespan, std::random_device{}())},
        {"ArcticMining Co", Stock("ArcticMining Co", 250.00, pow(1 + 0.03, 1.0/(365*24)) - 1, 0.05 / sqrt(365*24), _timespan, std::random_device{}())},
        {"Evergreen Real Estate", Stock("Evergreen Real Estate", 350.00, pow(1 + 0.04, 1.0/(365*24)) - 1, 0.06 / sqrt(365*24), _timespan, std::random_device{}())},
        {"BrightFutures Education", Stock("BrightFutures Education", 100.00, pow(1 - 0.02, 1.0/(365*24)) - 1, 0.04 / sqrt(365*24), _timespan, std::random_device{}())}
    };

    price_thread.detach(); // Detach the thread

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

void GammaTrade::update_prices() {

    while (!stop) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        std::lock_guard<std::mutex> lock(mtx);
        // Update the price here
        for (auto& [key, stock] : stocks) {
            stock.update();
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

std::unordered_map<std::string, int> GammaTrade::get_stocks_for(std::string name, std::string password) {
    for(Account& account : accounts) {
        if(account.get_name() == name && account.get_password() == password) {
            return account.get_stocks();
        }
    }
}