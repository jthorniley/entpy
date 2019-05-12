// Copyright 2019 James Thorniley

#include <pybind11/pybind11.h>
#include <pybind11/eigen.h>

#include "pairdist.hpp"
#include "shannonent.hpp"

namespace py = pybind11;

namespace entpy {
PYBIND11_MODULE(_entpy_calc, m) {
    m.doc() = "Calculation methods (C++ implementations)";

    m.def("pairdist", &pairdist,
        R"DOC(Calculate all pairwise distances between points.
          
Parameters
----------

data : ndarray

    Points to compare. Each row is a point.

Returns
-------

ndarray

    Set of Euclidean distances between every point in the array.

        )DOC",
          py::arg("data"));

    m.def("shannonent_bits", &shannonent_bits,
          "Shannon entropy",
          py::arg("data"));
    m.def("shannonent_nats", &shannonent_nats,
          "Shannon entropy",
          py::arg("data"));
    m.def("shannonent_base", &shannonent_base,
          "Shannon entropy",
          py::arg("data"), py::arg("base"));
}

}  // namespace entpy
