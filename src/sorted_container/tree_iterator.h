//
// Created by Violator Emilie on 2/10/23.
//

#ifndef S21_CONTAINERS_SRC_SORTED_CONTAINER_TREE_ITERATOR_H_
#define S21_CONTAINERS_SRC_SORTED_CONTAINER_TREE_ITERATOR_H_

#include <cstddef>
#include <initializer_list>
#include <iostream>
#include <memory>
#include <queue>
#include <utility>
#include <valarray>
#include "rbt_node.h"


namespace s21 {

enum OperatorType { PLUS_PLUS, MINUS_MINUS };

enum Duplicate { WITH_DUPLICATE, WITHOUT_DUPLICATE };

//template <typename const Key, typename T = int>
class ConstIterator {
 public:
//  friend Tree;  // need for access node in tree
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

// protected:
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

//template <typename const Key, typename T = int>
class Iterator : public ConstIterator {
 public:
  Iterator() { this->node_ = nullptr; }
  Iterator(const Iterator &other) : ConstIterator(other) {}

  std::pair<const Key, T> &operator*() {
	return *this->node_->data_;
  }

 private:
  explicit Iterator(RBT<const Key, T> *pt, RBT<const Key, T> *fake) {
	this->node_ = pt;
	this->it_fake_ = fake;
  }
};

//____ITERATORS____

ConstIterator &ConstIterator::operator++() {
  this->node_ = PrefIter(this->node_, PLUS_PLUS);
  return *this;
}

ConstIterator ConstIterator::operator++(int) {
  auto temp =
	  s21::Tree<Key, T, Compare, Alloc>::iterator(this->node_, this->it_fake_);
  this->node_ = PrefIter(this->node_, PLUS_PLUS);
  return temp;
}

ConstIterator &ConstIterator::operator--() {
  this->node_ = PrefIter(this->node_, MINUS_MINUS);
  return *this;
}

ConstIterator ConstIterator::operator--(int) {
  auto temp = iterator(this->node_, this->it_fake_);
  this->node_ = PrefIter(this->node_, MINUS_MINUS);
  return temp;
}

std::pair<const Key, T> &Tree<Key, T, Compare, Alloc>::Iterator::operator*() {
  return *this->node_->data_;
}

//____SUPPORT_ITERATORS_FUNC____

RBT<const Key, T> *ConstIterator::PrefIter(RBT<const Key, T> *node, OperatorType mode) {

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


RBT<const Key, T> *ConstIterator::GetNodeChild(
	RBT<const Key, T> *node, OperatorType mode) {
  if (mode == MINUS_MINUS) {
	return node->left_;
  } else {
	return node->right_;
  }
}


RBT<const Key, T> *ConstIterator::GetNodeParentChild(
	RBT<const Key, T> *node, OperatorType mode) {
  if (mode == MINUS_MINUS) {
	return node->parent_->left_;
  } else {
	return node->parent_->right_;
  }
}


RBT<const Key, T> *ConstIterator::MaxNode(
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


RBT<const Key, T> *ConstIterator::MinNode(
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

//template <typename const Key, typename T = int>
//class Iterator : public ConstIterator {
// public:
//  Iterator() { this->node_ = nullptr; }
//  Iterator(const Iterator &other) : ConstIterator(other) {}
//
//  std::pair<const Key, T> &operator*() {
//	return *this->node_->data_;
//  }
//  Iterator &operator=(const Iterator &other) {
//  this->node_ = other.node_;
//  return *this;
//  }
//
// private:
//  explicit Iterator(RBT<const Key, T> *pt, RBT<const Key, T> *fake) {
//	this->node_ = pt;
//	this->it_fake_ = fake;
//  }
//};
//
////____ITERATORS____
//
//template<const Key, typename T>
//ConstIterator &ConstIterator<const Key, T>::operator++() {
//  this->node_ = PrefIter(this->node_, PLUS_PLUS);
//  return *this;
//}
//
//template<const Key, typename T>
//ConstIterator ConstIterator<const Key, T>::operator++(int) {
//  auto temp =
//	  s21::Tree<Key, T, Compare, Alloc>::iterator(this->node_, this->it_fake_);
//  this->node_ = PrefIter(this->node_, PLUS_PLUS);
//  return temp;
//}
//
//template<const Key, typename T>
//ConstIterator &ConstIterator<const Key, T>::operator--() {
//  this->node_ = PrefIter(this->node_, MINUS_MINUS);
//  return *this;
//}
//
//template<const Key, typename T>
//ConstIterator ConstIterator<const Key, T>::operator--(int) {
//  auto temp =
//	  s21::Tree<Key, T, Compare, Alloc>::iterator(this->node_, this->it_fake_);
//  this->node_ = PrefIter(this->node_, MINUS_MINUS);
//  return temp;
//}
//
//
//template <typename Key, typename T, typename Compare, typename Alloc>
//std::pair<const Key, T> &Tree<Key, T, Compare, Alloc>::Iterator::operator*() {
//  return *this->node_->data_;
//}
//
//template <typename Key, typename T, typename Compare, typename Alloc>
//typename Tree<Key, T, Compare, Alloc>::Iterator &
//Tree<Key, T, Compare, Alloc>::Iterator::operator=(const Tree::Iterator &other) {
//  this->node_ = other.node_;
//  return *this;
//}
//
////____SUPPORT_ITERATORS_FUNC____
//
//
//template<const Key, typename T>
//RBT<const Key, T> *ConstIterator<const Key, T>::PrefIter(RBT<const Key, T> *node,OperatorType mode) {
//
//
//  if (mode == MINUS_MINUS) {
//	if (node == this->it_fake_) {
//	  node = this->node_->parent_;
//	  return node;
//	}
//  } else {
//	if (node == this->it_fake_->parent_) {
//	  node = this->it_fake_;
//	  return node;
//	}
//  }
//  // node->left or node->right == this->it_fake_
//  if (GetNodeChild(this->node_, mode) == this->it_fake_) {
//	// node == node->parent->left or node->parent->right
//	while (node == GetNodeParentChild(this->node_, mode)) {
//	  if (node == this->it_fake_->parent_) {
//		node = this->it_fake_;
//		return node;
//	  }
//	  node = node->parent_;
//	}
//	node = node->parent_;
//	return node;
//  } else {
//	if (mode == MINUS_MINUS) {
//	  node = MaxNode(GetNodeChild(this->node_, mode));
//	} else {
//	  node = MinNode(GetNodeChild(this->node_, mode));
//	}
//	return node;
//  }
//
//}
//
//
//template<const Key, typename T>
//RBT<const Key, T> *ConstIterator<const Key, T>::GetNodeChild(
//	RBT<const Key, T> *node, OperatorType mode) {
//  if (mode == MINUS_MINUS) {
//	return node->left_;
//  } else {
//	return node->right_;
//  }
//}
//
//template<const Key, typename T>
//RBT<const Key, T> *ConstIterator<const Key, T>::GetNodeParentChild(
//	RBT<const Key, T> *node, OperatorType mode) {
//  if (mode == MINUS_MINUS) {
//	return node->parent_->left_;
//  } else {
//	return node->parent_->right_;
//  }
//}
//
//template<const Key, typename T>
//RBT<const Key, T> *ConstIterator<const Key, T>::MaxNode(
//	RBT<const Key, T> *node) {
//  RBT<const Key, T> *ret = nullptr;
//  if (node != this->it_fake_) {
//	ret = node;
//	if (node->right_ != this->it_fake_) {
//	  ret = MaxNode(node->right_);
//	}
//  }
//  return ret;
//}
//
//template<const Key, typename T>
//RBT<const Key, T> *ConstIterator<const Key, T>::MinNode(
//	RBT<const Key, T> *node) {
//  RBT<const Key, T> *ret = nullptr;
//  if (node != this->it_fake_) {
//	ret = node;
//	if (node->left_ != this->it_fake_) {
//	  ret = MinNode(node->left_);
//	}
//  }
//  return ret;
//}


}  // namespace s21

#endif //S21_CONTAINERS_SRC_SORTED_CONTAINER_TREE_ITERATOR_H_
