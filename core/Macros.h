//
// Created by Yi Lu on 6/19/19.
//

#pragma once

#include <glog/logging.h>

DEFINE_string(file, "data.txt", "output file");

DEFINE_int32(n_points, 100, "number of data points");
DEFINE_int32(n_dimension, 100, "dimension of data points");

DEFINE_string(type, "binary", "data type: binary or int, real");

DEFINE_string(distribution, "uniform", "real: (uniform/normal/gamma/weibull)");

DEFINE_int32(range_low, 0, "lower bound on values");
DEFINE_int32(range_high, 100, "upper bound on values");

DEFINE_double(bernoulli, 0.5, "probability of true");

DEFINE_double(mean, 0, "mean of a normal distribution");
DEFINE_double(stddev, 1, "stddev of a normal distribution");

DEFINE_double(alpha, 2, "alpha of a gamma distribution");
DEFINE_double(beta, 2, "beta of a gamma distribution");

DEFINE_double(a, 2, "parameter a of a weibull distribution");
DEFINE_double(b, 4, "parameter b of a weibull distribution");

DEFINE_uint64(seed, 0, "seed of random engine");