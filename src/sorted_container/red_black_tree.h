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
  Tree() { this->root_ = nullptr; }
  ~Tree() = default;
  //_____MODIFIERS_SIMPLE_____
  void insert(const T &value) { add_tree(this->root_, value, this->root_); }
  void erase_node(T value);

  void print2D();
  void RBTPrint(RBT<T> *&node);
  void TreePrint() { RBTPrint(this->root_); };

 private:
  RBT<T> *root_{};
  //_____SUPPORT_FOR_INSERT_SIMPLE_____
  void add_tree(RBT<T> *&node, const T &value, RBT<T> *&parent);
  RBT<T> *create_node(const T &value);

  //_____SUPPORT_FOR_ERASE_SIMPLE_____
  void del_node_by_condition(RBT<T> *node);
  void del_node_with_one_child(RBT<T> *del_node, RBT<T> *child, RBT<T> *parent);

  //_____FIND_NODE_____
  RBT<T> *find_node(RBT<T> *node, T &value);
  RBT<T> *min_node(RBT<T> *node);

  //_____BALANCE_FUNC____
  void balance(RBT<T> *node, RBT<T> *parent);
  RBT<T> *get_bro(RBT<T> *node);
  RBT<T> *get_father(RBT<T> *node);
  void rotate() {}


  //_____SUPPORT_FOR_PRINT_____
  void print2DUtil(RBT<T> *root, int space);
};

//_____INSERT_SIMPLE_____
template <typename T>
void Tree<T>::add_tree(RBT<T> *&node, const T &value, RBT<T> *&parent) {
  if (node == nullptr) {
    node = create_node(value);
    if (node != root_) {
      node->parent_ = parent;
    } else {
      node->color_ = BLACK;
    }
    if (parent->color_ == RED) {
      balance(node, parent);
    }
  } else if (value < node->data_) {
    add_tree(node->left_, value, node);
  } else if (node->data_ < value) {
    add_tree(node->right_, value, node);
  }
}

template <typename T>
RBT<T> *Tree<T>::create_node(const T &value) {
  auto temp = new RBT<T>;
  temp->data_ = value;
  temp->left_ = temp->right_ = temp->parent_ = nullptr;
  return temp;
}

//_____ERASE_SIMPLE_____
template <typename T>
void Tree<T>::erase_node(T value) {
  RBT<T> *find = find_node(this->root_, value);
  if (find != nullptr) {
    del_node_by_condition(find);
  }
}

template <typename T>
void Tree<T>::del_node_by_condition(RBT<T> *node) {
  if (!node->right_ && !node->left_) {  // удаление листа
    if (node->parent_->left_ == node) {
      node->parent_->left_ = nullptr;
    } else {
      node->parent_->right_ = nullptr;
    }
    delete node;
  } else if (node->left_ && !node->right_) {
    del_node_with_one_child(node, node->left_, node->parent_);
  } else if (!node->left_ && node->right_) {
    del_node_with_one_child(node, node->right_, node->parent_);
  } else if (node->left_ && node->right_) {
    RBT<T> *change = min_node(node->right_);  // find min node in node->right_
    std::swap(change->data_, node->data_);
    del_node_by_condition(change);
  }
}

template <typename T>
void Tree<T>::del_node_with_one_child(RBT<T> *del_node, RBT<T> *child,
                                      RBT<T> *parent) {
  if (parent->left_ == del_node) {
    parent->left_ = child;
  } else {
    parent->right_ = child;
  }
  child->parent_ = parent;
  delete del_node;
}

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

//_____BALANCE_FUNC____
template <typename T>
void Tree<T>::balance(RBT<T> *node, RBT<T> *parent) {
  RBT<T> *bro_parent = get_bro(parent);
  if (bro_parent) {
    if (bro_parent->color_ == BLACK) {
      //  если отец и дедушка в одной стороне поворот большой иначе маленький

    }
  }
}

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

/*То что написал Саша ---->>>> */

// Tree &operator=(const Tree &other) {
//   if (this != &other) this->root_ = other.root_;
//   return *this;
// }
/**
 * рекурсивно идет по дереву и вставляет элемент больше вправо меньше влево
 * @param paste_here попробовать вставить сюда НОДУ
 * @param data НОДА с новой датой
 * @param parent родитель, при первой передаче передается рут
 * @return не реализовано
 */
//  RBT<T> *InsertRBT(RBT<T> *&paste_here, RBT<T> *&data, RBT<T> *&parent) {
//    if (paste_here == nullptr) {  // если нул можно добавить сюда
//      if (paste_here != parent) {  // проверка рута
//        data->parent_ = parent;    // добавить родителя
//      } else {
//        data->color_ = BLACK;  // рут черный
//      }
//      std::swap(paste_here, data);  // добавление элемента
//
//      if (paste_here->parent_ != nullptr) {  // проверка рута
//        BalanceInsert(paste_here);  // пишем в дату новый рут или нулл
//      }
//
//    } else if (data->data_ > paste_here->data_) {
//      InsertRBT(paste_here->right_, data, paste_here);
//    } else if (data->data_ < paste_here->data_) {
//      InsertRBT(paste_here->left_, data, paste_here);
//    }
//    return paste_here;
//  }
//
//  void Insert(const T &data) {
//    auto *temp = new RBT<T>;
//    temp->data_ = data;
//    root_ = InsertRBT(root_, temp, root_);
//    if (!temp) delete temp;
//  }
//
//  void BalanceInsert(RBT<T> *&balance_RBT) {
//    if (GetParent(balance_RBT) == nullptr) return;
//
//    if (GetParent(balance_RBT)->color_ == RED) {  // балансируем
//
//      // first r-r-B-r -> r-b-R-b if B -root B -> B
//      if (GetParent(balance_RBT)->color_ ==
//          GetBrotherColor(GetParent(balance_RBT))) {  // red == red
//        GetParent(balance_RBT)->color_ = BLACK;
//        GetBrother(GetParent(balance_RBT))->color_ = BLACK;
//
//        if (!IsRoot(GetGrandParent(balance_RBT))) {  // not root
//          GetGrandParent(balance_RBT)->color_ = RED;
//          BalanceInsert(GetGrandParent(balance_RBT));  // балансируем выше
//        }
//        // second r-r-B-b -> r-B-r-b / if B root -> change root
//      } else {  // parent and uncle is red and black
//
//        if (GetParent(balance_RBT) == GetGrandParent(balance_RBT)->left_) {
//          // вставка влево поворачиваем вправо
//          // проверка на рут деда
//          if (balance_RBT->parent_->parent_->parent_ != nullptr) {  // не рут
//            // замена указателя главного родителя
//            if (balance_RBT->parent_->parent_->parent_->left_ ==
//                balance_RBT->parent_->parent_) {
//              balance_RBT->parent_->parent_->parent_->left_ =
//                  balance_RBT->parent_;
//            } else {
//              balance_RBT->parent_->parent_->parent_->right_ =
//                  balance_RBT->parent_;
//            }
//
//          } else {  // рут/ как заменить рут
//                    // замена указателя главного родителя
//            auto temp_root = new RBT<T>;
//            temp_root = balance_RBT->parent_->parent_;
//            this->root_ = balance_RBT->parent_;
//          }
//          auto temp = new RBT<T>;
//          temp->parent_ = balance_RBT->parent_->parent_;
//          balance_RBT->parent_->parent_ =
//              balance_RBT->parent_->parent_->parent_;
//          temp->right_ = balance_RBT->parent_->right_;
//          balance_RBT->parent_->right_ = temp->parent_;
//          balance_RBT->parent_->right_->parent_ = balance_RBT->parent_;
//          balance_RBT->parent_->right_->left_ = temp->right_;
//          temp->parent_ = temp->right_ = temp->left_ = nullptr;
//          delete temp;
//          balance_RBT->parent_->color_ = BLACK;
//          balance_RBT->parent_->right_->color_ = RED;
//        } else {
//          // вставка вправо поворачиваем влево
//          // проверка на рут деда
//          if (balance_RBT->parent_->parent_->parent_ != nullptr) {  // не рут
//
//            // замена указателя главного родителя
//            if (balance_RBT->parent_->parent_->parent_->left_ ==
//                balance_RBT->parent_->parent_) {
//              balance_RBT->parent_->parent_->parent_->left_ =
//                  balance_RBT->parent_;
//            } else {
//              balance_RBT->parent_->parent_->parent_->right_ =
//                  balance_RBT->parent_;
//            }
//
//          } else {  // рут/ как заменить рут?
//            // замена указателя главного родителя
//            this->root_ = balance_RBT->parent_;
//          }
//          auto temp = new RBT<T>;
//          temp->parent_ = balance_RBT->parent_->parent_;
//          balance_RBT->parent_->parent_ =
//              balance_RBT->parent_->parent_->parent_;
//          temp->left_ = balance_RBT->parent_->left_;
//          balance_RBT->parent_->left_ = temp->parent_;
//          balance_RBT->parent_->left_->parent_ = balance_RBT->parent_;
//          balance_RBT->parent_->left_->right_ = temp->left_;
//          temp->parent_ = temp->right_ = temp->left_ = nullptr;
//          delete temp;
//          balance_RBT->parent_->color_ = BLACK;
//          balance_RBT->parent_->left_->color_ = RED;
//        }
//      }
//    }
//  }
//
//  RBT<T> *&GetParent(RBT<T> *&node) { return node->parent_; }
//
//  //  RBT<T> *GetGrandParent(RBT<T> *&node) {
//  //    if (GetParent(node) != nullptr)
//  //    return GetParent(node)->parent_;
//  //    else return nullptr;
//  //  }
//
//  RBT<T> *&GetGrandParent(RBT<T> *&node) { return GetParent(node)->parent_; }
//
//  RBT<T> *GetBrother(RBT<T> *&node) {
//    if (node->parent_ == nullptr) {
//      return nullptr;
//    } else {
//      if (node == node->parent_->left_)
//        return node->parent_->right_;
//      else
//        return node->parent_->left_;
//    }
//  }
//
//  RBT_colors GetBrotherColor(RBT<T> *&node) {
//    if (GetBrother(node) == nullptr) {
//      return BLACK;
//    } else
//      return GetBrother(node)->color_;
//  }
//
//  bool IsRoot(RBT<T> *&node) {
//    if (node->parent_ == nullptr)
//      return true;
//    else
//      return false;
//  }
//
//  //  bool IsRoot (RBT<T> *node) {
//  //    if (node->parent_ == nullptr) return true;
//  //    else return false;
//  //  }
//
//  void Remove(const T &data) {
//    auto *temp = new RBT<T>;
//    temp->data_ = data;
//    FindAndRemove(root_, temp, root_);
//    delete temp;
//  }
//
//  void FindAndRemove(RBT<T> *&find_here, RBT<T> *&remove, RBT<T> *&parent) {
//    if (find_here == nullptr) {  // пустое дерево
//      return;
//    } else if (find_here->data_ == remove->data_) {  // найден элемент
//      if (find_here->right_ == nullptr &&
//          find_here->left_ == nullptr) {  // нет детей
//        delete find_here;
//        find_here = nullptr;
//      } else if (find_here->right_ == nullptr) {  // только левый
//        delete remove;
//        remove = find_here->left_;
//        delete find_here;
//        find_here = remove;
//        find_here->parent_ = parent;
//      } else if (find_here->left_ == nullptr) {  // только правый
//        delete remove;
//        remove = find_here->right_;
//        delete find_here;
//        find_here = remove;
//        find_here->parent_ = parent;
//        // если есть оба - заменить на минимальное из правого поддерева
//      } else {
//        // найти минимум из правого дерева
//        //        auto *temp = new RBT<T>;
//        //        temp->data_ = FindMin(find_here->right_)->data_;
//        //        temp->left_ = find_here->left_;
//        //        temp->right_ = find_here->right_;
//        //        temp->parent_ = parent;
//        //        // удалить этот элемент
//        //        delete find_here;
//        //        find_here = nullptr;
//        //        // скопировать сюда минимум
//        //        std::swap(find_here, temp);
//
//        find_here->data_ = FindMin(find_here->right_)->data_;
//        // удалить минимум из правого поддерева
//        auto *temp = new RBT<T>;
//        temp->data_ = find_here->data_;
//        FindAndRemove(find_here->right_, temp, find_here);
//        delete temp;
//      }
//    } else if (remove->data_ >
//               find_here->data_) {  // искомое больше - искать справа
//      FindAndRemove(find_here->right_, remove, find_here);
//    } else if (remove->data_ <
//               find_here->data_) {  // искомое меньше - искать слева
//      FindAndRemove(find_here->left_, remove, find_here);
//    }
//  }
//
//  RBT<T> *FindMin(RBT<T> *&find_here) {
//    if (find_here->left_ == nullptr)
//      return find_here;
//    else
//      return FindMin(find_here->left_);
//  }
//
//  void WalkInWidth() {
//    std::queue<RBT<T> *> queue;
//    queue.push(this->root_);
//    int count = 0;
//    int sons = 1;
//    RBT<T> *fake;
//
//    while (!queue.empty()) {
//      RBT<T> *temp;
//      temp = queue.front();
//      queue.pop();
//      if (temp != fake) {
//        std::cout << temp->data_ << " ";
//      } else {
//        std::cout << "null"
//                  << " ";
//      }
//      ++count;
//      if (count == sons) {
//        std::cout << std::endl;
//        count = 0;
//        sons *= 2;
//      }
//
//      if (temp != fake) {
//        if (temp->left_ != nullptr) {
//          queue.push(temp->left_);
//        } else {
//          queue.push(fake);
//        }
//
//        if (temp->right_ != nullptr) {
//          queue.push(temp->right_);
//        } else {
//          queue.push(fake);
//        }
//      }
//    }
//  }
