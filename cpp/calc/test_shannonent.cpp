// Copyright 2019 James Thorniley

#include <catch.hpp>

#include "shannonent.hpp"


TEST_CASE("shannonent (0,1) -> 1", "[shannonent][calc]") {
    Eigen::VectorXi data(2);
    data << 0, 1;
    const auto result = entpy::shannonent_bits(data);

    REQUIRE_THAT(result, Catch::Matchers::WithinAbs(1.0, 1e-7));
}

TEST_CASE("shannonent (0,1,0,1) -> 1", "[shannonent][calc]") {
    Eigen::VectorXi data(4);
    data << 0, 1, 0, 1;
    const auto result = entpy::shannonent_bits(data);

    REQUIRE_THAT(result, Catch::Matchers::WithinAbs(1.0, 1e-7));
}

TEST_CASE("shannonent (0,1,0,1,0,1) -> 1", "[shannonent][calc]") {
    Eigen::VectorXi data(6);
    data << 0, 1, 0, 1, 0, 1;
    const auto result = entpy::shannonent_bits(data);

    REQUIRE_THAT(result, Catch::Matchers::WithinAbs(1.0, 1e-7));
}