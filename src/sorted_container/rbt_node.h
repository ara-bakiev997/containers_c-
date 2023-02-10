//
// Created by Violator Emilie on 2/10/23.
//

#ifndef S21_CONTAINERS_SRC_SORTED_CONTAINER_RBT_NODE_H_
#define S21_CONTAINERS_SRC_SORTED_CONTAINER_RBT_NODE_H_

#include <cstddef>
#include <initializer_list>
#include <iostream>
#include <memory>
#include <queue>
#include <utility>
#include <valarray>
#include "tree_iterator.h"



namespace s21 {

enum RBT_colors { RED, BLACK };

template <typename Key, typename T>
struct RBT {
  RBT() = default;

  ~RBT() = default;

  RBT<const Key, T> *parent_{};
  RBT<const Key, T> *left_{};
  RBT<const Key, T> *right_{};
  enum RBT_colors color_ = RED;
  std::pair<const Key, T> *data_{};
};

}  // namespace s21



#endif //S21_CONTAINERS_SRC_SORTED_CONTAINER_RBT_NODE_H_
