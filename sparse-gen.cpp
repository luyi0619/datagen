#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <unordered_set>

#include <glog/logging.h>

#include "common/Random.h"
#include "common/Zipf.h"
#include "core/Context.h"
#include "core/Macros.h"
#include "core/Vector.h"

DEFINE_double(sparsity, 0.01, "sparsity of data");
DEFINE_double(zipf, 0, "skew factor on data columns");

template <class DataType, class RNG>
void sparse_data_gen(SparseVector<DataType> &vec, RNG &random,
                     std::size_t size) {
  vec.clear();

  std::unordered_set<int> offset_set;
  while (offset_set.size() < size) {
    int offset = Zipf::globalZipf().next();
    offset_set.insert(offset);
  }

  std::vector<int> offsets(offset_set.begin(), offset_set.end());
  std::sort(offsets.begin(), offsets.end());

  for (auto i = 0u; i < size; i++) {
    auto v = random.next();
    static_assert(std::is_same<decltype(v), DataType>::value == 1,
                  "the return type of random.next() different from data type "
                  "of dense vector");
    vec.push_back(std::make_tuple(offsets[i], v));
  }
}

void binary_data_gen(const Context &context, std::ofstream &output) {
  BinaryRandom r(context.bernoulli, context.seed);
  uint64_t n_elements = context.n_elements;
  for (auto i = 0u; i < context.n_points; i++) {
    SparseVector<bool> v(i);
    int size = n_elements / (context.n_points - i);
    sparse_data_gen(v, r, size);
    n_elements -= size;
    v.print(output);
  }
}

void int_data_gen(const Context &context, std::ofstream &output) {
  UniformIntRandom r(context.range_low, context.range_high, context.seed);
  uint64_t n_elements = context.n_elements;
  for (auto i = 0u; i < context.n_points; i++) {
    SparseVector<int> v(i);
    int size = n_elements / (context.n_points - i);
    sparse_data_gen(v, r, size);
    n_elements -= size;
    v.print(output);
  }
}

void real_uniform_data_gen(const Context &context, std::ofstream &output) {
  UniformRealRandom r(context.range_low, context.range_high, context.seed);
  uint64_t n_elements = context.n_elements;
  for (auto i = 0u; i < context.n_points; i++) {
    SparseVector<double> v(i);
    int size = n_elements / (context.n_points - i);
    sparse_data_gen(v, r, size);
    n_elements -= size;
    v.print(output);
  }
}

void real_normal_data_gen(const Context &context, std::ofstream &output) {
  NormalRandom r(context.mean, context.stddev, context.seed);
  uint64_t n_elements = context.n_elements;
  for (auto i = 0u; i < context.n_points; i++) {
    SparseVector<double> v(i);
    int size = n_elements / (context.n_points - i);
    sparse_data_gen(v, r, size);
    n_elements -= size;
    v.print(output);
  }
}

int main(int argc, char *argv[]) {

  google::InitGoogleLogging(argv[0]);
  google::InstallFailureSignalHandler();
  google::ParseCommandLineFlags(&argc, &argv, true);

  Context context;
  SETUP_CONTEXT(context);
  context.sparsity = FLAGS_sparsity;
  context.zipf = FLAGS_zipf;
  context.n_elements =
      1LL * context.n_points * context.n_dimension * context.sparsity;

  std::string file = context.file;
  std::ofstream output(file);

  LOG(INFO) << "init zipf ...";
  Zipf::globalZipf().init(context.n_dimension, context.zipf);
  LOG(INFO) << "init zipf done.";

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