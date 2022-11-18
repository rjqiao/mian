//
// Created by rjqia on 3/9/2022.
//

#ifndef MIAN_SPIN_LOCK_H
#define MIAN_SPIN_LOCK_H

#include <assert.h>
#include <atomic>
#include <stdio.h>


struct SpinLock {
    std::atomic<bool> _x{false};

    void lock() {
        while (try_lock()) {
        }
        assert(_x.load());
    }

    void unlock() {
        assert(_x.load());
        _x.store(false);
    }

    bool try_lock() {
        bool expected = false;
        return _x.compare_exchange_weak(expected, true);
    }
};

#endif // MIAN_SPIN_LOCK_H
