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

template <typename Key, typename T>
struct RBT {
  RBT() = default;
  RBT(const Key &key, T value) {
    data_ = new std::pair<const Key, T>(key, value);
  }
  ~RBT() { delete data_; }
  RBT<Key, T> *parent_{};
  RBT<Key, T> *left_{};
  RBT<Key, T> *right_{};
  enum RBT_colors color_ = RED;
  std::pair<const Key, T> *data_{};
};

template <typename Key, typename T = int>
class Tree {
 public:
  Tree() : root_(nullptr) { InitFakeNode(); }
  ~Tree() {
    clearUtil(root_);
    root_ = nullptr;
    //    delete fake_->data_;
    //    delete fake_;
  };

  void insert_node(const Key &key, T value = 0) {
    AddNodeByCondition(this->root_, key, value, this->root_);
  }
  RBT<Key, T> *GetFake() const;

  void erase_node(T value);

  //_____MODIFIERS____
  void print2D();
  void RBTPrint(RBT<Key, T> *&node);
  void clearUtil(RBT<Key, T> *node);
  void TreePrint() { RBTPrint(this->root_); };

  class ConstIterator {
   public:
    friend Tree;  // need for access node in tree
    ConstIterator() : node_(nullptr) {}
    ConstIterator(const ConstIterator &other)
        : node_(other.node_), it_fake_(other.it_fake_) {}
    std::pair<const Key, T> &operator*() const { return *this->node_->data_; }
    bool operator!=(const ConstIterator &other) const {
      return node_ != other.node_;
    }
    bool operator==(const ConstIterator &other) const {
      return node_ == other.node_;
    }

   protected:
    RBT<Key, T> *node_{};
    RBT<Key, T> *it_fake_{};

   private:
    explicit ConstIterator(RBT<Key, T> *pt, RBT<Key, T> *fake)
        : node_(pt), it_fake_(fake) {}
  };

  class Iterator : public ConstIterator {
   public:
    friend Tree;  // need for access node in tree
    friend RBT<Key, T> *Tree<Key, T>::GetFake() const;
    Iterator() { this->node_ = nullptr; }
    Iterator(const Iterator &other) : ConstIterator(other) {}
    Iterator &operator++();
    Iterator operator++(int);
    Iterator &operator--();
    Iterator operator--(int);
    std::pair<const Key, T> &operator*();
    Iterator &operator=(const Iterator &other);

    RBT<Key, T> *MaxNode(RBT<Key, T> *node) {
      RBT<Key, T> *ret = nullptr;
      if (node != this->it_fake_) {
        ret = node;
        if (node->right_ != this->it_fake_) {
          ret = MaxNode(node->right_);
        }
      }
      return ret;
    }

    RBT<Key, T> *MinNode(RBT<Key, T> *node) {
      RBT<Key, T> *ret = nullptr;
      if (node != this->it_fake_) {
        ret = node;
        if (node->left_ != this->it_fake_) {
          ret = MinNode(node->left_);
        }
      }
      return ret;
    }

   protected:
    explicit Iterator(RBT<Key, T> *pt, RBT<Key, T> *fake) {
      this->node_ = pt;
      this->it_fake_ = fake;
    }
  };

  using iterator = Iterator;
  using const_iterator = const ConstIterator;

  iterator begin();
  iterator end();

 protected:
  RBT<Key, T> *root_{};
  RBT<Key, T> *fake_{};
  RBT<Key, T> *begin_{};
  RBT<Key, T> *end_{};
  int size;
  friend Iterator;
  friend ConstIterator;

 private:
  //_____SUPPORT_FOR_INSERT_____
  void AddNodeByCondition(RBT<Key, T> *&node, const Key &key, T value,
                          RBT<Key, T> *&parent);
  void InitFakeNode();
  RBT<Key, T> *CreateNode(const Key &key, T value);

  //_____SUPPORT_FOR_ERASE_____
  void DelNodeByCondition(RBT<Key, T> *node);
  void DelNodeWithOneChild(RBT<Key, T> *del_node, RBT<Key, T> *child,
                           RBT<Key, T> *parent);
  void DelNodeWithoutChild(RBT<Key, T> *del_node, RBT<Key, T> *parent);

  //_____FIND_NODE_____
  RBT<Key, T> *FindNode(RBT<Key, T> *node, T &value);
  RBT<Key, T> *MinNode(RBT<Key, T> *node);
  RBT<Key, T> *MaxNode(RBT<Key, T> *node);

  //_____BALANCE_FUNC____
  void BalanceInsert(RBT<Key, T> *node, RBT<Key, T> *parent);
  void BalanceErase(RBT<Key, T> *parent, RBT<Key, T> *child);

  //_____ACCESS_FUNC____
  RBT<Key, T> *GetBro(RBT<Key, T> *node);
  RBT<Key, T> *GetFather(RBT<Key, T> *node);
  RBT<Key, T> *GetChildLeft(RBT<Key, T> *node);
  RBT<Key, T> *GetChildRight(RBT<Key, T> *node);
  RBT<Key, T> *GetRedChild(RBT<Key, T> *node);

  //_____CHANGE_FUNC____
  void ChangeColorIfUncleRed(RBT<Key, T> *parent, RBT<Key, T> *bro_parent,
                             RBT<Key, T> *grand_parent);
  void ChangeColorAfterBigRotate(RBT<Key, T> *parent, RBT<Key, T> *grandfather);
  void SmallRotate(RBT<Key, T> *node, DirectionOfRotation direction);
  void BigRotate(RBT<Key, T> *node, DirectionOfRotation direction);

  //_____SUPPORT_FOR_PRINT_____
  void print2DUtil(RBT<Key, T> *root, int space);
};
template <typename Key, typename T>
typename Tree<Key, T>::Iterator &Tree<Key, T>::Iterator::operator++() {
  
//  if (this->node_ == this->it_fake_) {
//    this->node_ = this->node_->parent_;
//    return *this;
//  }
  
  if (this->node_->right_ == this->it_fake_) {
    while (this->node_ == this->node_->parent_->right_) {
      this->node_ = this->node_->parent_;
    }
    this->node_ = this->node_->parent_;
    return *this;
  }

  if (this->node_->right_ != this->it_fake_) {
    this->node_ = MinNode(this->node_->right_);
    return *this;
  }
}

template <typename Key, typename T>
typename Tree<Key, T>::Iterator Tree<Key, T>::Iterator::operator++(int) {
  return Tree::Iterator();
}

template <typename Key, typename T>
typename Tree<Key, T>::Iterator &Tree<Key, T>::Iterator::operator--() {

  if (this->node_ == this->it_fake_) {
    this->node_ = this->node_->parent_;
    return *this;
  }

  if (this->node_->left_ == this->it_fake_) {
    while (this->node_ == this->node_->parent_->left_) {
      this->node_ = this->node_->parent_;
    }
    this->node_ = this->node_->parent_;
    return *this;
  }

  if (this->node_->left_ != this->it_fake_) {
    this->node_ = MaxNode(this->node_->left_);
    return *this;
  }

}

template <typename Key, typename T>
typename Tree<Key, T>::Iterator Tree<Key, T>::Iterator::operator--(int) {
  return Tree::Iterator();
}

template <typename Key, typename T>
std::pair<const Key, T> &Tree<Key, T>::Iterator::operator*() {
  return *this->node_->data_;
}

//_____MODIFIERS_____
template <typename Key, typename T>
void Tree<Key, T>::erase_node(T value) {
  RBT<Key, T> *find = FindNode(this->root_, value);
  if (find != nullptr) {
    DelNodeByCondition(find);
  }
}

//_____SUPPORT_FOR_INSERT_____
template <typename Key, typename T>
void Tree<Key, T>::AddNodeByCondition(RBT<Key, T> *&node, const Key &key,
                                      T value, RBT<Key, T> *&parent) {
  if (node == fake_ || root_ == nullptr) {
    node = CreateNode(key, value);
    if (node != parent) {
      node->parent_ = parent;
    } else {
      node->color_ = BLACK;
      //	  begin_ = node;
    }
    if (parent && parent->color_ == RED) {
      BalanceInsert(node, parent);
    }
    //	if (node->data_->first < begin_->data_->first) {
    //	  begin_ = node;
    //	}
  } else if (key < node->data_->first) {
    AddNodeByCondition(node->left_, key, value, node);
  } else if (node->data_->first < key) {
    AddNodeByCondition(node->right_, key, value, node);
  }
}

template <typename Key, typename T>
void Tree<Key, T>::InitFakeNode() {
  fake_ = new RBT<Key, T>();
  fake_->data_ = new std::pair<const Key, T>();
  begin_ = fake_;
  end_ = fake_;
}

template <typename Key, typename T>
RBT<Key, T> *Tree<Key, T>::CreateNode(const Key &key, T value) {
  auto temp = new RBT<Key, T>(key, value);
  temp->parent_ = nullptr;
  temp->left_ = temp->right_ = fake_;
  return temp;
}

//_____SUPPORT_FOR_ERASE_____
template <typename Key, typename T>
void Tree<Key, T>::DelNodeByCondition(RBT<Key, T> *node) {
  if (node->left_ != fake_ && node->right_ != fake_) {
    //    RBT<Key, T> *change = MinNode(node->right_);  // node->right_ ранее

    RBT<Key, T> *change = MaxNode(node->left_);  // node->right_ ранее
    std::swap(change->data_, node->data_);
    DelNodeByCondition(change);
  } else if (node->left_ != fake_) {  // есть один левый ребенок
    //    if (node->color_ == BLACK) {
    DelNodeWithOneChild(node, node->left_, node->parent_);
    //    }
  } else if (node->right_ != fake_) {  // есть один правый ребенок
    //    if (node->color_ == BLACK) {
    DelNodeWithOneChild(node, node->right_, node->parent_);
    //    }
  } else {  // лист
    if (node->color_ == RED) {
      DelNodeWithoutChild(node, node->parent_);
    } else {
      RBT<Key, T> *parent = GetFather(node);
      RBT<Key, T> *brother_of_remote = GetBro(node);
      DelNodeWithoutChild(node, node->parent_);
      if (parent && brother_of_remote) {
        BalanceErase(parent, brother_of_remote);
      }
    }
  }
}

template <typename Key, typename T>
void Tree<Key, T>::DelNodeWithOneChild(RBT<Key, T> *del_node,
                                       RBT<Key, T> *child,
                                       RBT<Key, T> *parent) {
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

template <typename Key, typename T>
void Tree<Key, T>::DelNodeWithoutChild(RBT<Key, T> *del_node,
                                       RBT<Key, T> *parent) {
  if (del_node != root_) {
    if (parent->left_ == del_node) {
      parent->left_ = fake_;
    } else {
      parent->right_ = fake_;
    }
  } else {
    root_ = nullptr;
  }
  delete del_node;
}

//_____FIND_NODE_____
template <typename Key, typename T>
RBT<Key, T> *Tree<Key, T>::FindNode(RBT<Key, T> *node, T &value) {
  RBT<Key, T> *ret = nullptr;
  if (node != fake_) {
    if (node->data_->first == value) {
      ret = node;
    } else if (value < node->data_->first) {
      ret = FindNode(node->left_, value);
    } else if (node->data_->first < value) {
      ret = FindNode(node->right_, value);
    }
  }
  return ret;
}

template <typename Key, typename T>
RBT<Key, T> *Tree<Key, T>::MinNode(RBT<Key, T> *node) {
  RBT<Key, T> *ret = nullptr;
  if (node != fake_) {
    ret = node;
    if (node->left_ != fake_) {
      ret = MinNode(node->left_);
    }
  }
  return ret;
}

template <typename Key, typename T>
RBT<Key, T> *Tree<Key, T>::MaxNode(RBT<Key, T> *node) {
  RBT<Key, T> *ret = nullptr;
  if (node != fake_) {
    ret = node;
    if (node->right_ != fake_) {
      ret = MaxNode(node->right_);
    }
  }
  return ret;
}

//_____BALANCE_FUNC____
template <typename Key, typename T>
void Tree<Key, T>::BalanceInsert(RBT<Key, T> *node, RBT<Key, T> *parent) {
  RBT<Key, T> *bro_parent = GetBro(parent);
  if (parent->color_ == RED) {  // в рекурсии нужна проверка
    if (bro_parent != fake_ && bro_parent->color_ == RED) {
      ChangeColorIfUncleRed(parent, bro_parent, GetFather(parent));
      if (GetFather(parent) != root_) {
        BalanceInsert(GetFather(parent),
                      GetFather(parent)->parent_);  // рекурсивно для деда
      }
    } else {
      if (parent != root_) {
        if (GetFather(parent) &&
            GetFather(parent)->left_ == parent) {  // мы слева от деда
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
// Визуализация: https://www.cs.usfca.edu/~galles/visualization/RedBlack.html
template <typename Key, typename T>
void Tree<Key, T>::BalanceErase(RBT<Key, T> *parent, RBT<Key, T> *child) {
  if (parent->color_ == RED) {  // 2.1. Отец удаленной ноды красный
    RBT<Key, T> *grandsonRed = GetRedChild(child);
    if (grandsonRed) {  // 2.1.1  // Брат удаленной ноды красный
      if (parent->left_ == child) {          // мы слева от деда
        if (child->right_ == grandsonRed) {  // мы справа от отца
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
      } else {                              // мы справа от деда
        if (child->left_ == grandsonRed) {  // мы слева от отца
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
    } else {  // 2.1.2  // Брат удаленной ноды не красный
      std::swap(parent->color_, child->color_);
    }
  } else {  // 2.2. Отец удаленной ноды черный
    if (child->color_ == RED) {  // 2.2.1. Брат удаленной ноды красный
      RBT<Key, T> *grandsonLeft = GetChildLeft(child);  // внуки
      RBT<Key, T> *grandsonRight = GetChildRight(child);

      if (grandsonLeft && grandsonLeft->color_ == BLACK) {
        RBT<Key, T> *great_grandsonRed = GetRedChild(grandsonLeft);  // правнуки
        if (great_grandsonRed) {  // 2.2.1.1. есть красный правнук
          if (parent->right_ == child) {  // мы справа от отца
            BigRotate(grandsonLeft, LEFT);
            child->color_ = BLACK;
            parent->color_ = RED;
            BalanceErase(parent, parent->right_);
          } else {
            BigRotate(grandsonLeft, RIGHT);
            child->color_ = BLACK;
            parent->color_ = RED;
            BalanceErase(parent, parent->left_);
          }
        } else {  // 2.2.1.2 когда нет красного правнука
          if (parent->left_ == child) {
            BigRotate(grandsonLeft, RIGHT);  // внимание
            child->color_ = BLACK;
            parent->color_ = RED;
            BalanceErase(parent, parent->left_);
          } else {
            BigRotate(grandsonLeft, LEFT);
            child->color_ = BLACK;
            parent->color_ = RED;
            BalanceErase(parent, parent->right_);
          }
        }
      } else if (grandsonRight &&
                 grandsonRight->color_ ==
                     BLACK) {  // внук черный  // скорее всего не нужно когда мы
                               // работаем с max в левом поддереве
        RBT<Key, T> *great_grandsonRed = GetRedChild(grandsonRight);
        if (great_grandsonRed) {  // 2.2.1.1. есть красный правнук
          if (parent->left_ == child) {  // мы слева от отца
            SmallRotate(grandsonRight, LEFT);
            BigRotate(child, RIGHT);
            great_grandsonRed->color_ = BLACK;
          } else {
            BigRotate(grandsonRight, RIGHT);
            child->color_ = BLACK;
            grandsonRight->color_ = RED;
            great_grandsonRed->color_ = BLACK;
          }
        } else {  // 2.2.1.2 когда нет красного правнука
          if (parent->left_ == child) {
            BigRotate(grandsonRight, RIGHT);  // внимание
            child->color_ = BLACK;
            grandsonRight->color_ = RED;
          } else {
            BigRotate(grandsonRight, LEFT);
            child->color_ = BLACK;
            grandsonRight->color_ = RED;
          }
        }
      }
    } else {  // 2.2.2. Брат удаленной ноды черный
      RBT<Key, T> *grandsonRed = GetRedChild(child);
      if (grandsonRed) {  // 2.2.2.1 у брата удаленной ноды есть красные дети
        if (parent->left_ == child) {          // мы слева от деда
          if (child->right_ == grandsonRed) {  // мы справа от отца
            SmallRotate(grandsonRed, LEFT);
            BigRotate(child, RIGHT);
            grandsonRed->color_ = BLACK;
          } else {
            BigRotate(grandsonRed, RIGHT);
            grandsonRed->color_ = BLACK;
          }
        } else {                              // мы справа от деда
          if (child->left_ == grandsonRed) {  // мы слева от отца
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
        if (parent != root_) {  // рекурсивно к деду
          RBT<Key, T> *grandfather = GetFather(parent);
          RBT<Key, T> *brother_of_parent = GetBro(parent);
          if (grandfather && brother_of_parent) {
            BalanceErase(grandfather, brother_of_parent);
          }
        }
      }
    }
  }
}

//_____ACCESS_FUNC____
template <typename Key, typename T>
RBT<Key, T> *Tree<Key, T>::GetBro(RBT<Key, T> *node) {
  RBT<Key, T> *parent = node->parent_;
  RBT<Key, T> *ret = nullptr;
  if (parent != nullptr) {
    if (parent->left_ != node) {
      ret = parent->left_;
    } else {
      ret = parent->right_;
    }
  }
  return ret;
}

template <typename Key, typename T>
RBT<Key, T> *Tree<Key, T>::GetFather(RBT<Key, T> *node) {
  return node->parent_;
}

template <typename Key, typename T>
RBT<Key, T> *Tree<Key, T>::GetChildLeft(RBT<Key, T> *node) {
  return node->left_;
}

template <typename Key, typename T>
RBT<Key, T> *Tree<Key, T>::GetChildRight(RBT<Key, T> *node) {
  return node->right_;
}

template <typename Key, typename T>
RBT<Key, T> *Tree<Key, T>::GetRedChild(
    RBT<Key, T> *node) {  //м.б. не нужна пров с дед
  RBT<Key, T> *patent = node->parent_;
  RBT<Key, T> *grandFather = node->parent_->parent_;
  RBT<Key, T> *ret = nullptr;

  if (grandFather && grandFather->left_ == patent) {  // мы слева от дедушки
    if (patent->left_ == node) {  // мы слева от отца
      if (node->left_ != fake_ && node->left_->color_ == RED) {
        ret = node->left_;
      } else if (node->right_ != fake_ && node->right_->color_ == RED) {
        ret = node->right_;
      }
    } else {  // мы справа от отца
      if (node->right_ != fake_ && node->right_->color_ == RED) {
        ret = node->right_;
      } else if (node->left_ != fake_ && node->left_->color_ == RED) {
        ret = node->left_;
      }
    }
  } else {                         // мы справа от дедушки
    if (patent->right_ == node) {  // мы справа от отца
      if (node->right_ != fake_ && node->right_->color_ == RED) {
        ret = node->right_;
      } else if (node->left_ != fake_ && node->left_->color_ == RED) {
        ret = node->left_;
      }
    } else {  // мы слева от отца
      if (node->left_ != fake_ && node->left_->color_ == RED) {
        ret = node->left_;
      } else if (node->right_ != fake_ && node->right_->color_ == RED) {
        ret = node->right_;
      }
    }
  }
  return ret;
}

template <typename Key, typename T>
void Tree<Key, T>::ChangeColorIfUncleRed(RBT<Key, T> *parent,
                                         RBT<Key, T> *bro_parent,
                                         RBT<Key, T> *grand_parent) {
  parent->color_ = bro_parent->color_ = BLACK;
  if (grand_parent != this->root_) {
    grand_parent->color_ = RED;
  }
}

template <typename Key, typename T>
void Tree<Key, T>::ChangeColorAfterBigRotate(RBT<Key, T> *parent,
                                             RBT<Key, T> *grandfather) {
  if (parent) parent->color_ = BLACK;
  if (grandfather) grandfather->color_ = RED;
}

//_____CHANGE_FUNC____
template <typename Key, typename T>
void Tree<Key, T>::SmallRotate(RBT<Key, T> *node,
                               DirectionOfRotation direction) {
  RBT<Key, T> *temp = (direction == RIGHT) ? node->right_ : node->left_;
  RBT<Key, T> *parent = node->parent_;
  if (direction == RIGHT) {
    node->right_ = parent;
    parent->left_ = temp;
  } else {
    node->left_ = parent;
    parent->right_ = temp;
  }
  RBT<Key, T> *grandfather = GetFather(parent);
  if (grandfather) {
    node->parent_ = grandfather;
    if (direction == RIGHT) {
      grandfather->right_ = node;
    } else {
      grandfather->left_ = node;
    }
  }
  if (temp) {
    temp->parent_ = parent;
  }
  parent->parent_ = node;
}

template <typename Key, typename T>
void Tree<Key, T>::BigRotate(RBT<Key, T> *node, DirectionOfRotation direction) {
  RBT<Key, T> *parent = node->parent_;
  RBT<Key, T> *grandfather = GetFather(parent);
  RBT<Key, T> *temp = (direction == RIGHT) ? parent->right_ : parent->left_;
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
  RBT<Key, T> *great_grandfather = GetFather(grandfather);
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
template <typename Key, typename T>
void Tree<Key, T>::print2DUtil(RBT<Key, T> *root, int space) {
  // Base case
  if (root == nullptr || root == fake_) return;

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
    std::cout << root->data_->first << "_B"
              << " "
              << "\n";
  } else {
    std::cout << root->data_->first << "_R"
              << " "
              << "\n";
  }

  //  if (root->color_ == BLACK) {
  //	std::cout << root->data_->first << "_B" << " " << root->data_->second
  //			  << "\n";
  //  } else {
  //	std::cout << root->data_->first << "_R" << " " << root->data_->second
  //			  << "\n";
  //  }

  // Process left child
  print2DUtil(root->left_, space);
}

// Wrapper over print2DUtil()
template <typename Key, typename T>
void Tree<Key, T>::print2D() {
  // Pass initial space count as 0
  print2DUtil(this->root_, 0);
}

template <typename Key, typename T>
void Tree<Key, T>::RBTPrint(RBT<Key, T> *&node) {
  if (node == nullptr) return;
  RBTPrint(node->left_);
  std::cout << node->data_->first << std::endl;
  RBTPrint(node->right_);
}

template <typename Key, typename T>
void Tree<Key, T>::clearUtil(RBT<Key, T> *node) {
  if (node == nullptr || node == fake_) return;
  clearUtil(node->left_);
  auto tmp = node->right_;
  delete node;
  clearUtil(tmp);
}

template <typename Key, typename T>
typename Tree<Key, T>::iterator Tree<Key, T>::begin() {
  fake_->parent_ = nullptr;
  if (root_)
    return s21::Tree<Key, T>::iterator(MinNode(root_), fake_);
  else {
    return s21::Tree<Key, T>::iterator(fake_, fake_);
  }
}

template <typename Key, typename T>
typename Tree<Key, T>::iterator Tree<Key, T>::end() {
  fake_->parent_ = nullptr;
  if (root_) fake_->parent_ = MaxNode(root_);
  return s21::Tree<Key, T>::iterator(fake_, fake_);
}

template <typename Key, typename T>
RBT<Key, T> *Tree<Key, T>::GetFake() const {
  return fake_;
}

}  // namespace s21

#endif  // S21_CONTAINERS_SRC_SORTED_CONTAINER_RED_BLACK_TREE_H_
