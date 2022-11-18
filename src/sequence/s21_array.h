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
class S21Array: public SequenceContainer<T> {

 public:

  using value_type = typename SequenceContainer<T>::value_type;
  using reference = typename SequenceContainer<T>::reference;
  using const_reference = typename SequenceContainer<T>::const_reference;
  using iterator = typename SequenceContainer<T>::Iterator;
  using size_type = typename SequenceContainer<T>::size_type;
  using pointer = value_type*;
//  using iterator = pointer;
  using const_pointer = const value_type*;
//    using SequenceContainer<T>::arr_;
//    using SequenceContainer<T>::size_;

  /**
 * Constructors
 */
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

  S21Array &operator=(S21Array &&other) noexcept {
    swap(other);
    return *this;
    }

    /**
     * Member functions
     * @return
     */

  size_type size() noexcept {return size_;}
  bool empty() {return size_ == 0;}
  size_type max_size() {return size_;}

  void swap(S21Array& other) {
    std::swap(arr_, other.arr_);
    std::swap(size_, other.size_);
  }
  void fill(const_reference value) {
//    std::fill(arr_[0], arr_[size_-1], value);
      if (size_) {
        for (auto i = 0; i < size_; ++i) arr_[i] = value;
      }
  }

  const_reference front() {return arr_[0];}
  const_reference back() {return arr_[size_-1];}
  pointer data() noexcept {return arr_;}
  const_pointer data() const noexcept {return arr_;}

//  iterator begin(){return arr_;}
  iterator begin() noexcept override {
    iterator tmp(arr_);
    return tmp;
  }

  iterator end() noexcept override {
    iterator tmp(arr_ + size_);
    return tmp;
  }

  reference operator[](size_type pos) {return arr_[pos];}
  reference at(size_type pos) {return (pos < size_) ?  arr_[pos] : throw std::out_of_range("out_of_range");}
  const reference operator[](size_type pos) const {return arr_[pos];}
  const reference at(size_type pos) const {return (pos < size_) ? arr_[pos] : throw std::out_of_range("out_of_range");}

 private:
  size_type size_{};
  value_type arr_[N]{};

};

}

#endif  // S21_CONTAINERS_SRC_SEQUENCE_S21_ARRAY_H_
