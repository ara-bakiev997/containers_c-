//
// Created by Lok on 30.10.2022.
//

#ifndef S21_CONTAINERS_SRC_SEQUENCE_CONTAINER_H_
#define S21_CONTAINERS_SRC_SEQUENCE_CONTAINER_H_

#include "../container.h"

namespace s21 {

template <class T>
class SequenceContainer {
 public:
  class Iterator;
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using iterator = Iterator;
  using const_iterator = const Iterator;
  using size_type = size_t;

  //  SequenceContainer() : size_(5), arr_(new value_type[size_]{1, 2, 3, 4, 5})
  //  {}
  SequenceContainer() = default;
  ~SequenceContainer() = default;

//  virtual class Iterator {};
//	  {
//   public:
//    Iterator() = default;
//    explicit Iterator(T *pt) : data_(pt) {}
//    Iterator(const Iterator &other) : data_(other.data_) {}
//    Iterator &operator=(const Iterator &other) {
//      this->data_ = other.data_;
//      return *this;
//    }
//    ~Iterator() = default;
//
//    reference operator*() { return *data_; }
//    Iterator operator+(size_type size) {
//      Iterator temp(*this);
//      temp.data_ += size;
//      return temp;
//    }
//    const Iterator operator++() const {
//      ++data_;
//      return *this;
//    }
//
//    const Iterator operator++(int) const {
//      Iterator temp(*this);
//      this->data_++;
//      return temp;
//    }
//
//    Iterator operator--() {
//      --data_;
//      return *this;
//    }
//
//    Iterator operator--(int) {
//      Iterator temp(*this);
//      this->data_--;
//      return temp;
//    }
//
//    const Iterator operator--(int) const{
//      Iterator temp(*this);
//      this->data_--;
//      return temp;
//    }
//
//    Iterator operator-(const size_type value) {
//      data_ -= value;
//      return *this;
//    }
//
//    ptrdiff_t operator-(Iterator &value) { return this->data_ - value.data_; }
//
//    ptrdiff_t operator-(const Iterator &value) {
//      return this->data_ - value.data_;
//    }
//
//    bool operator==(const Iterator &other) {
//      return this->data_ == other.data_;
//    }
//
//    bool operator!=(const Iterator &other) {
//      return this->data_ != other.data_;
//    }
//
//   protected:
//    T *data_{};
//  };

//  virtual iterator begin() = 0;

//  virtual iterator end() = 0;

 protected:
  size_type size_{};
  T *arr_{};
};


}  // namespace s21

#endif  // S21_CONTAINERS_SRC_SEQUENCE_CONTAINER_H_

