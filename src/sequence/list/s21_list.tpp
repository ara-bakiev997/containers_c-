// #include "s21_list.h"

#include "s21_list.h"

namespace s21 {
//_____LIST_____
//_____CONSTRUCTORS_AND_DESTRUCTOR_____
template <typename value_type, typename Alloc>
S21List<value_type, Alloc>::S21List(size_type n) {
  InitFakeNode();
  for (auto i = n; i > 0; --i) {
    push_back(0);
  }
}

template <typename value_type, typename Alloc>
S21List<value_type, Alloc>::S21List(
    const std::initializer_list<value_type> &items) {
  InitFakeNode();
  for (auto it = items.begin(); it != items.end(); ++it) {
    push_back(*it);
  }
}

template <typename T, typename Alloc>
S21List<T, Alloc>::S21List(const S21List<T, Alloc> &l) {
  InitFakeNode();
  for (auto i = l.begin(); i != l.end(); ++i) {
    push_back(*i);
  }
}

template <typename value_type, typename Alloc>
S21List<value_type, Alloc>::~S21List() {
  for (;;) {
    auto it = this->begin();
    if (it == this->end()) break;
    pop_back();
  }
  alloc_.deallocate(fake_, 1);  // отдельно удаляем память под fake ноду
}

template <typename T, typename Alloc>
S21List<T, Alloc> &S21List<T, Alloc>::operator=(
    S21List<T, Alloc> &&l) noexcept {
  std::swap(size_, l.size_);
  std::swap(fake_, l.fake_);
  return *this;
}

//_____LIST_ELEMENT_ACCESS_____
//_____LIST_ITERATORS_____
template <typename value_type, typename Alloc>
typename S21List<value_type, Alloc>::iterator
S21List<value_type, Alloc>::begin() {
  iterator temp(fake_->next_);
  return temp;
}

template <typename value_type, typename Alloc>
typename S21List<value_type, Alloc>::iterator
S21List<value_type, Alloc>::end() {
  iterator temp(fake_);
  return temp;
}

template <typename value_type, typename Alloc>
typename S21List<value_type, Alloc>::const_iterator
S21List<value_type, Alloc>::begin() const {
  const_iterator temp(fake_->next_);
  return temp;
}

template <typename value_type, typename Alloc>
typename S21List<value_type, Alloc>::const_iterator
S21List<value_type, Alloc>::end() const {
  const_iterator temp(fake_);
  return temp;
}

// template <typename value_type>
// typename S21List<value_type>::iterator S21List<value_type>::end() {
//  iterator temp(&tail_->value_);
//  //  iterator temp(tail_);
//  return temp;
//}

//_____LIST_ELEMENT_ACCESS_____
//_____LIST_CAPACITY_____

//_____LIST_MODIFIERS_____
template <typename T, typename Alloc>
void S21List<T, Alloc>::clear() {
  for (auto i = size_; i > 0; --i) {
    pop_back();
  }
}

template <typename T, typename Alloc>
typename S21List<T, Alloc>::iterator S21List<T, Alloc>::insert(
    S21List<T, Alloc>::iterator pos, S21List<T, Alloc>::const_reference value) {
  Node<value_type> *shift_node = pos.AccessNode();
  Node<value_type> *prev_node = shift_node->prev_;
  Node<value_type> *new_node = CreateNode(value);
  new_node->next_ = shift_node;
  new_node->prev_ = prev_node;
  prev_node->next_ = new_node;
  shift_node->prev_ = new_node;
  ++size_;  // оригинал также работает, если пришел итератор от другого объекта
            // он не добавляет его в лист, но size увеличивает(ХА-ХА-ХА)
  return iterator(new_node);
}

template <typename T, typename Alloc>
void S21List<T, Alloc>::erase(iterator pos) {
  Node<value_type> *prev_node = pos.AccessNode()->prev_;
  Node<value_type> *next_node = pos.AccessNode()->next_;
  prev_node->next_ = next_node;
  next_node->prev_ = prev_node;
  RemNode(pos.AccessNode());
  --size_;
}

template <typename T, typename Alloc>
void S21List<T, Alloc>::push_back(const_reference value) {
  Node<value_type> *temp = CreateNode(value);
  if (this->begin() != this->end()) {
    fake_->prev_->next_ = temp;
    temp->prev_ = fake_->prev_;
    fake_->prev_ = temp;
  } else {
    fake_->next_ = fake_->prev_ = temp;
  }
  fake_->prev_->next_ = fake_;
  fake_->next_->prev_ = fake_;
  ++size_;
}

template <typename T, typename Alloc>
void S21List<T, Alloc>::pop_back() {
  Node<T> *temp = fake_->prev_;
  fake_->prev_ = fake_->prev_->prev_;
  fake_->prev_->next_ = fake_;
  RemNode(temp);
  --size_;
}

template <typename T, typename Alloc>
void S21List<T, Alloc>::push_front(const_reference value) {
  Node<value_type> *temp = CreateNode(value);
  if (this->begin() != this->end()) {
    fake_->next_->prev_ = temp;
    temp->next_ = fake_->next_;
    fake_->next_ = temp;
  } else {
    fake_->next_ = fake_->prev_ = temp;
  }
  fake_->prev_->next_ = fake_;
  fake_->next_->prev_ = fake_;
  ++size_;
}

template <typename T, typename Alloc>
void S21List<T, Alloc>::pop_front() {
  Node<T> *temp = fake_->next_;
  fake_->next_ = fake_->next_->next_;
  fake_->next_->prev_ = fake_;
  RemNode(temp);
  --size_;
}

template <typename T, typename Alloc>
void S21List<T, Alloc>::swap(S21List<T, Alloc> &other) {
  std::swap(fake_, other.fake_);
  std::swap(size_, other.size_);
}

template <typename T, typename Alloc>
void S21List<T, Alloc>::splice(const_iterator pos, S21List<T, Alloc> &other) {
  Node<T> *prev = pos.node_->prev_;
  prev->next_ = other.fake_->next_;       // prev pos <-> first elem other
  other.fake_->next_->prev_ = prev;       // first elem other <-> prev pos
  pos.node_->prev_ = other.fake_->prev_;  // pos <-> last elem other
  other.fake_->prev_->next_ = pos.node_;  // last elem other <-> pos
  size_ += other.size_;
  // create empty other list
  other.size_ = 0;
  other.fake_->next_ = other.fake_;
  other.fake_->prev_ = other.fake_;
}

template <typename T, typename Alloc>
void S21List<T, Alloc>::reverse() {
  auto it = this->begin();
  for (;;) {
    if (it == this->end()) break;
    Node<T> *temp = it.node_->next_;
    it.node_->next_ = it.node_->prev_;
    it.node_->prev_ = temp;
    ++it;
  }
  Node<T> *temp = fake_->next_;
  fake_->next_ = fake_->prev_;
  fake_->prev_ = temp;
}

//_____SUPPORT_FUNC_____
template <typename value_type, typename Alloc>
Node<value_type> *S21List<value_type, Alloc>::CreateNode(
    const_reference value) {
  Node<value_type> *new_node = alloc_.allocate(1);
  try {
    alloc_.construct(new_node, value);
  } catch (...) {
    alloc_.destroy(new_node);
    alloc_.deallocate(new_node, 1);
  }
  return new_node;
}

template <typename value_type, typename Alloc>
void S21List<value_type, Alloc>::RemNode(Node<value_type> *node) {
  alloc_.destroy(node);
  alloc_.deallocate(node, 1);
}

template <typename value_type, typename Alloc>
void S21List<value_type, Alloc>::InitFakeNode() {
  fake_ = alloc_.allocate(1);
  fake_->prev_ = fake_;
  fake_->next_ = fake_;
}

template <typename value_type, typename Alloc>
void S21List<value_type, Alloc>::print() {
  std::cout << "size = " << size_ << std::endl;
  Node<value_type> *temp = fake_->next_;
  for (auto i = size_; i > 0; --i) {
    std::cout << temp->value_ << ' ';
    temp = temp->next_;
  }
  std::cout << std::endl;
}

//_____ConstIterator_____
template <typename value_type, typename Alloc>
typename S21List<value_type, Alloc>::ConstIterator &
S21List<value_type, Alloc>::ConstIterator::operator++() {
  node_ = node_->next_;
  return *this;
}

template <typename value_type, typename Alloc>
typename S21List<value_type, Alloc>::ConstIterator
S21List<value_type, Alloc>::ConstIterator::operator++(int) {
  ConstIterator temp(*this);
  node_ = node_->next_;
  return temp;
}

template <typename value_type, typename Alloc>
typename S21List<value_type, Alloc>::ConstIterator &
S21List<value_type, Alloc>::ConstIterator::operator--() {
  node_ = node_->prev_;
  return *this;
}

template <typename value_type, typename Alloc>
typename S21List<value_type, Alloc>::ConstIterator
S21List<value_type, Alloc>::ConstIterator::operator--(int) {
  ConstIterator temp(*this);
  node_ = node_->prev_;
  return temp;
}

//_____Iterator_____
// template <typename value_type, typename Alloc>
// typename S21List<value_type, Alloc>::Iterator &
// S21List<value_type, Alloc>::Iterator::operator++() {
//  this->node_ = this->node_->next_;
//  return *this;
//}
//
// template <typename value_type, typename Alloc>
// typename S21List<value_type, Alloc>::Iterator
// S21List<value_type, Alloc>::Iterator::operator++(int) {
//  Iterator temp(*this);
//  this->node_ = this->node_->next_;
//  return temp;
//}
//
// template <typename value_type, typename Alloc>
// typename S21List<value_type, Alloc>::Iterator &
// S21List<value_type, Alloc>::Iterator::operator--() {
//  this->node_ = this->node_->prev_;
//  return *this;
//}
//
// template <typename value_type, typename Alloc>
// typename S21List<value_type, Alloc>::Iterator
// S21List<value_type, Alloc>::Iterator::operator--(int) {
//  Iterator temp(*this);
//  this->node_ = this->node_->prev_;
//  return temp;
//}

template <typename value_type, typename Alloc>
typename S21List<value_type, Alloc>::Iterator &
S21List<value_type, Alloc>::Iterator::operator=(const Iterator &other) {
  this->node_ = other.node_;
  return *this;
}

}  // namespace s21
