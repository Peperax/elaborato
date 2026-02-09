cmake_minimum_required(VERSION 3.30)
project(elaborato)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES
        main.cpp
        Transaction.cpp
        Transaction.h
        Date.cpp
        Date.h
        Amount.cpp
        Amount.h
        TransactionType.cpp
        TransactionType.h
        Register.cpp
        Register.h
)

add_library(core ${SOURCE_FILES})

add_executable(elaborato main.cpp)
target_link_libraries(elaborato core)

add_subdirectory(test)