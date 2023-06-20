#pragma once 

#include <iostream>
#include <list>
#include <random>

class Stock {
    public:
        Stock(const std::string& name, const double start, const double mean, const double stddev, const int timespan, unsigned seed);
        Stock();

        void update();

        const std::list<double>& getPriceHistory() const;

        const double getPrice() const;
        const std::string getName() const;
        
    private:
        std::string _name;
        double _start;
        double _mean;
        double _stddev;
        int _timespan;
        std::list<double> _price_history;

        std::default_random_engine generator;
        std::normal_distribution<double> distribution;
};
