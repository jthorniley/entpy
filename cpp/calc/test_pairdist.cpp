#include <vector>
#include <Eigen/Dense>
#include <catch.hpp>

#include "pairdist.hpp"

SCENARIO( "Pairwise distances" ) {
    GIVEN( "A set of points" ) {
        const std::vector<double> points = {
            2, 3,
            1, 1,
            2, 2
        };
        auto data = Eigen::Map<const entpy::DoubleArrayXXd>(points.data(), 3, 2);
        WHEN( "Pairwise distances are calculated" ) {
            const auto result = entpy::pairdist(data);
            THEN( "Matches precalculated data" ) {
                const std::vector<double> expected_distances = {
                    2.23606797749979,
                    1,
                    1.4142135623730951
                };

                std::vector<double> result_data(result.data(), result.data() + 3);
                REQUIRE_THAT( result_data, Catch::Matchers::Equals(expected_distances) );
            }
        }
    }

    GIVEN( "An empty set of points" ) {
        const std::vector<double> points;
        auto data = Eigen::Map<const entpy::DoubleArrayXXd>(points.data(), 0, 0);
        WHEN( "Pairwise distances are calculated" ) {
            const auto result = entpy::pairdist(data);
            THEN( "The program has not crashed" ) {
                REQUIRE( result.size() == 0 );
            }
        }
    }

    GIVEN( "A large set of points" ) {
        const std::vector<double> points(5000, 0);
        auto data = Eigen::Map<const entpy::DoubleArrayXXd>(points.data(), 1000, 5);
        WHEN( "Pairwise distances are calculated" ) {
            const auto result = entpy::pairdist(data);
            THEN( "Results are obtained" ) {
                REQUIRE( result.size() == 499500 );
            }
        }
    }

}
