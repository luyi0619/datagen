//
// Created by Yi Lu on 6/24/19.
//

#pragma once

#include <ostream>
#include <tuple>
#include <vector>

#include "core/Context.h"

#include "glog/logging.h"

template <class DataType> class SparseVector {

  class DokVectorPrinter {

  public:
    void operator()(std::ostream &o, const SparseVector &v,
                    const Context &context) {
      for (auto i = 0u; i < v.vec.size(); i++) {
        o << v.id << " " << std::get<0>(v.vec[i]) << " "
          << std::get<1>(v.vec[i]) << "\n";
      }
    }
  };

  class LineVectorPrinter {
  public:
    void operator()(std::ostream &o, const SparseVector &v,
                    const Context &context) {

      for (auto i = 0u; i < v.vec.size(); i++) {
        if (i > 0) {
          o << " ";
        }
        o << std::get<0>(v.vec[i]) << " " << std::get<1>(v.vec[i]);
      }
      o << "\n";
    }
  };

  class DenseVectorPrinter {
  public:
    void operator()(std::ostream &o, const SparseVector &v,
                    const Context &context) {

      int d = context.n_dimension;
      int i = 0, j = 0;
      while (i < d) {
        if (i > 0) {
          o << " ";
        }
        if (j < v.vec.size() && i == std::get<0>(v.vec[j])) {
          o << std::get<1>(v.vec[j]);
          j++;
        } else {
          o << 0;
        }
        i++;
      }
      CHECK(i == d && j == v.vec.size())
          << "fatal error: " << i << " " << j << " " << v.vec.size();
      o << "\n";
    }
  };

public:
  SparseVector(int id) : id(id) {}

  void print(std::ostream &o, const Context &context) {

    if (context.format == "dok") {
      DokVectorPrinter()(o, *this, context);
    } else if (context.format == "line") {
      LineVectorPrinter()(o, *this, context);
    } else if (context.format == "dense") {
      DenseVectorPrinter()(o, *this, context);
    } else {
      CHECK(false) << "output format is not valid.";
    }
  }

  void push_back(std::tuple<int, DataType> v) { vec.push_back(v); }

  void clear() { vec.clear(); }

private:
  int id;
  std::vector<std::tuple<int, DataType>> vec;
};
