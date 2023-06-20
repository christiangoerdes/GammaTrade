#include "../include/stock.hpp"
#include <cmath>

Stock::Stock(const std::string& name, const double start, const double mean, const double stddev, const int timespan, unsigned seed) 
    : _name(name), _start(start), _mean(mean), _stddev(stddev), _timespan(timespan), generator(seed), distribution(0.0, 1.0) {
    _price_history.push_back(start);
}

Stock::Stock() : _start(0.0), _mean(0.0), _stddev(1.0), _timespan(100), distribution(0.0, 1.0) {}

void Stock::update() {
    double current_value = _price_history.back();
    double W = distribution(generator);
    double new_value = current_value * exp((_mean - 0.5 * _stddev * _stddev) + _stddev * W);

    _price_history.push_back(new_value);
    if (_price_history.size() > _timespan) {
        _price_history.pop_front();
    }
}

const std::list<double>& Stock::getPriceHistory() const {
    return _price_history;
}

const double Stock::getPrice() const {
    return _price_history.back();
}

const std::string Stock::getName() const {
    return _name;
}