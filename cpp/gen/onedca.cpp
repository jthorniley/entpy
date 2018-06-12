#include <omp.h>

#include "onedca.hpp"

namespace entpy {

RuleLookup ruleByNumber(uint8_t ruleNumber) {
    RuleLookup result;
    for (uint32_t idx = 0; idx < 8; ++idx) {
        result(idx) = static_cast<uint8_t>((ruleNumber & 1 << idx) != 0);
    }
    return result;
}

void onedca(Eigen::Ref<ByteArray2D> ca, const RuleLookup& ruleLookup) {
    const auto nr = ca.rows();
    const auto nc = ca.cols();

    // Ensure no values greater than 1
    ca = (ca > 1).select(1, ca);

    for (Eigen::Index i = 0; i < nr - 1; ++i) {
#pragma omp parallel
#pragma omp for
        for (Eigen::Index j = 0; j < nc; ++j) {
            auto new_value = (ca(i, j) != 0) << 1;
            if (j > 0) {
                new_value += ca(i, j-1) << 2;
            }
            if (j < nc - 1) {
                new_value += ca(i, j+1);
            }
            ca(i+1, j) = ruleLookup(new_value);
        }
    }
}

}
