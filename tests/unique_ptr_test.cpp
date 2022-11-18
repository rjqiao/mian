//
// Created by rjqia on 1/8/2022.
//

#include <gtest/gtest.h>
#include "base/memory_management.h"
#include <iostream>
#include <memory>
#include "base/version_number.h"

using namespace rjqiao;

TEST(UniquePtrTest, BasicAssertions) {
    unique_ptr<int> x {new int(10)};
    std::unique_ptr<int> y {new int(11)};
    std::shared_ptr<int> z = std::make_shared<int>(123);

    std::cout<<true_cxx<<std::endl;
    std::cout<<*x<<std::endl;
}