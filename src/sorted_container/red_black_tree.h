//
// Created by Lok on 04.12.2022.
//

#ifndef S21_CONTAINERS_SRC_SORTED_CONTAINER_RED_BLACK_TREE_H_
#define S21_CONTAINERS_SRC_SORTED_CONTAINER_RED_BLACK_TREE_H_

#include <cstddef>
#include <initializer_list>
#include <iostream>
#include <memory>
#include <queue>
#include <utility>
#include <valarray>

namespace s21 {

enum RBT_colors { RED, BLACK };

enum DirectionOfRotation { LEFT, RIGHT };

enum OperatorType { PLUS_PLUS, MINUS_MINUS };

template <typename Key, typename T>
struct RBT {
  RBT() = default;

  ~RBT() = default;

  RBT<const Key, T> *parent_{};
  RBT<const Key, T> *left_{};
  RBT<const Key, T> *right_{};
  enum RBT_colors color_ = RED;
  std::pair<const Key, T> *data_{};
};

template <typename Key, typename T = int,
          typename Alloc = std::allocator<std::pair<const Key, T>>>
class Tree {
 public:
  using key_type = Key;
  using value_type = std::pair<const Key, T>;
  using reference = value_type &;
  using const_reference = const value_type &;
  using size_type = size_t;
  using ValueTypeAlloc = Alloc;                      // под пару
  using NodeAlloc = typename std::allocator_traits<  // под ноду
      Alloc>::template rebind_alloc<RBT<const Key, T>>;

  //____ITERATORS____
  class ConstIterator {
   public:
    friend Tree;  // need for access node in tree
    ConstIterator() : node_(nullptr) {}

    ConstIterator(const ConstIterator &other)
        : node_(other.node_), it_fake_(other.it_fake_) {}

    std::pair<const Key, T> &operator*() const { return *this->node_->data_; }

    std::pair<const Key, T> *operator->() const { return this->node_->data_; }

    bool operator!=(const ConstIterator &other) const {
      return node_ != other.node_;
    }

    bool operator==(const ConstIterator &other) const {
      return node_ == other.node_;
    }

   protected:
    RBT<const Key, T> *node_{};
    RBT<const Key, T> *it_fake_{};

   private:
    explicit ConstIterator(RBT<const Key, T> *pt, RBT<const Key, T> *fake)
        : node_(pt), it_fake_(fake) {}
  };

  class Iterator : public ConstIterator {
   public:
    friend Tree;  // need for access node in tree
    Iterator() { this->node_ = nullptr; }

    Iterator(const Iterator &other) : ConstIterator(other) {}

    Iterator &operator++();

    Iterator operator++(int);

    Iterator &operator--();

    Iterator operator--(int);

    std::pair<const Key, T> &operator*();

    Iterator &operator=(const Iterator &other);

   private:
    explicit Iterator(RBT<const Key, T> *pt, RBT<const Key, T> *fake) {
      this->node_ = pt;
      this->it_fake_ = fake;
    }

    //____SUPPORT_ITERATORS_FUNC____
    RBT<const Key, T> *PrefIter(RBT<const Key, T> *node, OperatorType mode);

    RBT<const Key, T> *GetNodeChild(RBT<const Key, T> *node, OperatorType mode);

    RBT<const Key, T> *GetNodeParentChild(RBT<const Key, T> *node,
                                          OperatorType mode);

    RBT<const Key, T> *MaxNode(RBT<const Key, T> *node);

    RBT<const Key, T> *MinNode(RBT<const Key, T> *node);
  };

  using iterator = Iterator;
  using const_iterator = const ConstIterator;

  //____CONSTRUCTOR_AND_DESTRUCTOR____
  Tree() : root_(nullptr) { InitFakeNode(); }

  Tree(std::initializer_list<value_type> const &items);

  Tree(const Tree &other);

  Tree(Tree &&other) noexcept;

  ~Tree();

  Tree &operator=(const Tree &other);

  Tree &operator=(Tree &&other) noexcept;

  //____MODIFIERS____
  void clear();
  //  std::pair<iterator, bool> insert_node(const Key &key, T value = 0);

  void erase(const Key &key);

  //____CAPACITY____
  bool empty() { return !this->root_; }

  size_type size() { return this->size_; }

  size_type max_size() { return node_alloc_.max_size(); }

  void swap(Tree &other) noexcept;

  //____PRINT____
  void print2D();

  //____ITERATORS_FOR_TREE____
  iterator begin() const;

  iterator end() const;

 protected:
  RBT<const Key, T> *root_{};
  RBT<const Key, T> *fake_{};
  size_type size_{};
  NodeAlloc node_alloc_{};
  ValueTypeAlloc value_type_alloc_{};

  std::pair<iterator, bool> insert_node(const Key &key, T value = 0);

  RBT<const Key, T> *FindNodeByKey(RBT<const Key, T> *node, const Key &key);

  friend Iterator;
  friend ConstIterator;

 private:
  //_____WORKING_WITH_MEMORY_____
  RBT<const Key, T> *CreateNode(const Key &key, T value);

  void RemNode(RBT<const Key, T> *node);
  void InitFakeNode();

  void clearUtil(RBT<const Key, T> *node);

  //_____SUPPORT_FOR_INSERT_____
  RBT<const Key, T> *AddNodeByCondition(RBT<const Key, T> *&node,
                                        const Key &key, T value,
                                        RBT<const Key, T> *&parent,
                                        bool &is_node_create);

  //_____SUPPORT_FOR_ERASE_____
  void DelNodeByCondition(RBT<const Key, T> *node);

  void DelNodeWithOneChild(RBT<const Key, T> *del_node,
                           RBT<const Key, T> *child, RBT<const Key, T> *parent);

  void DelNodeWithoutChild(RBT<const Key, T> *del_node,
                           RBT<const Key, T> *parent);

  //_____FIND_NODE_____
  //  RBT<const Key, T> *FindNodeByKey(RBT<const Key, T> *node, T &key);
  RBT<const Key, T> *MinNode(RBT<const Key, T> *node) const;

  RBT<const Key, T> *MaxNode(RBT<const Key, T> *node) const;

  //_____BALANCE_FUNC____
  void BalanceInsert(RBT<const Key, T> *node, RBT<const Key, T> *parent);

  void BalanceErase(RBT<const Key, T> *parent, RBT<const Key, T> *child);

  //_____ACCESS_FUNC____
  RBT<const Key, T> *GetBro(RBT<const Key, T> *node);

  RBT<const Key, T> *GetFather(RBT<const Key, T> *node);

  RBT<const Key, T> *GetChildLeft(RBT<const Key, T> *node);

  RBT<const Key, T> *GetChildRight(RBT<const Key, T> *node);

  RBT<const Key, T> *GetRedChild(RBT<const Key, T> *node);

  //_____CHANGE_FUNC____
  void ChangeColorIfUncleRed(RBT<const Key, T> *parent,
                             RBT<const Key, T> *bro_parent,
                             RBT<const Key, T> *grand_parent);

  void ChangeColorAfterBigRotate(RBT<const Key, T> *parent,
                                 RBT<const Key, T> *grandfather);

  void SmallRotate(RBT<const Key, T> *node, DirectionOfRotation direction);

  void BigRotate(RBT<const Key, T> *node, DirectionOfRotation direction);

  //_____SUPPORT_FOR_PRINT_____
  void print2DUtil(RBT<const Key, T> *root, int space);
};

//_____CONSTRUCTOR_AND_DESTRUCTOR____
template <typename Key, typename T, typename Alloc>
Tree<Key, T, Alloc>::Tree(std::initializer_list<value_type> const &items) {
  InitFakeNode();
  for (auto it = items.begin(); it != items.end(); ++it) {
    this->insert_node(*it);
  }
}

template <typename Key, typename T, typename Alloc>
Tree<Key, T, Alloc>::Tree(const Tree &other) {
  InitFakeNode();
  for (auto it = other.begin(); it != other.end(); ++it) {
    this->insert_node(*it);
  }
}

template <typename Key, typename T, typename Alloc>
Tree<Key, T, Alloc>::Tree(Tree &&other) noexcept {
  InitFakeNode();
  *this = std::move(other);
}

template <typename Key, typename T, typename Alloc>
Tree<Key, T, Alloc>::~Tree() {
  clear();
  node_alloc_.deallocate(this->fake_, 1);
  value_type_alloc_.deallocate(this->fake_->data_, 1);
}

template <typename Key, typename T, typename Alloc>
Tree<Key, T, Alloc> &Tree<Key, T, Alloc>::operator=(const Tree &other) {
  //        if (this == &other) return *this;
  //        this->clear();
  //        for (auto i = other.begin(); i != other.end(); ++i) {
  //            insert_node(*i);
  //        }
  //        return *this;

  if (this != &other) {
    this->clear();
    for (auto i = other.begin(); i != other.end(); ++i) {
      insert_node(*i);
    }
  }
  return *this;
}

template <typename Key, typename T, typename Alloc>
Tree<Key, T, Alloc> &Tree<Key, T, Alloc>::operator=(Tree &&other) noexcept {
  //  if (this == &other) return *this;
  //  std::swap(this->size_, other.size_);
  //  std::swap(fake_, other.fake_);
  //  return *this;
  if (this != &other) {
    std::swap(this->size_, other.size_);
    std::swap(fake_, other.fake_);
  }
  return *this;
}

//_____MODIFIERS____
template <typename Key, typename T, typename Alloc>
void Tree<Key, T, Alloc>::clear() {
  clearUtil(root_);
  root_ = nullptr;
  size_ = 0;
}

// template <typename Key, typename T, typename Alloc>
// std::pair<iterator, bool> Tree<Key, T, Alloc>::insert_node(const Key &key, T
// value) {
//   bool is_node_create = false;
//   auto node = AddNodeByCondition(this->root_, key, value, this->root_,
//   is_node_create); if (is_node_create) {
//	++this->size_;
//	return s21::Tree<Key, T, Alloc>::iterator(node, fake_);
//   } else {
//	return s21::Tree<Key, T, Alloc>::iterator(FindNode(key), fake_);
//   }
// }

template <typename Key, typename T, typename Alloc>
void Tree<Key, T, Alloc>::erase(const Key &key) {  // iterator pos нужно
  RBT<const Key, T> *find = FindNodeByKey(this->root_, key);
  if (find == this->fake_->parent_) {
    if (find == root_ && find->left_ == this->fake_) {
      this->fake_->parent_ = this->fake_;
    } else {
      this->fake_->parent_ = (--(iterator(find, this->fake_))).node_;
    }
  }
  if (find != this->fake_ && find != nullptr) {
    DelNodeByCondition(find);
  }
  --this->size_;
}

//____ITERATORS_FOR_TREE____
template <typename Key, typename T, typename Alloc>
typename Tree<Key, T, Alloc>::iterator Tree<Key, T, Alloc>::begin() const {
  //        fake_->parent_ = nullptr;
  if (root_)
    return s21::Tree<Key, T, Alloc>::iterator(MinNode(root_), fake_);
  else {
    return s21::Tree<Key, T, Alloc>::iterator(fake_, fake_);
  }
}

template <typename Key, typename T, typename Alloc>
typename Tree<Key, T, Alloc>::iterator Tree<Key, T, Alloc>::end() const {
  //        fake_->parent_ = nullptr;
  //        if (root_) fake_->parent_ = MaxNode(root_);
  return s21::Tree<Key, T, Alloc>::iterator(fake_, fake_);
}

//_____WORKING_WITH_MEMORY_____
template <typename Key, typename T, typename Alloc>
RBT<const Key, T> *Tree<Key, T, Alloc>::CreateNode(const Key &key, T value) {
  RBT<const Key, T> *new_node = node_alloc_.allocate(1);
  try {
    node_alloc_.construct(new_node, RBT<const Key, T>());
  } catch (...) {
    node_alloc_.deallocate(new_node, 1);
  }
  // memory alloc for value in node
  new_node->data_ = value_type_alloc_.allocate(1);
  try {
    value_type_alloc_.construct(new_node->data_,
                                std::pair<const Key, T>(key, value));
  } catch (...) {
    value_type_alloc_.deallocate(new_node->data_, 1);
  }
  new_node->parent_ = nullptr;
  new_node->left_ = new_node->right_ = fake_;
  return new_node;
}

template <typename Key, typename T, typename Alloc>
void Tree<Key, T, Alloc>::RemNode(RBT<const Key, T> *node) {
  value_type_alloc_.destroy(node->data_);
  value_type_alloc_.deallocate(node->data_, 1);
  node_alloc_.destroy(node);
  node_alloc_.deallocate(node, 1);
}

template <typename Key, typename T, typename Alloc>
void Tree<Key, T, Alloc>::InitFakeNode() {
  fake_ = node_alloc_.allocate(1);
  fake_->data_ = value_type_alloc_.allocate(1);
}

template <typename Key, typename T, typename Alloc>
void Tree<Key, T, Alloc>::clearUtil(RBT<const Key, T> *node) {
  if (node == nullptr || node == fake_) return;
  clearUtil(node->left_);
  auto tmp = node->right_;
  RemNode(node);
  clearUtil(tmp);
}

//_____SUPPORT_FOR_INSERT_____
template <typename Key, typename T, typename Alloc>
std::pair<typename Tree<Key, T, Alloc>::iterator, bool>
Tree<Key, T, Alloc>::insert_node(const Key &key, T value) {
  bool is_node_create = false;
  auto node =
      AddNodeByCondition(this->root_, key, value, this->root_, is_node_create);
  std::pair<iterator, bool> pair = std::make_pair(
      s21::Tree<Key, T, Alloc>::iterator(node, fake_), is_node_create);
  if (is_node_create) {
    ++this->size_;
  }
  return pair;
}

template <typename Key, typename T, typename Alloc>
RBT<const Key, T> *Tree<Key, T, Alloc>::AddNodeByCondition(
    RBT<const Key, T> *&node, const Key &key, T value,
    RBT<const Key, T> *&parent, bool &is_node_create) {
  RBT<const Key, T> *temp_node = nullptr;
  if (node == fake_ || root_ == nullptr) {
    node = CreateNode(key, value);
    temp_node = node;
    is_node_create = true;
    if (node != parent) {
      node->parent_ = parent;
    } else {
      node->color_ = BLACK;
    }
    if (node == root_) {
      this->fake_->parent_ = node;
    } else if (node->data_->first > this->fake_->parent_->data_->first) {
      this->fake_->parent_ = node;
    }
    if (parent && parent->color_ == RED) {
      BalanceInsert(node, parent);
    }
  } else if (key < node->data_->first) {
    temp_node =
        AddNodeByCondition(node->left_, key, value, node, is_node_create);
  } else if (node->data_->first < key) {
    temp_node =
        AddNodeByCondition(node->right_, key, value, node, is_node_create);
  } else {
    temp_node = node;
  }
  return temp_node;
}

//_____SUPPORT_FOR_ERASE_____
template <typename Key, typename T, typename Alloc>
void Tree<Key, T, Alloc>::DelNodeByCondition(RBT<const Key, T> *node) {
  if (node->left_ != fake_ && node->right_ != fake_) {
    RBT<const Key, T> *change = MaxNode(node->left_);
    std::swap(change->data_, node->data_);
    DelNodeByCondition(change);
  } else if (node->left_ != fake_) {  // есть один левый ребено
    DelNodeWithOneChild(node, node->left_, node->parent_);
  } else if (node->right_ != fake_) {  // есть один правый ребенок
    DelNodeWithOneChild(node, node->right_, node->parent_);
  } else {  // лист
    if (node->color_ == RED) {
      DelNodeWithoutChild(node, node->parent_);
    } else {
      RBT<const Key, T> *parent = GetFather(node);
      RBT<const Key, T> *brother_of_remote = GetBro(node);
      DelNodeWithoutChild(node, node->parent_);
      if (parent && brother_of_remote) {
        BalanceErase(parent, brother_of_remote);
      }
    }
  }
}

template <typename Key, typename T, typename Alloc>
void Tree<Key, T, Alloc>::DelNodeWithOneChild(RBT<const Key, T> *del_node,
                                              RBT<const Key, T> *child,
                                              RBT<const Key, T> *parent) {
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
  RemNode(del_node);
}

template <typename Key, typename T, typename Alloc>
void Tree<Key, T, Alloc>::DelNodeWithoutChild(RBT<const Key, T> *del_node,
                                              RBT<const Key, T> *parent) {
  if (del_node != root_) {
    if (parent->left_ == del_node) {
      parent->left_ = fake_;
    } else {
      parent->right_ = fake_;
    }
  } else {
    root_ = nullptr;
  }
  RemNode(del_node);
}

//_____FIND_NODE_____
template <typename Key, typename T, typename Alloc>
RBT<const Key, T> *Tree<Key, T, Alloc>::FindNodeByKey(RBT<const Key, T> *node,
                                                      const Key &key) {
  RBT<const Key, T> *ret = nullptr;
  if (node != fake_ && node != nullptr) {
    if (node->data_->first == key) {
      ret = node;
    } else if (key < node->data_->first) {
      ret = FindNodeByKey(node->left_, key);
    } else if (node->data_->first < key) {
      ret = FindNodeByKey(node->right_, key);
    }
  }
  return ret;
}

template <typename Key, typename T, typename Alloc>
RBT<const Key, T> *Tree<Key, T, Alloc>::MinNode(RBT<const Key, T> *node) const {
  RBT<const Key, T> *ret = nullptr;
  if (node != fake_) {
    ret = node;
    if (node->left_ != fake_) {
      ret = MinNode(node->left_);
    }
  }
  return ret;
}

template <typename Key, typename T, typename Alloc>
RBT<const Key, T> *Tree<Key, T, Alloc>::MaxNode(RBT<const Key, T> *node) const {
  RBT<const Key, T> *ret = nullptr;
  if (node != fake_) {
    ret = node;
    if (node->right_ != fake_) {
      ret = MaxNode(node->right_);
    }
  }
  return ret;
}

//_____BALANCE_FUNC____
template <typename Key, typename T, typename Alloc>
void Tree<Key, T, Alloc>::BalanceInsert(RBT<const Key, T> *node,
                                        RBT<const Key, T> *parent) {
  RBT<const Key, T> *bro_parent = GetBro(parent);
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
template <typename Key, typename T, typename Alloc>
void Tree<Key, T, Alloc>::BalanceErase(RBT<const Key, T> *parent,
                                       RBT<const Key, T> *child) {
  if (parent->color_ == RED) {  // 2.1. Отец удаленной ноды красный
    RBT<const Key, T> *grandsonRed = GetRedChild(child);
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
      RBT<const Key, T> *grandsonLeft = GetChildLeft(child);  // внуки
      RBT<const Key, T> *grandsonRight = GetChildRight(child);

      if (grandsonLeft && grandsonLeft->color_ == BLACK) {
        RBT<const Key, T> *great_grandsonRed =
            GetRedChild(grandsonLeft);  // правнуки
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
        RBT<const Key, T> *great_grandsonRed = GetRedChild(grandsonRight);
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
      RBT<const Key, T> *grandsonRed = GetRedChild(child);
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
          RBT<const Key, T> *grandfather = GetFather(parent);
          RBT<const Key, T> *brother_of_parent = GetBro(parent);
          if (grandfather && brother_of_parent) {
            BalanceErase(grandfather, brother_of_parent);
          }
        }
      }
    }
  }
}

//_____ACCESS_FUNC____
template <typename Key, typename T, typename Alloc>
RBT<const Key, T> *Tree<Key, T, Alloc>::GetBro(RBT<const Key, T> *node) {
  RBT<const Key, T> *parent = node->parent_;
  RBT<const Key, T> *ret = nullptr;
  if (parent != nullptr) {
    if (parent->left_ != node) {
      ret = parent->left_;
    } else {
      ret = parent->right_;
    }
  }
  return ret;
}

template <typename Key, typename T, typename Alloc>
RBT<const Key, T> *Tree<Key, T, Alloc>::GetFather(RBT<const Key, T> *node) {
  return node->parent_;
}

template <typename Key, typename T, typename Alloc>
RBT<const Key, T> *Tree<Key, T, Alloc>::GetChildLeft(RBT<const Key, T> *node) {
  return node->left_;
}

template <typename Key, typename T, typename Alloc>
RBT<const Key, T> *Tree<Key, T, Alloc>::GetChildRight(RBT<const Key, T> *node) {
  return node->right_;
}

template <typename Key, typename T, typename Alloc>
RBT<const Key, T> *Tree<Key, T, Alloc>::GetRedChild(
    RBT<const Key, T> *node) {  //м.б. не нужна пров с дед
  RBT<const Key, T> *patent = node->parent_;
  RBT<const Key, T> *grandFather = node->parent_->parent_;
  RBT<const Key, T> *ret = nullptr;

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

//_____CHANGE_FUNC____
template <typename Key, typename T, typename Alloc>
void Tree<Key, T, Alloc>::ChangeColorIfUncleRed(
    RBT<const Key, T> *parent, RBT<const Key, T> *bro_parent,
    RBT<const Key, T> *grand_parent) {
  parent->color_ = bro_parent->color_ = BLACK;
  if (grand_parent != this->root_) {
    grand_parent->color_ = RED;
  }
}

template <typename Key, typename T, typename Alloc>
void Tree<Key, T, Alloc>::ChangeColorAfterBigRotate(
    RBT<const Key, T> *parent, RBT<const Key, T> *grandfather) {
  if (parent) parent->color_ = BLACK;
  if (grandfather) grandfather->color_ = RED;
}

template <typename Key, typename T, typename Alloc>
void Tree<Key, T, Alloc>::SmallRotate(RBT<const Key, T> *node,
                                      DirectionOfRotation direction) {
  RBT<const Key, T> *temp = (direction == RIGHT) ? node->right_ : node->left_;
  RBT<const Key, T> *parent = node->parent_;
  if (direction == RIGHT) {
    node->right_ = parent;
    parent->left_ = temp;
  } else {
    node->left_ = parent;
    parent->right_ = temp;
  }
  RBT<const Key, T> *grandfather = GetFather(parent);
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

template <typename Key, typename T, typename Alloc>
void Tree<Key, T, Alloc>::BigRotate(RBT<const Key, T> *node,
                                    DirectionOfRotation direction) {
  RBT<const Key, T> *parent = node->parent_;
  RBT<const Key, T> *grandfather = GetFather(parent);
  RBT<const Key, T> *temp =
      (direction == RIGHT) ? parent->right_ : parent->left_;
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
  RBT<const Key, T> *great_grandfather = GetFather(grandfather);
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

//____ITERATORS____
template <typename Key, typename T, typename Alloc>
typename Tree<Key, T, Alloc>::Iterator &
Tree<Key, T, Alloc>::Iterator::operator++() {
  this->node_ = PrefIter(this->node_, PLUS_PLUS);
  return *this;
}

template <typename Key, typename T, typename Alloc>
typename Tree<Key, T, Alloc>::Iterator
Tree<Key, T, Alloc>::Iterator::operator++(int) {
  auto temp = s21::Tree<Key, T, Alloc>::iterator(this->node_, this->it_fake_);
  this->node_ = PrefIter(this->node_, PLUS_PLUS);
  return temp;
}

template <typename Key, typename T, typename Alloc>
typename Tree<Key, T, Alloc>::Iterator &
Tree<Key, T, Alloc>::Iterator::operator--() {
  this->node_ = PrefIter(this->node_, MINUS_MINUS);
  return *this;
}

template <typename Key, typename T, typename Alloc>
typename Tree<Key, T, Alloc>::Iterator
Tree<Key, T, Alloc>::Iterator::operator--(int) {
  auto temp = s21::Tree<Key, T, Alloc>::iterator(this->node_, this->it_fake_);
  this->node_ = PrefIter(this->node_, MINUS_MINUS);
  return temp;
}

template <typename Key, typename T, typename Alloc>
std::pair<const Key, T> &Tree<Key, T, Alloc>::Iterator::operator*() {
  return *this->node_->data_;
}

//____SUPPORT_ITERATORS_FUNC____
template <typename Key, typename T, typename Alloc>
RBT<const Key, T> *Tree<Key, T, Alloc>::Iterator::PrefIter(
    RBT<const Key, T> *node, OperatorType mode) {
  if (mode == MINUS_MINUS) {
    if (node == this->it_fake_) {
      node = this->node_->parent_;
      return node;
    }
  }
  // node->left or node->right == this->it_fake_
  if (GetNodeChild(this->node_, mode) == this->it_fake_) {
    // node == node->parent->left or node->parent->right
    while (node == GetNodeParentChild(this->node_, mode)) {
      if (node == this->it_fake_->parent_) {
        node = this->it_fake_;
        return node;
      }
      node = node->parent_;
    }
    node = node->parent_;
    return node;
  }

  if (GetNodeChild(this->node_, mode) != this->it_fake_) {
    node = MaxNode(GetNodeChild(this->node_, mode));
    return node;
  }
}

template <typename Key, typename T, typename Alloc>
RBT<const Key, T> *Tree<Key, T, Alloc>::Iterator::GetNodeChild(
    RBT<const Key, T> *node, OperatorType mode) {
  if (mode == MINUS_MINUS) {
    return node->left_;
  } else {
    return node->right_;
  }
}

template <typename Key, typename T, typename Alloc>
RBT<const Key, T> *Tree<Key, T, Alloc>::Iterator::GetNodeParentChild(
    RBT<const Key, T> *node, OperatorType mode) {
  if (mode == MINUS_MINUS) {
    return node->parent_->left_;
  } else {
    return node->parent_->right_;
  }
}

template <typename Key, typename T, typename Alloc>
RBT<const Key, T> *Tree<Key, T, Alloc>::Iterator::MaxNode(
    RBT<const Key, T> *node) {
  RBT<const Key, T> *ret = nullptr;
  if (node != this->it_fake_) {
    ret = node;
    if (node->right_ != this->it_fake_) {
      ret = MaxNode(node->right_);
    }
  }
  return ret;
}

template <typename Key, typename T, typename Alloc>
RBT<const Key, T> *Tree<Key, T, Alloc>::Iterator::MinNode(
    RBT<const Key, T> *node) {
  RBT<const Key, T> *ret = nullptr;
  if (node != this->it_fake_) {
    ret = node;
    if (node->left_ != this->it_fake_) {
      ret = MinNode(node->left_);
    }
  }
  return ret;
}

//_____FUNCTIONS_FOR_PRINT_____
template <typename Key, typename T, typename Alloc>
void Tree<Key, T, Alloc>::print2DUtil(RBT<const Key, T> *root, int space) {
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

  // Process left child
  print2DUtil(root->left_, space);
}

// Wrapper over print2DUtil()
template <typename Key, typename T, typename Alloc>
void Tree<Key, T, Alloc>::print2D() {
  // Pass initial space count as 0
  print2DUtil(this->root_, 0);
}

template <typename Key, typename T, typename Alloc>
void Tree<Key, T, Alloc>::swap(Tree &other) noexcept {
  using std::swap;
  swap(this->root_, other.root_);
  swap(this->fake_, other.fake_);
  swap(this->size_, other.size_);
  swap(this->node_alloc_, other.node_alloc_);
  swap(this->value_type_alloc_, other.value_type_alloc_);
}

}  // namespace s21

#endif  // S21_CONTAINERS_SRC_SORTED_CONTAINER_RED_BLACK_TREE_H_
