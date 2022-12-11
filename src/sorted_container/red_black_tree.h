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

enum RBT_colors { RED, BLACK };

template <class T> struct RBT {

  RBT<T> *parent_{};
  RBT<T> *left_{};
  RBT<T> *right_{};
  enum RBT_colors color_ = BLACK;
  bool is_empty_ = true;
  T data_;
  //    RBT()
  //        : parent_(nullptr), left_(nullptr), right_(nullptr), color_(BLACK),
  //          data_(), is_empty_(true) {}
  //    explicit RBT(const T &data)
  //        : parent_(nullptr), left_(nullptr), right_(nullptr), color_(RED),
  //          data_(data), is_empty_(false) {}

  //    RBT()= default;
  //    explicit RBT(const T &data) : color_(RED), data_(data), is_empty_(false)
  //    {}

  //  RBT &operator=(const RBT &other) {
  //    if (this != &other) {
  //      this->parent_ = other.parent_;
  //      this->color_ = other.color_;
  //      this->data_ = other.data_;
  //      this->left_ = other.left_;
  //      this->right_ = other.right_;
  //    }
  //    return *this;
  //  }

  //      RBT &operator=(RBT &&other)  noexcept {
  //  //      if (this != other) {
  //          std::swap(this, other);
  //    //      this->parent_ = other.parent_;
  //    //      this->color_ = other.color_;
  //    //      this->data_ = other.data_;
  //    //      this->left_ = other.left_;
  //    //      this->right_ = other.right_;
  //  //      }
  //        return *this;
  //      }

  void Insert(const T data) {

    if (this == nullptr) {
      //      this = new RBT<T>;
      //      std::swap(this, &temp);
      //      this->is_empty_ = false;
      return;
    } else if (this->is_empty_) {
      this->data_ = data;
      this->is_empty_ = false;
      return;
    } else if (this->data_ > data) {
      this->right_ = new RBT<T>;
      right_->data_ = data;
    } else if (this->data_ < data) {
      this->left_->Insert(data);
    }
  }

  void InsertRBT() {}

  void RBTPrint() {
    if (this == nullptr)
      return;
    this->right_->RBTPrint();
    std::cout << this->data_ << std::endl;
    this->left_->RBTPrint();
  }
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

  void fu() {}

  void InsertRBT(RBT<T>* & paste_here, RBT<T>* & node) {
    std::swap(paste_here, node);
  }

  void Insert(const T &data) {
    auto *temp = new RBT<T>;
    temp->data_ = data;

    if (this->root_ == nullptr) {
      //      this->root_ = temp;
      InsertRBT(this->root_, temp);
//      std::swap(this->root_, temp); // init
    } else if (temp->data_ > this->root_->data_) {
      // right
      InsertRBT(this->root_->right_, temp);
      //      this->root_->right_ = temp;
    } else if (temp->data_ < this->root_->data_) {
      // left
      InsertRBT(this->root_->left_, temp);
    }
  }

  void Remove(const T &data) {}

  RBT<T> *GetRoot() { return this->root_; }

private:
  RBT<T> *root_;
};
} // namespace s21

#endif // S21_CONTAINERS_SRC_SORTED_CONTAINER_RED_BLACK_TREE_H_
