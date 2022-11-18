//
// Created by rjqia on 3/6/2022.
//

#ifndef MIAN_BLOCKING_QUEUE_H
#define MIAN_BLOCKING_QUEUE_H

#include <condition_variable>
#include <functional>
#include <limits>
#include <memory>
#include <mutex>
#include <queue>
#include <utility>

namespace rjqiao {

template <class T> class BlockingQueue {
  private:
    size_t capacity;
    std::queue<T> q;
    std::mutex mu;
    std::condition_variable cond;
    std::function<bool()> stop_predicate;

    static bool default_stop_predicate() { return false; }

  public:
    explicit BlockingQueue(
        size_t cap_ = std::numeric_limits<size_t>::max(),
        std::function<bool()> stop_predicate_ = {default_stop_predicate})
        : capacity(cap_), stop_predicate(std::move(stop_predicate_)) {}

    bool enqueue(T &&value) {
        std::unique_lock<std::mutex> lock(mu);
        cond.wait(lock, [this] { return !stop_predicate() && q.size() == capacity; });
        if (!stop_predicate) {
            return false;
        }
        q.push(std::forward<T>(value));
        cond.notify_all();
    }

    bool dequeue(T& res) {
        std::unique_lock<std::mutex> lock(mu);
        cond.wait(lock, [this] { return !stop_predicate() && q.empty(); });
        if(stop_predicate()) {
            return false;
        }
        res = std::move(q.front());
        q.pop();
        cond.notify_all();
    }
};

} // namespace rjqiao

#endif // MIAN_BLOCKING_QUEUE_H
