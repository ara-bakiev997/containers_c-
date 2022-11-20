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

#include "../sequence_container.h"

namespace s21 {
template <typename T>
struct Node {
  T value_{};
  Node *next_{};
  Node *prev_{};
  Node() : value_(), next_(nullptr), prev_(nullptr) {}
  Node(const T &value) : value_(value), next_(nullptr), prev_(nullptr) {}
};

template <typename T, typename Alloc = std::allocator<T>>
class S21List : public SequenceContainer<T> {
 public:
  class ConstIterator;
  class Iterator;
  using value_type = typename SequenceContainer<T>::value_type;
  using reference = typename SequenceContainer<T>::reference;
  using const_reference = typename SequenceContainer<T>::const_reference;
  using iterator = S21List<T, Alloc>::Iterator;
  using const_iterator = const S21List<T, Alloc>::ConstIterator;
  using size_type = typename SequenceContainer<T>::size_type;
  using SequenceContainer<T>::arr_;
  using SequenceContainer<T>::size_;
  using NodeAlloc = typename std::allocator_traits<
      Alloc>::template rebind_alloc<Node<value_type>>;

  // Iterators for list
  class ConstIterator {
   public:
    ConstIterator() {}
    ConstIterator(const Node<value_type> *pt) : node_(pt) {}
    ConstIterator(ConstIterator &other) : node_(other.node_) {}
    ConstIterator &operator++();
    ConstIterator &operator--();
    const_reference operator*() const { return node_->value_; }

   protected:
    const Node<value_type> *node_{};
  };

  class Iterator : public ConstIterator {
    Iterator() {}
    Iterator(Node<value_type> *pt) : node_(pt) {}
    Iterator(Iterator &other) : node_(other.node_) {}
    reference operator*() { return node_->value_; }
    Iterator &operator=(Iterator &other);

   protected:
    Node<value_type> *node_{};
  };
  // Constructors and destructor
  S21List() {}
  S21List(size_type n);
  S21List(std::initializer_list<value_type> const &items);
  S21List(const S21List &l);
  S21List(S21List &&l) {}
  ~S21List();
  S21List &operator=(S21List &&l) {}

  // List Element access
  const_reference front() {return head_->value_;}
  const_reference back() {return tail_->value_;}

  // List Iterators
//    iterator begin() override;
  //  Iterator begin() override;
  //  ConstIterator end() const;
  //  Iterator end() override;

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
  Node<T> *NewNode(const_reference value);
  void DelNode(Node<value_type> *node);
  void print();

 private:
  Node<T> *head_{};
  Node<T> *tail_{};
  NodeAlloc alloc_{};
};

}  // namespace s21
#include "s21_list.tpp"

#endif  // S21_CONTAINERS_SRC_SEQUENCE_S21_LIST_H_
