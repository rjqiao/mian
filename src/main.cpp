//
// Created by Rongjin Qiao on 10/28/19.
//

#include <deque>
#include <iostream>
#include <string>
#include <mutex>

#include "base/deque.h"
#include "base/helpers.h"
// #include "thread_pool.h"
#include "base/concurrent_hash_map.h"
#include "base/concurrent_weak_map.h"
#include "base/spin_lock.h"
#include "base/read_write_spin_lock.h"
#include "base/lock_utils.h"

#include <atomic>

using std::cout;
using std::endl;

struct A {
    int id;

    A() = delete;

    explicit A(int id) : id(id) {}

    std::string to_string() { return "A::to_string, id = " + std::to_string(id); }
};

struct B {
};


int main2() {
//    std::atomic_fetch_add()
    rjqiao::deque<int> dq_rjqiao;

    std::deque<int> dq_std;

    rjqiao::deque<int>::pointer ptr1 = new int(10);
    std::cout << type_name<rjqiao::deque<int>::pointer>() << std::endl;

    std::cout << *ptr1 << std::endl;

    rjqiao::deque<A>::pointer ptr2 = new A(111);

    cout << ptr2->to_string() << endl;

    cout << "-----------" << endl;

    using it_B = rjqiao::deque<B>::iterator;
    using it_A = rjqiao::deque<A>::iterator;

    it_A a(nullptr);

//    rjqiao::operator+<A>(rjqiao::deque<A>::size_type(1), a);
    return 0;
}

int main() {
    std::deque<A> dq_std;
    cout<<"asdfasdfad\n";
//    rjqiao::deque<A> dq_rjqiao(1);
}