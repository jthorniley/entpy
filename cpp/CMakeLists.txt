cmake_minimum_required(VERSION 3.10)
project(entpy_cpp)

find_package(CTest)
enable_testing()

set(CMAKE_CXX_STANDARD 14)

add_subdirectory(pybind11)
include_directories(eigen Catch2/single_include)
add_subdirectory(gen)
