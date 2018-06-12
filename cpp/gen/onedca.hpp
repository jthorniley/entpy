#ifndef CPP_GEN_ONEDCA_HPP_
#define CPP_GEN_ONEDCA_HPP_

#include <cstdint>
#include <Eigen/Dense>

namespace entpy {

using ByteArray2D = Eigen::Array<uint8_t, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor>;
using CALookupTable = Eigen::Array<uint8_t, 8, 1>;

CALookupTable rule_number_lookup_table(uint8_t rule_number);

void onedca(Eigen::Ref<ByteArray2D> data, const CALookupTable& lookup_table);

}

#endif  // CPP_GEN_ONEDCA_HPP_
