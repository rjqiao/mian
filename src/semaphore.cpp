//
// Created by rjqia on 10/12/2022.
//

#include "base/semaphore.h"
#include <iostream>

void Semaphore::release() {
    std::lock_guard<decltype(mutex_)> lock(mutex_);
    ++count_;
    condition_.notify_one();
}

void Semaphore::acquire() {

    std::unique_lock<decltype(mutex_)> lock(mutex_);
    while (!count_) // Handle spurious wake-ups.
        condition_.wait(lock);
    --count_;
}

bool Semaphore::try_acquire() {
    std::lock_guard<decltype(mutex_)> lock(mutex_);
    if (count_) {
        --count_;
        return true;
    }
    return false;
}

void Semaphore::dummy() {
    std::cout<<"Semaphore::dummy()\n";
}