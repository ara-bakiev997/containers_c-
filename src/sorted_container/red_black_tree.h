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
//#include <windows.h>

namespace s21 {

enum RBT_colors { RED, BLACK };

template <class T>
struct RBT {
  RBT<T> *parent_{};
  RBT<T> *left_{};
  RBT<T> *right_{};
  enum RBT_colors color_ = RED;
  T data_;
};

template <class T>
class Tree {
 public:
  Tree() : root_(nullptr) {}
  ~Tree() = default;
  //_____MODIFIERS_____
  void insert_node(const T &value) {
    AddNodeByCondition(this->root_, value, this->root_);
  }
  void erase_node(T value);

  void print2D();
  void RBTPrint(RBT<T> *&node);
  void TreePrint() { RBTPrint(this->root_); };

 private:
  RBT<T> *root_{};
  //_____SUPPORT_FOR_INSERT_____
  void AddNodeByCondition(RBT<T> *&node, const T &value, RBT<T> *&parent);
  RBT<T> *CreateNode(const T &value);

  //_____SUPPORT_FOR_ERASE_____
  void DelNodeByCondition(RBT<T> *node);
  void DelNodeWithOneChild(RBT<T> *del_node, RBT<T> *child, RBT<T> *parent);
  void DelNodeWithoutChild(RBT<T> *del_node, RBT<T> *parent);

  //_____FIND_NODE_____
  RBT<T> *FindNode(RBT<T> *node, T &value);
  RBT<T> *MinNode(RBT<T> *node);
  RBT<T> *MaxNodeForTesting(RBT<T> *node);

  //_____BALANCE_FUNC____
  void BalanceInsert(RBT<T> *node, RBT<T> *parent);
  void BalanceErase(RBT<T> *parent, RBT<T> *child);

  //_____ACCESS_FUNC____
  RBT<T> *GetBro(RBT<T> *node);
  RBT<T> *GetFather(RBT<T> *node);
  RBT<T> *GetChildLeft(RBT<T> *node);
  RBT<T> *GetChildRight(RBT<T> *node);
  RBT<T> *GetRedChild(RBT<T>* node);

  //_____CHANGE_FUNC____
  void ChangeColorIfUncleRed(RBT<T> *parent, RBT<T> *bro_parent,
                             RBT<T> *grand_parent);
  void ChangeColorAfterBigRotate(RBT<T> *parent, RBT<T> *grandfather);
  void SmallRotateLeft(RBT<T> *node);
  void SmallRotateRight(RBT<T> *node);
  void BigRotateLeft(RBT<T> *node);
  void BigRotateRight(RBT<T> *node);

  //_____SUPPORT_FOR_PRINT_____
  void print2DUtil(RBT<T> *root, int space);
};

//_____MODIFIERS_____
template <typename T>
void Tree<T>::erase_node(T value) {
  RBT<T> *find = FindNode(this->root_, value);
  if (find != nullptr) {
    DelNodeByCondition(find);
  }
}

//_____SUPPORT_FOR_INSERT_____
template <typename T>
void Tree<T>::AddNodeByCondition(RBT<T> *&node, const T &value,
                                 RBT<T> *&parent) {
  if (node == nullptr) {
    node = CreateNode(value);
    if (node != parent) {
      node->parent_ = parent;
    } else {
      node->color_ = BLACK;
    }
    if (parent && parent->color_ == RED) {
      BalanceInsert(node, parent);
    }
  } else if (value < node->data_) {
    AddNodeByCondition(node->left_, value, node);
  } else if (node->data_ < value) {
    AddNodeByCondition(node->right_, value, node);
  }
}

template <typename T>
RBT<T> *Tree<T>::CreateNode(const T &value) {
  auto temp = new RBT<T>;
  temp->data_ = value;
  temp->left_ = temp->right_ = temp->parent_ = nullptr;
  return temp;
}

//_____SUPPORT_FOR_ERASE_____
template <typename T>
void Tree<T>::DelNodeByCondition(RBT<T> *node) {
  if (node->left_ && node->right_) {
    RBT<T> *change = MaxNodeForTesting(node->left_);  // node->right_ ранее
    std::swap(change->data_, node->data_);
    DelNodeByCondition(change);
  } else if (node->left_) {  // есть один левый ребенок
    //    if (node->color_ == BLACK) {
    DelNodeWithOneChild(node, node->left_, node->parent_);
    //    }
  } else if (node->right_) {  // есть один правый ребенок
    //    if (node->color_ == BLACK) {
    DelNodeWithOneChild(node, node->right_, node->parent_);
    //    }
  } else {  // лист
    if (node->color_ == RED) {
      DelNodeWithoutChild(node, node->parent_);
    } else {  // если лист черный то ппц
      RBT<T> *parent = GetFather(node);
      RBT<T> *brother_of_remote = GetBro(node);
      DelNodeWithoutChild(node, node->parent_);
      // требует доработки так как красит не верно
      if (parent && brother_of_remote) {
        BalanceErase(parent, brother_of_remote);
      }
    }
  }
}

template <typename T>
void Tree<T>::DelNodeWithOneChild(RBT<T> *del_node, RBT<T> *child,
                                  RBT<T> *parent) {
  if (del_node != root_) {
    if (parent->left_ == del_node) {
      parent->left_ = child;
    } else {
      parent->right_ = child;
    }
  } else {
    root_ = child;
  }
  child->parent_ = parent;
  child->color_ = BLACK;
  delete del_node;
}

template <typename T>
void Tree<T>::DelNodeWithoutChild(RBT<T> *del_node, RBT<T> *parent) {
  if (del_node != root_) {
    if (parent->left_ == del_node) {
      parent->left_ = nullptr;
    } else {
      parent->right_ = nullptr;
    }
  } else {
    root_ = nullptr;
  }
  delete del_node;
}

//_____БЕЗ__БАЛАНСА_____
// template <typename T>
// void Tree<T>::DelNodeByCondition(RBT<T> *node) {
//  if (!node->right_ && !node->left_) {  // удаление листа
//    if (node->parent_->left_ == node) {
//      node->parent_->left_ = nullptr;
//    } else {
//      node->parent_->right_ = nullptr;
//    }
//    delete node;
//  } else if (node->left_ && !node->right_) {
//    DelNodeWithOneChild(node, node->left_, node->parent_);
//  } else if (!node->left_ && node->right_) {
//    DelNodeWithOneChild(node, node->right_, node->parent_);
//  } else if (node->left_ && node->right_) {
//    RBT<T> *change = MinNode(node->right_);  // find min node in node->right_
//    std::swap(change->data_, node->data_);
//    DelNodeByCondition(change);
//  }
//}

//_____FIND_NODE_____
template <typename T>
RBT<T> *Tree<T>::FindNode(RBT<T> *node, T &value) {
  RBT<T> *ret = nullptr;
  if (node != nullptr) {
    if (node->data_ == value) {
      ret = node;
    } else if (value < node->data_) {
      ret = FindNode(node->left_, value);
    } else if (node->data_ < value) {
      ret = FindNode(node->right_, value);
    }
  }
  return ret;
}

template <typename T>
RBT<T> *Tree<T>::MinNode(RBT<T> *node) {
  RBT<T> *ret = nullptr;
  if (node != nullptr) {
    ret = node;
    if (node->left_) {
      ret = MinNode(node->left_);
    }
  }
  return ret;
}

template <typename T>
RBT<T> *Tree<T>::MaxNodeForTesting(RBT<T> *node) {
  RBT<T> *ret = nullptr;
  if (node != nullptr) {
    ret = node;
    if (node->right_) {
      ret = MaxNodeForTesting(node->right_);
    }
  }
  return ret;
}

//_____BALANCE_FUNC____
template <typename T>
void Tree<T>::BalanceInsert(RBT<T> *node, RBT<T> *parent) {
  RBT<T> *bro_parent = GetBro(parent);
  if (parent->color_ == RED) {  // в рекурсии нужна проверка
    if (bro_parent && bro_parent->color_ == RED) {  // что бы не было сеги
      ChangeColorIfUncleRed(parent, bro_parent, GetFather(parent));
      if (GetFather(parent) != root_) {
        BalanceInsert(GetFather(parent),
                      GetFather(parent)->parent_);  // рекурсивно для деда
      }
    } else {
      if (parent != root_) {
        if (GetFather(parent)->left_ == parent) {  // мы слева от деда
          if (parent->right_ == node) {  // мы справа от отца
            SmallRotateLeft(node);
            BigRotateRight(parent);  // т.к они поменялись местами
            ChangeColorAfterBigRotate(node, node->right_);
          } else {
            BigRotateRight(node);
            ChangeColorAfterBigRotate(parent, parent->right_);
          }
        } else {                        // мы справа от деда
          if (parent->left_ == node) {  // мы слева от отца
            SmallRotateRight(node);
            BigRotateLeft(parent);  // т.к они поменялись местами
            ChangeColorAfterBigRotate(node, node->left_);
          } else {
            BigRotateLeft(node);
            ChangeColorAfterBigRotate(parent, parent->left_);
          }
        }
      }
    }
  }
}

/*условия из статьи (https://habr.com/ru/company/otus/blog/521034/)
 * Сокращения:
 * КЧ1 — родитель красный, левый ребёнок чёрный с чёрными внуками;
 * КЧ2 — родитель красный, левый ребёнок чёрный с левым красным внуком;
 * ЧК3 — родитель чёрный, левый сын красный, у правого внука чёрные правнуки;
 * ЧК4 — родитель чёрный, левый сын красный, у правого внука левый правнук
 * красный; ЧЧ5 — родитель чёрный, левый сын чёрный с правым красным внуком;
 * ЧЧ6 — родитель чёрный, левый сын чёрный, его внуки тоже чёрные.*/
// template <typename T>
// void Tree<T>::BalanceErase(RBT<T> *parent, RBT<T> *child) {
//   if (parent->color_ == RED) {
//     if (child && child->color_ == BLACK) {
//       RBT<T> *grandson_left = child->left_;
//       RBT<T> *grandson_right = child->right_;
//       if ((grandson_left && grandson_left->color_ == BLACK) &&  // КЧ1
//           (grandson_right && grandson_right->color_ == BLACK)) {
//         std::swap(parent->color_, child->color_);
//       } else if (grandson_left && grandson_left->color_ == RED) {  // КЧ2
//         SmallRotateRight(child);
//         child->color_ = RED;
//         grandson_left->color_ = parent->color_ = BLACK;
//       }
//     }
//   } else {
//     if (child && child->color_ == RED) {
//       RBT<T> *grandson_left = GetChildLeft(child);  // внуки
//       RBT<T> *grandson_right = GetChildRight(child);
//       if ((grandson_left && grandson_left->color_ == BLACK) &&
//           (grandson_right && grandson_right->color_ == BLACK)) {
//         RBT<T> *great_grandson_left = grandson_right->left_;  // правнуки
//         RBT<T> *great_grandson_right = grandson_right->right_;
//         if ((great_grandson_left && great_grandson_left->color_ == BLACK) &&
//             (great_grandson_right &&
//              great_grandson_right->color_ == BLACK)) {  // ЧК3
//           if (parent->left_ == child) {
//             SmallRotateRight(child);
//           } else {
//             SmallRotateLeft(child);
//           }
//           child->color_ = BLACK;
//
//           grandson_right->color_ = RED;
//         } else if (great_grandson_left &&
//                    great_grandson_left->color_ ==
//                        RED) {  // ЧК4 - какая то херня внимание на повороты
//           SmallRotateLeft(grandson_right);
//           BigRotateRight(child);
//           parent->color_ = BLACK;
//           great_grandson_left->color_ = BLACK;
//         } else if (great_grandson_right &&
//                    great_grandson_right->color_ == RED) {
//           SmallRotateRight(grandson_left);
//           BigRotateRight(child);
//           parent->color_ = BLACK;
//           great_grandson_right->color_ = BLACK;
//         }
//       }
//     } else if (child && child->color_ == BLACK) {
//       RBT<T> *grandson_left = child->left_;  // внуки
//       RBT<T> *grandson_right = child->right_;
//       if (grandson_right && grandson_right->color_ == RED) {  // ЧЧ5
//         grandson_right->color_ = BLACK;
//         SmallRotateLeft(grandson_right);
//         BigRotateRight(child);
//         parent->color_ = BLACK;
//       } else if (grandson_left && grandson_left->color_ == RED) {  // ЧЧ5
//         grandson_left->color_ = BLACK;
//         SmallRotateRight(grandson_left);
//         BigRotateLeft(child);
//         parent->color_ = BLACK;
//       } else if ((grandson_left && grandson_left->color_ == BLACK) &&
//                  (grandson_right && grandson_right->color_ == BLACK)) {
//         child->color_ = RED;
//         if (parent->parent_ != root_) {
//           BalanceErase(parent->parent_, parent);
//         }
//       }
//     }
//   }
// }

// Источник: https://www.youtube.com/watch?v=T70nn4EyTrs
template <typename T>
void Tree<T>::BalanceErase(RBT<T> *parent, RBT<T> *child) {
  if (parent->color_ == RED) { // 2.1. Отец удаленной ноды красный
    RBT<T> *grandsonRed = GetRedChild(child);
    if (grandsonRed) { // 2.1.1  // Брат удаленной ноды красный
      if (parent->left_ == child) { // мы слева от деда
        if (child->right_ == grandsonRed) { // мы справа от отца
          SmallRotateLeft(grandsonRed);
          BigRotateRight(child);
          parent->color_ = BLACK;
          child->color_ = BLACK;
        } else {
          BigRotateRight(grandsonRed);
          parent->color_ = BLACK;
          child->color_ = RED;
          grandsonRed->color_ = BLACK;
        }
      } else { // мы справа от деда
        if (child->left_ == grandsonRed) { // мы слева от отца
          SmallRotateRight(grandsonRed);
          BigRotateLeft(child);
          parent->color_ = BLACK;
          child->color_ = BLACK;
        } else {
          BigRotateLeft(grandsonRed);
          parent->color_ = BLACK;
          child->color_ = RED;
          grandsonRed->color_ = BLACK;
        }
      }
    } else { // 2.1.2  // Брат удаленной ноды не красный
      std::swap(parent->color_, child->color_);
    }
  } else { // 2.2. Отец удаленной ноды черный
    if (child->color_ == RED) { // 2.2.1. Брат удаленной ноды красный
      RBT<T> *grandsonLeft = GetChildLeft(child); // внуки
      RBT<T> *grandsonRight = GetChildRight(child);

      if (grandsonLeft && grandsonLeft->color_ == BLACK) { // внук черный
        RBT<T> *great_grandsonRed = GetRedChild(grandsonLeft); // правнуки
        if (great_grandsonRed) { // 2.2.1.1. есть красный правнук
          if (parent->right_ == child) { // мы справа от отца
            SmallRotateRight(grandsonLeft);
            BigRotateLeft(child);
            great_grandsonRed->color_ = BLACK;
          } else {
            BigRotateLeft(grandsonLeft);
            child->color_ = BLACK;
            grandsonLeft->color_ = RED;
            great_grandsonRed->color_ = BLACK;
          }
        }
      } else if (grandsonRight && grandsonRight->color_ == BLACK) {  // внук черный
        RBT<T> *great_grandsonRed = GetRedChild(grandsonRight);
        if (great_grandsonRed) { // 2.2.1.1. есть красный правнук
          if (parent->left_ == child) { // мы слева от отца
            SmallRotateLeft(grandsonRight);
            BigRotateRight(child);
            great_grandsonRed->color_ = BLACK;
          } else {
            BigRotateRight(grandsonRight);
            child->color_ = BLACK;
            grandsonRight->color_ = RED;
            great_grandsonRed->color_ = BLACK;
          }

        }
      }

    }
  }




}

//_____ACCESS_FUNC____
template <typename T>
RBT<T> *Tree<T>::GetBro(RBT<T> *node) {
  RBT<T> *parent = node->parent_;
  RBT<T> *ret = nullptr;
  if (parent != nullptr) {
    if (parent->left_ != node) {
      ret = parent->left_;
    } else {
      ret = parent->right_;
    }
  }
  return ret;
}

template <typename T>
RBT<T> *Tree<T>::GetFather(RBT<T> *node) {
  return node->parent_;
}

template <typename T>
RBT<T> *Tree<T>::GetChildLeft(RBT<T> *node) {
  return node->left_;
}

template <typename T>
RBT<T> *Tree<T>::GetChildRight(RBT<T> *node) {
  return node->right_;
}

template <typename T>
RBT<T> *Tree<T>::GetRedChild(RBT<T> *node) {
  RBT<T> *ret = nullptr;
  if (node->left_ && node->left_->color_ == RED) {
    ret = node->left_;
  } else if (node->right_ && node->right_->color_ == RED) {
    ret = node->right_;
  }
  return ret;
}

template <typename T>
void Tree<T>::ChangeColorIfUncleRed(RBT<T> *parent, RBT<T> *bro_parent,
                                    RBT<T> *grand_parent) {
  parent->color_ = bro_parent->color_ = BLACK;
  if (grand_parent != this->root_) {
    grand_parent->color_ = RED;
  }
}

template <typename T>
void Tree<T>::ChangeColorAfterBigRotate(RBT<T> *parent, RBT<T> *grandfather) {
  if (parent) parent->color_ = BLACK;
  if (grandfather) grandfather->color_ = RED;
}

//_____CHANGE_FUNC____
template <typename T>
void Tree<T>::SmallRotateLeft(RBT<T> *node) {
  RBT<T> *temp = node->left_;
  RBT<T> *parent = node->parent_;
  node->left_ = parent;
  parent->right_ = temp;
  RBT<T> *grandfather = GetFather(parent);
  if (grandfather) {
    node->parent_ = grandfather;
    grandfather->left_ = node;
  }
  parent->parent_ = node;
}

template <typename T>
void Tree<T>::SmallRotateRight(RBT<T> *node) {
  RBT<T> *temp = node->right_;
  RBT<T> *parent = node->parent_;
  node->right_ = parent;
  parent->left_ = temp;
  RBT<T> *grandfather = GetFather(parent);
  if (grandfather) {
    node->parent_ = grandfather;
    grandfather->right_ = node;
  }
  parent->parent_ = node;
}

template <typename T>
void Tree<T>::BigRotateLeft(RBT<T> *node) {
  RBT<T> *parent = node->parent_;
  RBT<T> *grandfather = GetFather(parent);
  RBT<T> *temp = parent->left_;
  parent->left_ = grandfather;
  grandfather->right_ = temp;
  if (temp) {
    temp->parent_ = grandfather;
  }
  RBT<T> *great_grandfather = GetFather(grandfather);
  if (great_grandfather) {  // связка с прадедом
    if (great_grandfather->left_ == grandfather) {
      great_grandfather->left_ = parent;
    } else {
      great_grandfather->right_ = parent;
    }
  }
  parent->parent_ = great_grandfather;
  grandfather->parent_ = parent;
  if (grandfather == root_) {  // если нужно поменять рута
    root_ = parent;
  }
}

template <typename T>
void Tree<T>::BigRotateRight(RBT<T> *node) {
  RBT<T> *parent = node->parent_;
  RBT<T> *grandfather = GetFather(parent);
  RBT<T> *temp = parent->right_;
  parent->right_ = grandfather;
  grandfather->left_ = temp;
  if (temp) {
    temp->parent_ = grandfather;
  }
  RBT<T> *great_grandfather = GetFather(grandfather);
  if (great_grandfather) {  // связка с прадедом
    if (great_grandfather->left_ == grandfather) {
      great_grandfather->left_ = parent;
    } else {
      great_grandfather->right_ = parent;
    }
  }
  parent->parent_ = great_grandfather;
  grandfather->parent_ = parent;
  if (grandfather == root_) {  // если нужно поменять рута
    root_ = parent;
  }
}

//_____FUNCTIONS_FOR_PRINT_____
template <typename T>
void Tree<T>::print2DUtil(RBT<T> *root, int space) {
  // Base case
  if (root == nullptr) return;

  // Increase distance between levels
  space += 5;

  // Process right child first
  print2DUtil(root->right_, space);

  // Print current node after space
  // count
  std::cout << std::endl;
  for (int i = 5; i < space; i++) std::cout << " ";
  if (root->parent_ == nullptr) std::cout << "#";
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
template <typename T>
void Tree<T>::print2D() {
  // Pass initial space count as 0
  print2DUtil(this->root_, 0);
}

template <typename T>
void Tree<T>::RBTPrint(RBT<T> *&node) {
  if (node == nullptr) return;
  RBTPrint(node->left_);
  std::cout << node->data_ << std::endl;
  RBTPrint(node->right_);
}

}  // namespace s21

#endif  // S21_CONTAINERS_SRC_SORTED_CONTAINER_RED_BLACK_TREE_H_
