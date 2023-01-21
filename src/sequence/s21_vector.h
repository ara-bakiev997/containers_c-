//
// Created by Lok on 01.11.2022.
//

#ifndef S21_CONTAINERS_SRC_S21_VECTOR_H_
#define S21_CONTAINERS_SRC_S21_VECTOR_H_

#include <cstddef>
#include <initializer_list>
#include <iostream>
#include <utility>
#include <valarray>
#include <type_traits>
#include <iterator>

//#include "sequence_container.h"

namespace s21 {


    template<typename T, typename Alloc = std::allocator<T>>
    class S21Vector {
    public:
        using value_type = T;
        using reference = T &;
        using const_reference = const T &;
        using size_type = size_t;
        using AllocTraits = std::allocator_traits<Alloc>;

        S21Vector() = default;

        explicit S21Vector(size_type size, const T &value = T(), const Alloc &alloc = Alloc());

        S21Vector(std::initializer_list<value_type> const &items);

        S21Vector(const S21Vector &other);

        S21Vector(S21Vector &&other) noexcept {
            this->swap(other);
        }

        ~S21Vector() {
            if (capacity_) remove();
        }

        // iterators
        template<bool IsConst>
        class CommonIterator {
        public:

            CommonIterator() = default;

            explicit CommonIterator(value_type *ptr) : ptr_(ptr) {}

            CommonIterator(const CommonIterator &other) : ptr_(other.ptr_) {}

            CommonIterator &operator=(const CommonIterator &other) {
                ptr_ = other.ptr_;
                return *this;
            }

            ~CommonIterator() = default;

            std::conditional_t<IsConst, const value_type &, value_type &> operator*() {
                return *ptr_;
            }

            std::conditional_t<IsConst, const value_type &, const value_type &> operator*() const {
                return *ptr_;
            }

            std::conditional_t<IsConst, const value_type *, value_type *> operator->() {
                return ptr_;
            }

            std::conditional_t<IsConst, const value_type *, value_type *> operator->() const {
                return ptr_;
            }

            CommonIterator &operator++() {
                ++ptr_;
                return *this;
            }

            CommonIterator operator++(int) {
                CommonIterator tmp(*this);
                ++ptr_;
                return tmp;
            }

            CommonIterator &operator--() {
                --ptr_;
                return *this;
            }

            CommonIterator operator--(int) {
                CommonIterator tmp(*this);
                --ptr_;
                return tmp;
            }

            CommonIterator operator+(size_type n) {
                CommonIterator tmp(*this);
                tmp.ptr_ += n;
                return tmp;
            }

            CommonIterator operator-(size_type n) {
                CommonIterator tmp(*this);
                tmp.ptr_ -= n;
                return tmp;
            }

            ptrdiff_t operator-(CommonIterator &value) { return ptr_ - value.ptr_; }

            ptrdiff_t operator-(const CommonIterator &value) { return ptr_ - value.ptr_; }

            bool operator==(const CommonIterator &other) {
                return ptr_ == other.ptr_;
            }

            bool operator!=(const CommonIterator &other) {
                return ptr_ != other.ptr_;
            }

        private:

            std::conditional_t<IsConst, const value_type *, value_type *> ptr_{};
        };

        using const_iterator = const CommonIterator<false>;
        using iterator = CommonIterator<false>;

//        operator CommonIterator<true>()  { return CommonIterator<false>(this->arr_); }


        reference at(size_type pos);

        const_reference at(size_type pos) const;

        reference operator[](size_type pos) noexcept;

        const_reference operator[](size_type pos) const noexcept;

        reference front() noexcept;

        const_reference front() const noexcept;

        reference back() noexcept;

        const_reference back() const noexcept;

        T *data() noexcept;

        const T *data() const noexcept;

        //  Vector Iterators

        iterator begin() const {
            return iterator(arr_);
        }

        iterator end() const {
            return iterator(arr_ + size_);
        }

        bool empty() const noexcept;

        size_type size() const noexcept;

        size_type capacity() const noexcept;

        void swap(S21Vector &other);

        S21Vector &operator=(const S21Vector &other);

        S21Vector &operator=(S21Vector &&other) noexcept;

        size_type max_size() const noexcept;

        void reserve(size_type size);

        void shrink_to_fit() noexcept;

        void clear() noexcept;

        iterator insert(iterator pos, const_reference value);

        void erase(iterator pos);

        void push_back(const_reference value);

        void push_back(value_type &&value);

        void pop_back();

        template<typename... Args>
        void emplace_back(Args &&... args);

        template<typename... Args>
        iterator emplace(const_iterator pos, Args &&... args);

    protected:
        size_type size_{};
        T *arr_{};

    private:
        void remove();

        size_type capacity_{};
        Alloc alloc_{};
    };


//_____CONSTRUCTORS_____

    template<typename T, typename Alloc>
    S21Vector<T, Alloc>::S21Vector(S21Vector::size_type size, const T &value, const Alloc &alloc): size_(size),
                                                                                                   arr_(AllocTraits::allocate(
                                                                                                           alloc_,
                                                                                                           size)),
                                                                                                   capacity_(size_) {

        for (auto i = 0; i < size_; ++i) {
            AllocTraits::construct(alloc_, arr_ + i, value);
        }
    }

    template<class value_type, typename Alloc>
    S21Vector<value_type, Alloc>::S21Vector(
            const std::initializer_list<value_type> &items):S21Vector(items.size()) {
        std::copy(items.begin(), items.end(), arr_);
    }

    template<typename T, typename Alloc>
    S21Vector<T, Alloc>::S21Vector(const S21Vector &other):S21Vector(other.size_) {
        std::copy(other.arr_, (other.arr_ + other.size_), arr_);
    }

//_____ASSIGNMENT_OPERATORS(copy_and_swap)_____
    template<class value_type, typename Alloc>
    S21Vector<value_type, Alloc> &
    S21Vector<value_type, Alloc>::operator=(const S21Vector &other) {
        if (this != &other) {
            S21Vector tmp = other;
            tmp.swap(tmp);
        }
        return *this;
    }

    template<class value_type, typename Alloc>
    S21Vector<value_type, Alloc> &
    S21Vector<value_type, Alloc>::operator=(S21Vector &&other) noexcept {
        if (this != &other) {
            S21Vector tmp = std::move(other);
            this->swap(tmp);
        }
        return *this;
    }

    template<class value_type, typename Alloc>
    typename S21Vector<value_type, Alloc>::reference
    S21Vector<value_type, Alloc>::at(S21Vector::size_type pos) {
        if (pos >= size_) {
            throw std::out_of_range("out_of_range");
        } else {
            return arr_[pos];
        }
    }

    template<class value_type, typename Alloc>
    typename S21Vector<value_type, Alloc>::const_reference
    S21Vector<value_type, Alloc>::at(S21Vector::size_type pos) const {
        if (pos >= size_) {
            throw std::out_of_range("out_of_range");
        } else {
            return arr_[pos];
        }
    }

    template<class value_type, typename Alloc>
    typename S21Vector<value_type, Alloc>::reference
    S21Vector<value_type, Alloc>::operator[](S21Vector::size_type pos) noexcept {
        return arr_[pos];
    }

    template<class value_type, typename Alloc>
    typename S21Vector<value_type, Alloc>::const_reference
    S21Vector<value_type, Alloc>::operator[](S21Vector::size_type pos) const noexcept {
        return arr_[pos];
    }

    template<class value_type, typename Alloc>
    typename S21Vector<value_type, Alloc>::reference
    S21Vector<value_type, Alloc>::front() noexcept {
        return *arr_;
    }

    template<class value_type, typename Alloc>
    typename S21Vector<value_type, Alloc>::const_reference
    S21Vector<value_type, Alloc>::front() const noexcept {
        return *arr_;
    }

    template<class value_type, typename Alloc>
    typename S21Vector<value_type, Alloc>::reference
    S21Vector<value_type, Alloc>::back() noexcept {
        return arr_[size_ - 1];
    }

    template<class value_type, typename Alloc>
    typename S21Vector<value_type, Alloc>::const_reference
    S21Vector<value_type, Alloc>::back() const noexcept {
        return arr_[size_ - 1];
    }

    template<class T, typename Alloc>
    T *S21Vector<T, Alloc>::data() noexcept {
        return arr_;
    }

    template<class T, typename Alloc>
    const T *S21Vector<T, Alloc>::data() const noexcept {
        return arr_;
    }

    template<class value_type, typename Alloc>
    bool S21Vector<value_type, Alloc>::empty() const noexcept {
        return !size_;
    }

    template<class value_type, typename Alloc>
    typename S21Vector<value_type, Alloc>::size_type
    S21Vector<value_type, Alloc>::size() const noexcept {
        return size_;
    }

    template<class value_type, typename Alloc>
    typename S21Vector<value_type, Alloc>::size_type
    S21Vector<value_type, Alloc>::max_size() const noexcept {
        return AllocTraits::max_size(alloc_);
    }

    template<class value_type, typename Alloc>
    void S21Vector<value_type, Alloc>::reserve(S21Vector::size_type size) {
        if (size > this->max_size())
            throw std::length_error("size > max_size");

        if (size > capacity_) {
            value_type *new_arr = AllocTraits::allocate(alloc_, size);
            auto i = 0;
            try {
                for (; i < size_; ++i) {
                    AllocTraits::construct(alloc_, new_arr + i, std::move(arr_[i]));
                }
            } catch (...) {
                for (auto j = 0; j < i; ++j) {
                    AllocTraits::destroy(alloc_, new_arr + j);
                }
                AllocTraits::deallocate(alloc_, new_arr, size);
                throw;
            }
            remove();
            arr_ = new_arr;
            capacity_ = size;
        }
    }

    template<class value_type, typename Alloc>
    typename S21Vector<value_type, Alloc>::size_type
    S21Vector<value_type, Alloc>::capacity() const noexcept {
        return capacity_;
    }

    template<class value_type, typename Alloc>
    void S21Vector<value_type, Alloc>::shrink_to_fit() noexcept {
        if (size_ != capacity_) {
            S21Vector<value_type, Alloc> temp(size_);
            std::move(arr_, arr_ + size_, temp.arr_);
            std::swap(arr_, temp.arr_);
            capacity_ = temp.capacity_;
        }
    }

    template<class value_type, typename Alloc>
    void S21Vector<value_type, Alloc>::push_back(const_reference value) {
        if (!capacity_) {
            this->reserve(1);
        }
        if (size_ == capacity_) {
            this->reserve(capacity_ * 2);
        }
        AllocTraits::construct(alloc_, arr_ + size_, value);
        ++size_;
    }

    template<typename T, typename Alloc>
    void S21Vector<T, Alloc>::push_back(value_type &&value) {
        if (!capacity_) {
            this->reserve(1);
        }
        if (size_ == capacity_) {
            this->reserve(capacity_ * 2);
        }
        AllocTraits::construct(alloc_, arr_ + size_, std::move(value));
        ++size_;
    }

    template<class value_type, typename Alloc>
    void S21Vector<value_type, Alloc>::clear() noexcept {
        for (; size_ != 0;) pop_back();
    }

    template<class value_type, typename Alloc>
    typename S21Vector<value_type, Alloc>::iterator
    S21Vector<value_type, Alloc>::insert(iterator pos, const_reference value) {
        auto new_capacity = !capacity_ ? 1 : capacity_;
        auto pos_index = pos - this->begin();
        if (size_ + 1 >= capacity_) {
            new_capacity *= 2;
        }
        auto buff = AllocTraits::allocate(alloc_, new_capacity);
        std::copy(&(*this->begin()), &(*(this->begin() + pos_index)), buff);
        AllocTraits::construct(alloc_, buff + pos_index, value);
        std::copy(&(*(this->begin() + pos_index)), &(*(this->begin() + size_)),
                  buff + pos_index + 1);
        remove();
        arr_ = buff;

        ++size_, capacity_ = new_capacity;
        return this->begin() + pos_index;
    }

    template<class value_type, typename Alloc>
    void S21Vector<value_type, Alloc>::erase(S21Vector::iterator pos) {
        if (this->end() - 1 == pos) {
            pop_back();
        } else {
            auto *buff = AllocTraits::allocate(alloc_, capacity_);
            size_type pos_index = pos - this->begin();
            std::copy(&(*this->begin()), &(*(this->begin() + pos_index)), buff);
            std::copy(&(*(this->begin() + pos_index + 1)), &(*this->end()),
                      buff + pos_index);
            remove();
            arr_ = buff;
            --size_;
        }
    }

    template<class value_type, typename Alloc>
    void S21Vector<value_type, Alloc>::pop_back() {
        if (size_) {
            AllocTraits::destroy(alloc_, this->arr_ + (size_ - 1));
        }
        --size_;
    }

    template<class value_type, typename Alloc>
    void S21Vector<value_type, Alloc>::swap(S21Vector &other) {
//        std::swap(*this, other);
        std::swap(size_, other.size_);
        std::swap(capacity_, other.capacity_);
        std::swap(arr_, other.arr_);
        std::swap(alloc_, other.alloc_);

    }

    template<typename T, typename Alloc>
    void S21Vector<T, Alloc>::remove() {
        if ((size_ + 1) != 0) {
            for (auto i = 0; i < size_; ++i) {
                AllocTraits::destroy(alloc_, arr_ + i);
            }
        }
        AllocTraits::deallocate(alloc_, arr_, capacity_);
    }

//    template<typename T, typename Alloc>
//    template<typename... Args>
//    void S21Vector<T, Alloc>::emplace_back(Args &&... args) {
//        if (capacity_ == 0) {
//            this->reserve(1);
//        }
//        if (this->size_ == capacity_) {
//            this->reserve(capacity_ * 2);
//        }
//        AllocTraits::construct(alloc_, this->arr_ + this->size_, std::forward<Args>(args)...);
//        ++this->size_;
//    }

    template<typename T, typename Alloc>
    template<typename... Args>
    void S21Vector<T, Alloc>::emplace_back(Args &&... args) {
        push_back(value_type(std::forward<Args>(args)...));
    }

    template<typename T, typename Alloc>
    template<typename... Args>
    typename S21Vector<T, Alloc>::iterator
    S21Vector<T, Alloc>::emplace(const_iterator pos, Args &&... args) {

        auto it = pos;
        size_type new_capacity = !capacity_ ? 1 : capacity_;
        size_type pos_index = it - this->begin();
        if (size_ + 1 >= capacity_) {
            new_capacity *= 2;
        }
        auto buff = AllocTraits::allocate(alloc_, new_capacity);
        std::copy(&(*this->begin()), &(*(this->begin() + pos_index)), buff);
        AllocTraits::construct(alloc_, buff + pos_index, std::forward<Args>(args)...);
        std::copy(&(*(this->begin() + pos_index)), &(*(this->begin() + size_)),
                  buff + pos_index + 1);
        if (size_) {
            remove();
        }
        arr_ = buff;
        ++size_;
        capacity_ = new_capacity;
        return this->begin() + pos_index;
    }

//    template<typename T, typename Alloc>
//    template<typename... Args>
//    typename S21Vector<T, Alloc>::iterator
//    S21Vector<T, Alloc>::emplace(const_iterator pos, Args &&... args) {
//    auto it = pos;
//       return  insert(it, std::forward<Args>(args)...);
//    }




} // namespace s21

#endif // S21_CONTAINERS_SRC_S21_VECTOR_H_
