#pragma once 

#include <iostream>
#include <queue>

class Stock {
    public:
        Stock(const double start, const double tendenz, const double sd, const double timespan);

        void update(double dt);

        std::queue<double>& getPriceHistory() {
            return price_history;
        }

    private:
        const double start;
        const double tendenz;
        const double sd;
        const double timespan;
        std::queue<double> price_history;

};