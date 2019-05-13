// Copyright 2019 James Thorniley

#ifndef CPP_CALC_SORT_HPP_
#define CPP_CALC_SORT_HPP_

#include <Eigen/Dense>

// Sorting functions

namespace entpy {

using RowMajorArrayXXi =
    Eigen::Array<int, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor>;

/**
 * In-place sort 2d array by rows.
 * 
 * Takes a 2D and rearranges the rows so that they
 * are in ascending order lexicographically.
 */
void insertsort_rows(Eigen::Ref<RowMajorArrayXXi> data);

}  // namespace entpy

#endif  // CPP_CALC_SORT_HPP_
