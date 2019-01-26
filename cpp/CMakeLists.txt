cmake_minimum_required(VERSION 3.9)
project(entpy_cpp)

include(CTest)
enable_testing()

set(CMAKE_CXX_STANDARD 14)

add_subdirectory(pybind11)
include_directories(eigen Catch2/single_include)
add_subdirectory(gen)
add_subdirectory(calc)
