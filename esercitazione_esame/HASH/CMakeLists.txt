cmake_minimum_required(VERSION 3.30)
project(HASH)

set(CMAKE_CXX_STANDARD 20)

add_executable(HASH main.cpp
        hash.cpp
        hash.h
        hash_test.cpp)
