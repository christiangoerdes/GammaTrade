#pragma once 

#include <iostream>
#include <list>

class Stock {
    public:
        Stock(const std::string name, const double start, const double tendenz, const double sd, const double timespan);
        Stock();

        void update(const int dt);

        const std::list<double>& getPriceHistory();

        const double getPrice();
        const std::string getName();
        
    private:
        const std::string _name;
        const double _start;
        const double _tendenz;
        const double _sd;
        const double _timespan;
        std::list<double> _price_history;

};