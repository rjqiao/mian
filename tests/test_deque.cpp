//
// Created by Rongjin Qiao on 11/2/19.
//

#include <iostream>
#include <deque>
#include "gtest/gtest.h"
#include "base/deque.h"

using namespace rjqiao;

TEST (DequeTest1, DEQUE_INT) {
    deque<int> dq1;
    dq1.push_back(100);
    dq1.push_back(202);
    dq1.push_front(1);

    ASSERT_EQ(dq1.size(), 3);
    ASSERT_EQ(dq1.front(), 1);
    ASSERT_EQ(dq1.back(), 202);

    int arr[] = {1, 100, 202};
    int i = 0;

    for (auto x : dq1) {
        ASSERT_EQ(x, arr[i]);
        ++i;
    }

    i = 0;
    for (deque<int>::iterator it = dq1.begin(); it != dq1.end(); ++it) {
        ASSERT_EQ(*it, arr[i]);
//        std::cout<<"*it="<<*it<<std::endl;
        ++i;
    }


    int num = dq1.pop_and_get_front();
    ASSERT_EQ(num, 1);
    num = dq1.pop_and_get_back();
    ASSERT_EQ(num, 202);

//    std::cout<<"dq1.back()="<<dq1.back()<<std::endl;
//    std::cout<<"dq1.front()="<<dq1.front()<<std::endl;
    ASSERT_EQ(dq1.back(), dq1.front());
//    std::cout<<"dq1.size()="<<dq1.size()<<std::endl;
    ASSERT_EQ(dq1.size(), 1);

    num = dq1.pop_and_get_back();
    ASSERT_EQ(dq1.size(), 0);
    ASSERT_TRUE(dq1.empty());

}

TEST(DequeTest1, DEQUE_CONSTRUCTOR) {
    int arr[] = {5, 10, 15, 105};
    int *begin = &arr[0], *end = begin + 4;

    auto dq = deque<int>(begin, end);

    size_t i = 0;
    for (auto it = dq.begin(); it != dq.end(); ++it) {
        ASSERT_EQ(*it, arr[i]);
//        std::cout<<"*it="<<*it<<std::endl;
        ++i;
    }

    for (i = 0; i < 4; ++i) {
        ASSERT_EQ(dq[i], arr[i]);
    }

    dq[2] = 134;
    auto it = dq.begin();
    ASSERT_EQ(*(it + 2), 134);

    auto dq2 = deque<int>(begin, begin);
    ASSERT_EQ(dq2.size(), 0);
    ASSERT_EQ(dq2._head, nullptr);
    ASSERT_EQ(dq2.begin().dll_ptr, nullptr);
    auto dq_2_5 = dq2;

    auto dq_3 = dq;
    auto dq_4 = dq_3;
    dq_3[0] = 999;
    ASSERT_EQ(dq_4[0], 5);
    ASSERT_EQ(dq_3[0], 999);
}