cmake_minimum_required(VERSION 3.30)
project(elaborato)

set(CMAKE_CXX_STANDARD 17)

add_executable(elaborato main.cpp
        Transaction.cpp
        Transaction.h)
