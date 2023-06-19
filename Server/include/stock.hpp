#pragma once 

#include <iostream>
#include <list>
#include <random>

class Stock {
    public:
        Stock(const std::string name, const double start, const double mean, const double stddev, const int timespan);
        Stock();

        void update(const int dt);

        const std::list<double>& getPriceHistory();

        const double getPrice();
        const std::string getName();
        
    private:
        const std::string _name;
        const double _start;
        const double _mean;
        const double _stddev;
        const int _timespan;
        std::list<double> _price_history;

        std::default_random_engine generator;
        std::normal_distribution<double> distribution;

};