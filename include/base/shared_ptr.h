//
// Created by rjqia on 1/8/2022.
//

#ifndef MIAN_SHARED_PTR_H
#define MIAN_SHARED_PTR_H

#include <atomic>
#include <cassert>
#include <cstdint>
#include <functional>
#include <memory>

#include "atomic.h"
#include "unique_ptr.h"

namespace rjqiao {
template <class T> struct SharedInner {
  private:
    struct Count {
        int32_t shared;
        int32_t weak;
    };

    T *obj;
    std::function<void()> deleter;
    std::atomic<Count> count;

  public:
    SharedInner() = delete;

    SharedInner(SharedInner const &) = delete;

    SharedInner(SharedInner &&) = delete;

    explicit SharedInner(T *obj, std::function<void()> deleter = default_delete<T>())
        : obj(obj), deleter(std::move(deleter)), count{Count{1, 0}} {}

    // - by weak lock
    // - by shared copy
    // true on creating shared successfully
    bool add_shared() {
        bool succeed = false;
        atomic_update(&count, [&succeed](Count old) -> Count {
            uint32_t strong = old.shared, weak = old.weak;
            assert(strong > 0 || weak > 0);

            if (strong != 0) {
                strong++;
                succeed = true;
            } else {
                succeed = false;
            }
            return {strong, weak};
        });
        return succeed;
    }

    // shared destruct
    //
    void remove_shared() {
        bool delete_shared = false;
        bool delete_all = false;

        atomic_update(&count, [&delete_shared, &delete_all](Count old) -> Count {
            uint32_t strong = old.shared, weak = old.weak;
            assert(strong > 0);

            strong--;

            delete_shared = false;
            delete_all = false;
            if (strong == 0) {
                delete_shared = true;
                if (weak == 0) {
                    delete_all = true;
                }
            }

            return {strong, weak};
        });

        if (delete_shared) {
            deleter(obj);
        }
        if (delete_all) {
            delete this;
        }
    }

    // shared spawn weak.
    // weak copy
    // always succeed
    void add_weak() {
        atomic_update(&count, [](Count old) -> Count {
            uint32_t strong = old.shared, weak = old.weak;
            assert(weak > 0 || strong > 0);
            weak++;
            return {strong, weak};
        });
    }

    // weak destruct
    void remove_weak() {
        bool delete_all = false;
        atomic_update(&count, [&](Count old) -> Count {
            uint32_t strong = old.shared, weak = old.weak;
            assert(weak > 0);

            delete_all = false;
            if (strong == 0 && weak == 0) {
                delete_all = true;
            }
        });

        if (delete_all) {
            delete this;
        }
    }

    bool shared_refable() { return count.load().shared != 0; }
};

template <class T> struct weak_ptr;

template <class T> struct shared_ptr {
  private:
    SharedInner<T> *inner = nullptr;

  public:
    using element_type = T;
    using weak_type = weak_ptr<T>;

    constexpr shared_ptr(std::nullptr_t = nullptr) noexcept : inner(nullptr) {}

    template <class Y> explicit shared_ptr(Y *ptr) : inner(new SharedInner<T>(ptr)) {}

    template <class Y, class Deleter>
    shared_ptr(Y *ptr, Deleter d) : inner(new SharedInner<T>(ptr, d)) {}

    template <class Y> shared_ptr(shared_ptr<Y> const &r) noexcept : inner(r.inner) {
        inner->add_shared();
    }

    template <class Y> shared_ptr(shared_ptr<Y> &&r) noexcept : inner(r.inner) { inner = nullptr; }

    template <class Y> explicit shared_ptr(weak_ptr<Y> const &r);

    template<class Y, class Deleter>
    shared_ptr(std::unique_ptr<Y, Deleter> && r)
        : shared_ptr(r.get())
    {
        // Deleter reference or pointer
        r = nullptr;
    }

    template<class Y>
    shared_ptr & operator=(shared_ptr<Y> const & r) noexcept
    {
        shared_ptr(r).swap(*this); // no heap allocation
    }

    template<class Y>
    shared_ptr & operator=(shared_ptr && r) noexcept
    {
        shared_ptr(std::move(r)).swap(*this);
    }

    template<class Y, class Deleter>
    shared_ptr & operator=(std::unique_ptr<Y, Deleter>&&r) {

    }

    ~shared_ptr() {
        if (inner) {
            inner->remove_shared();
        }
    }

    element_type *get() { return inner->obj; }

    void reset() {
        inner->remove_shared();
        inner = nullptr;
    }

    T &operator*() const noexcept {
        return *inner->obj;
    }

    T *operator->() const noexcept {
        return &(*this);
    }

    friend void swap(shared_ptr &lhs, shared_ptr &rhs) {
        using std::swap;
        swap(lhs.inner, rhs.inner);
    }
};
template <class T> struct weak_ptr {
  private:
    SharedInner<T> *inner = nullptr;

  public:
    constexpr weak_ptr() noexcept = default;

    template <class Y> weak_ptr(weak_ptr<Y> const &r) noexcept : inner(r.inner) {
        inner->add_weak();
    }

    template <class Y> weak_ptr(shared_ptr<Y> const &r) noexcept : inner(r.inner) {
        inner->add_weak();
    }

    template <class Y> weak_ptr(weak_ptr<Y> &&r) noexcept : inner(r.inner) { inner->add_weak(); }

    shared_ptr<T> lock() const noexcept {
        shared_ptr<T> res;
        if (!inner->add_shared()) {
            return res;
        }
        res.inner = inner;
        return res;
    }

    bool expired() { return inner->shared_refable(); }

    ~weak_ptr() {
        if (inner != nullptr) {
            inner->remove_weak();
        }
    }
};

template <class T>
template <class Y>
shared_ptr<T>::shared_ptr(const weak_ptr<Y> &r) : shared_ptr(r.lock()) {}

} // namespace rjqiao

#endif // MIAN_SHARED_PTR_H
