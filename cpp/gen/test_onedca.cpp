#include <vector>
#include <Eigen/Dense>
#include <catch.hpp>

#include "onedca.hpp"

SCENARIO( "1D CA" ) {
    const auto N = 6;
    std::vector<uint8_t> _data(N*N, 0);
    auto data = Eigen::Map<entpy::ByteArrayXXd>(_data.data(), N, N);
    // All tests have the same result expected
    const std::vector<uint8_t> expected = {
        1, 0, 0, 0, 0, 0,
        0, 1, 0, 0, 0, 0,
        1, 0, 1, 0, 0, 0,
        0, 0, 0, 1, 0, 0,
        0, 0, 1, 0, 1, 0,
        0, 1, 0, 0, 0, 1};

    GIVEN( "An initialisation in one cell only" ) {
        data(0, 0) = 1;

        WHEN( "The Rule 90 CA is executed" ) {
            entpy::onedca(data, entpy::rule_number_lookup_table(90));
            THEN( "The result matches the rule" ) {
                REQUIRE_THAT( _data, Catch::Matchers::Equals(expected) );
            }
        }
    }

    GIVEN( "Initialisation with value 2" ) {
        data(0, 0) = 2;

        WHEN( "The Rule 90 CA is executed" ) {
            entpy::onedca(data, entpy::rule_number_lookup_table(90));
            THEN( "The result matches the rule as if the values were 1" ) {
                REQUIRE_THAT( _data, Catch::Matchers::Equals(expected) );
            }
        }
    }

    GIVEN( "Cells in a subsequent row are initialised" ) {
        data(0, 0) = 1;
        data(1, 3) = 1;

        WHEN( "The Rule 90 CA is executed" ) {
            entpy::onedca(data, entpy::rule_number_lookup_table(90));
            THEN( "The additional values are ignored" ) {
                // I.e. the result should be the same as always, the
                // value set in data(1, 3) has no effect
                REQUIRE_THAT( _data, Catch::Matchers::Equals(expected) );
            }
        }
    }
}
