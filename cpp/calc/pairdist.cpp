#include <atomic>
#include <omp.h>
#include <boost/math/special_functions/binomial.hpp>
#include <boost/assert.hpp>
#include "pairdist.hpp"

namespace entpy {

Eigen::VectorXd pairdist(Eigen::Ref<const RowMajorMatrixXXd> data) {
    using namespace boost::math;
    const auto n_samples = data.rows();
    const auto n_dims = data.cols();

    if (n_samples < 2) {
        // There are no pairwise distances for fewer than two points
        return Eigen::VectorXd::Zero(0);
    }

    const auto count = static_cast<uint32_t>(n_samples);
    const auto n_pairs_dbl = binomial_coefficient<double>(count, 2);
    const auto n_pairs = iround(n_pairs_dbl);
    Eigen::VectorXd result = Eigen::VectorXd::Zero(n_pairs);

    Eigen::Index ctr = 0;
    for (Eigen::Index i = 0; i < n_samples - 1; ++i) {
        const auto a = data.block(i, 0, 1, n_dims);
#pragma omp parallel for
        for (Eigen::Index j = i + 1; j < n_samples; ++j) {
            const auto b = data.block(j, 0, 1, n_dims);
            const auto dist = (b - a).norm();
            const auto insert_at = ctr + j - i - 1;
            BOOST_ASSERT_MSG(insert_at < n_pairs, "Unexpected rounding error");
            result(insert_at) = dist;
        }
        ctr += n_samples - i - 1;
    }
    // The size of the result array was calculated from an approximate
    // binomial. Its pretty unlikely that this would go wrong for the sizes
    // we are looking at, but just in case.
    BOOST_ASSERT_MSG(ctr == n_pairs, "Unexpected rounding error");

    return result;
}

}  // namespace
