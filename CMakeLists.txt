cmake_minimum_required(VERSION 3.14)
project(banking VERSION 1.0 LANGUAGES CXX)


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


enable_testing()

find_package(GTest REQUIRED)
include(GoogleTest)

option(ENABLE_COVERAGE "Enable coverage reporting" ON)
if(ENABLE_COVERAGE)
    add_compile_options(--coverage)
    add_link_options(--coverage)
endif()


add_library(banking
    src/Account.cpp
    src/Transaction.cpp
)

target_include_directories(banking PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/src/include
)


add_executable(banking_tests
    src/tests/AccountTest.cpp
    src/tests/TransactionTest.cpp
)


target_link_libraries(banking_tests
    banking
    GTest::GTest
    GTest::Main
    gcov
)

gtest_discover_tests(banking_tests)