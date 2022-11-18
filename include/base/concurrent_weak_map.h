//
// Created by rjqia on 3/7/2022.
//

#ifndef MIAN_CONCURRENT_WEAK_MAP_H
#define MIAN_CONCURRENT_WEAK_MAP_H

#include <mutex>
#include <unordered_map>
#include <memory>


template<class Key, class Value>
class ConcurrentWeakMap {

    std::mutex mu;
    std::unordered_map<Key, Value> storage;

    void put(Key const & key, std::weak_ptr<Value> const & value) {

    }

    // insert even if exist
    void put(Key const & key, std::weak_ptr<Value> && value) {
        std::unique_lock<std::mutex> lock;
        auto it = storage.find(key);
        if (it == storage.end()) {
            storage.emplace(key, std::move(value));
        } else {
            it->second = std::move(value);
        }
    }

};

#endif // MIAN_CONCURRENT_WEAK_MAP_H
