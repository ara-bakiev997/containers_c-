//
// Created by Lok on 04.12.2022.
//

#ifndef S21_CONTAINERS_SRC_SORTED_CONTAINER_RED_BLACK_TREE_H_
#define S21_CONTAINERS_SRC_SORTED_CONTAINER_RED_BLACK_TREE_H_

namespace s21 {

enum node_colors { RED, BLACK };

template <class T> class Node {

public:
  Node() : parent_(nullptr), left_(nullptr), right_(nullptr), color_(BLACK), data_(nullptr) {}
  Node(T *data) {}
  ~Node() = default;

private:
  Node<T> *parent_;
  Node<T> *left_;
  Node<T> *right_;
  enum node_colors color_;
  T *data_;

};
template <class T> class Tree {

public:
  Tree();
  ~Tree() = default;

private:
  size_t size_;
  Node<T> root_;
};
} // namespace s21

#endif // S21_CONTAINERS_SRC_SORTED_CONTAINER_RED_BLACK_TREE_H_
