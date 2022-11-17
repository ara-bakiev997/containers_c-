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
class S21List : private SequenceContainer<T> {
 public:
  using value_type = typename SequenceContainer<T>::value_type;
  using reference = typename SequenceContainer<T>::reference;
  using const_reference = typename SequenceContainer<T>::const_reference;
  using iterator = typename SequenceContainer<T>::Iterator;
  using const_iterator = typename SequenceContainer<T>::const_iterator;
  using size_type = typename SequenceContainer<T>::size_type;
  using SequenceContainer<T>::arr_;
  using SequenceContainer<T>::size_;

 private:
  struct Node {
    value_type value_{};
    Node() : next_(nullptr), prev_(nullptr) {
      //      this = reinterpret_cast<Node>((new int8_t));
    }
    Node* next_{};
    Node* prev_{};
  };
  //  Node this_node_{};
  Node* head_{};
  Node* tail_{};
  Node fake_{};

 public:
  // Constructors and destructor
  S21List() {}
  S21List(size_type n);
  S21List(std::initializer_list<value_type> const& items);
  S21List(const S21List& l);
  S21List(S21List&& l) {}
  ~S21List() {}
  S21List& operator=(S21List&& l) {}

  // List Element access
  const_reference front();
  const_reference back();

  // List Iterators
  iterator begin() override;
  //      iterator temp(head_);
  //      return temp;
  //    }
  iterator end() override;
  //    iterator temp(&tail_->value_);
  ////    iterator temp(tail_);
  //    return temp;
  //  }

  // List Capacity
  bool empty() { return (size_ ? false : true); }
  size_type size() { return size_; }
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

  // Support func
  void print() {
    std::cout << "size = " << size_ << std::endl;
    for (auto i = 0; i < size_; ++i) {
      std::cout << head_->value_ << ' ';
      head_ = head_->next_;
    }
  }
  Node* NewNode(value_type value);
};

//_____CONSTRUCTORS_AND_DESTRUCTOR_____
template <typename value_type>
S21List<value_type>::S21List(size_type n) {
  for (auto i = 0; i < n; ++i) {
    push_back(0);
  }
}

template <typename value_type>
S21List<value_type>::S21List(const std::initializer_list<value_type>& items) {
  for (auto it = items.begin(); it != items.end(); ++it) {
    push_back(*it);
  }
}
template <typename T>
S21List<T>::S21List(const S21List<T>& l) {
  //  for (auto i = 0; i < l.size_; ++i) {
  //    push_back(l.)
  // Нужен константный итератор

  //  }
}
// typename S21List<value_type>::S21List(const S21List<value_type>& l) {
//
// }

//_____LIST_ELEMENT_ACCESS_____
//_____LIST_ITERATORS_____
template <typename value_type>
typename S21List<value_type>::iterator S21List<value_type>::begin() {
  iterator temp(&head_->value_);
  ////    iterator temp(tail_);
  return temp;
}

template <typename value_type>
typename S21List<value_type>::iterator S21List<value_type>::end() {
  iterator temp(&tail_->value_);
  ////    iterator temp(tail_);
  return temp;
}

//_____LIST_ELEMENT_ACCESS_____
//_____LIST_CAPACITY_____

//_____LIST_MODIFIERS_____
template <typename T>
void S21List<T>::push_back(const_reference value) {
  Node* temp = NewNode(value);
  if (head_) {
    tail_->next_ = temp;
    temp->prev_ = tail_;
    tail_ = temp;
  } else {
    head_ = tail_ = temp;
  }
  ++size_;
}

//_____SUPPORT_FUNC_____
template <typename value_type>
typename S21List<value_type>::Node* S21List<value_type>::NewNode(
    value_type value) {
  Node* temp = new Node();
  if (!temp) throw std::bad_alloc();
  temp->next_ = temp->prev_ = nullptr;
  temp->value_ = value;
  return temp;
}

}  // namespace s21

#endif  // S21_CONTAINERS_SRC_SEQUENCE_S21_LIST_H_