//
// Created by Rongjin Qiao on 10/26/19.
//

#ifndef DATA_STRUCTURES_ITERATOR_H
#define DATA_STRUCTURES_ITERATOR_H

#include <cstddef>
#include <iterator>

namespace rjqiao {
    template<class Category,
            class T,
            class Distance=std::ptrdiff_t,
            class Pointer=T *,
            class Reference = T &
    >
    struct iterator {
        typedef T value_type;
        typedef Distance difference_type;
        typedef Pointer pointer;
        typedef Reference reference;
        typedef Category iterator_category;
    };

    using std::input_iterator_tag;
    using std::output_iterator_tag;
    using std::forward_iterator_tag;
    using std::bidirectional_iterator_tag;
    using std::random_access_iterator_tag;


    using std::iterator_traits;

//    template<class Iter>
//    class iterator_traits {
//        using difference_type = typename Iter::difference_type ;
//        using value_type  = typename Iter::value_type;
//        using pointer = void;
//        using reference = typename Iter::reference;
//        using iterator_category = typename Iter::iterator_category;
//    };
//
//    template<class T>
//    class iterator_traits<T *> {
//        using difference_type = std::ptrdiff_t ;
//        using value_type  = T;
//        using pointer = const T*;
//        using reference = const T&;
//        using iterator_category = std::random_access_iterator_tag;
//    };
//
//    template<class T>
//    class iterator_traits<const T *>{
//        using difference_type = std::ptrdiff_t ;
//        using value_type  = T;
//        using pointer = const T*;
//        using reference = const T&;
//        using iterator_category = std::random_access_iterator_tag;
//    };

}

#endif //DATA_STRUCTURES_ITERATOR_H
