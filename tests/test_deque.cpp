//
// Created by Rongjin Qiao on 11/2/19.
//

#include <iostream>
#include <deque>
#include "gtest/gtest.h"
#include "deque.h"

using namespace rjqiao;

TEST (DequeTest1, DEQUE_INT) {
    deque<int> dq1;
    dq1.push_back(100);
    dq1.push_back(202);
    dq1.push_front(1);

    ASSERT_EQ(dq1.size(), 3);
    ASSERT_EQ(dq1.front(), 1);
    ASSERT_EQ(dq1.back(), 202);

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
    ASSERT_EQ(dq1.size(),0);
    ASSERT_TRUE(dq1.empty());

}

TEST(DequeTest1, DEQUE_A) {

}