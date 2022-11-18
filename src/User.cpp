//
// Created by Rongjin Qiao on 2/20/20.
//

/* |IMPLEMENTATION| User.cpp file */

#include "User.h"
#include <iostream>
#include <utility>
using namespace std;

struct User::Impl {

    explicit Impl(string name)
            : name(std::move(name)){};

    ~Impl() = default;

    void welcomeMessage()
    {
        cout << "Welcome, "
             << name << endl;
    }

    string name;
    int salary = -1;
};

// Constructor connected with our Impl structure
User::User(string name)
        : pimpl(make_unique<Impl>(std::move(name)))
{
    pimpl->welcomeMessage();
}

// Default Constructor
User::~User() = default;

// Assignment operator and Copy constructor

User::User(const User& other)
        : pimpl(make_unique<Impl>(*other.pimpl))
{}

User& User::operator=(User rhs)
{
    swap(pimpl, rhs.pimpl);
    return *this;
}

// Getter and setter
int User::getSalary()
{
    return pimpl->salary;
}

void User::setSalary(int salary)
{
    pimpl->salary = salary;
    cout << "Salary set to "
         << salary << endl;
}