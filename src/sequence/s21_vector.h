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

#include "sequence_container.h"

namespace s21 {


    template<typename T, typename Alloc = std::allocator<T>>
    class S21Vector : public SequenceContainer<T> {
    public:
        using value_type = typename SequenceContainer<T>::value_type;
        using reference = typename SequenceContainer<T>::reference;
        using const_reference = typename SequenceContainer<T>::const_reference;
        using size_type = typename SequenceContainer<T>::size_type;
        using AllocTraits = std::allocator_traits<Alloc>;

        S21Vector() { this->size_ = 0U, capacity_ = 0U, this->arr_ = nullptr; }

        explicit S21Vector(size_type size, const T &value = T(), const Alloc &alloc = Alloc());

        S21Vector(std::initializer_list<value_type> const &items);

        S21Vector(const S21Vector &other);

        S21Vector(S21Vector &&other) noexcept {
            this->swap(other);
        }

        ~S21Vector() {
            remove();
        }


        // iterators
        template<bool IsConst>
        class CommonIterator {
        public:

            explicit CommonIterator(value_type *ptr) : ptr_(ptr) {}

            CommonIterator(const CommonIterator &other) : ptr_(other.ptr_) {}

            CommonIterator &operator=(const CommonIterator &other) {
                this->ptr_ = other.ptr_;
                return *this;
            }

            ~CommonIterator() = default;

            std::conditional_t<IsConst, const value_type &, value_type &> operator*() {
                return *ptr_;
            }

            std::conditional_t<IsConst, const value_type *, value_type *> operator->() {
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

            ptrdiff_t operator-(CommonIterator &value) { return this->ptr_ - value.ptr_; }

            ptrdiff_t operator-(const CommonIterator &value) { return this->ptr_ - value.ptr_; }

            bool operator==(const CommonIterator &other) {
                return this->ptr_ == other.ptr_;
            }

            bool operator!=(const CommonIterator &other) {
                return this->ptr_ != other.ptr_;
            }

        private:
            std::conditional_t<IsConst, const value_type *, value_type *> ptr_{};
        };

        using iterator = CommonIterator<false>;
        using const_iterator = CommonIterator<true>;

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

        iterator begin() {
            return iterator(this->arr_);
        }

        iterator end() {
            return iterator(this->arr_ + this->size_);
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
        void push_back(value_type&& value);
        void pop_back();

        template<typename... Args>
        void emplace_back(Args&&... args);
//        template<typename... Args>
//        iterator emplace(const_iterator pos, Args&&... args);

    private:
        void remove();

        size_type capacity_{};
        Alloc alloc_{};
    };

//_____CONSTRUCTORS_____

    template<typename T, typename Alloc>
    S21Vector<T, Alloc>::S21Vector(S21Vector::size_type size, const T &value, const Alloc &alloc) {
        this->size_ = size;
        capacity_ = size;
        this->arr_ = AllocTraits::allocate(alloc_, size);
        for (auto i = 0; i < this->size_; ++i) {
            AllocTraits::construct(alloc_, this->arr_ + i, value);
        }
//            this->arr_ = size ? new value_type[size] : nullptr;
    }

    template<class value_type, typename Alloc>
    S21Vector<value_type, Alloc>::S21Vector(
            const std::initializer_list<value_type> &items):S21Vector(items.size()) {
        std::copy(items.begin(), items.end(), this->arr_);
    }

    template<typename T, typename Alloc>
    S21Vector<T, Alloc>::S21Vector(const S21Vector &other):S21Vector(other.size_) {
        std::copy(other.arr_, (other.arr_ + other.size_), this->arr_);
    }

//_____ASSIGNMENT_OPERATORS(copy_and_swap)_____
    template<class value_type, typename Alloc>
    S21Vector<value_type, Alloc> &
    S21Vector<value_type, Alloc>::operator=(const S21Vector &other) {
        S21Vector tmp = other;
        tmp.swap(tmp);
        return *this;
    }

    template<class value_type, typename Alloc>
    S21Vector<value_type, Alloc> &
    S21Vector<value_type, Alloc>::operator=(S21Vector &&other) noexcept {
        S21Vector tmp = std::move(other);
        this->swap(tmp);
        return *this;
    }

    template<class value_type, typename Alloc>
    typename S21Vector<value_type, Alloc>::reference
    S21Vector<value_type, Alloc>::at(S21Vector::size_type pos) {
        return (pos < this->size_) ? this->arr_[pos]
                                   : throw std::out_of_range("out_of_range");
    }

    template<class value_type, typename Alloc>
    typename S21Vector<value_type, Alloc>::const_reference
    S21Vector<value_type, Alloc>::at(S21Vector::size_type pos) const {
        return (pos < this->size_) ? this->arr_[pos]
                                   : throw std::out_of_range("out_of_range");
    }

    template<class value_type, typename Alloc>
    typename S21Vector<value_type, Alloc>::reference
    S21Vector<value_type, Alloc>::operator[](S21Vector::size_type pos) noexcept {
        return this->arr_[pos];
    }

    template<class value_type, typename Alloc>
    typename S21Vector<value_type, Alloc>::const_reference
    S21Vector<value_type, Alloc>::operator[](S21Vector::size_type pos) const noexcept {
        return this->arr_[pos];
    }

    template<class value_type, typename Alloc>
    typename S21Vector<value_type, Alloc>::reference
    S21Vector<value_type, Alloc>::front() noexcept {
        return *this->arr_;
    }

    template<class value_type, typename Alloc>
    typename S21Vector<value_type, Alloc>::const_reference
    S21Vector<value_type, Alloc>::front() const noexcept {
        return *this->arr_;
    }

    template<class value_type, typename Alloc>
    typename S21Vector<value_type, Alloc>::reference
    S21Vector<value_type, Alloc>::back() noexcept {
        return this->arr_[this->size_ - 1];
    }

    template<class value_type, typename Alloc>
    typename S21Vector<value_type, Alloc>::const_reference
    S21Vector<value_type, Alloc>::back() const noexcept {
        return this->arr_[this->size_ - 1];
    }

    template<class T, typename Alloc>
    T *S21Vector<T, Alloc>::data() noexcept {
        return this->arr_;
    }

    template<class T, typename Alloc>
    const T *S21Vector<T, Alloc>::data() const noexcept {
        return this->arr_;
    }

    template<class value_type, typename Alloc>
    bool S21Vector<value_type, Alloc>::empty() const noexcept {
        return !this->size_;
    }

    template<class value_type, typename Alloc>
    typename S21Vector<value_type, Alloc>::size_type
    S21Vector<value_type, Alloc>::size() const noexcept {
        return this->size_;
    }

    template<class value_type, typename Alloc>
    typename S21Vector<value_type, Alloc>::size_type
    S21Vector<value_type, Alloc>::max_size() const noexcept {
//  return SIZE_MAX / sizeof(value_type);
        return AllocTraits::max_size(alloc_);
    }

    template<class value_type, typename Alloc>
    void S21Vector<value_type, Alloc>::reserve(S21Vector::size_type size) {
        if (size > this->max_size())
            throw std::length_error("size > max_size");

        if (size > capacity_) {
            value_type *new_arr = AllocTraits::allocate(alloc_, size);
            size_type i = 0;
            try {
                for (; i < this->size_; ++i) {
                    AllocTraits::construct(alloc_, new_arr + i, std::move(this->arr_[i]));
                }
            } catch (...) {
                for (auto j = 0; j < i; ++j) {
                    AllocTraits::destroy(alloc_, new_arr + j);
                }
                AllocTraits::deallocate(alloc_, new_arr, size);
                throw;
            }
            remove();
            this->arr_ = new_arr;
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
        if (this->size_ != capacity_) {
            S21Vector<value_type, Alloc> temp(this->size_);
            std::move(this->arr_, this->arr_ + this->size_, temp.arr_);
            std::swap(this->arr_, temp.arr_);
            capacity_ = temp.capacity_;
        }
    }

    template<class value_type, typename Alloc>
    void S21Vector<value_type, Alloc>::push_back(const_reference value) {
        if (capacity_ == 0) {
            this->reserve(1);
        }
        if (this->size_ == capacity_) {
            this->reserve(capacity_ * 2);
        }
        AllocTraits::construct(alloc_, this->arr_ + this->size_, value);
        ++this->size_;
    }

    template<typename T, typename Alloc>
    void S21Vector<T, Alloc>::push_back(value_type&& value) {
        if (capacity_ == 0) {
            this->reserve(1);
        }
        if (this->size_ == capacity_) {
            this->reserve(capacity_ * 2);
        }
        AllocTraits::construct(alloc_, this->arr_ + this->size_, std::move(value));
        ++this->size_;
    }

    template<class value_type, typename Alloc>
    void S21Vector<value_type, Alloc>::clear() noexcept {
        this->size_ = 0;
    }

    template<class value_type, typename Alloc>
    typename S21Vector<value_type, Alloc>::iterator
    S21Vector<value_type, Alloc>::insert(iterator pos, const_reference value) {
        size_type new_capacity = capacity_;
        size_type pos_index = pos - this->begin();
        if (this->size_ + 1 >= capacity_) {
            new_capacity *= 2;
        }
        auto *buff = AllocTraits::allocate(alloc_, new_capacity);
        std::copy(this->begin(), (this->begin() + pos_index), buff);
        AllocTraits::construct(alloc_, buff + pos_index, value);
        std::copy((this->begin() + pos_index), (this->begin() + this->size_),
                  buff + pos_index + 1);
        remove();
        this->arr_ = buff;

        ++this->size_, capacity_ = new_capacity;
        return this->begin() + pos_index;
    }

    template<class value_type, typename Alloc>
    void S21Vector<value_type, Alloc>::erase(S21Vector::iterator pos) {
        if (this->end() - 1 != pos) {
            auto *buff = AllocTraits::allocate(alloc_, capacity_);
            size_type pos_index = pos - this->begin();
            std::copy(&(*this->begin()), &(*(this->begin() + pos_index)), buff);
            std::copy(&(*(this->begin() + pos_index + 1)), &(*this->end()),
                      buff + pos_index);
            remove();
            this->arr_ = buff;
        }
        --this->size_;
    }

    template<class value_type, typename Alloc>
    void S21Vector<value_type, Alloc>::pop_back() {

        AllocTraits::destroy(alloc_, this->arr_ + (this->size_ - 1));
        --this->size_;
    }

    template<class value_type, typename Alloc>
    void S21Vector<value_type, Alloc>::swap(S21Vector &other) {
//        std::swap(*this, other);
        std::swap(this->size_, other.size_);
        std::swap(this->capacity_, other.capacity_);
        std::swap(this->arr_, other.arr_);
        std::swap(this->alloc_, other.alloc_);

    }

    template<typename T, typename Alloc>
    void S21Vector<T, Alloc>::remove() {
        for (auto i = 0; i < this->capacity_; ++i) {
            AllocTraits::destroy(alloc_, this->arr_ + i);
        }
        AllocTraits::deallocate(alloc_, this->arr_, this->capacity_);
    }

    template<typename T, typename Alloc>
    template<typename... Args>
    void S21Vector<T, Alloc>::emplace_back(Args &&... args) {
        if (capacity_ == 0) {
            this->reserve(1);
        }
        if (this->size_ == capacity_) {
            this->reserve(capacity_ * 2);
        }
        AllocTraits::construct(alloc_, this->arr_ + this->size_, std::forward<Args>(args)...);
        ++this->size_;
    }


} // namespace s21

#endif // S21_CONTAINERS_SRC_S21_VECTOR_H_
