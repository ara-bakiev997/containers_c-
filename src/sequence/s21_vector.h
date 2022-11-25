//
// Created by Lok on 01.11.2022.
//

#ifndef S21_CONTAINERS_SRC_S21_VECTOR_H_
#define S21_CONTAINERS_SRC_S21_VECTOR_H_

#include <cstddef>
#include <initializer_list>
#include <iostream>
#include <utility>
#include <valarray>

#include "sequence_container.h"

namespace s21 {

template <class T> class S21Vector : public SequenceContainer<T> {
public:
  using value_type = typename SequenceContainer<T>::value_type;
  using reference = typename SequenceContainer<T>::reference;
  using const_reference = typename SequenceContainer<T>::const_reference;
  using iterator = typename SequenceContainer<T>::Iterator;
  using const_iterator = typename SequenceContainer<T>::const_iterator;
  using size_type = typename SequenceContainer<T>::size_type;

  // default constructor (simplified syntax for assigning values to attributes)
  S21Vector() { this->size_ = 0U, capacity_ = 0U, this->arr_ = nullptr; }

  explicit S21Vector(size_type n) {
    this->size_ = n;
    capacity_ = n;
    this->arr_ = n ? new T[n] : nullptr;
  }
  S21Vector(std::initializer_list<value_type> const &items);
  S21Vector(const S21Vector &v) {
    this->size_ = v.size_, capacity_ = v.capacity_, this->arr_ = v.arr_;
  };
  S21Vector(S21Vector &&v) noexcept {
    this->size_ = v.size_, capacity_ = v.capacity_, this->arr_ = v.arr_;
    v.arr_ = nullptr;
    v.size_ = 0;
  }

  // destructor
  ~S21Vector() = default; //{ delete[] this->arr_; }

  //  Vector Element access

  reference at(size_type pos); // access specified element with bounds checking
  const_reference at(size_type pos) const;
  reference operator[](size_type pos);             // access specified element
  const_reference operator[](size_type pos) const; // access specified element

  const_reference front(); // access the first element
  const_reference back();  // access the last element
  T *data();               // direct access to the underlying array
  const T *data() const;   // direct access to the underlying array

  // Vector Capacity

  bool empty();
  size_type size();

  // Vector Modifiers

  void swap(S21Vector &other); // swaps the contents

  bool operator==(const S21Vector<value_type> &other);

//protected:
  // Assignment operator
  S21Vector &operator=(const S21Vector &v);
  S21Vector &operator=(S21Vector &&v) noexcept;

  size_type max_size() const noexcept;
  void reserve(size_type size);
  size_type capacity() const;
  void shrink_to_fit() noexcept;

  void clear(); // clears the contents
  iterator insert(iterator pos, const_reference value);
  void erase(iterator pos);              // erases element at pos
  void push_back(const_reference value); // adds an element to the end
  void pop_back();                       // removes the last element

private:
  size_type capacity_;
  void reserve_more_capacity(size_t size);
};

//_____CONSTRUCTORS_____
template <class value_type>
S21Vector<value_type>::S21Vector(
    const std::initializer_list<value_type> &items) {
  this->arr_ = new value_type[items.size()];
  int i = 0;
  for (auto it = items.begin(); it != items.end(); it++) {
    this->arr_[i] = *it;
    i++;
  }
  this->size_ = items.size();
  capacity_ = items.size();
}

//_____ASSIGNMENT_OPERATORS_____
// not ready
template <class value_type>
S21Vector<value_type> &S21Vector<value_type>::operator=(const S21Vector &v) {
  bool is_not_ready_to_return = true;

  if (this == &v) {
    is_not_ready_to_return = false;
  }

  if (is_not_ready_to_return) {
    if (this->arr_ != nullptr)
      delete[] this->arr_;
    this->capacity_ = v.capacity_;
    this->size_ = v.size_;
    this->arr_ = new value_type[capacity_];
    if (!this->arr_)
      throw std::bad_alloc();
    std::copy(v.arr_, v.arr_ + this->size_, this->arr_);
  }
  return *this;
}

// not ready
template <class value_type>
S21Vector<value_type> &
S21Vector<value_type>::operator=(S21Vector &&v) noexcept {
  if (this != &v) {
    if (this->arr_ != v.arr_) {
      if (this->arr_ != nullptr) {
        delete[] this->arr_;
        this->arr_ = nullptr;
        this->size_ = 0;
        this->capacity_ = 0;
      }
      std::swap(this->arr_, v.arr_);
      std::swap(this->size_, v.size_);
      std::swap(this->capacity_, v.capacity_);
    }
  }
  //  std::swap(*this, v);
  return *this;
}

//_____VECTOR_ELEMENT_ACCESS_____

template <class value_type>
typename S21Vector<value_type>::reference
S21Vector<value_type>::at(S21Vector::size_type pos) {
  return (pos < this->size_) ? this->arr_[pos]
                             : throw std::out_of_range("out_of_range");
}

template <class value_type>
typename S21Vector<value_type>::const_reference
S21Vector<value_type>::at(S21Vector::size_type pos) const {
  return (pos < this->size_) ? this->arr_[pos]
                             : throw std::out_of_range("out_of_range");
}

template <class value_type>
typename S21Vector<value_type>::reference
S21Vector<value_type>::operator[](S21Vector::size_type pos) {
  return this->arr_[pos];
}

template <class value_type>
typename S21Vector<value_type>::const_reference
S21Vector<value_type>::operator[](S21Vector::size_type pos) const {
  return this->arr_[pos];
}

template <class value_type>
typename S21Vector<value_type>::const_reference S21Vector<value_type>::front() {
  return at(0);
}

template <class value_type>
typename S21Vector<value_type>::const_reference S21Vector<value_type>::back() {
  return at(this->size_ - 1);
}

template <class T> T *S21Vector<T>::data() { return this->arr_; }
template <class T> const T *S21Vector<T>::data() const { return this->arr_; }

//_____VECTOR_ITERATORS_____
// template <class value_type>
// typename SequenceContainer<value_type>::Iterator
// S21Vector<value_type>::begin()  {
//  return this->arr_;
//}
//
// template <class value_type>
// typename S21Vector<value_type>::iterator S21Vector<value_type>::end() {
//  return this->arr_ + size_;
//}

//_____VECTOR_CAPACITY_____
template <class value_type> bool S21Vector<value_type>::empty() {
  return this->size_ == 0;
}

template <class value_type>
typename S21Vector<value_type>::size_type S21Vector<value_type>::size() {
  return this->size_;
}

template <class value_type>
typename S21Vector<value_type>::size_type
S21Vector<value_type>::max_size() const noexcept {
  //  char bits = 63;
  //  if (sizeof(void *) == 4) {
  //    bits = 31;
  //  }
  //  return static_cast<size_type>(pow(2, bits)) / sizeof(value_type) - 1;
  return SIZE_MAX / sizeof(value_type);
}

template <class value_type>
void S21Vector<value_type>::reserve(S21Vector::size_type size) {
  if (size > this->max_size())
    throw std::length_error("size > max_size");

  if (size > capacity_) {
    if (this->arr_ != nullptr) {
      auto *temp = new value_type[size];
      if (!temp)
        throw std::bad_alloc();
      std::move(this->arr_, this->arr_ + this->size_, temp);
      std::swap(this->arr_, temp);
      delete[] temp;
      capacity_ = size;
    }
  }
}

template <class value_type>
typename S21Vector<value_type>::size_type
S21Vector<value_type>::capacity() const {
  return capacity_;
}

template <class value_type>
void S21Vector<value_type>::shrink_to_fit() noexcept {
  if (this->size_ != capacity_) {
    S21Vector<value_type> temp(this->size_);
    std::move(this->arr_, this->arr_ + this->size_, temp.arr_);
    std::swap(this->arr_, temp.arr_);
    capacity_ = std::move(temp.capacity_);
  }
}

//_____VECTOR_MODIFIERS_____
template <class value_type>
void S21Vector<value_type>::push_back(const_reference value) {
  if (this->size_ == capacity_) {
    auto size = (this->size_) ? this->size_ : 1;
    reserve_more_capacity(size * 2);
  }
  this->arr_[this->size_++] = value;
}

//_____SUPPORT_FUN_____
template <typename value_type>
void S21Vector<value_type>::reserve_more_capacity(size_t size) {
  if (size > capacity_) {
    auto *buff = new value_type[size];
    for (size_t i = 0; i < this->size_; ++i)
      buff[i] = std::move(this->arr_[i]);
    delete[] this->arr_;
    this->arr_ = buff;
    capacity_ = size;
  }
}

template <class value_type> void S21Vector<value_type>::clear() {
  this->size_ = 0;
}

template <class value_type>
typename S21Vector<value_type>::iterator
S21Vector<value_type>::insert(iterator pos, const_reference value) {
  size_type new_capacity = capacity_;
  size_type pos_index = pos - this->begin();
  if (this->size_ + 1 >= capacity_) {
    new_capacity *= 2;
  }
  auto *buff = new value_type[new_capacity];
  std::copy(&(*this->begin()), &(*(this->begin() + pos_index)), buff);
  buff[pos_index] = value;
  std::copy(&(*(this->begin() + pos_index)), &(*(this->begin() + this->size_)),
            buff + pos_index + 1);
  std::swap(this->arr_, buff);
  ++this->size_, capacity_ = new_capacity;
  delete[] buff;

  return this->begin() + pos_index;
}

template <class value_type>
void S21Vector<value_type>::erase(S21Vector::iterator pos) {
  auto *buff = new value_type[capacity_];
  size_type pos_index = pos - this->begin();
  std::copy(&(*this->begin()), &(*(this->begin() + pos_index)), buff);
  std::copy(&(*(this->begin() + pos_index + 1)), &(*this->end()),
            buff + pos_index);
  std::swap(this->arr_, buff);
  --this->size_;
}

template <class value_type> void S21Vector<value_type>::pop_back() {
  --this->size_;
}

template <class value_type> void S21Vector<value_type>::swap(S21Vector &other) {
//  std::swap(this->arr_, other.arr_);
//  std::swap(this->size_, other.size_);
//  std::swap(this->capacity_, other.capacity_);
    std::swap(*this, other);
}
template <class T>
bool S21Vector<T>::operator==(const S21Vector<value_type> &other) {
  bool equal;
  bool skip = false;
  if (this == &other) {
    equal = true;
    skip = true;
  }
  if (!skip) {
    if (this->size_ != other.size_ || this->capacity_ != other.capacity_) {
      equal = false;
      skip = true;
    }
  }
  if (!skip) {
    equal = true;
    for (int i = 0; i < this->size_; ++i) {
      if ((this)->arr_[i] != other.arr_[i]) {
        equal = false;
        break;
      }
    }
  }
  return equal;
}

} // namespace s21

#endif // S21_CONTAINERS_SRC_S21_VECTOR_H_
