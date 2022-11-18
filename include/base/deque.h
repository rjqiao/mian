//
// Created by Rongjin Qiao on 10/26/19.
//
#pragma once

#include <memory>
#include <cstdint>

#include "base.h"
#include "iterator.h"
#include "helpers.h"


namespace rjqiao {

    template<class T, class Ref, class Ptr>
    struct _Deque_iterator {
        using value_type = T;
        using pointer = Ptr;
        using reference = Ref;
        using size_type = size_t;
        using difference_type = std::ptrdiff_t;
        using iterator_category = random_access_iterator_tag;

        doubly_linked_node_t<T> *dll_ptr;

        explicit _Deque_iterator(doubly_linked_node_t<T> *dll_ptr) : dll_ptr(dll_ptr) {}

        _Deque_iterator(const _Deque_iterator &other) : dll_ptr(other.dll_ptr) {}

        ~_Deque_iterator() = default;

        auto operator=(const _Deque_iterator &other) -> _Deque_iterator & {
            auto temp = _Deque_iterator(other);
            *this = std::move(other);
            return *this;
        }

        auto operator==(const _Deque_iterator &other) const -> bool {
            return dll_ptr == other.dll_ptr;  //
        }

        auto operator!=(const _Deque_iterator &other) const -> bool {
            return !(*this == other);
        }

        bool operator<(const _Deque_iterator &) const; //optional
        bool operator>(const _Deque_iterator &) const; //optional
        bool operator<=(const _Deque_iterator &) const; //optional
        bool operator>=(const _Deque_iterator &) const; //optional

        auto operator++() -> _Deque_iterator & {
            dll_ptr = dll_ptr->next;
            return *this;
        }

        _Deque_iterator operator++(int); //optional
        _Deque_iterator &operator--(); //optional
        _Deque_iterator operator--(int); //optional
        _Deque_iterator &operator+=(size_type); //optional

        _Deque_iterator operator+(size_type num) const {
            doubly_linked_node_t<T> *p = dll_ptr;
            while (p != nullptr && num > 0) {
                p = p->next;
                num--;
            }
            return _Deque_iterator(p);
        }

        friend auto operator+(size_type num, const _Deque_iterator &it)
        -> _Deque_iterator {
            return it + num;
        }

        _Deque_iterator &operator-=(size_type); //optional
        _Deque_iterator operator-(size_type) const; //optional
        difference_type operator-(_Deque_iterator) const; //optional


        auto operator*() const -> reference {
            return dll_ptr->val;
        }

        auto operator->() const -> pointer {
            return dll_ptr->next;
        }

        auto operator[](size_type num) const -> reference {
            return *(this + num);
        }
    };

    template<class T, class Alloc = allocator<T>>
    struct deque {
        struct deque_iterator;

        using value_type = T;
        using allocator_type = Alloc;
        using reference = value_type &;
        using const_reference = const value_type &;
        using pointer = typename allocator_traits<allocator_type>::pointer;
        using const_pointer = typename allocator_traits<allocator_type>::const_pointer;

        using iterator = _Deque_iterator<value_type, reference, pointer>;
        using const_iterator = _Deque_iterator<value_type, const_reference, const_pointer>;
        using size_type = std::size_t;
        using difference_type = std::ptrdiff_t;

        // ---------------------- members ----------------------=

        doubly_linked_node_t<value_type> *_head = nullptr, *_tail = nullptr;
        size_type _size = 0;

        // ---------------------- methods -----------------------

        deque() = default;

        explicit deque(const allocator_type &alloc) {}

        explicit deque(size_type n, const allocator_type &alloc = allocator_type()) :
                deque(n, value_type(), alloc) {}

        explicit deque(size_type n,
                       const value_type &val,
                       const allocator_type &alloc = allocator_type()) {
            for (size_type i = 0; i < n; i++) {
                push_back(val);
            }
        }

        template<class InputIterator>
        deque(InputIterator first, InputIterator last,
              const allocator_type &alloc = allocator_type()) {
            for (InputIterator curr = first; curr != last; ++curr) {
                push_back(*curr);
            }
        }

        deque(const deque &other) : deque(other.begin(), other.end()) {}

        deque(deque &&other) noexcept = delete;

        auto size() -> size_type { return _size; }

        auto max_size() -> size_type { return SIZE_MAX; }

        auto resize(size_type n, const value_type &val = value_type()) -> void {
            if (n < 0) {
                throw std::out_of_range("out of range in rjqiao::resize");
            }

            if (n < _size) {
                while (n != _size) {
                    pop_back();
                }
            } else if (n > _size) {
                while (n != _size) {
                    push_back(val);
                }
            }
        }

        bool empty() { return _head == nullptr; }

        auto operator[](size_type n) -> reference { return at(n); }

        auto at(size_type n) -> reference {
            if (n < 0 || n >= _size) {
                throw std::out_of_range("out of range in rjqiao::deque::at");
            }

            return *(iterator(_head) + n);
        }

        auto front() -> reference {
            if (_head == nullptr) {
                throw std::out_of_range("out of range in rjqiao::deque::front");
            }
            return _head->val;
        }
//        const T &front() const;

        void pop_front() {
            if (_head == nullptr) {
                throw std::out_of_range("out of range in rjqiao::deque::pop_front");
            }
            auto *old_head = _head;
            _head = _head->next;

//            old_head->next = nullptr;
            delete old_head;

            if (_head != nullptr) {
                _head->prev = nullptr;
            } else {
                _tail = nullptr;
            }
            _size--;
        }

        void push_front(value_type &&val) {
            if (_head == nullptr) {
                _head = _tail = new doubly_linked_node_t<T>(std::move(val), nullptr, nullptr);
            } else {
                _head->prev = new doubly_linked_node_t<T>(std::move(val), nullptr, _head);
                _head = _head->prev;
            }
            _size++;
        }

        void push_front(const value_type &val) {
            push_front(T(val));
        }

        auto pop_and_get_front() -> value_type {
            if (_head == nullptr) {
                throw std::out_of_range("out of range in rjqiao::deque::pop_and_get_front");
            }
            T res = std::move(front());
            pop_front();
            return res;
        }

        auto back() -> reference {
            if (_tail == nullptr) {
                throw std::out_of_range("out of range in rjqiao::deque::back");
            }
            return _tail->val;
        }

        void pop_back() {
            if (_tail == nullptr) {
                throw std::out_of_range("out of range in rjqiao::deque::pop_back");
            }
            auto *old_tail = _tail;

//            delete old_tail;
            _tail = _tail->prev;

            if (_tail != nullptr) {
                _tail->next = nullptr;
            } else {
                _head = nullptr;
            }
            _size--;
        }

        void push_back(const value_type &val) {
            push_back(T(val));
        }

        void push_back(value_type &&val) {
            if (_tail == nullptr) {
                _head = _tail = new doubly_linked_node_t<T>(std::move(val), nullptr, nullptr);
            } else {
                _tail->next = new doubly_linked_node_t<T>(std::move(val), _tail, nullptr);
                _tail = _tail->next;
            }
            _size++;
        }

        auto pop_and_get_back() -> value_type {
            if (_head == nullptr) {
                throw std::out_of_range("out of range in rjqiao::deque::pop_and_get_back");
            }
            T res = std::move(back());
            pop_back();
            return res;
        }

        iterator begin() const noexcept {
            return iterator(_head);
        }

        iterator end() const noexcept {
            return iterator(nullptr);
        }


    };

//    template<class T, class Alloc = allocator<T> >
//    auto operator+(
//            typename deque<T, Alloc>::size_type num,
//            const typename deque<T, Alloc>::deque_iterator &it)
//    -> typename deque<T, Alloc>::deque_iterator {
//        return it + num;
//    }
}
