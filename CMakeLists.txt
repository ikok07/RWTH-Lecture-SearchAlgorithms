cmake_minimum_required(VERSION 4.3)
project(search_algorithms)

set(CMAKE_CXX_STANDARD 23)

include_directories(include)

add_executable(search_algorithms
        include/bintree.hpp
        include/bintree.tpp
        include/student.hpp
        src/main.cpp)
