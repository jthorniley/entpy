#include <vector>
#include <Eigen/Dense>
#include <catch.hpp>

#include "onedca.hpp"

SCENARIO( "1D CA" ) {
    GIVEN( "A byte array buffer" ) {
        const auto N = 6;
        std::vector<uint8_t> _data(N*N, 0);
        auto data = Eigen::Map<entpy::ByteArray2D>(_data.data(), N, N);
        data(0, 0) = 1;

        WHEN( "The Rule 90 CA is executed" ) {
            entpy::onedca(data, entpy::ruleByNumber(90));
            THEN( "The result matches the rule" ) {
                std::vector<uint8_t> expected = {
                    1, 0, 0, 0, 0, 0,
                    0, 1, 0, 0, 0, 0,
                    1, 0, 1, 0, 0, 0,
                    0, 0, 0, 1, 0, 0,
                    0, 0, 1, 0, 1, 0,
                    0, 1, 0, 0, 0, 1};
                REQUIRE_THAT( _data, Catch::Matchers::Equals(expected) );
            }
        }
    }

    GIVEN( "A buffer with values greater than 1" ) {
        const auto N = 6;
        std::vector<uint8_t> _data(N*N, 0);
        auto data = Eigen::Map<entpy::ByteArray2D>(_data.data(), N, N);
        data(0, 0) = 2;

        WHEN( "The Rule 90 CA is executed" ) {
            entpy::onedca(data, entpy::ruleByNumber(90));
            THEN( "The result matches the rule as if the values were 1" ) {
                std::vector<uint8_t> expected = {
                    1, 0, 0, 0, 0, 0,
                    0, 1, 0, 0, 0, 0,
                    1, 0, 1, 0, 0, 0,
                    0, 0, 0, 1, 0, 0,
                    0, 0, 1, 0, 1, 0,
                    0, 1, 0, 0, 0, 1};
                REQUIRE_THAT( _data, Catch::Matchers::Equals(expected) );
            }
        }
    }
}
/*
int main(int argc, char **argv) {
    const auto N = 1024*4;
    entpy::MatrixByte data = entpy::MatrixByte::Zero(N, N*2);
    data(0, N) = 1;
    entpy::onedca(data);

    std::fstream output("data.dat", std::ios_base::out | std::ios_base::binary);
    output.write(reinterpret_cast<char*>(data.data()), N*N*2);

    return 0;
}
*/
