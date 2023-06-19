#pragma once 

#include <iostream>
#include <list>

class Stock {
    public:
        Stock(const std::string name, const double start, const double tendenz, const double sd, const double timespan);

        void update(const double dt);

        std::list<double>& getPriceHistory() {
            return _price_history;
        }

    private:
        const std::string _name;
        const double _start;
        const double _tendenz;
        const double _sd;
        const double _timespan;
        std::list<double> _price_history;

};