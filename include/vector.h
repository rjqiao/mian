//
// Created by Rongjin Qiao on 11/3/19.
//

#pragma once

#include "base.h"

namespace rjqiao {
    template<class T, class Alloc = allocator<T> >
    class vector;


    struct vector_iterator {

    };

    template<class T, class Alloc = allocator<T> >
    struct vector {
        using value_type = T;
        using allocator_type = Alloc;
        using reference = value_type &;
        using const_reference = const value_type &;
        using pointer = typename allocator_traits<allocator_type>::pointer;
        using size_type = std::size_t;
        using difference_type = std::ptrdiff_t;
        using iterator = vector_iterator;


    };
}
