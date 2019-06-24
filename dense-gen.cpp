#include <fstream>
#include <iostream>
#include <string>

#include <glog/logging.h>

#include "common/Random.h"
#include "core/Context.h"
#include "core/DenseVector.h"
#include "core/Macros.h"

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
  BinaryRandom r(context.bernoulli, context.seed);
  for (auto i = 0u; i < context.n_points; i++) {
    DenseVector<bool> v;
    dense_data_gen(v, r, context.n_dimension);
    v.print(output, context);
  }
}

void int_data_gen(const Context &context, std::ofstream &output) {
  UniformIntRandom r(context.range_low, context.range_high, context.seed);
  for (auto i = 0u; i < context.n_points; i++) {
    DenseVector<int> v;
    dense_data_gen(v, r, context.n_dimension);
    v.print(output, context);
  }
}

void real_uniform_data_gen(const Context &context, std::ofstream &output) {
  UniformRealRandom r(context.range_low, context.range_high, context.seed);
  for (auto i = 0u; i < context.n_points; i++) {
    DenseVector<double> v;
    dense_data_gen(v, r, context.n_dimension);
    v.print(output, context);
  }
}

void real_normal_data_gen(const Context &context, std::ofstream &output) {
  NormalRandom r(context.mean, context.stddev, context.seed);
  for (auto i = 0u; i < context.n_points; i++) {
    DenseVector<double> v;
    dense_data_gen(v, r, context.n_dimension);
    v.print(output, context);
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

  output.close();
  return 0;
}