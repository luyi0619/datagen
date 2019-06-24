//
// Created by Yi Lu on 6/18/19.
//

#pragma once

#include <ostream>
#include <tuple>
#include <vector>

#include "core/Context.h"

#include "glog/logging.h"

template <class DataType> class DenseVector {

  class DenseVectorPrinter {
  public:
    void operator()(std::ostream &o, const DenseVector &v,
                    const Context &context) {

      for (auto i = 0u; i < v.vec.size(); i++) {
        if (i > 0) {
          o << " ";
        }
        o << v.vec[i];
      }
      o << "\n";
    }
  };

public:
  void print(std::ostream &o, const Context &context) {

    DenseVectorPrinter()(o, *this, context);
  }

  void push_back(DataType v) { vec.push_back(v); }

  void clear() { vec.clear(); }

private:
  std::vector<DataType> vec;
};
