//
// Created by Lok on 04.12.2022.
//

#ifndef S21_CONTAINERS_SRC_SORTED_CONTAINER_RED_BLACK_TREE_H_
#define S21_CONTAINERS_SRC_SORTED_CONTAINER_RED_BLACK_TREE_H_

#include <cstddef>
#include <initializer_list>
#include <iostream>
#include <queue>
#include <utility>
#include <valarray>

namespace s21 {

enum RBT_colors { RED, BLACK };

template <class T> struct RBT {

  RBT<T> *parent_{};
  RBT<T> *left_{};
  RBT<T> *right_{};
  enum RBT_colors color_ = BLACK;
  T data_;
};

template <class T> class Tree {

public:
  Tree() { this->root_ = nullptr; }

  Tree &operator=(const Tree &other) {
    if (this != &other)
      this->root_ = other.root_;
    return *this;
  }

  ~Tree() = default;

  void InsertRBT(RBT<T> *&paste_here, RBT<T> *&paste_this, RBT<T> *&parent) {
    if (paste_here == nullptr) {
      if (paste_here != parent)
        paste_this->parent_ = parent;
      std::swap(paste_here, paste_this);
    } else if (paste_this->data_ > paste_here->data_) {
      InsertRBT(paste_here->right_, paste_this, paste_here);
    } else if (paste_this->data_ < paste_here->data_) {
      InsertRBT(paste_here->left_, paste_this, paste_here);
    }
  }

  void Insert(const T &data) {
    auto *temp = new RBT<T>;
    temp->data_ = data;
    InsertRBT(root_, temp, root_);
    if (!temp)
      delete temp;
  }

  void Remove(const T &data) {}

  void WalkInWidth() {
    std::queue<RBT<T> *> queue;
    queue.push(this->root_);
    int count = 1;
    int sons = 1;

    while (!queue.empty()) {
      RBT<T> *temp;
      temp = queue.front();
      queue.pop();
      if (temp != nullptr) {
        std::cout << temp->data_ << std::endl;
      } else {

      }

      if (temp->left_ != nullptr)
        queue.push(temp->left_);
      else
        queue.push(nullptr);
      if (temp->right_ != nullptr)
        queue.push(temp->right_);
      else
        queue.push(nullptr);
    }
  }

  void RBTPrint(RBT<T> *&node) {
    if (node == nullptr)
      return;
    RBTPrint(node->left_);
    std::cout << node->data_ << std::endl;
    RBTPrint(node->right_);
  }

  void TreePrint() { RBTPrint(this->root_); };

  RBT<T> *GetRoot() { return this->root_; }

private:
  RBT<T> *root_;
};
} // namespace s21

#endif // S21_CONTAINERS_SRC_SORTED_CONTAINER_RED_BLACK_TREE_H_
