//
// Created by rjqia on 1/9/2022.
//

#ifndef MIAN_VERSION_NUMBER_H
#define MIAN_VERSION_NUMBER_H

#include<iostream>
#include<string>

std::string ver_string(int a, int b, int c) {
    std::ostringstream ss;
    ss << a << '.' << b << '.' << c;
    return ss.str();
}

std::string true_cxx =
#ifdef __clang__
        "clang++";
#else
"g++";
#endif

std::string true_cxx_ver =
#ifdef __clang__
        ver_string(__clang_major__, __clang_minor__, __clang_patchlevel__);
#else
ver_string(__GNUC__, __GNUC_MINOR__, __GNUC_PATCHLEVEL__);
#endif

#endif //MIAN_VERSION_NUMBER_H
