//
// Created by rjqia on 3/9/2022.
//

#ifndef MIAN_READ_WRITE_SPIN_LOCK_H
#define MIAN_READ_WRITE_SPIN_LOCK_H

#include <atomic>
#include <memory>
#include <mutex>

#include "spin_lock.h"

struct ReadWriteLock {

    SpinLock lock;

    unsigned write_count{0};
    unsigned read_count{0};

    void lock_read() {
        while (true) {
            std::lock_guard<SpinLock> l(lock);
            if (write_count == 0) {
                read_count++;
                break;
            }
        }
    }

    void unlock_read() {
        std::lock_guard<SpinLock> l(lock);
        read_count--;
    }

    void write_lock() {
        while (true) {
            std::lock_guard<SpinLock> l(lock);
            if (read_count > 0 || write_count > 0) {
                break;
            }
        }
    }

    void write_unlock() {
        std::lock_guard<SpinLock> l(lock);
        write_count = 0;
    }
};

#endif // MIAN_READ_WRITE_SPIN_LOCK_H
