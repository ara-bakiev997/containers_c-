//
// Created by Lok on 12.11.2022.
//

#ifndef S21_CONTAINERS_SRC_SEQUENCE_S21_LIST_H_
#define S21_CONTAINERS_SRC_SEQUENCE_S21_LIST_H_

#include <cstddef>
#include <initializer_list>
#include <iostream>
#include <memory>
#include <utility>
#include <valarray>

#include "../sequence_container.h"

namespace s21 {
template<typename T>
struct Node {
  T *value_{};
  Node *next_{};
  Node *prev_{};
  Node() : value_(), next_(nullptr), prev_(nullptr) {}
  explicit Node(const T &value) : value_(value), next_(nullptr), prev_(nullptr) {}
  explicit Node(T &&value) : value_(std::move(value)), next_(nullptr), prev_(nullptr) {}
  //  ~Node() { next_ = nullptr, prev_ = nullptr;}
};

template<typename T, typename Alloc = std::allocator<T>>
class S21List : public SequenceContainer<T> {
 public:
  using value_type = typename SequenceContainer<T>::value_type;
  using reference = typename SequenceContainer<T>::reference;
  using const_reference = typename SequenceContainer<T>::const_reference;
  using size_type = typename SequenceContainer<T>::size_type;
  using ValueTypeAlloc = Alloc;
  using NodeAlloc = typename std::allocator_traits<Alloc>::template rebind_alloc<Node<T>>;

  // Iterators for list
  class ConstIterator {
   public:
	friend S21List; // need for access node in list
	ConstIterator() : node_(nullptr) {}
	explicit ConstIterator(Node<value_type> *pt) : node_(pt) {}
	ConstIterator(const ConstIterator &other) : node_(other.node_) {}
	const_reference operator*() const { return node_->value_; }
	bool operator!=(const ConstIterator &other) const {
	  return node_ != other.node_;
	}
	bool operator==(const ConstIterator &other) const {
	  return node_ == other.node_;
	}

   protected:
	Node<value_type> *node_{};
  };

  class Iterator : public ConstIterator {
   public:
	Iterator() { this->node_ = nullptr; }
	explicit Iterator(Node<value_type> *pt) { this->node_ = pt; }
	Iterator(const Iterator &other) : ConstIterator(other) {}
	Iterator &operator++();
	Iterator operator++(int);
	Iterator &operator--();
	Iterator operator--(int);
	reference operator*() { return *(this->node_->value_); }
	Iterator &operator=(const Iterator &other);
  };
  using iterator = Iterator;
  using const_iterator = const ConstIterator;
  // Constructors and destructor
  S21List() { InitFakeNode(); }
  explicit S21List(size_type n);
  S21List(std::initializer_list<value_type> const &items);
  S21List(const S21List &l);
  S21List(S21List &&l) noexcept {
	InitFakeNode();
	*this = std::move(l);
  }
  ~S21List();
  S21List &operator=(const S21List &l) noexcept;
  S21List &operator=(S21List &&l) noexcept;

  // List Element access
  const_reference front() { return *(fake_->next_->value_); }
  const_reference back() { return *(fake_->prev_->value_); }

  // List Iterators
  iterator begin() const;
  iterator end() const;

  // List Capacity
  bool empty() { return !this->size_; }
  size_type size() { return this->size_; }
  size_type max_size() { return node_alloc_.max_size(); }

  // List Modifiers
  void clear();
  iterator insert(iterator pos, const_reference value);
  void erase(iterator pos);
  void push_back(const_reference value);
  void push_back(T &&value);
  void pop_back();
  void push_front(const_reference value);
  void push_front(T &&value);
  void pop_front();
  void swap(S21List &other);
  void merge(S21List &other);
  void splice(const_iterator pos, S21List &other);
  void reverse();
  void unique();
  void sort();

  // Bonus
  template<typename... Args>
  iterator emplace(const_iterator pos, Args &&...args);
  template<typename... Args>
  void emplace_back(Args &&...args);
  template<typename... Args>
  void emplace_front(Args &&...args);

 private:
  Node<T> *fake_{};
  NodeAlloc node_alloc_{};
  ValueTypeAlloc value_type_alloc_{};
  // Support func
  template<typename... Args>
  Node<T> *CreateNode(Args &&...args);
  void RemNode(Node<T> *node);
  void InitFakeNode();
  iterator GetMiddleList();
  void ConnectBack(Node<T> *new_node);
  void ConnectFront(Node<T> *new_node);
};

}  // namespace s21
#include "s21_list.tpp"

#endif  // S21_CONTAINERS_SRC_SEQUENCE_S21_LIST_H_
