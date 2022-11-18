//
// Created by rjqia on 1/8/2022.
//

#ifndef MIAN_UNIQUE_PTR_H
#define MIAN_UNIQUE_PTR_H

#include <cstddef>
#include <utility>

namespace rjqiao {

template <typename T> struct default_delete {
    constexpr default_delete() noexcept = default;

    //        template<typename U>
    //        explicit default_delete(default_delete<U> const &d) noexcept;

    void operator()(T *ptr) const { delete ptr; }

    //        template<typename U>
    //        void operator()(U *ptr) const;
};

template <typename T, typename Deleter = default_delete<T>> struct unique_ptr {
  private:
    T *ptr;

  public:
//    template <class = T, std::enable_if_t<std::is_default_constructible_v<Deleter>, bool> = true>
    explicit unique_ptr(T *ptr = nullptr) : ptr(ptr) {}

//    template <class = T, std::enable_if_t<!std::is_default_constructible_v<Deleter>, bool> = false>
//    unique_ptr(T *ptr = nullptr) = delete;

    unique_ptr(unique_ptr const &) = delete;

    unique_ptr(unique_ptr &&other) noexcept : ptr(ptr) { other.ptr = nullptr; }

    ~unique_ptr() { Deleter()(ptr); }

    unique_ptr &operator=(unique_ptr const &) = delete;

    unique_ptr &operator=(unique_ptr &&other) noexcept;

    T *release();

    void reset();

    void swap(unique_ptr &other) noexcept;

    T *get();

    explicit operator bool() const noexcept;

    T &operator*() const noexcept;

    T *operator->() const noexcept;
};

template <typename T, typename... Args> unique_ptr<T> make_unique(Args &&...args);

template <typename T1, typename D1, typename T2, typename D2>
bool operator==(unique_ptr<T1, D1> const &x, unique_ptr<T2, D2> &y) {
    return x.ptr == y.ptr;
}

template <typename T1, typename D1, typename T2, typename D2>
bool operator!=(unique_ptr<T1, D1> const &x, unique_ptr<T2, D2> &y) {
    return !(x == y);
}

template <typename T, typename D> bool operator==(unique_ptr<T, D> const &x, std::nullptr_t) noexcept { return x; }

template <typename T, typename D> bool operator!=(unique_ptr<T, D> const &x, std::nullptr_t) noexcept { return !x; }
} // namespace rjqiao

// implementation
namespace rjqiao {
template <typename T, typename... Args> unique_ptr<T> make_unique(Args &&...args) {
    return unique_ptr<T>(new T(std::forward<Args>(args)...));
}

template <typename T, typename Deleter> void unique_ptr<T, Deleter>::swap(unique_ptr &other) noexcept {
    auto temp = ptr;
    ptr = other.ptr;
    other.ptr = temp;
}

template <typename T, typename Deleter> void unique_ptr<T, Deleter>::reset() { ptr = nullptr; }

template <typename T, typename Deleter> T *unique_ptr<T, Deleter>::release() {
    auto res = ptr;
    ptr = nullptr;
    return res;
}

template <typename T, typename Deleter>
auto unique_ptr<T, Deleter>::operator=(unique_ptr &&other) noexcept -> unique_ptr & {
    ptr = other.ptr;
    other.ptr = nullptr;
}

template <typename T, typename Deleter> T *unique_ptr<T, Deleter>::get() { return ptr; }

template <typename T, typename Deleter> unique_ptr<T, Deleter>::operator bool() const noexcept {
    return ptr != nullptr;
}

template <typename T, typename Deleter> T &unique_ptr<T, Deleter>::operator*() const noexcept { return *ptr; }

template <typename T, typename Deleter> T *unique_ptr<T, Deleter>::operator->() const noexcept { return ptr; }

} // namespace rjqiao
#endif // MIAN_UNIQUE_PTR_H
