#include "gammaTrade.hpp"
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

namespace py = pybind11;

PYBIND11_MODULE(gammaTrade, m) {
    // Map the Account class
    py::class_<Account>(m, "Account")
        .def(py::init<std::string, std::string>())
        .def("add_to_balance", &Account::add_to_balance)
        .def("take_from_balance", &Account::take_from_balance)
        .def("buy_stock", &Account::buy_stock)
        .def("sell_stock", &Account::sell_stock)
        .def("get_name", &Account::get_name)
        .def("get_password", &Account::get_password)
        .def("get_balance", &Account::get_balance)
        .def("get_stocks", &Account::get_stocks);
    // Map the Stock class
    py::class_<Stock>(m, "Stock")
        .def(py::init<const std::string&, const double, const double, const double, const int, unsigned>())
        .def(py::init<>())
        .def("update", &Stock::update)
        .def("getPriceHistory", &Stock::getPriceHistory)
        .def("getName", &Stock::getName)
        .def("getPrice", &Stock::getPrice);
    // Map the GammaTrade class
    py::class_<GammaTrade>(m, "GammaTrade") 
        .def(py::init<int>())
        .def("sign_up", &GammaTrade::sign_up)
        .def("login", &GammaTrade::login)
        .def("deposit", &GammaTrade::deposit)
        .def("withdraw", &GammaTrade::withdraw)
        .def("buy_stocks", &GammaTrade::buy_stocks)
        .def("sell_stocks", &GammaTrade::sell_stocks)
        .def("get_stocks", &GammaTrade::get_stocks)
        .def("get_stocks_for", &GammaTrade::get_stocks_for)
        .def("get_balance_for", &GammaTrade::get_balance_for)
        .def("get_account", &GammaTrade::get_account)
        .def("get_stock_sum_for", &GammaTrade::get_stock_sum_for);
}