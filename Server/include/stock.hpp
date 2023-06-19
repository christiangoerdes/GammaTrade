#pragma once 

#include <iostream>
#include <list>

class Stock {
    public:
        Stock(const double start, const double tendenz, const double sd, const double timespan);

        void update(double dt);

        std::list<double>& getPriceHistory() {
            return price_history;
        }

    private:
        const double start;
        const double tendenz;
        const double sd;
        const double timespan;
        std::list<double> price_history;

};