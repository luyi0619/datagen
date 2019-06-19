//
// Created by Yi Lu on 6/18/19.
//

#pragma once

#include <ostream>
#include <vector>

class Vector {
public:
  virtual ~Vector() = default;

  virtual void print(std::ostream &o) = 0;

  virtual void clear() = 0;
};

template <class DataType> class DenseVector : public Vector {

public:
  void print(std::ostream &o) override {
    for (auto i = 0u; i < vec.size(); i++) {
      if (i > 0) {
        o << " ";
      }
      o << vec[i];
    }
    o << std::endl;
  }

  void push_back(DataType v) { vec.push_back(v); }

  void clear() override { vec.clear(); }

private:
  std::vector<DataType> vec;
};

template <class DataType> class SparseVector : public Vector {

public:
  void print(std::ostream &o) override {}

private:
};