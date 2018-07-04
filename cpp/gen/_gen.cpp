#include <pybind11/pybind11.h>
#include <pybind11/eigen.h>

#include "onedca.hpp"

namespace py = pybind11;

namespace entpy {
PYBIND11_MODULE(_entpy_gen, m) {
    m.doc() = "Data generating functions (C++ implementations)";

    m.def("rule_number_lookup_table", &rule_number_lookup_table,
    "Get 1D CA lookup from rule number.\n"
    "\n"
    "This converts a CA \"rule number\" into a lookup table (suitable\n"
    "for use with the `onedca` generator). A rule number is simply\n"
    "the lookup table treated as a binary number and converted to\n"
    "decmal.\n"
    "\n"
    ":param rule_number: (int) The rule number to convert.\n"
    ":return: (ndarray) Equivalent rule lookup table",
    py::arg("rule_number"));

    m.def("onedca", &onedca, "Generate 1D Cellular Automata data\n"
    "\n"
    "The first row of the supplied ``data`` argument will be left\n"
    "alone. All subsequent rows are built by applying the 1D CA\n"
    "defined by the ``lookup_table``\n"
    "\n"
    ":param data: (ndarray) CA data array. The first row should be\n"
    "             already configured with the desired initialisation.\n"
    "             Subsequent rows will be generated (by modifying the\n"
    "             original array in-place\n"
    ":param lookup_table: (ndarray) Lookup table defining the CA.",
    py::arg("data"), py::arg("lookup_table"));
}
}
