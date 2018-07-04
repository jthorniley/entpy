#include <omp.h>
#include <boost/math/special_functions/round.hpp>
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

    const auto n_pairs = iround((n_samples * (n_samples - 1)) / 2.0);
    Eigen::VectorXd result = Eigen::VectorXd::Zero(n_pairs);

    Eigen::Index ctr = 0;
    for (Eigen::Index i = 0; i < n_samples - 1; ++i) {
        const auto a = data.block(i, 0, 1, n_dims);
#pragma omp parallel for
        for (Eigen::Index j = i + 1; j < n_samples; ++j) {
            const auto b = data.block(j, 0, 1, n_dims);
            const auto dist = (b - a).norm();
            const auto insert_at = ctr + j - i - 1;
            result(insert_at) = dist;
        }
        ctr += n_samples - i - 1;
    }

    return result;
}

}  // namespace
