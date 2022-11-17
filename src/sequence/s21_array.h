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


#include "sequence_container.h"
#include "s21_vector.h"

namespace s21 {

template <class T, size_t N>
class S21Array: public S21Vector<T> {

 public:

  using value_type = typename SequenceContainer<T>::value_type;
  using reference = typename SequenceContainer<T>::reference;
  using const_reference = typename SequenceContainer<T>::const_reference;
  using iterator = typename SequenceContainer<T>::Iterator;
  using size_type = typename SequenceContainer<T>::size_type;

  S21Array(): size_(N){}


  S21Array(std::initializer_list<value_type> const &items): size_(N) {
    std::copy(items.begin(),items.end(), arr_);
  }

  S21Array(const S21Array &other): size_(N) {
    std::memcpy(arr_, other.arr_, sizeof(value_type) *size_);
  }

  S21Array(S21Array &&other) noexcept : size_(N) {
    swap(other);
  }

  ~S21Array() = default;

//  S21Array<value_type> &operator=(S21Array<value_type> &&other) {}

  size_type size() {return size_;}
  bool empty() {return size_ == 0;}
  size_type max_size() {return size_;}

  void swap(S21Array& other) {
    std::swap(arr_, other.arr_);
    std::swap(size_, other.size_);
  }
  void fill(const_reference value) {
//    std::fill();
      if (size_) {
        for (auto i = 0; i < size_; ++i) arr_[i] = value;
      }
  }


  reference operator[](size_type pos) {return arr_[pos];}
  reference at(size_type pos) {return (pos >= size_) ? throw "out_of_range": arr_[pos];}

 private:
  size_type size_{};
  value_type arr_[N]{};

};

}

#endif  // S21_CONTAINERS_SRC_SEQUENCE_S21_ARRAY_H_
