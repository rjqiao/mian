//
// Created by rjqia on 3/6/2022.
//

#include "gtest/gtest.h"
#include <deque>
#include <iostream>
#include <memory>

#include "base/semaphore.h"
#include "base/thread_pool.h"

using namespace rjqiao;

//TEST(FixedThreadPoolTest, Basic) {
//    auto thread_pool = std::make_shared<FixedThreadPool>(5);
//    std::cout << "in semaphore\n";
//}

TEST(SemaphoreTest, Basic) {
    auto sem = Semaphore();
//    sem.acquire();
    sem.dummy();
    EXPECT_EQ(7 * 6, 42);
//    std::cout << "in semaphore\n";
//    sem.release();
}