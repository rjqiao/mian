cmake_minimum_required(VERSION 3.15)
project(mian)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")


set(INCLUDE_PROJECT_DIR ${CMAKE_SOURCE_DIR}/include)
include_directories(${INCLUDE_PROJECT_DIR})

add_subdirectory(src)
add_subdirectory(tests)
