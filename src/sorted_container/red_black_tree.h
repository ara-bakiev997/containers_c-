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

enum DirectionOfRotation { LEFT, RIGHT };

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
  void SmallRotate(RBT<T> *node, DirectionOfRotation direction);
  void BigRotate(RBT<T> *node, DirectionOfRotation direction);

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
//    RBT<T> *change = MinNode(node->right_);  // node->right_ ранее

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
    } else {
      RBT<T> *parent = GetFather(node);
      RBT<T> *brother_of_remote = GetBro(node);
      DelNodeWithoutChild(node, node->parent_);
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
            SmallRotate(node, LEFT);
            BigRotate(parent, RIGHT);  // т.к они поменялись местами
            ChangeColorAfterBigRotate(node, node->right_);
          } else {
            BigRotate(node, RIGHT);
            ChangeColorAfterBigRotate(parent, parent->right_);
          }
        } else {                        // мы справа от деда
          if (parent->left_ == node) {  // мы слева от отца
            SmallRotate(node, RIGHT);
            BigRotate(parent, LEFT);  // т.к они поменялись местами
            ChangeColorAfterBigRotate(node, node->left_);
          } else {
            BigRotate(node, LEFT);
            ChangeColorAfterBigRotate(parent, parent->left_);
          }
        }
      }
    }
  }
}

// Источник: https://www.youtube.com/watch?v=T70nn4EyTrs
template <typename T>
void Tree<T>::BalanceErase(RBT<T> *parent, RBT<T> *child) {
  if (parent->color_ == RED) { // 2.1. Отец удаленной ноды красный
    RBT<T> *grandsonRed = GetRedChild(child);
    if (grandsonRed) { // 2.1.1  // Брат удаленной ноды красный
      if (parent->left_ == child) { // мы слева от деда
        if (child->right_ == grandsonRed) { // мы справа от отца
          SmallRotate(grandsonRed, LEFT);
          BigRotate(child, RIGHT);
          parent->color_ = BLACK;
          child->color_ = BLACK;
        } else {
          BigRotate(grandsonRed, RIGHT);
          parent->color_ = BLACK;
          child->color_ = RED;
          grandsonRed->color_ = BLACK;
        }
      } else { // мы справа от деда
        if (child->left_ == grandsonRed) { // мы слева от отца
          SmallRotate(grandsonRed, RIGHT);
          BigRotate(child, LEFT);
          parent->color_ = BLACK;
          child->color_ = BLACK;
        } else {
          BigRotate(grandsonRed, LEFT);
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

      if (grandsonLeft && grandsonLeft->color_ == BLACK) { // внук черный // добавить проверку на красного правнука
        RBT<T> *great_grandsonRed = GetRedChild(grandsonLeft); // правнуки
        if (great_grandsonRed) { // 2.2.1.1. есть красный правнук
          if (parent->right_ == child) { // мы справа от отца
//            SmallRotateRight(grandsonLeft); // как будто не нужно /// надеюсь тесты не заходят
            BigRotate(grandsonLeft, LEFT);
//            great_grandsonRed->color_ = BLACK;
            child->color_ = BLACK;
            parent->color_ = RED;
            BalanceErase(parent, parent->right_);
          } else { // мб излишне
            BigRotate(grandsonLeft, LEFT);
            child->color_ = BLACK;
            grandsonLeft->color_ = RED;
            great_grandsonRed->color_ = BLACK;
//            child->color_ = BLACK;///// ДОБАВИТЬ скорее всего
//            parent->color_ = RED; //grandsonRight->color_ = RED;
//            BalanceErase(parent, parent->left_); ///// ДОБАВИТЬ
          }
        } else { // 2.2.1.2 когда нет красного правнука
          if (parent->left_ == child) {
            BigRotate(grandsonLeft, RIGHT); // внимание
            child->color_ = BLACK;
//            grandsonLeft->color_ = RED;
            parent->color_ = RED; //grandsonRight->color_ = RED;
            BalanceErase(parent, parent->left_);
          } else {
            BigRotate(grandsonLeft, LEFT);
            child->color_ = BLACK;
            parent->color_ = RED;
            BalanceErase(parent, parent->right_);
//            grandsonLeft->color_ = RED;
          }
        }
      } else if (grandsonRight && grandsonRight->color_ == BLACK) {  // внук черный  // скорее всего не нужно когда мы работаем с max в левом поддереве
        RBT<T> *great_grandsonRed = GetRedChild(grandsonRight);
        if (great_grandsonRed) { // 2.2.1.1. есть красный правнук
          if (parent->left_ == child) { // мы слева от отца
            SmallRotate(grandsonRight, LEFT);
            BigRotate(child, RIGHT);
            great_grandsonRed->color_ = BLACK;
          } else {
            BigRotate(grandsonRight, RIGHT);
            child->color_ = BLACK;
            grandsonRight->color_ = RED;
            great_grandsonRed->color_ = BLACK;
          }
        } else { // 2.2.1.2 когда нет красного правнука
          if (parent->left_ == child) {
            BigRotate(grandsonRight, RIGHT); // внимание
            child->color_ = BLACK;
            grandsonRight->color_ = RED;
          } else {
            BigRotate(grandsonRight, LEFT);
            child->color_ = BLACK;
            grandsonRight->color_ = RED;
          }
        }
      }
    } else { // 2.2.2. Брат удаленной ноды черный
      RBT<T> *grandsonRed = GetRedChild(child);
      if (grandsonRed) { // 2.2.2.1 у брата удаленной ноды есть красные дети
        if (parent->left_ == child) { // мы слева от деда
          if (child->right_ == grandsonRed) { // мы справа от отца
            SmallRotate(grandsonRed, LEFT);
            BigRotate(child, RIGHT);
            grandsonRed->color_ = BLACK;
          } else {
            BigRotate(grandsonRed, RIGHT);
            grandsonRed->color_ = BLACK;
          }
        } else { // мы справа от деда
          if (child->left_ == grandsonRed) { // мы слева от отца
            SmallRotate(grandsonRed, RIGHT);
            BigRotate(child, LEFT);
            grandsonRed->color_ = BLACK;
          } else {
            BigRotate(grandsonRed, LEFT);
            grandsonRed->color_ = BLACK;
          }
        }
      } else {  // 2.2.2.2 у брата удаленной ноды нет красныех детей
        child->color_ = RED;
        // рекурсивно вверх
        if (parent != root_) { // рекурсивно к деду
          RBT<T> *grandfather = GetFather(parent);
          RBT<T> *brother_of_parent = GetBro(parent);
          if (grandfather && brother_of_parent) {
            BalanceErase(grandfather, brother_of_parent);
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
RBT<T> *Tree<T>::GetRedChild(RBT<T> *node) { // нужно упростить может быть не нужна проверка с дедушкой
  RBT<T> *patent = node->parent_;
  RBT<T> *grandFather = node->parent_->parent_;
  RBT<T> *ret = nullptr;

  if (grandFather && grandFather->left_ == patent) { // мы слева от дедушки
    if (patent->left_ == node) { // мы слева от отца
      if (node->left_ && node->left_->color_ == RED) {
        ret = node->left_;
      } else if (node->right_ && node->right_->color_ == RED) {
        ret = node->right_;
      }
    } else { // мы справа от отца
      if (node->right_ && node->right_->color_ == RED) {
        ret = node->right_;
      } else if (node->left_ && node->left_->color_ == RED) {
        ret = node->left_;
      }
    }
  } else { // мы справа от дедушки
    if (patent->right_ == node) { // мы справа от отца
      if (node->right_ && node->right_->color_ == RED) {
        ret = node->right_;
      } else if (node->left_ && node->left_->color_ == RED) {
        ret = node->left_;
      }
    } else { // мы слева от отца
      if (node->left_ && node->left_->color_ == RED) {
        ret = node->left_;
      } else if (node->right_ && node->right_->color_ == RED) {
        ret = node->right_;
      }
    }
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
void Tree<T>::SmallRotate(RBT<T> *node, DirectionOfRotation direction) {
  RBT<T> *temp = (direction == RIGHT) ? node->right_ : node->left_;
  RBT<T> *parent = node->parent_;
  if (direction == RIGHT) {
    node->right_ = parent;
    parent->left_ = temp;
  } else {
    node->left_ = parent;
    parent->right_ = temp;
  }
  RBT<T> *grandfather = GetFather(parent);
  if (grandfather) {
    node->parent_ = grandfather;
    if (direction == RIGHT) {
      grandfather->right_ = node;
    } else {
      grandfather->left_ = node;
    }
  }
  parent->parent_ = node;
}

template <typename T>
void Tree<T>::BigRotate(RBT<T> *node, DirectionOfRotation direction) {
  RBT<T> *parent = node->parent_;
  RBT<T> *grandfather = GetFather(parent);
  RBT<T> *temp = (direction == RIGHT) ? parent->right_ : parent->left_;
  if (direction == RIGHT) {
    parent->right_ = grandfather;
    grandfather->left_ = temp;
  } else {
    parent->left_ = grandfather;
    grandfather->right_ = temp;
  }
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
