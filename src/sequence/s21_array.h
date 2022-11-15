//
// Created by Qyburn Bongo on 11/15/22.
//

#ifndef S21_CONTAINERS_SRC_SEQUENCE_S21_ARRAY_H_
#define S21_CONTAINERS_SRC_SEQUENCE_S21_ARRAY_H_

#include <cstdio>
#include <cstring>
#include <initializer_list>
#include <algorithm>
#include <utility>
#include <iostream>


//#include "sequence_container.h"

namespace s21 {

template <class T, size_t N>
class S21Array {

 public:

  using value_type = T;
  using reference = T&;
  using consr_reference = const T&;
  using iterator = T*;
  using size_type = std::size_t;

  S21Array() {}

  S21Array(std::initializer_list<value_type> const &items) {
    //    size_type i = 0;
    //    for (auto it : items) arr_[i++] = it;
    std::copy(items.begin(),items.end(), arr_);
  }

  size_type size() {return size_;}
  reference operator[](size_type pos) {return arr_[pos];}

 private:
  size_type size_ = N;
  value_type arr_[N]{};


};

}

#endif  // S21_CONTAINERS_SRC_SEQUENCE_S21_ARRAY_H_
