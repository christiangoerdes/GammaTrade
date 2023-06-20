#include "gammaTrade.hpp"
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

namespace py = pybind11;

PYBIND11_MODULE(gammaTrade, m) {
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
        .def("get_stocks_for", &GammaTrade::get_stocks_for);
}