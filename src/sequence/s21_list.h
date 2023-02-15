#ifndef S21_CONTAINERS_SRC_SEQUENCE_S21_LIST_H_
#define S21_CONTAINERS_SRC_SEQUENCE_S21_LIST_H_

#include <cstddef>
#include <initializer_list>
#include <iostream>
#include <memory>
#include <utility>
#include <valarray>

namespace s21 {
template <typename T> struct Node {
  T *value_{};
  Node *next_{};
  Node *prev_{};
  Node() : value_(), next_(nullptr), prev_(nullptr) {}
  explicit Node(const T &value)
      : value_(value), next_(nullptr), prev_(nullptr) {}
  explicit Node(T &&value)
      : value_(std::move(value)), next_(nullptr), prev_(nullptr) {}
};

template <typename T, typename Alloc = std::allocator<T>> class S21List {
public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = std::size_t;
  using ValueTypeAlloc = Alloc;
  using NodeAlloc =
      typename std::allocator_traits<Alloc>::template rebind_alloc<Node<T>>;

  // Iterators for list
  class ConstIterator {
  public:
    friend S21List; // need for access node in list
    ConstIterator() : node_(nullptr) {}
    explicit ConstIterator(Node<value_type> *pt) : node_(pt) {}
    ConstIterator(const ConstIterator &other) : node_(other.node_) {}
    const_reference operator*() const { return *(node_->value_); }
    ConstIterator &operator++();
    ConstIterator operator++(int);
    ConstIterator &operator--();
    ConstIterator operator--(int);
    bool operator!=(const ConstIterator &other) const {
      return node_ != other.node_;
    }
    bool operator==(const ConstIterator &other) const {
      return node_ == other.node_;
    }

  protected:
    Node<value_type> *node_{};
  };

  class Iterator : public ConstIterator {
  public:
    Iterator() { this->node_ = nullptr; }
    explicit Iterator(Node<value_type> *pt) { this->node_ = pt; }
    Iterator(const Iterator &other) : ConstIterator(other) {}
    reference operator*() { return *(this->node_->value_); }
    Iterator &operator=(const Iterator &other);
  };
  using iterator = Iterator;
  using const_iterator = const ConstIterator;
  // Constructors and destructor
  S21List() { InitFakeNode(); }
  explicit S21List(size_type n);
  S21List(std::initializer_list<value_type> const &items);
  S21List(const S21List &l);
  S21List(S21List &&l) noexcept {
    InitFakeNode();
    *this = std::move(l);
  }
  ~S21List();
  S21List &operator=(const S21List &l) noexcept;
  S21List &operator=(S21List &&l) noexcept;

  // List Element access
  const_reference front() { return *(fake_->next_->value_); }
  const_reference back() { return *(fake_->prev_->value_); }

  // List Iterators
  iterator begin() const;
  iterator end() const;

  // List Capacity
  bool empty() { return !this->size_; }
  size_type size() { return this->size_; }
  size_type max_size() { return node_alloc_.max_size(); }

  // List Modifiers
  void clear();
  iterator insert(iterator pos, const_reference value);
  void erase(iterator pos);
  void push_back(const_reference value);
  void push_back(T &&value);
  void pop_back();
  void push_front(const_reference value);
  void push_front(T &&value);
  void pop_front();
  void swap(S21List &other);
  void merge(S21List &other);
  void splice(const_iterator pos, S21List &other);
  void reverse();
  void unique();
  void sort();

  // Bonus
  template <typename... Args>
  iterator emplace(const_iterator pos, Args &&...args);
  template <typename... Args> void emplace_back(Args &&...args);
  template <typename... Args> void emplace_front(Args &&...args);

private:
  Node<T> *fake_{};
  size_type size_{};
  NodeAlloc node_alloc_{};
  ValueTypeAlloc value_type_alloc_{};
  // Support func
  template <typename... Args> Node<T> *CreateNode(Args &&...args);
  void RemNode(Node<T> *node);
  void InitFakeNode();
  iterator GetMiddleList();
  void ConnectBack(Node<T> *new_node);
  void ConnectFront(Node<T> *new_node);
};

//_____LIST_____
//_____CONSTRUCTORS_AND_DESTRUCTOR_____
template <typename T, typename Alloc> S21List<T, Alloc>::S21List(size_type n) {
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

template <typename T, typename Alloc> S21List<T, Alloc>::~S21List() {
  for (;;) {
    auto it = this->begin();
    if (it == this->end())
      break;
    pop_back();
  }
  value_type_alloc_.deallocate(fake_->value_, 1);
  node_alloc_.deallocate(fake_, 1); // отдельно удаляем память под fake ноду
}

template <typename T, typename Alloc>
S21List<T, Alloc> &
S21List<T, Alloc>::operator=(const S21List<T, Alloc> &l) noexcept {
  if (this == &l)
    return *this;
  this->clear();
  for (auto i = l.begin(); i != l.end(); ++i) {
    push_back(*i);
  }
  return *this;
}

template <typename T, typename Alloc>
S21List<T, Alloc> &
S21List<T, Alloc>::operator=(S21List<T, Alloc> &&l) noexcept {
  std::swap(this->size_, l.size_);
  std::swap(fake_, l.fake_);
  return *this;
}

//_____LIST_ITERATORS_____
template <typename T, typename Alloc>
typename S21List<T, Alloc>::iterator S21List<T, Alloc>::begin() const {
  return iterator(fake_->next_);
}

template <typename T, typename Alloc>
typename S21List<T, Alloc>::iterator S21List<T, Alloc>::end() const {
  return iterator(fake_);
}

//_____LIST_MODIFIERS_____
template <typename T, typename Alloc> void S21List<T, Alloc>::clear() {
  for (auto i = this->size_; i > 0; --i) {
    pop_back();
  }
}

template <typename T, typename Alloc>
typename S21List<T, Alloc>::iterator
S21List<T, Alloc>::insert(S21List<T, Alloc>::iterator pos,
                          S21List<T, Alloc>::const_reference value) {
  Node<value_type> *shift_node = pos.node_;
  Node<value_type> *prev_node = shift_node->prev_;
  Node<value_type> *new_node = CreateNode(value);
  new_node->next_ = shift_node;
  new_node->prev_ = prev_node;
  prev_node->next_ = new_node;
  shift_node->prev_ = new_node;
  ++this->size_; // оригинал также работает, если пришел итератор от другого
                 // объекта он не добавляет его в лист, но size увеличивает
  return iterator(new_node);
}

template <typename T, typename Alloc>
void S21List<T, Alloc>::erase(iterator pos) {
  Node<value_type> *prev_node = pos.node_->prev_;
  Node<value_type> *next_node = pos.node_->next_;
  prev_node->next_ = next_node;
  next_node->prev_ = prev_node;
  RemNode(pos.node_);
  --this->size_;
}

template <typename T, typename Alloc>
void S21List<T, Alloc>::push_back(const_reference value) {
  Node<value_type> *temp = CreateNode(value);
  ConnectBack(temp);
  ++this->size_;
}

template <typename T, typename Alloc>
void S21List<T, Alloc>::push_back(T &&value) {
  Node<value_type> *temp = CreateNode(std::move(value));
  ConnectBack(temp);
  ++this->size_;
}

template <typename T, typename Alloc> void S21List<T, Alloc>::pop_back() {
  Node<T> *temp = fake_->prev_;
  fake_->prev_ = fake_->prev_->prev_;
  fake_->prev_->next_ = fake_;
  RemNode(temp);
  --this->size_;
}

template <typename T, typename Alloc>
void S21List<T, Alloc>::push_front(const_reference value) {
  Node<value_type> *temp = CreateNode(value);
  ConnectFront(temp);
  ++this->size_;
}

template <typename T, typename Alloc>
void S21List<T, Alloc>::push_front(T &&value) {
  Node<value_type> *temp = CreateNode(std::move(value));
  ConnectFront(temp);
  ++this->size_;
}

template <typename T, typename Alloc> void S21List<T, Alloc>::pop_front() {
  Node<T> *temp = fake_->next_;
  fake_->next_ = fake_->next_->next_;
  fake_->next_->prev_ = fake_;
  RemNode(temp);
  --this->size_;
}

template <typename T, typename Alloc>
void S21List<T, Alloc>::swap(S21List<T, Alloc> &other) {
  std::swap(fake_, other.fake_);
  std::swap(this->size_, other.size_);
}

template <typename T, typename Alloc>
void S21List<T, Alloc>::merge(S21List<T, Alloc> &other) {
  if (this != &other) {
    auto it = this->begin();
    auto it_other = other.begin();
    while (!other.empty()) {
      if (it == this->end()) { // если дошли до конца первого списка
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

template <typename T, typename Alloc>
void S21List<T, Alloc>::splice(const_iterator pos, S21List<T, Alloc> &other) {
  Node<T> *prev = pos.node_->prev_;
  prev->next_ = other.fake_->next_;      // prev pos <-> first elem other
  other.fake_->next_->prev_ = prev;      // first elem other <-> prev pos
  pos.node_->prev_ = other.fake_->prev_; // pos <-> last elem other
  other.fake_->prev_->next_ = pos.node_; // last elem other <-> pos
  this->size_ += other.size_;
  // create empty other list
  other.size_ = 0;
  other.fake_->next_ = other.fake_;
  other.fake_->prev_ = other.fake_;
}

template <typename T, typename Alloc> void S21List<T, Alloc>::reverse() {
  for (auto it = this->begin(); it != this->end(); --it) {
    if (it == this->end())
      break;
    std::swap(it.node_->next_, it.node_->prev_);
  }
  std::swap(fake_->next_, fake_->prev_);
}

template <typename T, typename Alloc> void S21List<T, Alloc>::unique() {
  auto first = this->begin();
  while (first != this->end()) {
    auto rm_node = first;
    auto next = ++first;
    if (next == this->end()) {
      break; // нужно чтобы не было обращение к неинит. переменной
    }
    if (*rm_node == *(next)) {
      this->erase(rm_node);
    }
  }
}

template <typename T, typename Alloc> void S21List<T, Alloc>::sort() {
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
template <typename T, typename Alloc>
template <typename... Args>
typename S21List<T, Alloc>::iterator
S21List<T, Alloc>::emplace(const_iterator pos, Args &&...args) {
  iterator it(pos.node_);
  return insert(it,
                value_type(std::forward<Args>(
                    args)...)); // к сожалению, вызывается конструктор
                                // копирования.. Или делать без insert
}

template <typename T, typename Alloc>
template <typename... Args>
void S21List<T, Alloc>::emplace_back(Args &&...args) {
  Node<value_type> *new_node = CreateNode(std::forward<Args>(args)...);
  ConnectBack(new_node);
  ++this->size_;
}

template <typename T, typename Alloc>
template <typename... Args>
void S21List<T, Alloc>::emplace_front(Args &&...args) {
  Node<value_type> *new_node = CreateNode(std::forward<Args>(args)...);
  ConnectFront(new_node);
  ++this->size_;
}

//_____SUPPORT_FUNC_____
template <typename T, typename Alloc>
template <typename... Args>
Node<T> *S21List<T, Alloc>::CreateNode(Args &&...args) {
  // memory alloc for node
  Node<value_type> *new_node = node_alloc_.allocate(1);
  try {
    node_alloc_.construct(new_node, Node<value_type>());
  } catch (...) {
    node_alloc_.deallocate(new_node, 1);
  }
  // memory alloc for value in node
  new_node->value_ = value_type_alloc_.allocate(1);
  try {
    value_type_alloc_.construct(new_node->value_, std::forward<Args>(args)...);
  } catch (...) {
    value_type_alloc_.deallocate(new_node->value_, 1);
  }
  return new_node;
}

template <typename T, typename Alloc>
void S21List<T, Alloc>::RemNode(Node<T> *node) {
  value_type_alloc_.destroy(node->value_);
  value_type_alloc_.deallocate(node->value_, 1);
  node_alloc_.destroy(node);
  node_alloc_.deallocate(node, 1);
}

template <typename T, typename Alloc> void S21List<T, Alloc>::InitFakeNode() {
  fake_ = node_alloc_.allocate(1);
  fake_->value_ = value_type_alloc_.allocate(1);
  fake_->prev_ = fake_;
  fake_->next_ = fake_;
}

template <typename T, typename Alloc>
typename S21List<T, Alloc>::iterator S21List<T, Alloc>::GetMiddleList() {
  auto it_fast = this->begin();
  auto it_slow = this->begin();
  auto it_fake = this->end();
  for (; it_fast != it_fake && ++it_fast != it_fake;) {
    ++it_slow;
    ++it_fast;
  }
  return it_slow;
}

template <typename T, typename Alloc>
void S21List<T, Alloc>::ConnectBack(Node<T> *new_node) {
  if (this->begin() != this->end()) {
    fake_->prev_->next_ = new_node;
    new_node->prev_ = fake_->prev_;
    fake_->prev_ = new_node;
  } else {
    fake_->next_ = fake_->prev_ = new_node;
  }
  fake_->prev_->next_ = fake_;
  fake_->next_->prev_ = fake_;
}

template <typename T, typename Alloc>
void S21List<T, Alloc>::ConnectFront(Node<T> *new_node) {
  if (this->begin() != this->end()) {
    fake_->next_->prev_ = new_node;
    new_node->next_ = fake_->next_;
    fake_->next_ = new_node;
  } else {
    fake_->next_ = fake_->prev_ = new_node;
  }
  fake_->prev_->next_ = fake_;
  fake_->next_->prev_ = fake_;
}

//_____Iterator_____
template <typename value_type, typename Alloc>
typename S21List<value_type, Alloc>::ConstIterator &
S21List<value_type, Alloc>::ConstIterator::operator++() {
  this->node_ = this->node_->next_;
  return *this;
}

template <typename value_type, typename Alloc>
typename S21List<value_type, Alloc>::ConstIterator
S21List<value_type, Alloc>::ConstIterator::operator++(int) {
  ConstIterator temp(*this);
  this->node_ = this->node_->next_;
  return temp;
}

template <typename value_type, typename Alloc>
typename S21List<value_type, Alloc>::ConstIterator &
S21List<value_type, Alloc>::ConstIterator::operator--() {
  this->node_ = this->node_->prev_;
  return *this;
}

template <typename value_type, typename Alloc>
typename S21List<value_type, Alloc>::ConstIterator
S21List<value_type, Alloc>::ConstIterator::operator--(int) {
  ConstIterator temp(*this);
  this->node_ = this->node_->prev_;
  return temp;
}

template <typename value_type, typename Alloc>
typename S21List<value_type, Alloc>::Iterator &
S21List<value_type, Alloc>::Iterator::operator=(const Iterator &other) {
  this->node_ = other.node_;
  return *this;
}

} // namespace s21

#endif // S21_CONTAINERS_SRC_SEQUENCE_S21_LIST_H_
