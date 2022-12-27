#define S21_CONTAINERS_SRC_CONTAINER_ADAPTOR_CONTAINER_ADAPTOR_H_
#include "../container.h"

namespace s21 {
template <class T, class container = Container<T>>
class ContainerAdaptor {
 public:
  ContainerAdaptor() = default;
  virtual ~ContainerAdaptor() = default;
};
}  // namespace s21

#ifndef S21_CONTAINERS_SRC_CONTAINER_ADAPTOR_CONTAINER_ADAPTOR_H_
#endif  // S21_CONTAINERS_SRC_CONTAINER_ADAPTOR_CONTAINER_ADAPTOR_H_
