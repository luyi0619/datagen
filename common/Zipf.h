//
// Created by Yi Lu on 7/19/18.
//

#pragma once

#include <cmath>
#include <glog/logging.h>

class Zipf {

  class Random {
  public:
    Random(uint64_t seed = 0) { init_seed(seed); }

    void init_seed(uint64_t seed) {
      seed_ = (seed ^ 0x5DEECE66DULL) & ((1ULL << 48) - 1);
    }

    void set_seed(uint64_t seed) { seed_ = seed; }

    uint64_t get_seed() { return seed_; }

    uint64_t next() { return ((uint64_t)next(32) << 32) + next(32); }

    uint64_t next(unsigned int bits) {
      seed_ = (seed_ * 0x5DEECE66DULL + 0xBULL) & ((1ULL << 48) - 1);
      return (seed_ >> (48 - bits));
    }

    /* [0.0, 1.0) */
    double next_double() {
      return (((uint64_t)next(26) << 27) + next(27)) / (double)(1ULL << 53);
    }

  private:
    uint64_t seed_;
  };

public:
  void init(int n, double theta) {
    hasInit = true;

    n_ = n;
    theta_ = theta;
    alpha_ = 1.0 / (1.0 - theta_);
    zetan_ = zeta(n_);
    eta_ = (1.0 - std::pow(2.0 / n_, 1.0 - theta_)) / (1.0 - zeta(2) / zetan_);
  }

  int next() { return value(rng.next_double()); }

  static Zipf &globalZipf() {
    static Zipf z;
    return z;
  }

private:
  int value(double u) {
    CHECK(hasInit);

    double uz = u * zetan_;
    int v;
    if (uz < 1) {
      v = 0;
    } else if (uz < 1 + std::pow(0.5, theta_)) {
      v = 1;
    } else {
      v = static_cast<int>(n_ * std::pow(eta_ * u - eta_ + 1, alpha_));
    }
    DCHECK(v >= 0 && v < n_);
    return v;
  }

  double zeta(int n) {
    DCHECK(hasInit);

    double sum = 0;

    for (auto i = 1; i <= n; i++) {
      sum += std::pow(1.0 / i, theta_);
    }

    return sum;
  }

  bool hasInit = false;

  Random rng;

  int n_;
  double theta_;
  double alpha_;
  double zetan_;
  double eta_;
};
