#include "../include/stock.hpp"
#include <cmath>

// Implementation for the Stock class

/**
 * @brief Constructs a Stock object with the specified parameters.
 * 
 * @param name The name of the stock.
 * @param start The initial price of the stock.
 * @param mean The mean return of the stock.
 * @param stddev The standard deviation of the stock's returns.
 * @param timespan The maximum size of the price history.
 * @param seed The seed value for the random number generator.
 */
Stock::Stock(const std::string& name, const double start, const double mean, const double stddev, const int timespan, unsigned seed) 
    : _name(name), _start(start), _mean(mean), _stddev(stddev), _timespan(timespan), generator(seed), distribution(0.0, 1.0) {
    _price_history.push_back(start);
}

/**
 * @brief Default constructor for the Stock class.
 * Initializes the stock with default values.
 */
Stock::Stock() : _start(0.0), _mean(0.0), _stddev(1.0), _timespan(100), distribution(0.0, 1.0) {}

/**
 * @brief Updates the stock's price based on a Brownian Motion model.
 */
void Stock::update() {
    double current_value = _price_history.back();
    double W = distribution(generator);
    double new_value = current_value * exp((_mean - 0.5 * _stddev * _stddev) + _stddev * W);

    _price_history.push_back(new_value);
    if (_price_history.size() > _timespan) {
        _price_history.pop_front();
    }
}

/**
 * @brief Returns the price history of the stock.
 * 
 * @return A constant reference to the price history list.
 */
const std::list<double>& Stock::getPriceHistory() const {
    return _price_history;
}

/**
 * @brief Returns the current price of the stock.
 * 
 * @return The price of the stock.
 */
const double Stock::getPrice() const {
    return _price_history.back();
}

/**
 * @brief Returns the name of the stock.
 * 
 * @return The name of the stock.
 */
const std::string Stock::getName() const {
    return _name;
}