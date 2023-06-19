#include "../include/stock.hpp"
#include <cmath>

Stock::Stock(const std::string name, const double start, const double mean = 0.0, const double stddev = 1.0, const int timespan = 100) 
    : _name(name), _timespan(timespan), _start(start), _mean(mean), _stddev(stddev), _price_history(std::list<double>({start})), distribution(mean, stddev) {
}

Stock::Stock() : _name(NULL), _timespan(NULL), _start(NULL), _mean(NULL), _stddev(NULL), _price_history(NULL), distribution(NULL, NULL) {
}

void Stock::update(const int dt) {

    const double current_value = _price_history.back();
    const double new_value = current_value + distribution(generator);

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

const std::string Stock::getName() {
    return _name;
}