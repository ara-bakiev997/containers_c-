//
// Created by Lok on 29.10.2022.
//

#ifndef SRC_PAIR_H_
#define SRC_PAIR_H_

#include "container.h"
#include <algorithm>

namespace s21 {

template<class T1, class T2>
class Pair{

 public:
  Pair() : first_(), second_() {};
  Pair(T1 first, T2 second) {
    this->first_ = first;
    this->second_ = second;
  }

  Pair(Pair &other) {
    std::copy(*this, other);
  }

  Pair(Pair &&other) {
    std::move(*this, other);
  }

  Pair &operator=(Pair &other) {
    std::copy(*this, other);
    return *this;
  }

  Pair &operator=(Pair &&other) {
    std::move(*this, other);
    return *this;
  }

  ~Pair() = default;

  T1 GetFirst() const {
    return first_;
  }
  T2 GetSecond() const {
    return second_;
  }

  void SetFirst(T1 first) {
    first_ = first;
  }
  void SetSecond(T2 second) {
    second_ = second;
  }

 private:
  T1 first_;
  T2 second_;
};

} // s21

#endif //SRC_PAIR_H_
