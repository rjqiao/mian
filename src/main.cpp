//
// Created by Rongjin Qiao on 10/28/19.
//

#include <deque>
#include <iostream>
#include <string>

#include "deque.h"
#include "helpers.h"

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

    rjqiao::operator+<A>(rjqiao::deque<A>::size_type(1), a);
}

int main() {
    std::deque<A> dq_std;
//    rjqiao::deque<A> dq_rjqiao(1);
}