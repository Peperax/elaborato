find_package(GTest REQUIRED)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/..)

set(SOURCE_FILES
        test_amount.cpp
        test_transaction.cpp
        test_transactiontype.cpp
        test_date.cpp
        test_register.cpp

        ../Amount.cpp
        ../Date.cpp
        ../Transaction.cpp
        ../TransactionType.cpp
        ../Register.cpp

)

add_executable(runAllTests ${SOURCE_FILES})

target_link_libraries(runAllTests GTest::gtest_main GTest::gtest core)