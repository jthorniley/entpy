#ifndef ENTPY_CPP_CALC_PAIRDIST_HPP_
#define ENTPY_CPP_CALC_PAIRDIST_HPP_

#include <Eigen/Dense>

namespace entpy {

using RowMajorMatrixXXd = Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor>;

/**
 * @brief Calculate pairwise distances between all elements
 * @param data A set of n-dimensional points. Each row is a point.
 * @return The distances between all combinations of points in the data.
 */
Eigen::VectorXd pairdist(Eigen::Ref<const RowMajorMatrixXXd> data);

}  // namespace entpy

#endif  // ENTPY_CPP_CALC_PAIRDIST_HPP_
