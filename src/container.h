#ifndef S21_CONTAINERS_SRC_CONTAINER_H_
#define S21_CONTAINERS_SRC_CONTAINER_H_

namespace s21 {
template <class T>
class Container {
 public:
  Container() = default;
  virtual ~Container() = default;
};

// Container::~Container() {}

}  // namespace s21

#endif  // S21_CONTAINERS_SRC_CONTAINER_H_
