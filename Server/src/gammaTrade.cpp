#include "../include/gammaTrade.hpp"
#include "../include/account.hpp"

// Implementation for the GammaTrade class

/**
 * @class GammaTrade
 * @brief Represents a trading system for buying and selling stocks.
 */
GammaTrade::GammaTrade(const int timespan) : _timespan(timespan), price_thread(&GammaTrade::update_prices, this, timespan) {

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

}

// Destructor
GammaTrade::~GammaTrade() {
    stop_updates();
    if (price_thread.joinable()) {
        price_thread.join();
    }
}

/**
 * @brief Stops the background thread for updating stock prices.
 */
void GammaTrade::stop_updates() {
    {
        std::lock_guard<std::mutex> lock(mtx);
        stop = true;
    }
    cv.notify_all();
}


/**
 * @brief Background thread function for updating stock prices at regular intervals.
 */
void GammaTrade::update_prices(const int timespan) {
    
    for (int i = 0; i < timespan; i++) { // Anfangshistorie erzeugen
        for (auto& [key, stock] : stocks) {
            std::lock_guard<std::mutex> lock(mtx);
            stock.update();
        }
    }

    while (true) {
        {
            std::unique_lock<std::mutex> lk(mtx);
            if(cv.wait_for(lk, std::chrono::seconds(1), [this]() { return stop.load(); })) {
                break; // If stop is true, break the loop
            }
        }
        
        // Update the price here
        for (auto& [key, stock] : stocks) {
            std::lock_guard<std::mutex> lock(mtx);
            stock.update();
        }
    }
}

/**
 * @brief Registers a new account with the given name and password.
 * @param name The name of the account holder.
 * @param password The password for the account.
 * @return True if the account was successfully created, false if an account with the same name already exists.
 */
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

/**
 * @brief Attempts to log in with the provided name and password.
 * @param name The name of the account holder.
 * @param password The password for the account.
 * @return 0 if the login is successful, 1 if the password is incorrect, 2 if the account is not found.
 */
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

/**
 * @brief Deposits the specified amount of money into the account.
 * @param name The name of the account holder.
 * @param password The password for the account.
 * @param amount The amount of money to deposit.
 * @return True if the deposit was successful, false if the account was not found.
 */
bool GammaTrade::deposit(std::string name, std::string password, int amount) {
    for(Account& account : accounts) {
        if(account.get_name() == name && account.get_password() == password) {
            return account.add_to_balance(amount);
        }
    }
    return false;
}

/**
 * @brief Withdraws the specified amount of money from the account.
 * @param name The name of the account holder.
 * @param password The password for the account.
 * @param amount The amount of money to withdraw.
 * @return True if the withdrawal was successful, false if the account was not found or the balance was insufficient.
 */
bool GammaTrade::withdraw(std::string name, std::string password, int amount) {
    for(Account& account : accounts) {
        if(account.get_name() == name && account.get_password() == password) {
            return account.take_from_balance(amount);
        }
    }
    return false;
}

/**
 * @brief Buys the specified quantity of stocks for the account.
 * @param name The name of the account holder.
 * @param password The password for the account.
 * @param stock The name of the stock to buy.
 * @param quantity The quantity of stocks to buy.
 * @return True if the purchase was successful, false otherwise. 
 */
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

/**
 * @brief Sells the specified quantity of stocks from the account.
 * @param name The name of the account holder.
 * @param password The password for the account.
 * @param stock The name of the stock to sell.
 * @param quantity The quantity of stocks to sell.
 * @return True if the sale was successful, false if the account or stock was not found, or the quantity exceeded the holdings.
 */
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

/**
 * @brief Retrieves a vector containing information about all available stocks.
 * @return A vector of Stock objects representing the available stocks.
 */
std::vector<Stock> GammaTrade::get_stocks() {
    std::vector<Stock> result;
    for (const auto& pair : stocks) {
        result.push_back(pair.second);
    }
    return result;
}

/**
 * @brief Retrieves the stocks for the specified account.
 * @param name The name of the account holder.
 * @param password The password for the account.
 * @return A vector of Stock objects held by the account.
 */
std::vector<Stock> GammaTrade::get_stocks_for(std::string name, std::string password) {
    for(Account& account : accounts) {
        if(account.get_name() == name && account.get_password() == password) {
            std::unordered_map<std::string, int> s = account.get_stocks();
            std::vector<std::string> keys;
            for (const auto& pair : s) {
                keys.push_back(pair.first);
            }
            std::vector<Stock> result;
             for (const auto& key : keys) {
                result.push_back(stocks[key]);
            }
            return result;
        }
    }
}

/**
 * @brief Retrieves the account balance for the specified account.
 * @param name The name of the account holder.
 * @param password The password for the account.
 * @return A double which reprensents the account balance for an account
 */
double GammaTrade::get_balance_for(std::string name, std::string password) {
    for(Account& account : accounts) {
        if(account.get_name() == name && account.get_password() == password) {
            return account.get_balance();
        }
    }
    return NULL;
}

/**
 * @brief Retrieves the account for the given name and password.
 * @param name The name of the account holder.
 * @param password The password for the account.
 * @return The account for the given name and password 
 */
Account GammaTrade::get_account(std::string name, std::string password) {
    for(Account& account : accounts) {
        if(account.get_name() == name && account.get_password() == password) {
            return account;
        }
    }
}

/**
 * @brief Retrieves the total value of all stocks an account owns.
 * @param name The name of the account holder.
 * @param password The password for the account.
 * @return A double representing the total stock value of an account
 */
double GammaTrade::get_stock_sum_for(std::string name, std::string password) {
    double sum = 0;
    for(Account& account : accounts) {
        if(account.get_name() == name && account.get_password() == password) {
            std::unordered_map<std::string, int> s = account.get_stocks();
            std::vector<std::string> keys;
            for (const auto& pair : s) {
                keys.push_back(pair.first);
            }
            std::vector<Stock> result;
            for (const auto& key : keys) {
                result.push_back(stocks[key]);
            }
            for (const auto& st : result) {
                sum += st.getPrice() * s[st.getName()];
            }
        }
    }
    return sum;
}