//
// Created by Rongjin Qiao on 10/26/19.
//

#ifndef DATA_STRUCTURES_BASE_H
#define DATA_STRUCTURES_BASE_H

#include <memory>

namespace rjqiao {
    template<typename T>
    struct node_t {
        T value;
        std::unique_ptr<node_t> next;


        explicit node_t(T value, std::unique_ptr<T> &&next = nullptr)
                : value(std::move(value)),
                  next(std::move(next)) {}

        node_t(const node_t &other) = delete;

        node_t(node_t &&other) noexcept
                : value(std::move(other.value)),
                  next(std::move(other.next)) {}


        static node_t *copy_ptr_node_t(node_t *other) {
            return other ==
                   nullptr ? nullptr
                           : new node_t(other->value, copy_ptr_node_t(other->next));
        }


    };


    template<typename T>
    struct doubly_linked_node_t {
        T val;
        doubly_linked_node_t *prev;
        doubly_linked_node_t *next;

        explicit doubly_linked_node_t(T val,
                                      doubly_linked_node_t *prev = nullptr,
                                      doubly_linked_node_t *succ = nullptr)
                : val(val), prev(prev), next(succ) {}

        ~doubly_linked_node_t() = default;
    };

}

//        node_t(const node_t &other)
//                : value(other.value), next(new node_t<T>(value, copy_ptr_node_t(other.next)) {}


#endif //DATA_STRUCTURES_BASE_H
