//
// Created by Lok on 17.11.2022.
//

#ifndef S21_CONTAINERS_SRC_SORTED_CONTAINER_ASSOCIATIVE_CONTAINER_MAP_H_
#define S21_CONTAINERS_SRC_SORTED_CONTAINER_ASSOCIATIVE_CONTAINER_MAP_H_

#include <iostream>
#include <initializer_list>
#include "../red_black_tree.h"

namespace s21 {


    template<typename Key, typename Value, typename Compare = std::less<Key>, typename Alloc = std::allocator<std::pair<const Key, Value>>>
class S21Map : public Tree<Key, Value> {
    public:
        class MapIterator {};
        class MapConstIterator {};

        using key_type = Key;
        using mapped_type = Value;
        using value_type = std::pair<const key_type, mapped_type>;
        using reference = value_type &;
        using const_reference = const value_type &;
        using iterator = typename Tree<Key, Value>::iterator;
        using const_iterator = typename Tree<Key, Value>::const_iterator;
        using ValueTypeAlloc = typename Tree<Key, Value>::ValueTypeAlloc;
        using NodeAlloc = typename Tree<Key, Value>::NodeAlloc;
        using size_type = size_t;

        S21Map() {}
        ~S21Map() = default;

//        S21Map(std::pair<key_type, mapped_type> data) {
//            createNode(data);
//        }
//
//        S21Map(std::initializer_list<value_type> const &items);
//
//        S21Map(const S21Map &other);
//
//        S21Map(const S21Map &&other) noexcept;
//
//        ~S21Map() {
////            removeNode();
//        }

        S21Map &operator=(const S21Map &other);

        S21Map &operator=(S21Map &&other) noexcept;

        mapped_type &at(const key_type &key);

        const mapped_type &at(const key_type &key) const;

        mapped_type &operator[](const key_type &key);

//        iterator begin();
//        iterator end();

        bool empty();

//        size_type size();

//        size_type max_size();

//        void clear();

        std::pair<iterator, bool> insert(const value_type &value);

        std::pair<iterator, bool> insert(const Key &key, const Value &obj);

        std::pair<iterator, bool> insert_or_assign(const Key &key, const Value &obj);

        void erase(const Key &key);

        void swap(S21Map &other);

        void merge(S21Map &other);

        bool contains(const Key &key);

        template<typename... Args>
        std::pair<iterator, bool> emplace( Args &&... args );

        void print() {
          Tree<Key, Value>::print2D();
        }

    private:
//        AllocTraits  alloc_{};
//        AllocNode anode_{};
//        Node<Key, Value>* node_{};
        size_type size_{};

//        template<typename... Args>
//        Node<Key, Value>* createNode(Args&& ...args);
//
//        void removeNode(Node<key_type , mapped_type>* node);

    };

//    template<typename Key, typename Value, typename Compare, typename Alloc>
//    S21Map<Key, Value, Compare, Alloc>::S21Map(const std::initializer_list<value_type> &items) {
//
//    }
//
//    template<typename Key, typename Value, typename Compare, typename Alloc>
//    S21Map<Key, Value, Compare, Alloc>::S21Map(const S21Map &other) {
//
//    }
//
//    template<typename Key, typename Value, typename Compare, typename Alloc>
//    S21Map<Key, Value, Compare, Alloc>::S21Map(const S21Map &&other) noexcept {
//
//    }

    template<typename Key, typename Value, typename Compare, typename Alloc>
    S21Map<Key, Value, Compare, Alloc> &S21Map<Key, Value, Compare, Alloc>::operator=(const S21Map &other) {
        return *this;
    }

    template<typename Key, typename Value, typename Compare, typename Alloc>
    S21Map<Key, Value, Compare, Alloc> &S21Map<Key, Value, Compare, Alloc>::operator=(S21Map &&other) noexcept {
        return *this;
    }

    template<typename Key, typename Value, typename Compare, typename Alloc>
    Value &S21Map<Key, Value, Compare, Alloc>::at(const key_type &key) {
//        return;
    }

    template<typename Key, typename Value, typename Compare, typename Alloc>
    const Value &S21Map<Key, Value, Compare, Alloc>::at(const key_type &key) const {
//        return;
    }

    template<typename Key, typename Value, typename Compare, typename Alloc>
    Value &S21Map<Key, Value, Compare, Alloc>::operator[](const key_type &key) {
//        return;
    }

    template<typename Key, typename Value, typename Compare, typename Alloc>
    std::pair<typename S21Map<Key, Value, Compare, Alloc>::iterator, bool>
    S21Map<Key, Value, Compare, Alloc>::insert(const S21Map::value_type &value) {
        return Tree<Key, Value>::insert_node(value.first, value.second);

//        return std::pair<iterator, bool>();
    }

    template<typename Key, typename Value, typename Compare, typename Alloc>
    std::pair<typename S21Map<Key, Value, Compare, Alloc>::iterator, bool> S21Map<Key, Value, Compare, Alloc>::insert(
            const Key &key, const Value &obj) {
        Tree<Key, Value>::insert_node(key, obj);


        return std::pair<iterator, bool>();
    }
    template <typename Key, typename Value, typename Compare, typename Alloc>
    void S21Map<Key, Value, Compare, Alloc>::erase(const Key &key) {
      Tree<Key, Value>::erase_node(key);
    }
//    template <typename Key, typename Value, typename Compare, typename Alloc>
//    void S21Map<Key, Value, Compare, Alloc>::clear() {
//      Tree<Key, Value>::ClearRBT();
//      size_ = 0;
//    }


    //    template<typename Key, typename Value, typename Compare, typename Alloc>
//    template<typename... Args>
//    Node<Key, Value> *S21Map<Key, Value, Compare, Alloc>::createNode(Args&& ...args) {
//
//        Node<key_type, mapped_type>* new_node = AllocTraits::allocate(anode_, 1);//AllocNode::allocate(a_node_, 1);//this->a_node_.allocate(1);
//        try {
//            AllocTraits::construct(anode_, new_node, Node<key_type, mapped_type>());
//        } catch (...) {
//            AllocTraits::deallocate(anode_, new_node, 1);
//        }
//
//        new_node->data = AllocTraits::allocate(alloc_, 1);
//        try {
//            AllocTraits::construct(alloc_, new_node->data, std::forward<Args>(args)...);
//        } catch (...) {
//            AllocTraits::deallocate(alloc_, new_node->data, 1);
//        }
//        return new_node;
//    }

//    template<typename Key, typename Value, typename Compare, typename Alloc>
//    void S21Map<Key, Value, Compare, Alloc>::removeNode(Node<key_type, mapped_type> *node) {
//        AllocTraits::destroy(alloc_, node->data);
//        AllocTraits::deallocate(alloc_, node->data, 1);
//
//        AllocTraits::destroy(anode_, node);
//        AllocTraits::deallocate(anode_, node, 1);
//    }




}

#endif //S21_CONTAINERS_SRC_SORTED_CONTAINER_ASSOCIATIVE_CONTAINER_MAP_H_
