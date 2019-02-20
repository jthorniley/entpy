// Copyright (c) James Thorniley
// License: GPLv3

#include <numeric>
#include <utility>
#include <vector>

#include <catch.hpp>

#include "arraywrapper.hpp"

namespace entpy {

using Catch::Matchers::Equals;

TEST_CASE("entpy Arrays") {
    int data_a[5] = {1, 2, 3, 4, 5};
    int data_b[5] = {1, 3, 2, 4, 1};

    ArrayWrapper<int> a(data_a, 5);
    ArrayWrapper<int> b(data_b, 5);
    REQUIRE(a[0] == 1);
    REQUIRE(a[1] == 2);
    REQUIRE(a[4] == 5);
    REQUIRE(b[0] == 1);
    REQUIRE(b[1] == 3);
    REQUIRE(b[2] == 2);

    SECTION("Can swap arrays") {
        using std::swap;
        swap(a, b);
        REQUIRE(b[0] == 1);
        REQUIRE(b[1] == 2);
        REQUIRE(b[4] == 5);
        REQUIRE(a[0] == 1);
        REQUIRE(a[1] == 3);
        REQUIRE(a[2] == 2);
    }

    SECTION("Swap swaps underlying data") {
        // The original arrays should be swapped
        using std::swap;
        swap(a, b);
        REQUIRE(data_b[0] == 1);
        REQUIRE(data_b[1] == 2);
        REQUIRE(data_b[4] == 5);
        REQUIRE(data_a[0] == 1);
        REQUIRE(data_a[1] == 3);
        REQUIRE(data_a[2] == 2);
    }

    SECTION("Can copy") {
        a = b;
        REQUIRE(a[0] == 1);
        REQUIRE(a[1] == 3);
        REQUIRE(a[2] == 2);
        REQUIRE(b[0] == 1);
        REQUIRE(b[1] == 3);
        REQUIRE(b[2] == 2);
    }

    SECTION("Can move (but it behaves as copy)") {
        a = std::move(b);
        REQUIRE(a[0] == 1);
        REQUIRE(a[1] == 3);
        REQUIRE(a[2] == 2);
        REQUIRE(b[0] == 1);
        REQUIRE(b[1] == 3);
        REQUIRE(b[2] == 2);
    }
}

TEST_CASE("Array sorting") {
    // Confirm that arrays can be compared to the extend required
    // by std::sort

    int data[3][3] = {
        {1, 2, 1},
        {1, 2, 2},
        {2, 2, 1}
    };

    std::vector<ArrayWrapper<int>> arrays;
    arrays.emplace_back(ArrayWrapper<int>(data[0], 3));
    arrays.emplace_back(ArrayWrapper<int>(data[1], 3));
    arrays.emplace_back(ArrayWrapper<int>(data[2], 3));

    SECTION("No effect when already sorted") {
        std::sort(arrays.begin(), arrays.end());
        REQUIRE_THAT(std::vector<int>(&data[0][0], &data[0][0] + 3),
                     Equals(std::vector<int>({1, 2, 1})));
        REQUIRE_THAT(std::vector<int>(&data[1][0], &data[1][0] + 3),
                     Equals(std::vector<int>({1, 2, 2})));
        REQUIRE_THAT(std::vector<int>(&data[2][0], &data[2][0] + 3),
                     Equals(std::vector<int>({2, 2, 1})));
    }

    SECTION("Sorts unsorted array") {
        std::vector<ArrayWrapper<int>> arrays;
        arrays.emplace_back(ArrayWrapper<int>(data[2], 3));
        arrays.emplace_back(ArrayWrapper<int>(data[1], 3));
        arrays.emplace_back(ArrayWrapper<int>(data[0], 3));
        // N.B. data are now swapped!
        REQUIRE_THAT(std::vector<int>(&arrays[0][0], &arrays[0][0] + 3),
                     Equals(std::vector<int>({2, 2, 1})));
        REQUIRE_THAT(std::vector<int>(&arrays[1][0], &arrays[1][0] + 3),
                     Equals(std::vector<int>({1, 2, 2})));
        REQUIRE_THAT(std::vector<int>(&arrays[2][0], &arrays[2][0] + 3),
                     Equals(std::vector<int>({1, 2, 1})));
        std::sort(arrays.begin(), arrays.end());
        REQUIRE_THAT(std::vector<int>(&arrays[0][0], &arrays[0][0] + 3),
                     Equals(std::vector<int>({1, 2, 1})));
        REQUIRE_THAT(std::vector<int>(&arrays[1][0], &arrays[1][0] + 3),
                     Equals(std::vector<int>({1, 2, 2})));
        REQUIRE_THAT(std::vector<int>(&arrays[2][0], &arrays[2][0] + 3),
                     Equals(std::vector<int>({2, 2, 1})));
    }
}

}  // namespace entpy
