cmake_minimum_required(VERSION 3.15)
project(mian)

set(CMAKE_CXX_STANDARD 20)

# compile_commands.json
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)




# libc++
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++ -v")
# set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -stdlib=libc++ -lc++abi")


# Does this work? force c++ compiler?
#set(CMAKE_CXX_COMPILER "/usr/bin/clang++-13")
#set(CMAKE_C_COMPILER "/usr/bin/clang-13")

#libcxx which we will use with specific version of clang
# SET(LIBCXX_INC_PATH /usr/lib/llvm-13/include/c++/v1)
# SET(LIBCXX_LIB_PATH /usr/lib/llvm-13/lib/)






set(PROJECT_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)
include_directories(${PROJECT_INCLUDE_DIR})

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

set(EXECUTABLE_INSTALL_DIR ${CMAKE_SOURCE_DIR}/bin)
set(LIB_INSTALL_DIR ${CMAKE_SOURCE_DIR}/lib)
set(HEADER_INSTALL_DIR ${PROJECT_INCLUDE_DIR}/${PROJECT_NAME})

add_subdirectory(src)
add_subdirectory(tests)
