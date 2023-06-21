#pragma once 

#include <iostream>
#include <list>
#include <random>

/**
 * @brief Represents a stock with price history.
 */
class Stock {
public:
    /**
     * @brief Constructs a Stock object.
     * @param name The name of the stock.
     * @param start The initial price of the stock.
     * @param mean The mean value for generating price changes.
     * @param stddev The standard deviation for generating price changes.
     * @param timespan The number of price updates to simulate.
     * @param seed The seed value for the random number generator.
     */
    Stock(const std::string& name, const double start, const double mean, const double stddev, unsigned seed);

    /**
     * @brief Default constructor for Stock.
     */
    Stock();

    /**
     * @brief Updates the stock price by generating a new price based on the mean and standard deviation.
     */
    void update(const int timespan);

    /**
     * @brief Retrieves the price history of the stock.
     * @return A constant reference to the list of historical prices.
     */
    const std::list<double>& getPriceHistory() const;

    /**
     * @brief Retrieves the current price of the stock.
     * @return The current price.
     */
    const double getPrice() const;

    /**
     * @brief Retrieves the name of the stock.
     * @return The name of the stock.
     */
    const std::string getName() const;

private:
    std::string _name;                  /**< The name of the stock. */
    double _start;                      /**< The initial price of the stock. */
    double _mean;                       /**< The mean value for generating price changes. */
    double _stddev;                     /**< The standard deviation for generating price changes. */
    std::list<double> _price_history;   /**< The history of stock prices. */

    std::default_random_engine generator;              /**< The random number generator. */
    std::normal_distribution<double> distribution;     /**< The normal distribution for generating price changes. */
};