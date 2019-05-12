// Copyright 2019 James Thorniley

#include "shannonent.hpp"

#include <algorithm>
#include <numeric>
#include <functional>
#include <vector>

namespace {

double shannonent(Eigen::VectorXi data,
                  const std::function<double(double)>& f_log_f) {
    const auto n = data.size();
    std::sort(data.data(), data.data() + n);

    std::vector<double> freq;
    Eigen::VectorXi::Index accum = 0;
    int current_symbol = data[0];
    for (Eigen::VectorXi::Index i = 1; i < n; ++i) {
        if (data[i] != current_symbol) {
            freq.push_back(static_cast<float>(i - accum)/n);
            accum = i;
            current_symbol = data[i];
        }
    }
    freq.push_back(float(n - accum)/n);

    double sum = 0.0;
    const auto n_symbols = freq.size();

    std::transform(freq.begin(), freq.end(), freq.begin(), f_log_f);
    return -std::accumulate(freq.begin(), freq.end(), 0.0);
}

}  // namespace

namespace entpy {


double shannonent_bits(Eigen::VectorXi data) {
    return shannonent(std::move(data), 
        [](double f) { 
            return f * std::log2(f); 
        }
    );
}

double shannonent_nats(Eigen::VectorXi data) {
    return shannonent(std::move(data), 
        [](double f) { 
            return f * std::log(f); 
        }
    );
}

double shannonent_base(Eigen::VectorXi data, double base) {
    return shannonent(std::move(data), 
        [denom = std::log(base)](double f) { 
            return f * std::log(f) / denom;
        }
    );
}

}  // namespace entpy