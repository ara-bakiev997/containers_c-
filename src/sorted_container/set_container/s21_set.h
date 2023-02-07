//
// Created by Lok on 17.11.2022.
//

#ifndef S21_CONTAINERS_SRC_SORTED_CONTAINER_SET_CONTAINER_SET_H_
#define S21_CONTAINERS_SRC_SORTED_CONTAINER_SET_CONTAINER_SET_H_

#include <initializer_list>
#include <iostream>

#include "../../sequence/s21_vector.h"
#include "../red_black_tree.h"

namespace s21 {

template <typename Key, typename Compare = std::less<Key>,
          typename Alloc = std::allocator<const Key>>
class S21Set : public Tree<Key> {
 public:
  using key_type = Key;
  using value_type = Key;
  using reference = value_type &;
  using const_reference = const value_type &;
  using iterator = typename Tree<Key>::iterator;
  using const_iterator = typename Tree<Key>::const_iterator;
  using ValueTypeAlloc = typename Tree<Key>::ValueTypeAlloc;
  using NodeAlloc = typename Tree<Key>::NodeAlloc;
  using size_type = size_t;

  S21Set() {}

  S21Set(std::initializer_list<value_type> const &items);

  S21Set(const S21Set &other);

  S21Set(S21Set &&other) noexcept;

  ~S21Set() = default;

  S21Set &operator=(const S21Set &other);

  S21Set &operator=(S21Set &&other) noexcept;

  std::pair<iterator, bool> insert(const value_type &value);

  void merge(S21Set &other);
  
//  iterator find(const Key& key);

  bool contains(const Key &key);

  template <typename... Args>
  S21Vector<std::pair<iterator, bool>> emplace(Args &&...args);
};

template <typename Key, typename Compare, typename Alloc>
S21Set<Key, Compare, Alloc>::S21Set(
    const std::initializer_list<value_type> &items) {
  for (const auto &it : items) {
    Tree<Key>::insert_node(it);
  }
}

template <typename Key, typename Compare, typename Alloc>
S21Set<Key, Compare, Alloc>::S21Set(const S21Set &other) {
  for (auto it = other.begin(); it != other.end(); ++it) {
    Tree<Key>::insert_node((*it).first, (*it).second);
  }
}

template <typename Key, typename Compare, typename Alloc>
S21Set<Key, Compare, Alloc>::S21Set(S21Set &&other) noexcept {
  this->swap(other);
}

template <typename Key, typename Compare, typename Alloc>
S21Set<Key, Compare, Alloc>
    &S21Set<Key, Compare, Alloc>::operator=(const S21Set &other) {
  if (this != &other) {
    this->clear();
    for (auto it = other.begin(); it != other.end(); ++it) {
      Tree<Key>::insert_node((*it).first, (*it).second);
    }
  }
  return *this;
}

template <typename Key, typename Compare, typename Alloc>
S21Set<Key, Compare, Alloc>
    &S21Set<Key, Compare, Alloc>::operator=(S21Set &&other) noexcept {
  if (this != &other) {
    this->clear();
    this->swap(other);
  }
  return *this;
}

template <typename Key, typename Compare, typename Alloc>
std::pair<typename S21Set<Key, Compare, Alloc>::iterator, bool>
S21Set<Key, Compare, Alloc>::insert(const S21Set::value_type &value) {
  return Tree<Key>::insert_node(value.first.second);
}

template <typename Key, typename Compare, typename Alloc>
void S21Set<Key, Compare, Alloc>::merge(S21Set &other) {
  auto it = other.begin();
  auto size = other.size();
  auto end_elem = size - 1;
  for (auto i = 0; i < size; ++i) {
    auto res = insert(std::pair(it->first, it->second));
    if (res.second) {
      other.erase(it);
    }
    if (i < end_elem) {
      ++it;
    }
  }
}

template <typename Key, typename Compare, typename Alloc>
bool S21Set<Key, Compare, Alloc>::contains(const Key &key) {
  auto ptr = Tree<Key>::FindNodeByKey(this->root_, key);
  return ptr != nullptr;
}

template <typename Key, typename Compare, typename Alloc>
template <typename... Args>
S21Vector<std::pair<typename Tree<Key>::iterator, bool>>
S21Set<Key, Compare, Alloc>::emplace(Args &&...args) {
  S21Vector<std::pair<iterator, bool>> data;
  data.push_back(insert(std::forward<Args>(args)...));
  return data;
}

}  // namespace s21

#endif //S21_CONTAINERS_SRC_SORTED_CONTAINER_SET_CONTAINER_SET_H_
