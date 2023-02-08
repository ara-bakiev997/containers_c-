//
// Created by Lok on 17.11.2022.
//

#ifndef S21_CONTAINERS_SRC_SORTED_CONTAINER_SET_CONTAINER_MULTISET_H_
#define S21_CONTAINERS_SRC_SORTED_CONTAINER_SET_CONTAINER_MULTISET_H_
#include <initializer_list>
#include <iostream>

#include "../../sequence/s21_vector.h"
#include "../red_black_tree.h"

namespace s21 {

template <typename Key, typename Value, typename Compare = std::less<Key>,
          typename Alloc = std::allocator<std::pair<const Key, Value>>>
class S21Multiset : public Tree<Key, Value, Compare> {
 public:
  using key_type = Key;
  using mapped_type = Value;
  using value_type = std::pair<const key_type, mapped_type>;
  using reference = value_type &;
//  using key_compare = typename Tree<Key, Value, Compare, Alloc>::key_compare;
  using const_reference = const value_type &;
  using iterator = typename Tree<Key, Value, Compare, Alloc>::iterator;
  using const_iterator = typename Tree<Key, Value, Compare, Alloc>::const_iterator;
  using ValueTypeAlloc = typename Tree<Key, Value, Compare, Alloc>::ValueTypeAlloc;
  using NodeAlloc = typename Tree<Key, Value, Compare, Alloc>::NodeAlloc;
  using size_type = size_t;

  S21Multiset() {}

  S21Multiset(std::initializer_list<value_type> const &items);

  S21Multiset(const S21Multiset &other);

  S21Multiset(S21Multiset &&other) noexcept;

  ~S21Multiset() = default;

  S21Multiset &operator=(const S21Multiset &other);

  S21Multiset &operator=(S21Multiset &&other) noexcept;

  mapped_type &at(const key_type &key);

  const mapped_type &at(const key_type &key) const;

  mapped_type &operator[](const key_type &key);

  std::pair<iterator, bool> insert(const value_type &value);

  std::pair<iterator, bool> insert(const Key &key, const Value &obj);

  std::pair<iterator, bool> insert_or_assign(const Key &key, const Value &obj);

  void merge(S21Multiset &other);

  bool contains(const Key &key);

  template <typename... Args>
  S21Vector<std::pair<iterator, bool>> emplace(Args &&...args);
};

template <typename Key, typename Value, typename Compare, typename Alloc>
S21Multiset<Key, Value, Compare, Alloc>::S21Multiset(
    const std::initializer_list<value_type> &items) {
  for (const auto &it : items) {
    Tree<Key, Value, Compare, Alloc>::insert_node(it.first, it.second);
  }
}

template <typename Key, typename Value, typename Compare, typename Alloc>
S21Multiset<Key, Value, Compare, Alloc>::S21Multiset(const S21Multiset &other) {
  for (auto it = other.begin(); it != other.end(); ++it) {
    Tree<Key, Value, Compare, Alloc>::insert_node((*it).first, (*it).second);
  }
}

template <typename Key, typename Value, typename Compare, typename Alloc>
S21Multiset<Key, Value, Compare, Alloc>::S21Multiset(
    S21Multiset &&other) noexcept {
  this->swap(other);
}

template <typename Key, typename Value, typename Compare, typename Alloc>
S21Multiset<Key, Value, Compare, Alloc> &
S21Multiset<Key, Value, Compare, Alloc>::operator=(const S21Multiset &other) {
  if (this != &other) {
    this->clear();
    for (auto it = other.begin(); it != other.end(); ++it) {
      Tree<Key, Value, Compare, Alloc>::insert_node((*it).first, (*it).second);
    }
  }
  return *this;
}

template <typename Key, typename Value, typename Compare, typename Alloc>
S21Multiset<Key, Value, Compare, Alloc>
    &S21Multiset<Key, Value, Compare, Alloc>::operator=(
        S21Multiset &&other) noexcept {
  if (this != &other) {
    this->clear();
    this->swap(other);
  }
  return *this;
}

template <typename Key, typename Value, typename Compare, typename Alloc>
Value &S21Multiset<Key, Value, Compare, Alloc>::at(const key_type &key) {
  auto ptr = Tree<Key, Value, Compare, Alloc>::FindNodeByKey(this->root_, key);
  if (!ptr) {
    throw std::out_of_range("key not found");
  }
  return ptr->data_->second;
}

template <typename Key, typename Value, typename Compare, typename Alloc>
const Value &S21Multiset<Key, Value, Compare, Alloc>::at(
    const key_type &key) const {
  auto ptr = Tree<Key, Value, Compare, Alloc>::FindNodeByKey(this->root_, key);
  if (!ptr) {
    throw std::out_of_range("key not found");
  }
  return ptr->data_->second;
}

template <typename Key, typename Value, typename Compare, typename Alloc>
Value &S21Multiset<Key, Value, Compare, Alloc>::operator[](
    const key_type &key) {
  auto ptr = Tree<Key, Value, Compare, Alloc>::FindNodeByKey(this->root_, key);
  if (!ptr) {
    insert(key, {});
  }
  return at(key);
}

template <typename Key, typename Value, typename Compare, typename Alloc>
std::pair<typename S21Multiset<Key, Value, Compare, Alloc>::iterator, bool>
S21Multiset<Key, Value, Compare, Alloc>::insert(
    const S21Multiset::value_type &value) {
  return Tree<Key, Value, Compare, Alloc>::insert_node(value.first, value.second);
}

template <typename Key, typename Value, typename Compare, typename Alloc>
std::pair<typename S21Multiset<Key, Value, Compare, Alloc>::iterator, bool>
S21Multiset<Key, Value, Compare, Alloc>::insert(const Key &key,
                                                const Value &obj) {
  return Tree<Key, Value, Compare, Alloc>::insert_node(key, obj);
}

template <typename Key, typename Value, typename Compare, typename Alloc>
std::pair<typename S21Multiset<Key, Value, Compare, Alloc>::iterator, bool>
S21Multiset<Key, Value, Compare, Alloc>::insert_or_assign(const Key &key,
                                                          const Value &obj) {
  auto pr = insert(key, obj);
  if (!pr.second) (*(pr.first)).second = obj;
  return pr;
}

template <typename Key, typename Value, typename Compare, typename Alloc>
void S21Multiset<Key, Value, Compare, Alloc>::merge(S21Multiset &other) {
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

template <typename Key, typename Value, typename Compare, typename Alloc>
bool S21Multiset<Key, Value, Compare, Alloc>::contains(const Key &key) {
  auto ptr = Tree<Key, Value, Compare, Alloc>::FindNodeByKey(this->root_, key);
  return ptr != nullptr;
}

template <typename Key, typename Value, typename Compare, typename Alloc>
template <typename... Args>
S21Vector<std::pair<typename Tree<Key, Value, Compare, Alloc>::iterator, bool>>
S21Multiset<Key, Value, Compare, Alloc>::emplace(Args &&...args) {
  S21Vector<std::pair<iterator, bool>> data;
  data.push_back(insert(std::forward<Args>(args)...));
  return data;
}

}  // namespace s21

#endif  // S21_CONTAINERS_SRC_SORTED_CONTAINER_SET_CONTAINER_MULTISET_H_
