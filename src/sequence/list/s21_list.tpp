// #include "s21_list.h"

#include "s21_list.h"

namespace s21 {
//_____LIST_____
//_____CONSTRUCTORS_AND_DESTRUCTOR_____
template<typename value_type, typename Alloc>
S21List<value_type, Alloc>::S21List(size_type n) {
  InitFakeNode();
  for (auto i = n; i > 0; --i) {
	push_back(0);
  }
}

template<typename value_type, typename Alloc>
S21List<value_type, Alloc>::S21List(
	const std::initializer_list<value_type> &items) {
  InitFakeNode();
  for (auto it = items.begin(); it != items.end(); ++it) {
	push_back(*it);
  }
}

template<typename T, typename Alloc>
S21List<T, Alloc>::S21List(const S21List<T, Alloc> &l) {
  InitFakeNode();
  for (auto i = l.begin(); i != l.end(); ++i) {
	push_back(*i);
  }
}

template<typename value_type, typename Alloc>
S21List<value_type, Alloc>::~S21List() {
  for (;;) {
	auto it = this->begin();
	if (it == this->end()) break;
	pop_back();
  }
  node_alloc_.deallocate(fake_, 1);  // отдельно удаляем память под fake ноду
}

template<typename T, typename Alloc>
S21List<T, Alloc> &S21List<T, Alloc>::operator=(const S21List<T, Alloc> &l) noexcept {
  if (this == &l) return *this;
  this->clear();
  for (auto i = l.begin(); i != l.end(); ++i) {
	push_back(*i);
  }
  return *this;
}

template<typename T, typename Alloc>
S21List<T, Alloc> &S21List<T, Alloc>::operator=(
	S21List<T, Alloc> &&l) noexcept {
  std::swap(this->size_, l.size_);
  std::swap(fake_, l.fake_);
  return *this;
}

//_____LIST_ITERATORS_____
template<typename value_type, typename Alloc>
typename S21List<value_type, Alloc>::iterator
S21List<value_type, Alloc>::begin() const {
  return iterator(fake_->next_);
}

template<typename value_type, typename Alloc>
typename S21List<value_type, Alloc>::iterator S21List<value_type, Alloc>::end()
const {
  return iterator(fake_);
}

//_____LIST_MODIFIERS_____
template<typename T, typename Alloc>
void S21List<T, Alloc>::clear() {
  for (auto i = this->size_; i > 0; --i) {
	pop_back();
  }
}

template<typename T, typename Alloc>
typename S21List<T, Alloc>::iterator S21List<T, Alloc>::insert(
	S21List<T, Alloc>::iterator pos, S21List<T, Alloc>::const_reference value) {
  Node<value_type> *shift_node = pos.node_;
  Node<value_type> *prev_node = shift_node->prev_;
  Node<value_type> *new_node = CreateNode(value);
  new_node->next_ = shift_node;
  new_node->prev_ = prev_node;
  prev_node->next_ = new_node;
  shift_node->prev_ = new_node;
  ++this->size_;  // оригинал также работает, если пришел итератор от другого
  // объекта
  // он не добавляет его в лист, но size увеличивает(ХА-ХА-ХА)
  return iterator(new_node);
}

template<typename T, typename Alloc>
void S21List<T, Alloc>::erase(iterator pos) {
  Node<value_type> *prev_node = pos.node_->prev_;
  Node<value_type> *next_node = pos.node_->next_;
  prev_node->next_ = next_node;
  next_node->prev_ = prev_node;
  RemNode(pos.node_);
  --this->size_;
}

template<typename T, typename Alloc>
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
  ++this->size_;
}

template<typename T, typename Alloc>
void S21List<T, Alloc>::pop_back() {
  Node<T> *temp = fake_->prev_;
  fake_->prev_ = fake_->prev_->prev_;
  fake_->prev_->next_ = fake_;
  RemNode(temp);
  --this->size_;
}

template<typename T, typename Alloc>
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
  ++this->size_;
}

template<typename T, typename Alloc>
void S21List<T, Alloc>::pop_front() {
  Node<T> *temp = fake_->next_;
  fake_->next_ = fake_->next_->next_;
  fake_->next_->prev_ = fake_;
  RemNode(temp);
  --this->size_;
}

template<typename T, typename Alloc>
void S21List<T, Alloc>::swap(S21List<T, Alloc> &other) {
  std::swap(fake_, other.fake_);
  std::swap(this->size_, other.size_);
}

template<typename T, typename Alloc>
void S21List<T, Alloc>::merge(S21List<T, Alloc> &other) {
  if (this != &other) {
	auto it = this->begin();
	auto it_other = other.begin();
	while (!other.empty()) {
	  if (it == this->end()) {  // если дошли до конца первого списка
		this->insert(it, *it_other);
		auto temp = it_other;
		++it_other;
		other.erase(temp);
	  } else if (*it > *it_other) {
		this->insert(it, *it_other);
		auto temp = it_other;
		++it_other;
		other.erase(temp);
	  } else {
		++it;
	  }
	}
  }
}

template<typename T, typename Alloc>
void S21List<T, Alloc>::splice(const_iterator pos, S21List<T, Alloc> &other) {
  Node<T> *prev = pos.node_->prev_;
  prev->next_ = other.fake_->next_;       // prev pos <-> first elem other
  other.fake_->next_->prev_ = prev;       // first elem other <-> prev pos
  pos.node_->prev_ = other.fake_->prev_;  // pos <-> last elem other
  other.fake_->prev_->next_ = pos.node_;  // last elem other <-> pos
  this->size_ += other.size_;
  // create empty other list
  other.size_ = 0;
  other.fake_->next_ = other.fake_;
  other.fake_->prev_ = other.fake_;
}

template<typename T, typename Alloc>
void S21List<T, Alloc>::reverse() {
  for (auto it = this->begin(); it != this->end(); --it) {
	if (it == this->end()) break;
	std::swap(it.node_->next_, it.node_->prev_);
  }
  std::swap(fake_->next_, fake_->prev_);
}

template<typename T, typename Alloc>
void S21List<T, Alloc>::unique() {
  auto first = this->begin();
  while (first != this->end()) {
	auto rm_node = first;
	auto next = ++first;
	if (next == this->end()) {
	  break;  // нужно чтобы не было обращение к неинит. переменной
	}
	if (*rm_node == *(next)) {
	  this->erase(rm_node);
	}
  }
}

template<typename T, typename Alloc>
void S21List<T, Alloc>::sort() {
  iterator middle = this->GetMiddleList();
  S21List<T> temp;
  for (auto it = temp.begin(); middle != this->end();) {
	iterator temp_it = middle;
	temp.insert(it, *middle);
	++middle;
	this->erase(temp_it);
	++it;
  }
  if (this->size() != 1) {
	this->sort();
  }
  if (temp.size() != 1) {
	temp.sort();
  }
  this->merge(temp);
}

//_____BONUS_____
template<typename T, typename Alloc>
template<typename... Args>
typename S21List<T, Alloc>::iterator S21List<T, Alloc>::emplace(
	const_iterator pos, Args &&...args) {
  iterator it(pos.node_);
  Node<value_type> *shift_node = pos.node_;
  Node<value_type> *prev_node = shift_node->prev_;

  // memory alloc
  Node<value_type> *new_node = node_alloc_.allocate(1);
  try {
	node_alloc_.construct(new_node, Node<value_type>());
  } catch (...) {
	node_alloc_.deallocate(new_node, 1);
  }
  new_node->value_ = value_type_alloc_.allocate(1);
  try {
	value_type_alloc_.construct(new_node->value_, args...);
  } catch (...) {
	value_type_alloc_.deallocate(new_node->value_, 1);
  }

  new_node->next_ = shift_node;
  new_node->prev_ = prev_node;
  prev_node->next_ = new_node;
  shift_node->prev_ = new_node;
  ++this->size_;
  return iterator(shift_node);
}

template<typename T, typename Alloc>
template<typename... Args>
void S21List<T, Alloc>::emplace_back(Args &&...args) {
//  push_back(std::forward<Args>(args) ...);
// Переписать все в одну функцию ->>

  Node<value_type> *new_node = node_alloc_.allocate(1);
  try {
	node_alloc_.construct(new_node, Node<value_type>());
  } catch (...) {
	node_alloc_.deallocate(new_node, 1);
  }
  new_node->value_ = value_type_alloc_.allocate(1);
  try {
	value_type_alloc_.construct(new_node->value_, args...);
  } catch (...) {
	value_type_alloc_.deallocate(new_node->value_, 1);
  }


  if (this->begin() != this->end()) {
	fake_->prev_->next_ = new_node;
	new_node->prev_ = fake_->prev_;
	fake_->prev_ = new_node;
  } else {
	fake_->next_ = fake_->prev_ = new_node;
  }
  fake_->prev_->next_ = fake_;
  fake_->next_->prev_ = fake_;
  ++this->size_;

}

template<typename T, typename Alloc>
template<typename... Args>
void S21List<T, Alloc>::emplace_front(Args &&...args) {
  push_front(std::forward<Args>(args) ...);
}

//_____SUPPORT_FUNC_____
template<typename value_type, typename Alloc>
Node<value_type> *S21List<value_type, Alloc>::CreateNode(
	const_reference value) {
  Node<value_type> *new_node = node_alloc_.allocate(1);
  try {
	node_alloc_.construct(new_node, Node<value_type>());
  } catch (...) {
	node_alloc_.deallocate(new_node, 1);
  }
  new_node->value_ = value_type_alloc_.allocate(1);
  try {
	value_type_alloc_.construct(new_node->value_, value);
  } catch (...) {
	value_type_alloc_.deallocate(new_node->value_, 1);
  }

  return new_node;
}

template<typename value_type, typename Alloc>
void S21List<value_type, Alloc>::RemNode(Node<value_type> *node) {
  value_type_alloc_.destroy(node->value_);
  value_type_alloc_.deallocate(node->value_, 1);
  node_alloc_.destroy(node);
  node_alloc_.deallocate(node, 1);
}

template<typename value_type, typename Alloc>
void S21List<value_type, Alloc>::InitFakeNode() {
  fake_ = node_alloc_.allocate(1);
  fake_->prev_ = fake_;
  fake_->next_ = fake_;
}

template<typename value_type, typename Alloc>
typename S21List<value_type, Alloc>::iterator
S21List<value_type, Alloc>::GetMiddleList() {
  auto it_fast = this->begin();
  auto it_slow = this->begin();
  auto it_fake = this->end();
  for (; it_fast != it_fake && ++it_fast != it_fake;) {
	++it_slow;
	++it_fast;
  }
  return it_slow;
}

template<typename value_type, typename Alloc>
void S21List<value_type, Alloc>::print() {
  std::cout << "size = " << this->size_ << std::endl;
  Node<value_type> *temp = fake_->next_;
  for (auto i = this->size_; i > 0; --i) {
	std::cout << temp->value_ << ' ';
	temp = temp->next_;
  }
  std::cout << std::endl;
}

//_____Iterator_____
template<typename value_type, typename Alloc>
typename S21List<value_type, Alloc>::Iterator &
S21List<value_type, Alloc>::Iterator::operator++() {
  this->node_ = this->node_->next_;
  return *this;
}

template<typename value_type, typename Alloc>
typename S21List<value_type, Alloc>::Iterator
S21List<value_type, Alloc>::Iterator::operator++(int) {
  Iterator temp(*this);
  this->node_ = this->node_->next_;
  return temp;
}

template<typename value_type, typename Alloc>
typename S21List<value_type, Alloc>::Iterator &
S21List<value_type, Alloc>::Iterator::operator--() {
  this->node_ = this->node_->prev_;
  return *this;
}

template<typename value_type, typename Alloc>
typename S21List<value_type, Alloc>::Iterator
S21List<value_type, Alloc>::Iterator::operator--(int) {
  Iterator temp(*this);
  this->node_ = this->node_->prev_;
  return temp;
}

template<typename value_type, typename Alloc>
typename S21List<value_type, Alloc>::Iterator &
S21List<value_type, Alloc>::Iterator::operator=(const Iterator &other) {
  this->node_ = other.node_;
  return *this;
}

}  // namespace s21
