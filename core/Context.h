//
// Created by Yi Lu on 6/19/19.
//

#pragma once

#include <string>

class Context {
public:
  std::string file;

  int32_t n_points;
  int32_t n_dimension;

  std::string type;

  std::string distribution;

  int32_t range_low;
  int32_t range_high;

  double bernoulli;

  double mean;
  double stddev;

  uint64_t seed;
};

#define SETUP_CONTEXT(context)                                                 \
  context.file = FLAGS_file;                                                   \
  context.n_points = FLAGS_n_points;                                           \
  context.n_dimension = FLAGS_n_dimension;                                     \
  context.type = FLAGS_type;                                                   \
  context.distribution = FLAGS_distribution;                                   \
  context.range_low = FLAGS_range_low;                                         \
  context.range_high = FLAGS_range_high;                                       \
  context.bernoulli = FLAGS_bernoulli;                                         \
  context.mean = FLAGS_mean;                                                   \
  context.stddev = FLAGS_stddev;                                               \
  context.seed = FLAGS_seed;