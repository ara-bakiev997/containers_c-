#define S21_CONTAINERS_SRC_CONTAINER_ADAPTOR_CONTAINER_ADAPTOR_H_
#include "../container.h"

#ifndef S21_CONTAINERS_SRC_CONTAINER_ADAPTOR_CONTAINER_ADAPTOR_H_
namespace s21 {
template <class T, class container = Container<T>>
class ContainerAdaptor {
  ContainerAdaptor() = default;
  virtual ~ContainerAdaptor() = default;
};
}  // namespace s21


#endif  // S21_CONTAINERS_SRC_CONTAINER_ADAPTOR_CONTAINER_ADAPTOR_H_
