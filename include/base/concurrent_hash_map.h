//
// Created by rjqia on 3/7/2022.
//

#ifndef MIAN_CONCURRENT_HASH_MAP_H
#define MIAN_CONCURRENT_HASH_MAP_H

#include <mutex>
#include <unordered_map>

template<class Key, class Value>
class ConcurrentHashMap {
    std::mutex mu;
    std::unordered_map<Key,Value> hash_map;


    void put(Key && key, Value && value) {
        std::unique_lock<std::mutex> lock(mu);

        auto it = hash_map.find(key);
        if (it == hash_map.end()) {
            hash_map.emplace(key, std::move(value));
        } else {
            it->second = std::move(value);
        }
    }
};

#endif // MIAN_CONCURRENT_HASH_MAP_H
