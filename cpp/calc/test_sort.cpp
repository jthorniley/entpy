// Copyright 2019 James Thorniley

#include <vector>
#include <catch.hpp>

#include "sort.hpp"


TEST_CASE("insertion sort simple vector") {
    std::vector<int> raw_data = {1, 2, 4, 3};
    Eigen::Map<entpy::RowMajorArrayXXi> data(raw_data.data(), 4, 1);

    entpy::insertsort_rows(data);

    const std::vector<int> expected = {1, 2, 3, 4};
    REQUIRE_THAT(raw_data, Catch::Matchers::Equals(expected));
}


TEST_CASE("insertion sort 2d data") {
    std::vector<int> raw_data = {
        1, 1, 2,
        4, 1, 3,
        1, 2, 2,
        1, 2, 3};
    Eigen::Map<entpy::RowMajorArrayXXi> data(raw_data.data(), 4, 3);

    entpy::insertsort_rows(data);

    const std::vector<int> expected = {
        1, 1, 2,
        1, 2, 2,
        1, 2, 3,
        4, 1, 3};

    REQUIRE_THAT(raw_data, Catch::Matchers::Equals(expected));
}
