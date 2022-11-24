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

  using value_type = typename S21Vector<T>::value_type;
  using reference = typename S21Vector<T>::reference;
  using const_reference = typename S21Vector<T>::const_reference;
  using size_type = typename S21Vector<T>::size_type;
  using pointer = value_type*;
  using iterator = pointer;
  using const_pointer = const value_type*;

  /**
 * Constructors
 */
  S21Array();

  S21Array(std::initializer_list<value_type> const &items);

    S21Array(const S21Array &other);

    S21Array(S21Array &&other) noexcept;

    ~S21Array()=default;

    S21Array &operator=(S21Array &&other) noexcept {
//    swap(other);
        std::move(other.begin(), other.end(), this->arr_);
        return *this;
    }

    /**
     * Member functions
     * @return
     */

  size_type max_size() {return this->size_;}

//  void swap(S21Array& other) {
////    std::swap(arr_, other.arr_);
////    std::swap(size_, other.size_);
//    std::swap(*this, other);
//  }
  void fill(const_reference value) {
      if (this->size_) {
        for (auto i = 0; i < this->size_; ++i) this->arr_[i] = value;
      }
  }

//  const_pointer data() const noexcept {return this->arr_;}
  iterator begin() const;
  iterator end() const;


private:
  value_type arr_stat[N]{};
    void push_back(const_reference value);
    void pop_back();

};

template<class T, size_t N>
   S21Array<T, N>::S21Array() {
        this->size_ = N;
        this->arr_ = arr_stat;
    }

 template<class value_type, size_t N>
   S21Array<value_type, N>::S21Array(std::initializer_list<value_type> const &items) : S21Array() {
     this->size_ < items.size() ? throw std::out_of_range("too few items") :
     std::copy(items.begin(), items.end(), this->arr_);
 }

    template<class T, size_t N>
    S21Array<T, N>::S21Array(const S21Array &other) : S21Array() {
        std::memcpy(this->arr_, other.arr_, sizeof(value_type) * this->size_);
    }

    template<class T, size_t N>
    S21Array<T, N>::S21Array(S21Array &&other) noexcept: S21Array() {
        std::move(other.begin(), other.end(), this->arr_);
    }


template <class T, size_t N>
typename S21Array<T, N>::iterator S21Array<T, N>::begin() const {
    return this->arr_;
}

template <class T, size_t N>
typename S21Array<T, N>::iterator S21Array<T, N>::end() const {
    return this->arr_ + this->size_;
}



} // namespace 21

#endif  // S21_CONTAINERS_SRC_SEQUENCE_S21_ARRAY_H_
