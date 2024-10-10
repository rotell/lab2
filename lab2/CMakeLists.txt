cmake_minimum_required(VERSION 3.10)
project(DominoTest)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(googletest)

add_executable(DominoTest
        Domino.cpp
        DominoGroup.cpp
        test_domino.cpp
)

target_link_libraries(DominoTest gtest gtest_main)

enable_testing()
add_test(NAME DominoTest COMMAND DominoTest)
