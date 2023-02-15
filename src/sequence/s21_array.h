#ifndef S21_CONTAINERS_SRC_SEQUENCE_S21_ARRAY_H_
#define S21_CONTAINERS_SRC_SEQUENCE_S21_ARRAY_H_

#include <algorithm>
#include <cstdio>
#include <cstring>
#include <initializer_list>
#include <iostream>
#include <utility>

#include "s21_vector.h"

namespace s21 {

template <class T, size_t N> class S21Array : protected S21Vector<T> {
public:
  using value_type = typename S21Vector<T>::value_type;
  using reference = typename S21Vector<T>::reference;
  using const_reference = typename S21Vector<T>::const_reference;
  using size_type = typename S21Vector<T>::size_type;
  using iterator = value_type *;
  using const_iterator = const value_type *;

  /**
   * Constructors
   */
  S21Array();

  S21Array(std::initializer_list<value_type> const &items);

  S21Array(const S21Array &other);

  S21Array(S21Array &&other) noexcept;

  ~S21Array() = default;

  S21Array &operator=(S21Array &&other) noexcept;

  /**
   * Member functions
   * @return
   */
  using S21Vector<T>::size;
  using S21Vector<T>::at;
  using S21Vector<T>::front;
  using S21Vector<T>::back;
  using S21Vector<T>::data;
  using S21Vector<T>::empty;

  size_type max_size() { return this->size_; }

  void swap(S21Array &other) { std::swap(*this, other); }

  void fill(const_reference value);

  iterator begin() const;

  iterator end() const;

  using S21Vector<T>::operator[];

private:
  value_type arr_stat[N]{};
};

/**
 * Constructors
 */
template <class T, size_t N> S21Array<T, N>::S21Array() {
  this->size_ = N;
  if (this->size_)
    this->arr_ = arr_stat;
}

template <class value_type, size_t N>
S21Array<value_type, N>::S21Array(
    std::initializer_list<value_type> const &items)
    : S21Array() {
  this->size_ < items.size()
      ? throw std::out_of_range("too few items")
      : std::copy(items.begin(), items.end(), this->arr_);
}

template <class T, size_t N>
S21Array<T, N>::S21Array(const S21Array &other) : S21Array() {
  std::copy(other.begin(), other.end(), this->arr_);
}

template <class T, size_t N>
S21Array<T, N>::S21Array(S21Array &&other) noexcept : S21Array() {
  std::move(other.begin(), other.end(), this->arr_);
}

/**
 * Member functions
 * @return
 */
template <class T, size_t N>
typename S21Array<T, N>::iterator S21Array<T, N>::begin() const {
  return this->arr_;
}

template <class T, size_t N>
typename S21Array<T, N>::iterator S21Array<T, N>::end() const {
  return this->arr_ + this->size_;
}

template <class T, size_t N>
S21Array<T, N> &S21Array<T, N>::operator=(S21Array &&other) noexcept {
  std::move(other.begin(), other.end(), this->arr_);
  return *this;
}

template <class T, size_t N> void S21Array<T, N>::fill(const_reference value) {
  if (this->size_) {
    for (size_t i = 0; i < this->size_; ++i)
      this->arr_[i] = value;
  }
}

} // namespace s21

#endif // S21_CONTAINERS_SRC_SEQUENCE_S21_ARRAY_H_
