//
// Created by rjqia on 3/6/2022.
//

#ifndef MIAN_THREAD_POOL_H
#define MIAN_THREAD_POOL_H

#include <atomic>
#include <condition_variable>
#include <functional>
#include <limits>
#include <mutex>
#include <queue>
#include <thread>
#include <vector>

#include "blocking_queue.h"

// struct ThreadPoolItf {
//
//     template<class func_t>
//     bool add_task(func_t func) = 0;
// };

namespace rjqiao {

struct FixedThreadPool {

  private:
    size_t const capacity;
    size_t const max_waiting = std::numeric_limits<size_t>::max();
    bool _stopped{false};

    std::mutex mu;
    std::condition_variable cond;

    std::queue<std::function<void()>> tasks;
    //    BlockingQueue<std::function<void()>> tasks;
    std::vector<std::thread> threads;

  public:
    explicit FixedThreadPool(size_t cap_) : capacity(cap_) {
        for (size_t i = 0; i < capacity; ++i) {
            std::thread(&FixedThreadPool::run_thread, this).detach();
        }
    }

    FixedThreadPool(FixedThreadPool const &) = delete;
    FixedThreadPool(FixedThreadPool &&) = delete;

    template <class func_t> bool add_task(func_t func) {
        std::unique_lock<std::mutex> lock(mu);
        cond.wait(lock, [this]() { return !_stopped && tasks.size() == capacity; });
        if (_stopped) {
            return false;
        }
        tasks.emplace(std::move(func));

        return true;
    }

    void run_thread() {
        while (true) {
            std::unique_lock<std::mutex> lock(mu);
            cond.wait(lock, [this]() { return !_stopped && tasks.empty(); });
            if (_stopped) {
                return;
            }
            auto task = std::move(tasks.front());
            tasks.pop();
        }
    }

    void stop() {
        std::unique_lock<std::mutex> lock(mu);
        _stopped = true;
        cond.notify_all();
    }

    bool stopped() {
        std::unique_lock<std::mutex> lock(mu);
        return _stopped;
    }

    ~FixedThreadPool() {}
};

} // namespace rjqiao
#endif // MIAN_THREAD_POOL_H
