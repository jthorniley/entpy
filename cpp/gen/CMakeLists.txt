cmake_minimum_required(VERSION 3.9)

set(SOURCES onedca.hpp
	onedca.cpp)

find_package(OpenMP REQUIRED)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
add_library(gen ${SOURCES})
set_property(TARGET gen PROPERTY POSITION_INDEPENDENT_CODE on)

pybind11_add_module(_entpy_gen _gen.cpp)
target_link_libraries(_entpy_gen PRIVATE gen)

add_executable(gen_test test.cpp test_onedca.cpp)
target_link_libraries(gen_test PRIVATE gen)

add_test(NAME gen_module COMMAND gen_test)
