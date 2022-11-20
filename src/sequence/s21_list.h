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
template <typename T> struct Node final {
  T value_{};
  Node *next_{};
  Node *prev_{};
  Node() : value_(), next_(nullptr), prev_(nullptr) {}
  Node(const T &value) : value_(value), next_(nullptr), prev_(nullptr) {}
};

template <typename T, typename Alloc = std::allocator<T>>
class S21List : public SequenceContainer<T> {
public:
  using value_type = typename SequenceContainer<T>::value_type;
  using reference = typename SequenceContainer<T>::reference;
  using const_reference = typename SequenceContainer<T>::const_reference;
  using iterator = typename SequenceContainer<T>::Iterator;
  using const_iterator = typename SequenceContainer<T>::const_iterator;
  using size_type = typename SequenceContainer<T>::size_type;
  using SequenceContainer<T>::arr_;
  using SequenceContainer<T>::size_;
  using NodeAlloc = typename std::allocator_traits<
      Alloc>::template rebind_alloc<Node<value_type>>;

private:
  Node<T> *head_{};
  Node<T> *tail_{};
  NodeAlloc alloc_{};

  // Iterators for list
  class ConstIterator {
  public:
    ConstIterator() = default;
    ConstIterator(const Node<value_type> *pt) : node_(pt) {}
    ConstIterator(ConstIterator &other) : node_(other.node_) {}
    ConstIterator &operator++() {
      node_ = node_->next_;
      return node_;
    }
    ConstIterator &operator--() {
      node_ = node_->prev_;
      return node_;
    }
    const_reference operator*() const { return node_->value_; }

  protected:
    const Node<value_type> *node_{};
  };

  class Iterator : public ConstIterator {
    Iterator() = default;
    Iterator(Node<value_type> *pt) : node_(pt) {}
    Iterator(Iterator &other) : node_(other.node_) {}
    reference operator*() { return node_->value_; }
    Iterator &operator=(Iterator &other) {
      node_ = other.node_;
      return *this;
    }

  protected:
    Node<value_type> *node_{};
  };

public:
  // Constructors and destructor
  S21List() {}
  S21List(size_type n);
  S21List(std::initializer_list<value_type> const &items);
  S21List(const S21List &l);
  S21List(S21List &&l) {}
  ~S21List() {
    for (auto i = size_; i > 0; --i) {
      Node<value_type> *temp = head_;
      head_ = head_->next_;
      DelNode(temp);
    }
  }
  S21List &operator=(S21List &&l) {}

  // List Element access
  const_reference front();
  const_reference back();

  // List Iterators

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
  void swap(S21List &other);
  void merge(S21List &other);
  void splice(const_iterator pos, S21List &other);
  void reverse();
  void unique();
  void sort();

  // Support func
  void print() {
    std::cout << "size = " << size_ << std::endl;
    Node<value_type> *temp = head_;
    for (auto i = size_; i > 0; --i) {
      std::cout << temp->value_ << ' ';
      temp = temp->next_;
    }
    std::cout << std::endl;
  }
  Node<value_type> *NewNode(const_reference value) {
    //    Node<value_type> *new_node = new Node<value_type>(value);
    Node<value_type> *new_node = alloc_.allocate(1);
    alloc_.construct(new_node, value);
    return new_node;
  }
  void DelNode(Node<value_type> *node) {
    alloc_.destroy(node);
    alloc_.deallocate(node, 1);
  }
};

//_____CONSTRUCTORS_AND_DESTRUCTOR_____
template <typename value_type, typename Alloc>
S21List<value_type, Alloc>::S21List(size_type n) {
  for (auto i = 0; i < n; ++i) {
    push_back(0);
  }
}

template <typename value_type, typename Alloc>
S21List<value_type, Alloc>::S21List(
    const std::initializer_list<value_type> &items) {
  for (auto it = items.begin(); it != items.end(); ++it) {
    push_back(*it);
  }
}

template <typename T, typename Alloc>
S21List<T, Alloc>::S21List(const S21List<T, Alloc> &l) {
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
// template <typename value_type>
// typename S21List<value_type>::iterator S21List<value_type>::begin() {
//  iterator temp(&head_->value_);
//  //  iterator temp(tail_);
//  return temp;
//}
//
// template <typename value_type>
// typename S21List<value_type>::iterator S21List<value_type>::end() {
//  iterator temp(&tail_->value_);
//  //  iterator temp(tail_);
//  return temp;
//}

//_____LIST_ELEMENT_ACCESS_____
//_____LIST_CAPACITY_____

//_____LIST_MODIFIERS_____
template <typename T, typename Alloc>
void S21List<T, Alloc>::push_back(const_reference value) {
  Node<value_type> *temp = NewNode(value);
  if (head_) {
    tail_->next_ = temp;
    temp->prev_ = tail_;
    tail_ = temp;
  } else {
    head_ = tail_ = temp;
  }
  ++size_;
}

template <typename T, typename Alloc> void S21List<T, Alloc>::pop_back() {
  Node<T> *temp = tail_;
  tail_ = tail_->prev_;
  DelNode(temp);
  --size_;
}

//_____SUPPORT_FUNC_____
// template <typename value_type, typename Alloc>
// typename S21List<value_type, Alloc>::Node *
// S21List<value_type, Alloc>::NewNode(const_reference value) {
//
//  Node<value_type> *new_node = alloc_.allocate(sizeof(Node<value_type>));
//
//  //  Node *new_node = reinterpret_cast<Node *>(new int8_t[sizeof(Node)]);
//  //  try {
//  //    new (new_node) Node(value);
//  //  } catch (...) {
//  //    new_node->~Node();
//  //    delete[] reinterpret_cast<int8_t *>(new_node);
//  //  }
//  return new_node;
//}

// template <typename value_type>
// void S21List<value_type>::DelNode(Node *node) {
//
// }

} // namespace s21

#endif // S21_CONTAINERS_SRC_SEQUENCE_S21_LIST_H_
