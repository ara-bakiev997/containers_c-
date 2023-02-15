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

enum Duplicate { WITH_DUPLICATE, WITHOUT_DUPLICATE };

template <typename Key, typename T> struct RBT {
  RBT() = default;
  ~RBT() = default;

  RBT<const Key, T> *parent_{};
  RBT<const Key, T> *left_{};
  RBT<const Key, T> *right_{};
  enum RBT_colors color_ = RED;
  std::pair<const Key, T> *data_{};
};

template <typename Key, typename T = int, typename Compare = std::less<Key>,
          typename Alloc = std::allocator<std::pair<const Key, T>>>
class Tree {
public:
  using key_type = Key;
  using value_type = std::pair<const Key, T>;
  using reference = value_type &;
  using key_compare = Compare;
  using const_reference = const value_type &;
  using size_type = size_t;
  using ValueTypeAlloc = Alloc;                     // под пару
  using NodeAlloc = typename std::allocator_traits< // под ноду
      Alloc>::template rebind_alloc<RBT<const Key, T>>;

  //____ITERATORS____
  class ConstIterator {
  public:
    friend Tree; // need for access node in tree
    ConstIterator() : node_(nullptr) {}
    ConstIterator(const ConstIterator &other)
        : node_(other.node_), it_fake_(other.it_fake_) {}

    ConstIterator &operator++();
    ConstIterator operator++(int);
    ConstIterator &operator--();
    ConstIterator operator--(int);
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

    //____SUPPORT_ITERATORS_FUNC____
    RBT<const Key, T> *PrefIter(RBT<const Key, T> *node, OperatorType mode);
    RBT<const Key, T> *GetNodeChild(RBT<const Key, T> *node, OperatorType mode);
    RBT<const Key, T> *GetNodeParentChild(RBT<const Key, T> *node,
                                          OperatorType mode);
    RBT<const Key, T> *MaxNode(RBT<const Key, T> *node);
    RBT<const Key, T> *MinNode(RBT<const Key, T> *node);
  };

  class Iterator : public ConstIterator {
  public:
    friend Tree; // need for access node in tree
    Iterator() { this->node_ = nullptr; }
    Iterator(const Iterator &other) : ConstIterator(other) {}

    std::pair<const Key, T> &operator*();
    Iterator &operator=(const Iterator &other);

  private:
    explicit Iterator(RBT<const Key, T> *pt, RBT<const Key, T> *fake) {
      this->node_ = pt;
      this->it_fake_ = fake;
    }
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
  iterator find(const Key &key);

  //____MODIFIERS____
  void clear();
  void erase(iterator pos);

  //____CAPACITY____
  bool empty() { return !this->root_; }
  size_type size() { return this->size_; }
  size_type max_size() { return node_alloc_.max_size(); }
  void swap(Tree &other) noexcept;

  //____ITERATORS_FOR_TREE____
  iterator begin() const;

  iterator end() const;

protected:
  RBT<const Key, T> *root_{};
  RBT<const Key, T> *fake_{};
  size_type size_{};
  key_compare compare_{};
  NodeAlloc node_alloc_{};
  ValueTypeAlloc value_type_alloc_{};

  std::pair<iterator, bool> InsertNode(const Key &key, T value = 0,
                                       Duplicate duplicate = WITHOUT_DUPLICATE);
  RBT<const Key, T> *FindNodeByKey(RBT<const Key, T> *node, const Key &key);
  RBT<const Key, T> *FindNodeByKeyMulti(RBT<const Key, T> *node, const Key &key,
                                        RBT<const Key, T> *&ret);

  friend Iterator;
  friend ConstIterator;

private:
  bool CommonCompareEqual(Key first, Key second);

  //_____WORKING_WITH_MEMORY_____
  RBT<const Key, T> *CreateNode(const Key &key, T value);

  void RemNode(RBT<const Key, T> *node);
  void InitFakeNode();

  void ClearUtil(RBT<const Key, T> *node);

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
  void Case1(RBT<const Key, T> *parent, RBT<const Key, T> *child,
             RBT<const Key, T> *grandsonRed);
  void Case2(RBT<const Key, T> *parent, RBT<const Key, T> *child);
  void Case3(RBT<const Key, T> *parent, RBT<const Key, T> *child,
             RBT<const Key, T> *grandsonRed);

  //_____FIND_NODE_____
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
};

//_____CONSTRUCTOR_AND_DESTRUCTOR____
template <typename Key, typename T, typename Compare, typename Alloc>
Tree<Key, T, Compare, Alloc>::Tree(
    std::initializer_list<value_type> const &items) {
  InitFakeNode();
  for (auto it = items.begin(); it != items.end(); ++it) {
    this->InsertNode(*it);
  }
}

template <typename Key, typename T, typename Compare, typename Alloc>
Tree<Key, T, Compare, Alloc>::Tree(const Tree &other) {
  InitFakeNode();
  for (auto it = other.begin(); it != other.end(); ++it) {
    this->InsertNode(*it);
  }
}

template <typename Key, typename T, typename Compare, typename Alloc>
Tree<Key, T, Compare, Alloc>::Tree(Tree &&other) noexcept {
  InitFakeNode();
  *this = std::move(other);
}

template <typename Key, typename T, typename Compare, typename Alloc>
Tree<Key, T, Compare, Alloc>::~Tree() {
  clear();
  value_type_alloc_.deallocate(this->fake_->data_, 1);
  node_alloc_.deallocate(this->fake_, 1);
}

template <typename Key, typename T, typename Compare, typename Alloc>
Tree<Key, T, Compare, Alloc> &
Tree<Key, T, Compare, Alloc>::operator=(const Tree &other) {
  if (this != &other) {
    this->clear();
    for (auto i = other.begin(); i != other.end(); ++i) {
      InsertNode(*i);
    }
  }
  return *this;
}

template <typename Key, typename T, typename Compare, typename Alloc>
Tree<Key, T, Compare, Alloc> &
Tree<Key, T, Compare, Alloc>::operator=(Tree &&other) noexcept {
  if (this != &other) {
    std::swap(this->size_, other.size_);
    std::swap(fake_, other.fake_);
  }
  return *this;
}

//_____MODIFIERS____
template <typename Key, typename T, typename Compare, typename Alloc>
void Tree<Key, T, Compare, Alloc>::clear() {
  ClearUtil(root_);
  root_ = nullptr;
  size_ = 0;
}

template <typename Key, typename T, typename Compare, typename Alloc>
void Tree<Key, T, Compare, Alloc>::erase(iterator pos) {
  if (pos.node_ == this->fake_->parent_) {
    if (pos.node_ == root_ && pos.node_->left_ == this->fake_) {
      this->fake_->parent_ = this->fake_;
    } else {
      this->fake_->parent_ = (--(iterator(pos.node_, this->fake_))).node_;
    }
  }
  if (pos.node_ != this->fake_ && pos.node_ != nullptr) {
    DelNodeByCondition(pos.node_);
    --this->size_;
  }
}

template <typename Key, typename T, typename Compare, typename Alloc>
void Tree<Key, T, Compare, Alloc>::swap(Tree &other) noexcept {
  using std::swap;
  swap(this->root_, other.root_);
  swap(this->fake_, other.fake_);
  swap(this->size_, other.size_);
  swap(this->node_alloc_, other.node_alloc_);
  swap(this->value_type_alloc_, other.value_type_alloc_);
}

//____ITERATORS_FOR_TREE____
template <typename Key, typename T, typename Compare, typename Alloc>
typename Tree<Key, T, Compare, Alloc>::iterator
Tree<Key, T, Compare, Alloc>::begin() const {
  if (root_)
    return s21::Tree<Key, T, Compare, Alloc>::iterator(MinNode(root_), fake_);
  else {
    return s21::Tree<Key, T, Compare, Alloc>::iterator(fake_, fake_);
  }
}

template <typename Key, typename T, typename Compare, typename Alloc>
typename Tree<Key, T, Compare, Alloc>::iterator
Tree<Key, T, Compare, Alloc>::end() const {
  return s21::Tree<Key, T, Compare, Alloc>::iterator(fake_, fake_);
}

//_____WORKING_WITH_MEMORY_____
template <typename Key, typename T, typename Compare, typename Alloc>
RBT<const Key, T> *Tree<Key, T, Compare, Alloc>::CreateNode(const Key &key,
                                                            T value) {
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

template <typename Key, typename T, typename Compare, typename Alloc>
void Tree<Key, T, Compare, Alloc>::RemNode(RBT<const Key, T> *node) {
  value_type_alloc_.destroy(node->data_);
  value_type_alloc_.deallocate(node->data_, 1);
  node_alloc_.destroy(node);
  node_alloc_.deallocate(node, 1);
}

template <typename Key, typename T, typename Compare, typename Alloc>
void Tree<Key, T, Compare, Alloc>::InitFakeNode() {
  fake_ = node_alloc_.allocate(1);
  fake_->data_ = value_type_alloc_.allocate(1);
}

template <typename Key, typename T, typename Compare, typename Alloc>
void Tree<Key, T, Compare, Alloc>::ClearUtil(RBT<const Key, T> *node) {
  if (node == nullptr || node == fake_)
    return;
  ClearUtil(node->left_);
  auto tmp = node->right_;
  RemNode(node);
  ClearUtil(tmp);
}

//_____SUPPORT_FOR_INSERT_____
template <typename Key, typename T, typename Compare, typename Alloc>
std::pair<typename Tree<Key, T, Compare, Alloc>::iterator, bool>
Tree<Key, T, Compare, Alloc>::InsertNode(const Key &key, T value,
                                         Duplicate duplicate) {
  bool is_node_create = false;
  RBT<const Key, T> *node = nullptr;
  auto find_node = this->FindNodeByKey(this->root_, key);
  if (duplicate == WITHOUT_DUPLICATE) {
    if (!find_node) {
      node = AddNodeByCondition(this->root_, key, value, this->root_,
                                is_node_create);
    }
  } else {
    node = AddNodeByCondition(this->root_, key, value, this->root_,
                              is_node_create);
  }
  if (is_node_create) {
    ++this->size_;
    return std::make_pair(
        s21::Tree<Key, T, Compare, Alloc>::iterator(node, fake_),
        is_node_create);
  } else {
    return std::make_pair(
        s21::Tree<Key, T, Compare, Alloc>::iterator(find_node, fake_),
        is_node_create);
  }
}

template <typename Key, typename T, typename Compare, typename Alloc>
RBT<const Key, T> *Tree<Key, T, Compare, Alloc>::AddNodeByCondition(
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

    } else if (CommonCompareEqual(this->fake_->parent_->data_->first,
                                  node->data_->first)) {
      this->fake_->parent_ = node;
    }
    if (parent && parent->color_ == RED) {
      BalanceInsert(node, parent);
    }
  } else if (this->compare_(key, node->data_->first)) {
    temp_node =
        AddNodeByCondition(node->left_, key, value, node, is_node_create);
  } else {
    temp_node =
        AddNodeByCondition(node->right_, key, value, node, is_node_create);
  }
  return temp_node;
}

//_____SUPPORT_FOR_ERASE_____
template <typename Key, typename T, typename Compare, typename Alloc>
void Tree<Key, T, Compare, Alloc>::DelNodeByCondition(RBT<const Key, T> *node) {
  if (node->left_ != fake_ && node->right_ != fake_) {
    RBT<const Key, T> *change = MaxNode(node->left_);
    std::swap(change->data_, node->data_);
    DelNodeByCondition(change);
  } else if (node->left_ != fake_) { // есть один левый ребено
    DelNodeWithOneChild(node, node->left_, node->parent_);
  } else if (node->right_ != fake_) { // есть один правый ребенок
    DelNodeWithOneChild(node, node->right_, node->parent_);
  } else { // лист
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

template <typename Key, typename T, typename Compare, typename Alloc>
void Tree<Key, T, Compare, Alloc>::DelNodeWithOneChild(
    RBT<const Key, T> *del_node, RBT<const Key, T> *child,
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

template <typename Key, typename T, typename Compare, typename Alloc>
void Tree<Key, T, Compare, Alloc>::DelNodeWithoutChild(
    RBT<const Key, T> *del_node, RBT<const Key, T> *parent) {
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

// 2.1.1  Отец удаленной ноды красный // Брат удаленной ноды красный
template <typename Key, typename T, typename Compare, typename Alloc>
void Tree<Key, T, Compare, Alloc>::Case1(RBT<const Key, T> *parent,
                                         RBT<const Key, T> *child,
                                         RBT<const Key, T> *grandsonRed) {
  if (parent->left_ == child) {         // мы слева от деда
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
  } else {                             // мы справа от деда
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
}

// 2.2.1. Отец удаленной ноды черный // Брат удаленной ноды красный
template <typename Key, typename T, typename Compare, typename Alloc>
void Tree<Key, T, Compare, Alloc>::Case2(RBT<const Key, T> *parent,
                                         RBT<const Key, T> *child) {
  RBT<const Key, T> *grandsonLeft = GetChildLeft(child); // внуки
  if (grandsonLeft && grandsonLeft->color_ == BLACK) {
    RBT<const Key, T> *great_grandsonRed =
        GetRedChild(grandsonLeft); // правнуки
    if (great_grandsonRed) { // 2.2.1.1. есть красный правнук
      if (parent->right_ == child) { // мы справа от отца
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
    } else { // 2.2.1.2 когда нет красного правнука
      if (parent->left_ == child) {
        BigRotate(grandsonLeft, RIGHT); // внимание
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
  }
}

// 2.2.2.1 у брата удаленной ноды есть красные дети
template <typename Key, typename T, typename Compare, typename Alloc>
void Tree<Key, T, Compare, Alloc>::Case3(RBT<const Key, T> *parent,
                                         RBT<const Key, T> *child,
                                         RBT<const Key, T> *grandsonRed) {
  if (parent->left_ == child) {         // мы слева от деда
    if (child->right_ == grandsonRed) { // мы справа от отца
      SmallRotate(grandsonRed, LEFT);
      BigRotate(child, RIGHT);
      grandsonRed->color_ = BLACK;
    } else {
      BigRotate(grandsonRed, RIGHT);
      grandsonRed->color_ = BLACK;
    }
  } else {                             // мы справа от деда
    if (child->left_ == grandsonRed) { // мы слева от отца
      SmallRotate(grandsonRed, RIGHT);
      BigRotate(child, LEFT);
      grandsonRed->color_ = BLACK;
    } else {
      BigRotate(grandsonRed, LEFT);
      grandsonRed->color_ = BLACK;
    }
  }
}

//_____FIND_NODE_____
template <typename Key, typename T, typename Compare, typename Alloc>
typename Tree<Key, T, Compare, Alloc>::iterator
Tree<Key, T, Compare, Alloc>::find(const Key &key) {
  RBT<const Key, T> *ret = nullptr;
  auto ptr = Tree<Key>::FindNodeByKeyMulti(this->root_, key, ret);
  return ptr ? iterator(ptr, this->fake_) : this->end();
}

template <typename Key, typename T, typename Compare, typename Alloc>
RBT<const Key, T> *
Tree<Key, T, Compare, Alloc>::FindNodeByKey(RBT<const Key, T> *node,
                                            const Key &key) {
  RBT<const Key, T> *ret = nullptr;

  if (node != fake_ && node != nullptr) {
    if (node->data_->first == key) {
      ret = node;

    } else if (this->compare_(key, node->data_->first)) {
      ret = FindNodeByKey(node->left_, key);

    } else if (this->compare_(node->data_->first, key)) {
      ret = FindNodeByKey(node->right_, key);
    }
  }
  return ret;
}

template <typename Key, typename T, typename Compare, typename Alloc>
RBT<const Key, T> *Tree<Key, T, Compare, Alloc>::FindNodeByKeyMulti(
    RBT<const Key, T> *node, const Key &key, RBT<const Key, T> *&ret) {
  if (node != fake_ && node != nullptr) {
    if (node->data_->first == key) {
      ret = node;
    }

    if (CommonCompareEqual(key, node->data_->first)) {
      ret = FindNodeByKeyMulti(node->left_, key, ret);

    } else {
      ret = FindNodeByKeyMulti(node->right_, key, ret);
    }
  }
  return ret;
}

template <typename Key, typename T, typename Compare, typename Alloc>
RBT<const Key, T> *
Tree<Key, T, Compare, Alloc>::MinNode(RBT<const Key, T> *node) const {
  RBT<const Key, T> *ret = nullptr;
  if (node != fake_) {
    ret = node;
    if (node->left_ != fake_) {
      ret = MinNode(node->left_);
    }
  }
  return ret;
}

template <typename Key, typename T, typename Compare, typename Alloc>
RBT<const Key, T> *
Tree<Key, T, Compare, Alloc>::MaxNode(RBT<const Key, T> *node) const {
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
template <typename Key, typename T, typename Compare, typename Alloc>
void Tree<Key, T, Compare, Alloc>::BalanceInsert(RBT<const Key, T> *node,
                                                 RBT<const Key, T> *parent) {
  RBT<const Key, T> *bro_parent = GetBro(parent);
  if (parent->color_ == RED) { // в рекурсии нужна проверка
    if (bro_parent != fake_ && bro_parent->color_ == RED) {
      ChangeColorIfUncleRed(parent, bro_parent, GetFather(parent));
      if (GetFather(parent) != root_) {
        BalanceInsert(GetFather(parent),
                      GetFather(parent)->parent_); // рекурсивно для деда
      }
    } else {
      if (parent != root_) {
        if (GetFather(parent) &&
            GetFather(parent)->left_ == parent) { // мы слева от деда
          if (parent->right_ == node) { // мы справа от отца
            SmallRotate(node, LEFT);
            BigRotate(parent, RIGHT); // т.к они поменялись местами
            ChangeColorAfterBigRotate(node, node->right_);
          } else {
            BigRotate(node, RIGHT);
            ChangeColorAfterBigRotate(parent, parent->right_);
          }
        } else {                       // мы справа от деда
          if (parent->left_ == node) { // мы слева от отца
            SmallRotate(node, RIGHT);
            BigRotate(parent, LEFT); // т.к они поменялись местами
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
template <typename Key, typename T, typename Compare, typename Alloc>
void Tree<Key, T, Compare, Alloc>::BalanceErase(RBT<const Key, T> *parent,
                                                RBT<const Key, T> *child) {
  if (parent->color_ == RED) { // 2.1. Отец удаленной ноды красный
    RBT<const Key, T> *grandsonRed = GetRedChild(child);
    if (grandsonRed) { // Брат удаленной ноды красный
      Case1(parent, child, grandsonRed);
    } else { // 2.1.2  // Брат удаленной ноды не красный
      std::swap(parent->color_, child->color_);
    }
  } else { // 2.2. Отец удаленной ноды черный
    if (child->color_ == RED) { // 2.2.1. Брат удаленной ноды красный
      Case2(parent, child);
    } else { // 2.2.2. Брат удаленной ноды черный
      RBT<const Key, T> *grandsonRed = GetRedChild(child);
      if (grandsonRed) { // 2.2.2.1 у брата удаленной ноды есть красные дети
        Case3(parent, child, grandsonRed);
      } else { // 2.2.2.2 у брата удаленной ноды нет красныех детей
        child->color_ = RED;
        if (parent != root_) { // рекурсивно к деду
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
template <typename Key, typename T, typename Compare, typename Alloc>
RBT<const Key, T> *
Tree<Key, T, Compare, Alloc>::GetBro(RBT<const Key, T> *node) {
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

template <typename Key, typename T, typename Compare, typename Alloc>
RBT<const Key, T> *
Tree<Key, T, Compare, Alloc>::GetFather(RBT<const Key, T> *node) {
  return node->parent_;
}

template <typename Key, typename T, typename Compare, typename Alloc>
RBT<const Key, T> *
Tree<Key, T, Compare, Alloc>::GetChildLeft(RBT<const Key, T> *node) {
  return node->left_;
}

template <typename Key, typename T, typename Compare, typename Alloc>
RBT<const Key, T> *
Tree<Key, T, Compare, Alloc>::GetChildRight(RBT<const Key, T> *node) {
  return node->right_;
}

template <typename Key, typename T, typename Compare, typename Alloc>
RBT<const Key, T> *
Tree<Key, T, Compare, Alloc>::GetRedChild(RBT<const Key, T> *node) {
  RBT<const Key, T> *patent = node->parent_;
  RBT<const Key, T> *grandFather = node->parent_->parent_;
  RBT<const Key, T> *ret = nullptr;
  if (grandFather && grandFather->left_ == patent) { // мы слева от дедушки
    if (patent->left_ == node) { // мы слева от отца
      if (node->left_ != fake_ && node->left_->color_ == RED) {
        ret = node->left_;
      } else if (node->right_ != fake_ && node->right_->color_ == RED) {
        ret = node->right_;
      }
    } else { // мы справа от отца
      if (node->right_ != fake_ && node->right_->color_ == RED) {
        ret = node->right_;
      } else if (node->left_ != fake_ && node->left_->color_ == RED) {
        ret = node->left_;
      }
    }
  } else {                        // мы справа от дедушки
    if (patent->right_ == node) { // мы справа от отца
      if (node->right_ != fake_ && node->right_->color_ == RED) {
        ret = node->right_;
      } else if (node->left_ != fake_ && node->left_->color_ == RED) {
        ret = node->left_;
      }
    } else { // мы слева от отца
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
template <typename Key, typename T, typename Compare, typename Alloc>
void Tree<Key, T, Compare, Alloc>::ChangeColorIfUncleRed(
    RBT<const Key, T> *parent, RBT<const Key, T> *bro_parent,
    RBT<const Key, T> *grand_parent) {
  parent->color_ = bro_parent->color_ = BLACK;
  if (grand_parent != this->root_) {
    grand_parent->color_ = RED;
  }
}

template <typename Key, typename T, typename Compare, typename Alloc>
void Tree<Key, T, Compare, Alloc>::ChangeColorAfterBigRotate(
    RBT<const Key, T> *parent, RBT<const Key, T> *grandfather) {
  if (parent)
    parent->color_ = BLACK;
  if (grandfather)
    grandfather->color_ = RED;
}

template <typename Key, typename T, typename Compare, typename Alloc>
void Tree<Key, T, Compare, Alloc>::SmallRotate(RBT<const Key, T> *node,
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
  if (temp != this->fake_) {
    temp->parent_ = parent;
  }
  parent->parent_ = node;
}

template <typename Key, typename T, typename Compare, typename Alloc>
void Tree<Key, T, Compare, Alloc>::BigRotate(RBT<const Key, T> *node,
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
  if (temp != this->fake_) {
    temp->parent_ = grandfather;
  }
  RBT<const Key, T> *great_grandfather = GetFather(grandfather);
  if (great_grandfather) { // связка с прадедом
    if (great_grandfather->left_ == grandfather) {
      great_grandfather->left_ = parent;
    } else {
      great_grandfather->right_ = parent;
    }
  }
  parent->parent_ = great_grandfather;
  grandfather->parent_ = parent;
  if (grandfather == root_) { // если нужно поменять рута
    root_ = parent;
  }
}

//____ITERATORS____
template <typename Key, typename T, typename Compare, typename Alloc>
typename Tree<Key, T, Compare, Alloc>::ConstIterator &
Tree<Key, T, Compare, Alloc>::ConstIterator::operator++() {
  this->node_ = PrefIter(this->node_, PLUS_PLUS);
  return *this;
}

template <typename Key, typename T, typename Compare, typename Alloc>
typename Tree<Key, T, Compare, Alloc>::ConstIterator
Tree<Key, T, Compare, Alloc>::ConstIterator::operator++(int) {
  auto temp =
      s21::Tree<Key, T, Compare, Alloc>::iterator(this->node_, this->it_fake_);
  this->node_ = PrefIter(this->node_, PLUS_PLUS);
  return temp;
}

template <typename Key, typename T, typename Compare, typename Alloc>
typename Tree<Key, T, Compare, Alloc>::ConstIterator &
Tree<Key, T, Compare, Alloc>::ConstIterator::operator--() {
  this->node_ = PrefIter(this->node_, MINUS_MINUS);
  return *this;
}

template <typename Key, typename T, typename Compare, typename Alloc>
typename Tree<Key, T, Compare, Alloc>::ConstIterator
Tree<Key, T, Compare, Alloc>::ConstIterator::operator--(int) {
  auto temp =
      s21::Tree<Key, T, Compare, Alloc>::iterator(this->node_, this->it_fake_);
  this->node_ = PrefIter(this->node_, MINUS_MINUS);
  return temp;
}

template <typename Key, typename T, typename Compare, typename Alloc>
std::pair<const Key, T> &Tree<Key, T, Compare, Alloc>::Iterator::operator*() {
  return *this->node_->data_;
}

template <typename Key, typename T, typename Compare, typename Alloc>
typename Tree<Key, T, Compare, Alloc>::Iterator &
Tree<Key, T, Compare, Alloc>::Iterator::operator=(const Tree::Iterator &other) {
  this->node_ = other.node_;
  return *this;
}

//____SUPPORT_ITERATORS_FUNC____
template <typename Key, typename T, typename Compare, typename Alloc>
RBT<const Key, T> *
Tree<Key, T, Compare, Alloc>::ConstIterator::PrefIter(RBT<const Key, T> *node,
                                                      OperatorType mode) {
  if (mode == MINUS_MINUS) {
    if (node == this->it_fake_) {
      node = this->node_->parent_;
      return node;
    }
  } else {
    if (node == this->it_fake_->parent_) {
      node = this->it_fake_;
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
  } else {
    if (mode == MINUS_MINUS) {
      node = MaxNode(GetNodeChild(this->node_, mode));
    } else {
      node = MinNode(GetNodeChild(this->node_, mode));
    }
    return node;
  }
}

template <typename Key, typename T, typename Compare, typename Alloc>
RBT<const Key, T> *Tree<Key, T, Compare, Alloc>::ConstIterator::GetNodeChild(
    RBT<const Key, T> *node, OperatorType mode) {
  if (mode == MINUS_MINUS) {
    return node->left_;
  } else {
    return node->right_;
  }
}

template <typename Key, typename T, typename Compare, typename Alloc>
RBT<const Key, T> *
Tree<Key, T, Compare, Alloc>::ConstIterator::GetNodeParentChild(
    RBT<const Key, T> *node, OperatorType mode) {
  if (mode == MINUS_MINUS) {
    return node->parent_->left_;
  } else {
    return node->parent_->right_;
  }
}

template <typename Key, typename T, typename Compare, typename Alloc>
RBT<const Key, T> *
Tree<Key, T, Compare, Alloc>::ConstIterator::MaxNode(RBT<const Key, T> *node) {
  RBT<const Key, T> *ret = nullptr;
  if (node != this->it_fake_) {
    ret = node;
    if (node->right_ != this->it_fake_) {
      ret = MaxNode(node->right_);
    }
  }
  return ret;
}

template <typename Key, typename T, typename Compare, typename Alloc>
RBT<const Key, T> *
Tree<Key, T, Compare, Alloc>::ConstIterator::MinNode(RBT<const Key, T> *node) {
  RBT<const Key, T> *ret = nullptr;
  if (node != this->it_fake_) {
    ret = node;
    if (node->left_ != this->it_fake_) {
      ret = MinNode(node->left_);
    }
  }
  return ret;
}

template <typename Key, typename T, typename Compare, typename Alloc>
bool Tree<Key, T, Compare, Alloc>::CommonCompareEqual(Key first, Key second) {
  return this->compare_(first, second) ||
         !(this->compare_(first, second) || this->compare_(second, first));
}

} // namespace s21

#endif // S21_CONTAINERS_SRC_SORTED_CONTAINER_RED_BLACK_TREE_H_
