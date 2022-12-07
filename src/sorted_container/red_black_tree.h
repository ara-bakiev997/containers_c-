//
// Created by Lok on 04.12.2022.
//

#ifndef S21_CONTAINERS_SRC_SORTED_CONTAINER_RED_BLACK_TREE_H_
#define S21_CONTAINERS_SRC_SORTED_CONTAINER_RED_BLACK_TREE_H_

#include <cstddef>
#include <initializer_list>
#include <iostream>
#include <utility>
#include <valarray>

namespace s21 {

enum node_colors { RED, BLACK };

template <class T> struct Node {

  Node<T> *parent_{};
  Node<T> *left_{};
  Node<T> *right_{};
  enum node_colors color_;
  T data_;
  Node()
      : parent_(nullptr), left_(nullptr), right_(nullptr), color_(BLACK),
        data_() {}
  explicit Node(const T &data)
      : parent_(nullptr), left_(nullptr), right_(nullptr), color_(RED),
        data_(data) {}
  Node &operator=(const Node &other) {
    if (this != &other) {
      this->parent_ = other.parent_;
      this->color_ = other.color_;
      this->data_ = other.data_;
      this->left_ = other.left_;
      this->right_ = other.right_;
    }
  }
};

template <class T> class Tree {

public:
  Tree() { this->root_ = nullptr; }

  Tree &operator=(const Tree &other) {
    //    if (this->root_ != other.root_)
    this->root_ = other.root_;
    return *this;
  }

  ~Tree() = default;

  void Insert(const T &data) {
    auto *temp = new Node<T>(data);
    //    temp->data_ = data;
    if (this->root_ == nullptr) {
//      this->root_ = temp;
      std::swap(this->root_, temp);
    } else if (temp->data_ > this->root_->data_) {
      // right
      std::swap(this->root_->right_, temp);
//      this->root_->right_ = temp;
    } else if (temp->data_ < this->root_->data_) {
      // left
      std::swap(this->root_->left_, temp);
    }
  }

  void Remove(const T &data) {}

  Node<T> *GetRoot() { return this->root_; }

private:
  Node<T> *root_;
};
} // namespace s21

#endif // S21_CONTAINERS_SRC_SORTED_CONTAINER_RED_BLACK_TREE_H_
