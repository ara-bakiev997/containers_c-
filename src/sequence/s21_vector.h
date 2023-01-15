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
//        using iterator = typename SequenceContainer<T>::Iterator;
//        using const_iterator = typename SequenceContainer<T>::const_iterator;
        using size_type = typename SequenceContainer<T>::size_type;
        using AllocTraits = std::allocator_traits<Alloc>;

        // default constructor (simplified syntax for assigning values to attributes)
        S21Vector() { this->size_ = 0U, capacity_ = 0U, this->arr_ = nullptr; }

        explicit S21Vector(size_type n, const T& value = T(), const Alloc &alloc = Alloc()) {
            this->size_ = n;
            capacity_ = n;
//            this->arr_ = n ? alloc_.allocate(n) : nullptr;
            this->arr_ = n ? new value_type[n] : nullptr;
        }

        S21Vector(std::initializer_list<value_type> const &items);

        S21Vector(const S21Vector &other);

        S21Vector(S21Vector&& other) noexcept {
            this->swap(other);
        }

        ~S21Vector() = default;//{ delete[] this->arr_; }

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

        using iterator = CommonIterator<true>;
        using const_iterator = CommonIterator<false>;
        //  Vector Element access

        reference at(size_type pos); // access specified element with bounds checking
        const_reference at(size_type pos) const;

        reference operator[](size_type pos) noexcept;             // access specified element
        const_reference operator[](size_type pos) const noexcept; // access specified element

        reference front() noexcept; // access the first element
        const_reference front() const noexcept;

        reference back() noexcept;  // access the last element
        const_reference back() const noexcept;

        T *data() noexcept;               // direct access to the underlying array
        const T *data() const noexcept;   // direct access to the underlying array

        //  Vector Iterators

        iterator begin() {
            return iterator(this->arr_);
        }

        iterator end() {
            return iterator(this->arr_ + this->size_);
        }

        // Vector Capacity

        bool empty() const noexcept;

        size_type size() const noexcept;

        size_type capacity() const noexcept;
        // Vector Modifiers

        void swap(S21Vector &other); // swaps the contents

        //  Assignment operator
        S21Vector &operator=(const S21Vector &other);

        S21Vector &operator=(S21Vector&& other) noexcept;

        size_type max_size() const noexcept;

        void reserve(size_type size);


        void shrink_to_fit() noexcept;

        void clear() noexcept; // clears the contents
        iterator insert(iterator pos, const_reference value);

        void erase(iterator pos);              // erases element at pos
        void push_back(const_reference value); // adds an element to the end
        void pop_back();                       // removes the last element

    private:
        size_type capacity_{};
        Alloc alloc_{};
    };

//_____CONSTRUCTORS_____

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
    S21Vector<value_type, Alloc>&
    S21Vector<value_type, Alloc>::operator=(S21Vector&& other) noexcept {
        S21Vector tmp = std::move(other);
        this->swap(tmp);
        return *this;
    }

//_____VECTOR_ELEMENT_ACCESS_____

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

//_____VECTOR_CAPACITY_____
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
//        std::uninitialized_copy(this->arr_, this->arr_ + this->size_, new_arr);
                for (; i < this->size_; ++i) {
                    AllocTraits::construct(alloc_, new_arr + i, this->arr_[i]);
                }
            } catch (...) {
                for (auto j = 0; j < i; ++j) {
                    AllocTraits::destroy(alloc_, new_arr + j);
                }
                AllocTraits::deallocate(alloc_, new_arr, size);
                throw;
            }

            this->arr_ = new_arr;
            capacity_ = size;

            for (auto k = 0; k < this->size_; ++k) {
                AllocTraits::destroy(alloc_, new_arr + k);
            }
            AllocTraits::deallocate(alloc_, new_arr, size);
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

//_____VECTOR_MODIFIERS_____
    template<class value_type, typename Alloc>
    void S21Vector<value_type, Alloc>::push_back(const_reference value) {
        if (capacity_ == 0) {
            this->reserve(1);
        }
        if (this->size_ == capacity_) {
            this->reserve(capacity_ * 2);
        }
//  this->arr_[this->size_++] = value;
        AllocTraits::construct(alloc_, this->arr_ + this->size_, value);
        this->size_++;
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
        auto *buff = alloc_.allocate(new_capacity);
        std::copy(this->begin(), (this->begin() + pos_index), buff);
        buff[pos_index] = value;
        std::copy((this->begin() + pos_index), (this->begin() + this->size_),
                  buff + pos_index + 1);
        std::swap(this->arr_, buff);
        ++this->size_, capacity_ = new_capacity;
        alloc_.deallocate(buff, capacity_);

        return this->begin() + pos_index;
    }

    template<class value_type, typename Alloc>
    void S21Vector<value_type, Alloc>::erase(S21Vector::iterator pos) {
        if (this->end() - 1 != pos) {
            auto *buff = alloc_.allocate(capacity_);
            size_type pos_index = pos - this->begin();
            std::copy(&(*this->begin()), &(*(this->begin() + pos_index)), buff);
            std::copy(&(*(this->begin() + pos_index + 1)), &(*this->end()),
                      buff + pos_index);
            std::swap(this->arr_, buff);
            alloc_.deallocate(buff, capacity_);
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


} // namespace s21

#endif // S21_CONTAINERS_SRC_S21_VECTOR_H_
