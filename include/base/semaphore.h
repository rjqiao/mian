//
// Created by rjqia on 3/7/2022.
//

#ifndef PLAYGROUND_SEMAPHORE_H
#define PLAYGROUND_SEMAPHORE_H

#include <condition_variable>
#include <mutex>

class Semaphore {
    std::mutex mutex_;
    std::condition_variable condition_;
    unsigned long count_ = 0; // Initialized as locked.

  public:
    void release();

    void acquire();

    bool try_acquire();

    void dummy();
};
#endif // PLAYGROUND_SEMAPHORE_H
