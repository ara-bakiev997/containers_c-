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
    add_node_by_condition(this->root_, value, this->root_);
  }
  void erase_node(T value);

  void print2D();
  void RBTPrint(RBT<T> *&node);
  void TreePrint() { RBTPrint(this->root_); };

 private:
  RBT<T> *root_{};
  //_____SUPPORT_FOR_INSERT_____
  void add_node_by_condition(RBT<T> *&node, const T &value, RBT<T> *&parent);
  RBT<T> *create_node(const T &value);

  //_____SUPPORT_FOR_ERASE_____
  void del_node_by_condition(RBT<T> *node);
  void del_node_with_one_child(RBT<T> *del_node, RBT<T> *child, RBT<T> *parent);
  void del_node_without_child(RBT<T> *del_node, RBT<T> *parent);

  //_____FIND_NODE_____
  RBT<T> *find_node(RBT<T> *node, T &value);
  RBT<T> *min_node(RBT<T> *node);
  RBT<T> *max_node_for_testing(RBT<T> *node);

  //_____BALANCE_FUNC____
  void balance_insert(RBT<T> *node, RBT<T> *parent);
  void balance_erase(RBT<T> *node);

  //_____ACCESS_FUNC____
  RBT<T> *get_bro(RBT<T> *node);
  RBT<T> *get_father(RBT<T> *node);
  RBT<T> *get_child_left(RBT<T> *node);
  RBT<T> *get_child_right(RBT<T> *node);

  //_____CHANGE_FUNC____
  void change_color(RBT<T> *parent, RBT<T> *bro_parent, RBT<T> *grand_parent);
  void small_rotate_left(RBT<T> *node, RBT<T> *parent);
  void small_rotate_right(RBT<T> *node, RBT<T> *parent);
  void big_rotate_left(RBT<T> *node, RBT<T> *parent);
  void big_rotate_right(RBT<T> *node, RBT<T> *parent);

  //_____SUPPORT_FOR_PRINT_____
  void print2DUtil(RBT<T> *root, int space);
};

//_____MODIFIERS_____
template <typename T>
void Tree<T>::erase_node(T value) {
  RBT<T> *find = find_node(this->root_, value);
  if (find != nullptr) {
    del_node_by_condition(find);
  }
}

//_____SUPPORT_FOR_INSERT_____
template <typename T>
void Tree<T>::add_node_by_condition(RBT<T> *&node, const T &value,
                                    RBT<T> *&parent) {
  if (node == nullptr) {
    node = create_node(value);
    if (node != parent) {
      node->parent_ = parent;
    } else {
      root_ = node;
      node->color_ = BLACK;
    }
    if (parent->color_ == RED) {  // возможна сега!!!
      balance_insert(node, parent);
    }
  } else if (value < node->data_) {
    add_node_by_condition(node->left_, value, node);
  } else if (node->data_ < value) {
    add_node_by_condition(node->right_, value, node);
  }
}

template <typename T>
RBT<T> *Tree<T>::create_node(const T &value) {
  auto temp = new RBT<T>;
  temp->data_ = value;
  temp->left_ = temp->right_ = temp->parent_ = nullptr;
  return temp;
}

//_____SUPPORT_FOR_ERASE_____
template <typename T>
void Tree<T>::del_node_by_condition(RBT<T> *node) {
  if (node->left_ && node->right_) {
    RBT<T> *change = max_node_for_testing(node->left_);  // node->right_ ранее
    std::swap(change->data_, node->data_);
    del_node_by_condition(change);
  } else if (node->left_ && !node->right_) {  // есть один левый ребенок
    if (node->color_ == BLACK) {
      del_node_with_one_child(node, node->left_, node->parent_);
    }
  } else if (!node->left_ && node->right_) {  // есть один правый ребенок
    if (node->color_ == BLACK) {
      del_node_with_one_child(node, node->right_, node->parent_);
    }
  } else {  // лист
    if (node->color_ == RED) {
      del_node_without_child(node, node->parent_);
    } else {  // если лист черный то ппц
      RBT<T> *parent = get_father(node);
      del_node_without_child(node, node->parent_);
      // требует доработки так как красит не верно
      if (parent != root_) {
        balance_erase(parent);
      }
    }
  }
}

template <typename T>
void Tree<T>::del_node_with_one_child(RBT<T> *del_node, RBT<T> *child,
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
  std::swap(del_node->color_, child->color_);
  delete del_node;
}

template <typename T>
void Tree<T>::del_node_without_child(RBT<T> *del_node, RBT<T> *parent) {
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
// void Tree<T>::del_node_by_condition(RBT<T> *node) {
//  if (!node->right_ && !node->left_) {  // удаление листа
//    if (node->parent_->left_ == node) {
//      node->parent_->left_ = nullptr;
//    } else {
//      node->parent_->right_ = nullptr;
//    }
//    delete node;
//  } else if (node->left_ && !node->right_) {
//    del_node_with_one_child(node, node->left_, node->parent_);
//  } else if (!node->left_ && node->right_) {
//    del_node_with_one_child(node, node->right_, node->parent_);
//  } else if (node->left_ && node->right_) {
//    RBT<T> *change = min_node(node->right_);  // find min node in node->right_
//    std::swap(change->data_, node->data_);
//    del_node_by_condition(change);
//  }
//}

//_____FIND_NODE_____
template <typename T>
RBT<T> *Tree<T>::find_node(RBT<T> *node, T &value) {
  RBT<T> *ret = nullptr;
  if (node != nullptr) {
    if (node->data_ == value) {
      ret = node;
    } else if (value < node->data_) {
      ret = find_node(node->left_, value);
    } else if (node->data_ < value) {
      ret = find_node(node->right_, value);
    }
  }
  return ret;
}

template <typename T>
RBT<T> *Tree<T>::min_node(RBT<T> *node) {
  RBT<T> *ret = nullptr;
  if (node != nullptr) {
    ret = node;
    if (node->left_) {
      ret = min_node(node->left_);
    }
  }
  return ret;
}

template <typename T>
RBT<T> *Tree<T>::max_node_for_testing(RBT<T> *node) {
  RBT<T> *ret = nullptr;
  if (node != nullptr) {
    ret = node;
    if (node->right_) {
      ret = max_node_for_testing(node->right_);
    }
  }
  return ret;
}

//_____BALANCE_FUNC____
template <typename T>
void Tree<T>::balance_insert(RBT<T> *node, RBT<T> *parent) {
  RBT<T> *bro_parent = get_bro(parent);
  if (parent->color_ == RED) {  // в рекурсии нужна проверка
    if (bro_parent && bro_parent->color_ == RED) {  // что бы не было сеги
      change_color(parent, bro_parent, get_father(parent));
      if (get_father(parent) != root_) {
        balance_insert(get_father(parent),
                       get_father(parent)->parent_);  // рекурсивно для деда
      }
    } else {
      if (parent != root_) {
        if (get_father(parent)->left_ == parent) {  // мы слева от деда
          if (parent->right_ == node) {  // мы справа от отца
            small_rotate_left(node, parent);
            big_rotate_right(parent, node);  // т.к они поменялись местами
          } else {
            big_rotate_right(node, parent);
          }
        } else {                        // мы справа от деда
          if (parent->left_ == node) {  // мы слева от отца
            small_rotate_right(node, parent);
            big_rotate_left(parent, node);  // т.к они поменялись местами
          } else {
            big_rotate_left(node, parent);
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
template <typename T>
void Tree<T>::balance_erase(RBT<T> *node) {
  if (node->color_ == RED) {
    RBT<T> *left_child = node->left_;
    if (left_child && left_child->color_ == BLACK) {
      RBT<T> *grandson_left = left_child->left_;
      RBT<T> *grandson_right = left_child->right_;
      if ((grandson_left && grandson_left->color_ == BLACK) &&  // КЧ1
          (grandson_right && grandson_right->color_ == BLACK)) {
        std::swap(node->color_, left_child->color_);
      } else if (grandson_left && grandson_left->color_ == RED) {  // КЧ2
        small_rotate_right(left_child, node);
        left_child->color_ = RED;
        grandson_left->color_ = node->color_ = BLACK;
      }
    }
  } else {
    RBT<T> *left_child = node->left_;  // сын
    if (left_child && left_child->color_ == RED) {
      RBT<T> *grandson_left = left_child->left_;  // внуки
      RBT<T> *grandson_right = left_child->right_;
      if ((grandson_left && grandson_left->color_ == BLACK) &&
          (grandson_right && grandson_right->color_ == BLACK)) {
        RBT<T> *great_grandson_left = grandson_right->left_;  // правнуки
        RBT<T> *great_grandson_right = grandson_right->right_;
        if ((great_grandson_left && great_grandson_left->color_ == BLACK) &&
            (great_grandson_right &&
             great_grandson_right->color_ == BLACK)) {  // ЧК3
          small_rotate_right(left_child, node);
          left_child->color_ = BLACK;
          grandson_right->color_ = RED;
        } else if (great_grandson_left &&
                   great_grandson_left->color_ ==
                       RED) {  // ЧК4 - какая то херня внимание на повороты
          small_rotate_left(grandson_right, left_child);
          big_rotate_right(left_child, grandson_right);
          node->color_ = BLACK;
          great_grandson_left->color_ = BLACK;
        }
      }
    } else if (left_child && left_child->color_ == BLACK) {
      RBT<T> *grandson_left = left_child->left_;  // внуки
      RBT<T> *grandson_right = left_child->right_;
      if (grandson_left && grandson_right &&
          grandson_right->color_ == RED) {  // ЧЧ5
        grandson_right->color_ = BLACK;
        small_rotate_left(grandson_right, left_child);
        big_rotate_right(left_child, grandson_right);
        node->color_ = BLACK;
      } else if ((grandson_left && grandson_left->color_ == BLACK) &&
                 (grandson_right && grandson_right->color_ == BLACK)) {
        left_child->color_ = RED;
        balance_erase(node->parent_);
      }
    }
  }
}

//_____ACCESS_FUNC____
template <typename T>
RBT<T> *Tree<T>::get_bro(RBT<T> *node) {
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
RBT<T> *Tree<T>::get_father(RBT<T> *node) {
  return node->parent_;
}

template <typename T>
RBT<T> *Tree<T>::get_child_left(RBT<T> *node) {
  return node->left_;
}

template <typename T>
RBT<T> *Tree<T>::get_child_right(RBT<T> *node) {
  return node->right_;
}

template <typename T>
void Tree<T>::change_color(RBT<T> *parent, RBT<T> *bro_parent,
                           RBT<T> *grand_parent) {
  parent->color_ = bro_parent->color_ = BLACK;
  if (grand_parent != this->root_) {
    grand_parent->color_ = RED;
  }
}

//_____CHANGE_FUNC____
template <typename T>
void Tree<T>::small_rotate_left(RBT<T> *node, RBT<T> *parent) {
  RBT<T> *temp = node->left_;
  node->left_ = parent;
  parent->right_ = temp;
  RBT<T> *grandfather = get_father(parent);
  if (grandfather) {
    node->parent_ = grandfather;
    grandfather->left_ = node;
  }
  parent->parent_ = node;
}

template <typename T>
void Tree<T>::small_rotate_right(RBT<T> *node, RBT<T> *parent) {
  RBT<T> *temp = node->right_;
  node->right_ = parent;
  parent->left_ = temp;
  RBT<T> *grandfather = get_father(parent);
  if (grandfather) {
    node->parent_ = grandfather;
    grandfather->right_ = node;
  }
  parent->parent_ = node;
}

template <typename T>
void Tree<T>::big_rotate_left(RBT<T> *node, RBT<T> *parent) {
  RBT<T> *grandfather = get_father(parent);
  RBT<T> *temp = parent->left_;
  parent->left_ = grandfather;
  grandfather->right_ = temp;
  if (temp) {
    temp->parent_ = grandfather;
  }
  RBT<T> *great_grandfather = get_father(grandfather);
  if (great_grandfather) {  // связка с прадедом
    if (great_grandfather->left_ == grandfather) {
      great_grandfather->left_ = parent;
    } else {
      great_grandfather->right_ = parent;
    }
  }
  parent->parent_ = great_grandfather;
  grandfather->parent_ = parent;
  parent->color_ = BLACK;
  grandfather->color_ = RED;
  if (grandfather == root_) {  // если нужно поменять рута
    root_ = parent;
  }
}

template <typename T>
void Tree<T>::big_rotate_right(RBT<T> *node, RBT<T> *parent) {
  RBT<T> *grandfather = get_father(parent);
  RBT<T> *temp = parent->right_;
  parent->right_ = grandfather;
  grandfather->left_ = temp;
  if (temp) {
    temp->parent_ = grandfather;
  }
  RBT<T> *great_grandfather = get_father(grandfather);
  if (great_grandfather) {  // связка с прадедом
    if (great_grandfather->left_ == grandfather) {
      great_grandfather->left_ = parent;
    } else {
      great_grandfather->right_ = parent;
    }
  }
  parent->parent_ = great_grandfather;
  grandfather->parent_ = parent;
  parent->color_ = BLACK;
  grandfather->color_ = RED;
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
