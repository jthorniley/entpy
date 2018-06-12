#ifndef CPP_GEN_ONEDCA_HPP_
#define CPP_GEN_ONEDCA_HPP_

#include <cstdint>
#include <Eigen/Dense>

namespace entpy {

using ByteArray2D = Eigen::Array<uint8_t, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor>;
using RuleLookup = Eigen::Array<uint8_t, 8, 1>;

RuleLookup ruleByNumber(uint8_t ruleNumber);

void onedca(Eigen::Ref<ByteArray2D> ca, const RuleLookup& ruleLookup);

}

#endif  // CPP_GEN_ONEDCA_HPP_
