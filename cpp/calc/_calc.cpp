#include <pybind11/pybind11.h>
#include <pybind11/eigen.h>

#include "pairdist.hpp"

namespace py = pybind11;

namespace entpy {
PYBIND11_MODULE(_entpy_calc, m) {
    m.doc() = "Calculation methods (C++ implementations)";

    m.def("pairdist", &pairdist,
          "Calculate all pairwise distances between points.\n"
          "\n"
          ":param data: (ndarray) Points to compare. Each row is a point,\n"
          "             any number of points between rows\n"
          ":return: (ndarray) Set of Euclidean distances between every\n"
          "         point in the input array\n",
          py::arg("data"));
}

}  // namespace entpy
