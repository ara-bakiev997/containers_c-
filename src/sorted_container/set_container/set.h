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
  class SetIterator<Key>;
  using key_type = Key;
  using value_type = Key;
  using reference = value_type &;
  using const_reference = const value_type &;
  using iterator = SetIterator<value_type>;
  using const_iterator = SetConstIterator<value_type>;
  using size_type = size_t;


  class SetIterator<Key> {


  };


};


}

#endif // S21_CONTAINERS_SRC_SORTED_CONTAINER_SET_CONTAINER_SET_H_
