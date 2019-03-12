// Copyright 2019 James Thorniley

#ifndef CPP_CALC_SHANNONENT_HPP_
#define CPP_CALC_SHANNONENT_HPP_

#include <Eigen/Dense>

namespace entpy {

/**
 * Shannon entropy (bits)
 */
double shannonent_bits(Eigen::VectorXi data);
/**
 * Shannon entropy (nats)
 */
double shannonent_nats(Eigen::VectorXi data);
/**
 * Shannon entropy (arbitrary base)
 */
double shannonent_base(Eigen::VectorXi data, double base);

}  // namespace entpy

#endif  // CPP_CALC_SHANNONENT_HPP_
