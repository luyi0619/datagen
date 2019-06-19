#include <fstream>
#include <iostream>
#include <string>

#include "common/Random.h"
#include "core/Context.h"
#include "core/Vector.h"

#include <glog/logging.h>

DEFINE_string(file, "dense-data.txt", "output file");

DEFINE_int32(n_points, 100, "number of data points");
DEFINE_int32(n_dimension, 100, "dimension of data points");

DEFINE_string(type, "binary", "data type: binary or int, real");

DEFINE_string(distribution, "uniform", "real: (uniform/normal)");

DEFINE_int32(range_low, 0, "lower bound on values");
DEFINE_int32(range_high, 100, "upper bound on values");

DEFINE_double(bernoulli, 0.5, "probability of true");

DEFINE_double(mean, 0, "mean of a normal distribution");
DEFINE_double(stddev, 1, "stddev of a normal distribution");

DEFINE_uint64(seed, 0, "seed of random engine");

template <class DataType, class RNG>
void dense_data_gen(DenseVector<DataType> &vec, RNG &random, std::size_t size) {
  vec.clear();
  for (auto i = 0u; i < size; i++) {
    auto v = random.next();
    static_assert(std::is_same<decltype(v), DataType>::value == 1,
                  "the return type of random.next() different from data type "
                  "of dense vector");
    vec.push_back(v);
  }
}

void binary_data_gen(const Context &context, std::ofstream &output) {
  BinaryRandom r(context.bernoulli);
  for (auto i = 0u; i < context.n_points; i++) {
    DenseVector<bool> v;
    dense_data_gen(v, r, context.n_dimension);
    v.print(output);
  }
}

void int_data_gen(const Context &context, std::ofstream &output) {
  UniformIntRandom r(context.range_low, context.range_high);
  for (auto i = 0u; i < context.n_points; i++) {
    DenseVector<int> v;
    dense_data_gen(v, r, context.n_dimension);
    v.print(output);
  }
}

void real_uniform_data_gen(const Context &context, std::ofstream &output) {
  UniformRealRandom r(context.range_low, context.range_high);
  for (auto i = 0u; i < context.n_points; i++) {
    DenseVector<double> v;
    dense_data_gen(v, r, context.n_dimension);
    v.print(output);
  }
}

void real_normal_data_gen(const Context &context, std::ofstream &output) {
  NormalRandom r(context.mean, context.stddev);
  for (auto i = 0u; i < context.n_points; i++) {
    DenseVector<double> v;
    dense_data_gen(v, r, context.n_dimension);
    v.print(output);
  }
}

int main(int argc, char *argv[]) {

  google::InitGoogleLogging(argv[0]);
  google::InstallFailureSignalHandler();
  google::ParseCommandLineFlags(&argc, &argv, true);

  Context context;
  SETUP_CONTEXT(context);

  std::string file = context.file;
  std::ofstream output(file);

  if (context.type == "binary") {
    binary_data_gen(context, output);
  } else if (context.type == "int") {
    int_data_gen(context, output);
  } else if (context.type == "real") {
    if (context.distribution == "uniform") {
      real_uniform_data_gen(context, output);
    } else if (context.distribution == "normal") {
      real_normal_data_gen(context, output);
    } else {
      CHECK(false) << "wrong distribution type.";
    }

  } else {
    CHECK(false) << "wrong data type.";
  }

  return 0;
}