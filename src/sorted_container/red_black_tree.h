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
#include <windows.h>

namespace s21 {

enum RBT_colors { RED, BLACK };

template <class T> struct RBT {

  RBT<T> *parent_{};
  RBT<T> *left_{};
  RBT<T> *right_{};
  enum RBT_colors color_ = RED;
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

  /**
   * рекурсивно идет по дереву и вставляет элемент больше вправо меньше влево
   * @param paste_here попробовать вставить сюда НОДУ
   * @param data НОДА с новой датой
   * @param parent родитель, при первой передаче передается рут
   * @return не реализовано
   */
  RBT<T> *InsertRBT(RBT<T> *&paste_here, RBT<T> *&data, RBT<T> *&parent) {
    if (paste_here == nullptr) { // если нул можно добавить сюда
      if (paste_here != parent) { // проверка рута
        data->parent_ = parent;   // добавить родителя
      } else {
        data->color_ = BLACK; // рут черный
      }
      std::swap(paste_here, data); // добавление элемента

      if (paste_here->parent_ != nullptr) { // проверка рута
        BalanceInsert(paste_here); // пишем в дату новый рут или нулл
      }

    } else if (data->data_ > paste_here->data_) {
      InsertRBT(paste_here->right_, data, paste_here);
    } else if (data->data_ < paste_here->data_) {
      InsertRBT(paste_here->left_, data, paste_here);
    }
    return paste_here;
  }

  void Insert(const T &data) {
    auto *temp = new RBT<T>;
    temp->data_ = data;
    root_ = InsertRBT(root_, temp, root_);
    if (!temp)
      delete temp;
  }

  void BalanceInsert(RBT<T> *&balance_RBT) {
    if (GetParent(balance_RBT) == nullptr)
      return;

    if (GetParent(balance_RBT)->color_ == RED) { // балансируем

      // first r-r-B-r -> r-b-R-b if B -root B -> B
      if (GetParent(balance_RBT)->color_ ==
          GetBrotherColor(GetParent(balance_RBT))) { // red == red
        RedParentRedUncleFix(balance_RBT);

        // second r-r-B-b -> r-B-r-b / if B root -> change root
      } else { // parent and uncle is red and black

        auto temp = new RBT<T>;
        temp->parent_ = GetGrandParent(balance_RBT); // temp = B

        if (GetParent(balance_RBT) == GetGrandParent(balance_RBT)->left_) {
          // вставка влево поворачиваем вправо
          if (balance_RBT == GetParent(balance_RBT)->right_) { // малый поворот
            auto temp_parent = new RBT<T>;
            temp_parent->data_ = balance_RBT->parent_->data_;
            auto temp_x = new RBT<T>;
            temp_x->data_ = balance_RBT->data_;

            balance_RBT->parent_->parent_->left_ = temp_x;
            temp_x->parent_ = balance_RBT->parent_->parent_;
            temp_x->left_ = temp_parent;

            temp_parent->parent_ = temp_x;
            BalanceInsert(temp_parent);
          } else {
            ChangeMainParentLink(balance_RBT);
            RotationRight(balance_RBT, temp);
          }

        } else {
          // вставка вправо поворачиваем влево
          if (balance_RBT == GetParent(balance_RBT)->left_) { // малый поворот

            auto temp_parent = new RBT<T>;
            temp_parent->data_ = balance_RBT->parent_->data_;
            auto temp_x = new RBT<T>;
            temp_x->data_ = balance_RBT->data_;
            balance_RBT->parent_->parent_->right_ = temp_x;
            temp_x->parent_ = balance_RBT->parent_->parent_;
            temp_x->right_ = temp_parent;
            temp_parent->parent_ = temp_x;
            BalanceInsert(temp_parent);


//            auto temp_small = new RBT<T>;
//            temp_small->parent_ = GetParent(balance_RBT);
//            GetGrandParent(balance_RBT)->right_ = balance_RBT;
//            balance_RBT->parent_ = temp_small->parent_->parent_;
//            balance_RBT->right_ = temp_small->parent_;
//            balance_RBT->right_->parent_ = balance_RBT;
//            std::swap(balance_RBT->right_->left_, temp_small->left_);
//            delete temp_small;
//            BalanceInsert(balance_RBT->right_);
          } else {
            ChangeMainParentLink(balance_RBT);
            RotationLeft(balance_RBT, temp);
          }

        }
      }
    }
  }

  void RedParentRedUncleFix(RBT<T> *&balance_RBT) {
    GetParent(balance_RBT)->color_ = BLACK;
    GetBrother(GetParent(balance_RBT))->color_ = BLACK;

    if (!IsRoot(GetGrandParent(balance_RBT))) { // not root
      GetGrandParent(balance_RBT)->color_ = RED;
      BalanceInsert(GetGrandParent(balance_RBT)); // балансируем выше
    }
  }

  void RotationRight(RBT<T> *&balance_RBT, RBT<T> *&temp) {
    GetParent(balance_RBT)->parent_ = GetGrandParent(balance_RBT)->parent_;
    temp->right_ = GetParent(balance_RBT)->right_;
    GetParent(balance_RBT)->right_ = temp->parent_;
    GetParent(balance_RBT)->right_->parent_ = GetParent(balance_RBT);
    GetParent(balance_RBT)->right_->left_ = temp->right_;
    temp->parent_ = temp->right_ = temp->left_ = nullptr;
    delete temp;
    GetParent(balance_RBT)->color_ = BLACK;
    GetParent(balance_RBT)->right_->color_ = RED;
  }

  void RotationLeft(RBT<T> *&balance_RBT, RBT<T> *&temp) {
    GetParent(balance_RBT)->parent_ = GetGrandParent(balance_RBT)->parent_;
    temp->left_ = GetParent(balance_RBT)->left_;
    GetParent(balance_RBT)->left_ = temp->parent_;
    GetParent(balance_RBT)->left_->parent_ = balance_RBT->parent_;
    GetParent(balance_RBT)->left_->right_ = temp->left_;
    temp->parent_ = temp->right_ = temp->left_ = nullptr;
    delete temp;
    balance_RBT->parent_->color_ = BLACK;
    balance_RBT->parent_->left_->color_ = RED;
  }

  void ChangeMainParentLink(RBT<T> *&balance_RBT) {

    if (GetGrandParent(balance_RBT)->parent_ != nullptr) { // не рут
      // замена указателя главного родителя
      if (GetGrandParent(balance_RBT)->parent_->left_ ==
          GetGrandParent(balance_RBT)) { // замена левого
        GetGrandParent(balance_RBT)->parent_->left_ =
            GetParent(balance_RBT); // main parent = A
      } else {                      // замена правого
        GetGrandParent(balance_RBT)->parent_->right_ =
            GetParent(balance_RBT); // main parent = A
      }
    } else { // рут/ как заменить рут
      // замена указателя главного родителя
      this->root_ = GetParent(balance_RBT); // root = A
    }
  }

  RBT<T> *&GetParent(RBT<T> *&node) { return node->parent_; }

  RBT<T> *&GetGrandParent(RBT<T> *&node) { return GetParent(node)->parent_; }

  RBT<T> *GetBrother(RBT<T> *&node) {
    if (node->parent_ == nullptr) {
      return nullptr;
    } else {
      if (node == node->parent_->left_)
        return node->parent_->right_;
      else
        return node->parent_->left_;
    }
  }

  RBT_colors GetBrotherColor(RBT<T> *&node) {
    if (GetBrother(node) == nullptr) {
      return BLACK;
    } else
      return GetBrother(node)->color_;
  }

  bool IsRoot(RBT<T> *&node) {
    if (node->parent_ == nullptr)
      return true;
    else
      return false;
  }

  //  bool IsRoot (RBT<T> *node) {
  //    if (node->parent_ == nullptr) return true;
  //    else return false;
  //  }

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
        //        auto *temp = new RBT<T>;
        //        temp->data_ = FindMin(find_here->right_)->data_;
        //        temp->left_ = find_here->left_;
        //        temp->right_ = find_here->right_;
        //        temp->parent_ = parent;
        //        // удалить этот элемент
        //        delete find_here;
        //        find_here = nullptr;
        //        // скопировать сюда минимум
        //        std::swap(find_here, temp);

        find_here->data_ = FindMin(find_here->right_)->data_;
        // удалить минимум из правого поддерева
        auto *temp = new RBT<T>;
        temp->data_ = find_here->data_;
        FindAndRemove(find_here->right_, temp, find_here);
        delete temp;
      }
    } else if (remove->data_ >
               find_here->data_) { // искомое больше - искать справа
      FindAndRemove(find_here->right_, remove, find_here);
    } else if (remove->data_ <
               find_here->data_) { // искомое меньше - искать слева
      FindAndRemove(find_here->left_, remove, find_here);
    }
  }

  RBT<T> *FindMin(RBT<T> *&find_here) {
    if (find_here->left_ == nullptr)
      return find_here;
    else
      return FindMin(find_here->left_);
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
    if (root->parent_ == nullptr)
      std::cout << "#";
    if (root->color_ == BLACK) {
      std::cout << root->data_ << "_B"
                << "\n";
    } else {
      std::cout << root->data_ << "_R"
                << "\n";
    }

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
