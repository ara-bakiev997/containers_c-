//
// Created by Lok on 17.11.2022.
//


//#include <cstddef>
//#include <initializer_list>
#include <iostream>
//#include <utility>
//#include <valarray>

#ifndef S21_CONTAINERS_SRC_SORTED_CONTAINER_SET_CONTAINER_SET_H_
#define S21_CONTAINERS_SRC_SORTED_CONTAINER_SET_CONTAINER_SET_H_

namespace s21 {

template <class Key, class Compare = std::less<Key>,
          class Allocator = std::allocator<Key>>

class S21Set{
  using key_type = Key;
};


}

#endif // S21_CONTAINERS_SRC_SORTED_CONTAINER_SET_CONTAINER_SET_H_
