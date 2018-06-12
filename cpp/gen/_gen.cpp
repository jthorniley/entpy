#include <pybind11/pybind11.h>
#include <pybind11/eigen.h>

#include "onedca.hpp"

namespace entpy {
PYBIND11_MODULE(_gen, m) {
    m.doc() = "Data generating functions (C++ implementations)";

    m.def("rule_by_number", &ruleByNumber, "Get 1D CA Rule according to numeric value");
    m.def("onedca", &onedca, "Generate 1D Cellular Automata data");
}
}
