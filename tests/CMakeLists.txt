cmake_minimum_required(VERSION 3.14)

# GoogleTest requires at least C++14
set(CMAKE_CXX_STANDARD 20)

include(FetchContent)
FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG release-1.12.1
)

# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

find_package (Threads)

# Now simply link against gtest or gtest_main as needed. Eg
add_executable(mian_test
        fake_unittest.cpp
        test_deque.cpp
        unique_ptr_test.cpp
        hello_test.cc
        )

target_link_libraries(
        mian_test
        GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(mian_test)


add_executable(test_thread_pool test_thread_pool.cpp)


target_link_libraries(
        test_thread_pool
        mian_lib
        GTest::gtest_main
        # Threads::Threads
)

include(GoogleTest)
gtest_discover_tests(test_thread_pool)

#link_directories(${PROJECT_SOURCE_DIR}/src)

#add_test(NAME unittest_0 COMMAND mian_test)

