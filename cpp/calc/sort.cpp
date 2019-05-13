// Copyright 2019 James Thorniley

#include "sort.hpp"

namespace {

bool rowlt(const Eigen::Ref<entpy::RowMajorArrayXXi>& data, int i, int j) {
    // Return true if row i < row j
    const auto ncols = data.cols();
    for (int c = 0; c < ncols; ++c) {
        const auto first = data(i, c);
        const auto second = data(j, c);
        if (first < second) {
            return true;
        } else if (first > second) {
            return false;
        }
    }
    return false;
}

void rowswap(Eigen::Ref<entpy::RowMajorArrayXXi> data, int i, int j) {
    const auto left = data.row(j).eval();
    data.row(j) = data.row(i);
    data.row(i) = left;
}

}  // namespace

namespace entpy {

void insertsort_rows(Eigen::Ref<RowMajorArrayXXi> data) {
    const auto N = data.rows();
    for (int i = 1; i < N; ++i) {
        for (int j = i; j > 0 && rowlt(data, j, j - 1); --j) {
            rowswap(data, j - 1, j);
        }
    }
}

}  // namespace entpy
