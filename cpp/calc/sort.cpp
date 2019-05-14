// Copyright 2019 James Thorniley

#include "sort.hpp"

namespace {

class RowSorter {
    using ArrayType = entpy::RowMajorArrayXXi;
    using RefType = Eigen::Ref<ArrayType>;
    using IndexType = ArrayType::Index;

 public:
    explicit RowSorter(RefType data) : data_(data), tmp_(1, data.cols()) {}
    ~RowSorter() = default;

    RowSorter(const RowSorter&) = delete;

    void InsertSort();

 private:
    bool LessThan(IndexType i, IndexType j);
    void SwapRows(IndexType i, IndexType j);

    RefType data_;
    ArrayType tmp_;
};

bool RowSorter::LessThan(IndexType i, IndexType j) {
    // Return true if row i < row j
    const auto ncols = data_.cols();
    for (IndexType c = 0; c < ncols; ++c) {
        const auto first = data_(i, c);
        const auto second = data_(j, c);
        if (first < second) {
            return true;
        } else if (first > second) {
            return false;
        }
    }
    return false;
}

void RowSorter::SwapRows(IndexType i, IndexType j) {
    tmp_ = data_.row(j).eval();
    data_.row(j) = data_.row(i);
    data_.row(i) = tmp_;
}

void RowSorter::InsertSort() {
    const auto N = data_.rows();
    for (IndexType i = 1; i < N; ++i) {
        for (IndexType j = i; j > 0 && LessThan(j, j - 1); --j) {
            SwapRows(j, j - 1);
        }
    }
}

}  // namespace

namespace entpy {

void insertsort_rows(Eigen::Ref<RowMajorArrayXXi> data) {
    RowSorter sorter(data);
    sorter.InsertSort();
}

}  // namespace entpy
