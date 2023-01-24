//
// Created by Lok on 17.11.2022.
//

#ifndef S21_CONTAINERS_SRC_SORTED_CONTAINER_ASSOCIATIVE_CONTAINER_MAP_H_
#define S21_CONTAINERS_SRC_SORTED_CONTAINER_ASSOCIATIVE_CONTAINER_MAP_H_

#include <iostream>
#include <initializer_list>

namespace s21 {

    template<typename Key, typename T, typename Compare = std::less<Key>, typename Alloc = std::allocator<std::pair<const Key, T>>>
    class S21Map {
    public:
        class MapIterator;
        class MapConstIterator;

        using key_type = Key;
        using mapped_type = T;
        using value_type = std::pair<const key_type, mapped_type>;
        using reference = value_type &;
        using const_reference = const value_type &;
        using iterator = MapIterator;
        using const_iterator = MapConstIterator;
        using AllocTraits = std::allocator_traits<Alloc>;
        using size_type = size_t;

        S21Map() {}

        S21Map(std::initializer_list<value_type> const &items);

        S21Map(const S21Map &other);

        S21Map(const S21Map &&other) noexcept;

        ~S21Map() {}

        S21Map &operator=(const S21Map &other);

        S21Map &operator=(S21Map &&other) noexcept;

        mapped_type &at(const key_type &key);

        const mapped_type &at(const key_type &key) const;

        mapped_type &operator[](const key_type &key);

//        iterator begin();
//        iterator end();

        bool empty();

        size_type size();

        size_type max_size();

        void clear();

        std::pair<iterator, bool> insert(const value_type &value);

        std::pair<iterator, bool> insert(const Key &key, const T &obj);

        std::pair<iterator, bool> insert_or_assign(const Key &key, const T &obj);

        void erase(iterator pos);

        void swap(S21Map &other);

        void merge(S21Map &other);

        bool contains(const Key &key);

        template<typename... Args>
        std::pair<iterator, bool> emplace( Args &&... args );


    };

    template<typename Key, typename T, typename Compare, typename Alloc>
    S21Map<Key, T, Compare, Alloc>::S21Map(const std::initializer_list<value_type> &items) {

    }

    template<typename Key, typename T, typename Compare, typename Alloc>
    S21Map<Key, T, Compare, Alloc>::S21Map(const S21Map &other) {

    }

    template<typename Key, typename T, typename Compare, typename Alloc>
    S21Map<Key, T, Compare, Alloc>::S21Map(const S21Map &&other) noexcept {

    }

    template<typename Key, typename T, typename Compare, typename Alloc>
    S21Map<Key, T, Compare, Alloc> &S21Map<Key, T, Compare, Alloc>::operator=(const S21Map &other) {
        return *this;
    }

    template<typename Key, typename T, typename Compare, typename Alloc>
    S21Map<Key, T, Compare, Alloc> &S21Map<Key, T, Compare, Alloc>::operator=(S21Map &&other) noexcept {
        return *this;
    }

    template<typename Key, typename T, typename Compare, typename Alloc>
    T &S21Map<Key, T, Compare, Alloc>::at(const key_type &key) {
        return;
    }

    template<typename Key, typename T, typename Compare, typename Alloc>
    const T &S21Map<Key, T, Compare, Alloc>::at(const key_type &key) const {
        return;
    }

    template<typename Key, typename T, typename Compare, typename Alloc>
    T &S21Map<Key, T, Compare, Alloc>::operator[](const key_type &key) {
        return;
    }


}

#endif //S21_CONTAINERS_SRC_SORTED_CONTAINER_ASSOCIATIVE_CONTAINER_MAP_H_
