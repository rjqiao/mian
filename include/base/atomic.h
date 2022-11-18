//
// Created by rjqia on 1/22/2022.
//

#ifndef MIAN_ATOMIC_H
#define MIAN_ATOMIC_H

#include <atomic>
#include <functional>

namespace rjqiao {

// template <class T> using MappingFunc = T(T);

template <class T, class MappingFunc>
auto atomic_update(std::atomic<T> *x, MappingFunc mapping) -> void {
    while (true) {
        T expected = x->load(); // T need copy constructor?
        // copy a new one, and modify it, then save to $desired
        T desired = mapping(expected);
        if (x->compare_exchange_weak(expected, std::move(desired))) {
            return;
        }
    }
}

template <class T, class MappingFunc>
auto atomic_update_fetch(std::atomic<T> *x, MappingFunc mapping) -> T {
    while (true) {
        T expected = x->load();
        T desired = mapping(expected);
        if (x->compare_exchange_weak(expected, desired)) {
            return desired;
        }
    }
}

template <class T> using MappingCancelableFunc = bool(T *);

template <class T>
auto atomic_update_cancelable(std::atomic<T> *x,
                              std::function<MappingCancelableFunc<T>> mapping_cancelable) -> void {
    while (true) {
        T expected = x->load();
        T desired = expected;
        if (!mapping_cancelable(&desired)) {
            return;
        }
        if (x->compare_exchange_weak(expected, std::move(desired))) {
            return;
        }
    }
}

} // namespace rjqiao

#endif // MIAN_ATOMIC_H
