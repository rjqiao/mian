//
// Created by Rongjin Qiao on 11/3/19.
//

#pragma once

#include "iterator.h"
#include "base.h"

namespace rjqiao {
    template<class T, class Alloc>
    struct vector;

    template<class T, class Ref, class Ptr>
    struct _Vector_iterator {
        using value_type = T;
        using pointer = Ptr;
        using reference = Ref;
        using size_type = size_t;
        using difference_type = std::ptrdiff_t;
        using iterator_category = random_access_iterator_tag;


    };

    template<class T, class Alloc = allocator<T> >
    struct vector {
        using value_type = T;
        using allocator_type = Alloc;
        using reference = value_type &;
        using const_reference = const value_type &;
        using pointer = typename allocator_traits<allocator_type>::pointer;
        using const_pointer = typename allocator_traits<allocator_type>::const_pointer;
        using size_type = std::size_t;
        using difference_type = std::ptrdiff_t;

        using iterator = _Vector_iterator<value_type, reference, pointer>;
        using const_iterator = _Vector_iterator<value_type, const_reference, const_pointer>;

        // -------------------------- Members --------------------------------

        size_t size = 0;


        vector() {

        }
    };
}
