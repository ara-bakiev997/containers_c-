#ifndef S21_CONTAINERS_SRC_CONTAINER_ADAPTOR_QUEUE_H_
#define S21_CONTAINERS_SRC_CONTAINER_ADAPTOR_QUEUE_H_

#include "../sequence/s21_list.h"

namespace s21 {
template <typename T, typename Container = S21List<T>> class S21Queue {
public:
  using container_type = Container;
  using value_type = typename Container::value_type;
  using size_type = typename Container::size_type;
  using reference = typename Container::reference;
  using const_reference = typename Container::const_reference;
  S21Queue() : container_() {}
  S21Queue(std::initializer_list<value_type> const &items)
      : container_(items) {}
  S21Queue(const S21Queue &q) : container_(q.container_) {}
  S21Queue(S21Queue &&q) noexcept : container_(std::move(q.container_)) {}
  ~S21Queue() = default;
  S21Queue &operator=(S21Queue<T> &&q) {
    this->container_ = std::move(q.container_);
    return *this;
  }
  S21Queue &operator=(const S21Queue<T> &q) {
    this->container_ = q.container_;
    return *this;
  }
  const_reference front() { return container_.front(); }
  const_reference back() { return container_.back(); }
  bool empty() { return container_.empty(); }
  size_type size() { return container_.size(); }
  void push(const_reference value) { container_.push_back(value); }
  void push(T &&value) { container_.push_back(value); }
  void pop() { container_.pop_front(); }
  void swap(S21Queue<T> &other) { this->container_.swap(other.container_); }

  // Bonus
  template <typename... Args> void emplace_back(Args &&...args) {
    container_.emplace_back(args...);
  }

private:
  container_type container_{};
};

} // namespace s21

#endif // S21_CONTAINERS_SRC_CONTAINER_ADAPTOR_QUEUE_H_
