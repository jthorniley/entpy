cmake_minimum_required(VERSION 3.9)

set(SOURCES 
	pairdist.hpp
    pairdist.cpp
    shannonent.hpp
    shannonent.cpp)

find_package(Boost REQUIRED)
find_package(OpenMP REQUIRED)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS} -D_GLIBCXX_PARALLEL")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS} -D_GLIBCXX_PARALLEL")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
add_library(calc ${SOURCES})
set_property(TARGET calc PROPERTY POSITION_INDEPENDENT_CODE on)
set_property(TARGET calc PROPERTY INCLUDE_DIRECTORIES
    ${Boost_INCLUDE_DIRS}
    ${CMAKE_SOURCE_DIR}/eigen)

pybind11_add_module(_entpy_calc _calc.cpp)
target_link_libraries(_entpy_calc PRIVATE calc)

add_executable(calc_test test.cpp test_pairdist.cpp test_shannonent.cpp)
target_link_libraries(calc_test PRIVATE calc)

add_test(NAME calc_module COMMAND calc_test)
