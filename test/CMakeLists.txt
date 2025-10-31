find_package(GTest REQUIRED)

include_directories(${GTEST_INCLUDE_DIRS})

set(SOURCE_FILES
        test_main.cpp
        test_amount.cpp
        test_transaction.cpp
        test_transactiontype.cpp
        test_date.cpp
)

add_executable(runAllTests ${SOURCE_FILES})

target_link_libraries(runAllTests ${GTEST_BOTH_LIBRARIES} core)