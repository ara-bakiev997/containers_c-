#ifndef S21_CONTAINERS_SRC_SORTED_CONTAINER_SET_CONTAINER_MULTISET_H_
#define S21_CONTAINERS_SRC_SORTED_CONTAINER_SET_CONTAINER_MULTISET_H_
#include <initializer_list>
#include <iostream>

#include "../sequence/s21_vector.h"
#include "red_black_tree.h"

namespace s21 {

template <typename Key, typename Compare = std::less<Key>,
          typename Alloc = std::allocator<const Key>>
class S21Multiset : public Tree<Key> {
public:
  using key_type = Key;
  using value_type = Key;
  using reference = value_type &;
  using const_reference = const value_type &;
  using iterator = typename Tree<Key>::iterator;
  using const_iterator = typename Tree<Key>::const_iterator;
  using size_type = size_t;

  S21Multiset() = default;

  S21Multiset(std::initializer_list<value_type> const &items);

  S21Multiset(const S21Multiset &other);

  S21Multiset(S21Multiset &&other) noexcept;

  ~S21Multiset() = default;

  S21Multiset &operator=(const S21Multiset &other);

  S21Multiset &operator=(S21Multiset &&other) noexcept;

  iterator insert(const value_type &value);

  void merge(S21Multiset &other);

  bool contains(const Key &key);

  size_type count(const Key &key);

  iterator lower_bound(const Key &key);

  iterator upper_bound(const Key &key);

  std::pair<iterator, iterator> equal_range(const Key &key);

  template <typename... Args>
  S21Vector<std::pair<iterator, bool>> emplace(Args &&...args);
};

template <typename Key, typename Compare, typename Alloc>
S21Multiset<Key, Compare, Alloc>::S21Multiset(
    const std::initializer_list<value_type> &items) {
  for (const auto &it : items) {
    Tree<Key>::InsertNode(it, {}, WITH_DUPLICATE);
  }
}

template <typename Key, typename Compare, typename Alloc>
S21Multiset<Key, Compare, Alloc>::S21Multiset(const S21Multiset &other)
    : Tree<Key>() {
  for (auto it = other.begin(); it != other.end(); ++it) {
    Tree<Key>::InsertNode((*it).first, {}, WITH_DUPLICATE);
  }
}

template <typename Key, typename Compare, typename Alloc>
S21Multiset<Key, Compare, Alloc>::S21Multiset(S21Multiset &&other) noexcept {
  this->swap(other);
}

template <typename Key, typename Compare, typename Alloc>
S21Multiset<Key, Compare, Alloc> &
S21Multiset<Key, Compare, Alloc>::operator=(const S21Multiset &other) {
  if (this != &other) {
    this->clear();
    for (auto it = other.begin(); it != other.end(); ++it) {
      Tree<Key>::InsertNode((*it).first, {}, WITH_DUPLICATE);
    }
  }
  return *this;
}

template <typename Key, typename Compare, typename Alloc>
S21Multiset<Key, Compare, Alloc> &
S21Multiset<Key, Compare, Alloc>::operator=(S21Multiset &&other) noexcept {
  if (this != &other) {
    this->clear();
    this->swap(other);
  }
  return *this;
}

template <typename Key, typename Compare, typename Alloc>
typename S21Multiset<Key, Compare, Alloc>::iterator
S21Multiset<Key, Compare, Alloc>::insert(const value_type &value) {
  auto pair = Tree<Key>::InsertNode(value, {}, WITH_DUPLICATE);
  return pair.first;
}

template <typename Key, typename Compare, typename Alloc>
void S21Multiset<Key, Compare, Alloc>::merge(S21Multiset &other) {
  auto it = other.begin();
  auto size = other.size();
  auto end_elem = size - 1;
  for (size_t i = 0; i < size; ++i) {
    Tree<Key>::InsertNode(it->first, {}, WITH_DUPLICATE);
    if (i < end_elem) {
      ++it;
    }
  }
  other.clear();
}

template <typename Key, typename Compare, typename Alloc>
typename S21Multiset<Key, Compare, Alloc>::size_type
S21Multiset<Key, Compare, Alloc>::count(const Key &key) {
  auto it = lower_bound(key);
  auto count = 0;
  while (it != this->end() && (*it).first == key) {
    ++count;
    ++it;
  }
  return count;
}

template <typename Key, typename Compare, typename Alloc>
bool S21Multiset<Key, Compare, Alloc>::contains(const Key &key) {
  auto ptr = Tree<Key>::FindNodeByKey(this->root_, key);
  return ptr != nullptr;
}

template <typename Key, typename Compare, typename Alloc>
template <typename... Args>
S21Vector<std::pair<typename Tree<Key>::iterator, bool>>
S21Multiset<Key, Compare, Alloc>::emplace(Args &&...args) {
  S21Vector<std::pair<iterator, bool>> data;
  data.push_back(
      Tree<Key>::InsertNode(std::forward<Args>(args)..., {}, WITH_DUPLICATE));
  return data;
}

template <typename Key, typename Compare, typename Alloc>
typename S21Multiset<Key, Compare, Alloc>::iterator
S21Multiset<Key, Compare, Alloc>::lower_bound(const Key &key) {
  return this->find(key);
}

template <typename Key, typename Compare, typename Alloc>
typename S21Multiset<Key, Compare, Alloc>::iterator
S21Multiset<Key, Compare, Alloc>::upper_bound(const Key &key) {
  auto it = this->find(key);
  if (it != this->end()) {
    auto count_eq_keys = count(key);
    while (count_eq_keys) {
      ++it;
      --count_eq_keys;
    }
  }
  return it;
}

template <typename Key, typename Compare, typename Alloc>
std::pair<typename S21Multiset<Key, Compare, Alloc>::iterator,
          typename S21Multiset<Key, Compare, Alloc>::iterator>
S21Multiset<Key, Compare, Alloc>::equal_range(const Key &key) {
  return std::make_pair(lower_bound(key), upper_bound(key));
}

} // namespace s21

#endif // S21_CONTAINERS_SRC_SORTED_CONTAINER_SET_CONTAINER_MULTISET_H_
