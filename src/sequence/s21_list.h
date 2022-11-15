//
// Created by Lok on 12.11.2022.
//

#ifndef S21_CONTAINERS_SRC_SEQUENCE_S21_LIST_H_
#define S21_CONTAINERS_SRC_SEQUENCE_S21_LIST_H_

#include <cstddef>
#include <initializer_list>
#include <iostream>
#include <utility>
#include <valarray>

#include "sequence_container.h"

namespace s21 {
template <typename T>
class S21List : SequenceContainer<T> {
 public:
  using value_type = typename SequenceContainer<T>::value_type;
  using reference = typename SequenceContainer<T>::reference;
  using const_reference = typename SequenceContainer<T>::const_reference;
  using iterator = typename SequenceContainer<T>::Iterator;
  using const_iterator = typename SequenceContainer<T>::const_iterator;
  using size_type = typename SequenceContainer<T>::size_type;
  using SequenceContainer<T>::arr_;
  using SequenceContainer<T>::size_;

  // Constructors and destructor
  S21List() {}
  S21List(size_type n) {}
  S21List(std::initializer_list<value_type> const& items) {}
  S21List(const S21List& l) {}
  S21List(S21List&& l) {}
  ~S21List() {}
  S21List& operator=(S21List&& l) {}

  // List Element access
  const_reference front();
  const_reference back();

  // List Iterators
  //  iterator begin();
  //  iterator end();

  // List Capacity
  bool empty();
  size_type size();
  size_type max_size();

  // List Modifiers
  void clear();
  iterator insert(iterator pos, const_reference value);
  void erase(iterator pos);
  void push_back(const_reference value);
  void pop_back();
  void push_front(const_reference value);
  void pop_front();
  void swap(S21List& other);
  void merge(S21List& other);
  void splice(const_iterator pos, S21List& other);
  void reverse();
  void unique();
  void sort();

 private:
};

}  // namespace s21

#endif  // S21_CONTAINERS_SRC_SEQUENCE_S21_LIST_H_
