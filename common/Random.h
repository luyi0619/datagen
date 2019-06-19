//
// Created by Yi Lu on 6/18/19.
//

#pragma once

#include <cstdint>
#include <random>

template <class ResultType> class Random {
public:
  Random(uint64_t seed) : generator(seed) {}

  virtual ~Random() = default;

  virtual ResultType next() = 0;

protected:
  std::default_random_engine generator;
};

class BinaryRandom : public Random<bool> {
public:
  BinaryRandom(double p, uint64_t seed = 0)
      : Random<bool>(seed), distribution(p) {}

  bool next() override { return distribution(generator); }

private:
  std::bernoulli_distribution distribution;
};

class UniformIntRandom : public Random<int> {
public:
  UniformIntRandom(int low, int high, uint64_t seed = 0)
      : Random<int>(seed), distribution(low, high) {}

  int next() override { return distribution(generator); }

private:
  std::default_random_engine generator;
  std::uniform_int_distribution<int> distribution;
};

class UniformRealRandom : public Random<double> {
public:
  UniformRealRandom(double low, double high, uint64_t seed = 0)
      : Random<double>(seed), distribution(low, high) {}

  double next() override { return distribution(generator); }

private:
  std::default_random_engine generator;
  std::uniform_real_distribution<double> distribution;
};

class NormalRandom : public Random<double> {
public:
  NormalRandom(double mean, double stddev, uint64_t seed = 0)
      : Random<double>(seed), distribution(mean, stddev) {}

  double next() override { return distribution(this->generator); }

private:
  std::normal_distribution<double> distribution;
};
