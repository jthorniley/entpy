#include "shannonent.hpp"

#include <algorithm>
#include <functional>
#include <vector>

namespace {

struct Log {
    virtual double operator()(double) const = 0;
};

struct LogNatural : public Log {
    double operator()(double x) const override {
        return std::log(x);
    }
};

struct Log2 : public Log{
    double operator()(double x) const override {
        return std::log2(x);
    }
};

struct LogBase : public Log {
    double denom;

    LogBase(double base) {
        denom = std::log(base);
    }

    double operator()(double x) const override {
        return std::log(x) / denom;
    }
};

}  // namespace

namespace entpy {

double shannonent_(Eigen::VectorXi data, const Log& log) {
    const auto n = data.size();
    std::sort(data.data(), data.data() + n);

    std::vector<double> freq;
    Eigen::VectorXi::Index accum = 0;
    int current_symbol = data[0];
    for (Eigen::VectorXi::Index i = 1; i < n; ++i) {
        if (data[i] != current_symbol) {
            freq.push_back(float(i - accum)/n);
            accum = i;
            current_symbol = data[i];
        }
    }
    freq.push_back(float(n - accum)/n);

    double sum = 0.0;
    for (const auto f : freq) {
        sum -= f * log(f);
    }

    return sum;    
}

double shannonent_bits(Eigen::VectorXi data) {
    return shannonent_(std::move(data), Log2());
}

double shannonent_nats(Eigen::VectorXi data) {
    return shannonent_(std::move(data), LogNatural());
}

double shannonent_base(Eigen::VectorXi data, double base) {
    return shannonent_(std::move(data), LogBase(base));
}

}  // namespace entpy