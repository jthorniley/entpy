// Copyright (c) 2019 James Thorniley
// License: GPLv3

#ifndef CPP_CALC_ARRAY_HPP_
#define CPP_CALC_ARRAY_HPP_

#include <algorithm>
#include <exception>
#include <vector>
#include <utility>

namespace entpy {

template <typename T>
T xor_function(const T& a, const T& b) {
    return a ^ b;
}

template <typename T>
class Array {
 public:
    Array(T* data, size_t n) : data_(data), n_(n) {
    }

    void swap(Array<T>& other) {
        if (other.n_ != n_) {
            throw std::runtime_error("Arrays must be of equal length");
        }
        // The classic interview question - swap two arrays without
        // making a copy.
        std::transform(data_, data_ + n_,
            other.data_, data_, &xor_function<T>);
        std::transform(data_, data_ + n_,
            other.data_, other.data_, &xor_function<T>);
        std::transform(data_, data_ + n_,
            other.data_, data_, &xor_function<T>);
    }

    T& operator[](size_t index) {
        return data_[index];
    }

    const T& operator[](size_t index) const {
        return data_[index];
    }

    bool lessThan(const Array<T>& other) const {
        if (other.n_ != n_) {
            throw std::runtime_error("Arrays must be of equal length");
        }
        for (size_t i = 0; i < n_; ++i) {
            if (data_[i] < other[i]) {
                return true;
            }
        }
        return false;
    }

 private:
    T* data_;
    size_t n_;
};

template <typename T>
bool operator<(const Array<T>& lhs, const Array<T>& rhs) {
    return lhs.lessThan(rhs);
}

template <typename T>
void swap(Array<T>& a, Array<T>& b) {
    a.swap(b);
}

}  // namespace entpy

#endif  // CPP_CALC_ARRAY_HPP_
