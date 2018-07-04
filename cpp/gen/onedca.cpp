#include "onedca.hpp"

#include <omp.h>

namespace entpy {

CALookupTable rule_number_lookup_table(uint8_t rule_number) {
    CALookupTable result;
    for (uint32_t idx = 0; idx < 8; ++idx) {
        result(idx) = static_cast<uint8_t>((rule_number & 1 << idx) != 0);
    }
    return result;
}

void onedca(Eigen::Ref<ByteArrayXXd> data, const CALookupTable& lookup_table) {
    const auto nr = data.rows();
    const auto nc = data.cols();

    // Ensure no values greater than 1
    auto row1 = data.block(0, 0, 1, nc);
    row1 = (row1 > 1).select(1, row1);

    for (Eigen::Index i = 0; i < nr - 1; ++i) {
#pragma omp parallel
#pragma omp for
        for (Eigen::Index j = 0; j < nc; ++j) {
            auto new_value = (data(i, j) != 0) << 1;
            if (j > 0) {
                new_value += data(i, j-1) << 2;
            }
            if (j < nc - 1) {
                new_value += data(i, j+1);
            }
            data(i+1, j) = lookup_table(new_value);
        }
    }
}

}
