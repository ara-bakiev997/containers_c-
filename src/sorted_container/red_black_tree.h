//
// Created by Lok on 04.12.2022.
//

#ifndef S21_CONTAINERS_SRC_SORTED_CONTAINER_RED_BLACK_TREE_H_
#define S21_CONTAINERS_SRC_SORTED_CONTAINER_RED_BLACK_TREE_H_

namespace s21 {

enum node_colors { RED, BLACK };

template <class T, class Alloc = std::allocator<T>> class Node {

public:
  Node()
      : parent_(nullptr), left_(nullptr), right_(nullptr), color_(BLACK),
        data_(nullptr) {}
  explicit Node(const T &data) {
    this->data_ = alloc_.allocate(sizeof(data_));
    std::copy(this->data_, data);
    color_ = BLACK;
  }
  ~Node() = default;

  Node &operator=(const Node<T> &v) {
    if (this != &v) {
      if (this->data_ != nullptr) {
        alloc_.deallocate(this->data_, sizeof(this->data_));
        this->data_ = nullptr;
      }
      std::swap(this->data_, v.data_);
    }
    return *this;
  }

  Node &operator=(Node<T> &&v) noexcept {
    if (this != &v) {
      if (this->data_ != nullptr) {
        alloc_.deallocate(this->data_, sizeof(this->data_));
        this->data_ = nullptr;
      }
      std::swap(this->data_, v.data_);
    }
    return *this;
  }

private:
  Node<T> *parent_;
  Node<T> *left_;
  Node<T> *right_;
  enum node_colors color_;
  T *data_;
  Alloc alloc_;
};
template <class T> class Tree {

public:
  Tree () {
    size_ = 0;
    root_ = new Node<T>();
  }

  ~Tree() = default;

  void insert(const T &data) {
    Node<T> temp = Node<T>(data);
    ++size_;
    if (root_ == nullptr) {
      root_ = std::swap(temp);
    } else if (temp > root_) {
      // right
    } else if (temp < root_) {
      // left
    } else {
      --size_;
    }
  }

private:
  size_t size_;
  Node<T> root_;
};
} // namespace s21

#endif // S21_CONTAINERS_SRC_SORTED_CONTAINER_RED_BLACK_TREE_H_
