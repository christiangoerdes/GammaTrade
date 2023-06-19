#include "../include/stock.hpp"
#include <cmath>
#include <random>

Stock::Stock(const std::string name, const double start, const double tendenz, const double sd, const double timespan) 
    : _name(name), _start(start), _tendenz(tendenz), _sd(sd), _timespan(timespan), _price_history(std::list<double>({start})) {
}
Stock::Stock() : _name(NULL), _start(NULL), _tendenz(NULL), _sd(NULL), _timespan(NULL), _price_history(std::list<double>({NULL})) {
}

void Stock::update(const int dt) {

    std::random_device rd;
    std::mt19937 generator(rd()); // Mersenne Twister random number generator
    std::normal_distribution<> distribution(0.0, 1.0); // Standard normal distribution (mean = 0, standard deviation = 1)

    const double rand_num = distribution(generator);
    const double current_value = _price_history.back();
    const double new_value = current_value * (1 + _tendenz * dt + _sd * std::sqrt(dt) * rand_num);
    
    _price_history.push_back(new_value);
    if (_price_history.size() > _timespan) {
        _price_history.pop_front();
    }

}

const std::list<double>& Stock::getPriceHistory() {
    return _price_history;
}

const double Stock::getPrice() {
    return _price_history.back();
}