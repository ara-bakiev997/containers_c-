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

  void InsertRBT(RBT<T> *&paste_here, RBT<T> *&data, RBT<T> *&parent) {
    if (paste_here == nullptr) {
      if (paste_here != parent)
        data->parent_ = parent;
      std::swap(paste_here, data);
    } else if (data->data_ > paste_here->data_) {
      InsertRBT(paste_here->right_, data, paste_here);
    } else if (data->data_ < paste_here->data_) {
      InsertRBT(paste_here->left_, data, paste_here);
    }
  }

  void Insert(const T &data) {
    auto *temp = new RBT<T>;
    temp->data_ = data;
    InsertRBT(root_, temp, root_);
    if (!temp)
      delete temp;
  }

  void Remove(const T &data) {
    auto *temp = new RBT<T>;
    temp->data_ = data;
    FindAndRemove(root_, temp, root_);
    delete temp;
  }

  void FindAndRemove(RBT<T> *&find_here, RBT<T> *&remove, RBT<T> *&parent) {
    if (find_here == nullptr) { // пустое дерево
      return;
    } else if (find_here->data_ == remove->data_) { // найден элемент
      if (find_here->right_ == nullptr &&
          find_here->left_ == nullptr) { // нет детей
        delete find_here;
        find_here = nullptr;
      } else if (find_here->right_ == nullptr) { // только левый
        delete remove;
        remove = find_here->left_;
        delete find_here;
        find_here = remove;
        find_here->parent_ = parent;
      } else if (find_here->left_ == nullptr) { // только правый
        delete remove;
        remove = find_here->right_;
        delete find_here;
        find_here = remove;
        find_here->parent_ = parent;
        // если есть оба - заменить на минимальное из правого поддерева
      } else {
        // найти минимум из правого дерева
        auto *temp = new RBT<T>;
        temp->data_ = FindMin(find_here->right_)->data_;
        temp->left_ = find_here->left_;
        temp->right_ = find_here->right_;
        temp->parent_ = parent;
        // удалить этот элемент
        delete find_here;
        find_here = nullptr;
        // скопировать сюда минимум
        std::swap(find_here, temp);
        // удалить минимум из правого поддерева
        FindAndRemove(find_here->right_, find_here, find_here);
      }
    } else if (remove->data_ >
               find_here->data_) { // искомое больше - искать справа
      FindAndRemove(find_here->right_, remove, find_here);
    } else if (remove->data_ <
               find_here->data_) { // искомое меньше - искать слева
      FindAndRemove(find_here->left_, remove, find_here);
    }
  }

  RBT<T> * FindMin(RBT<T> *&find_here) {
    if (find_here->left_ == nullptr) return find_here;
    else return FindMin(find_here->left_);
  }

  void WalkInWidth() {
    std::queue<RBT<T> *> queue;
    queue.push(this->root_);
    int count = 0;
    int sons = 1;
    RBT<T> *fake;

    while (!queue.empty()) {
      RBT<T> *temp;
      temp = queue.front();
      queue.pop();
      if (temp != fake) {
        std::cout << temp->data_ << " ";
      } else {
        std::cout << "null"
                  << " ";
      }
      ++count;
      if (count == sons) {
        std::cout << std::endl;
        count = 0;
        sons *= 2;
      }

      if (temp != fake) {
        if (temp->left_ != nullptr) {
          queue.push(temp->left_);
        } else {
          queue.push(fake);
        }

        if (temp->right_ != nullptr) {
          queue.push(temp->right_);
        } else {
          queue.push(fake);
        }
      }
    }
  }

  // Function to print binary tree in 2D
  // It does reverse inorder traversal
  void print2DUtil(RBT<T> *root, int space) {
    // Base case
    if (root == NULL)
      return;

    // Increase distance between levels
    space += 5;

    // Process right child first
    print2DUtil(root->right_, space);

    // Print current node after space
    // count
    std::cout << std::endl;
    for (int i = 5; i < space; i++)
      std::cout << " ";
    std::cout << root->data_ << "\n";

    // Process left child
    print2DUtil(root->left_, space);
  }

  // Wrapper over print2DUtil()
  void print2D() {
    // Pass initial space count as 0
    print2DUtil(this->root_, 0);
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
  RBT<T> *root_{};
};
} // namespace s21

#endif // S21_CONTAINERS_SRC_SORTED_CONTAINER_RED_BLACK_TREE_H_
