

find_package (Threads)
add_library(mian_lib deque.cpp iterator.cpp User.cpp unique_ptr.cpp semaphore.cpp)

# target_link_libraries (mian_lib Threads::Threads)

add_executable(mian_src main.cpp User.cpp)
