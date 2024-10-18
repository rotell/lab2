cmake_minimum_required(VERSION 3.27)
project(DominoTest)

set(CMAKE_CXX_STANDARD 23)

add_subdirectory(googletest)

add_executable(DominoTest
        Domino.cpp
        DominoGroup.cpp
        test_domino.cpp
)

target_link_libraries(DominoTest gtest gtest_main)

enable_testing()
add_test(NAME DominoTest COMMAND DominoTest)

find_package(Doxygen)

if(DOXYGEN_FOUND)
    set(DOXYGEN_IN ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile)

    set(DOXYGEN_OUT ${CMAKE_CURRENT_BINARY_DIR}/docs)

    add_custom_target(doc ALL
            COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_IN}
            WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
            COMMENT "Генерация документации с помощью Doxygen"
            VERBATIM
    )
else()
    message(WARNING "Doxygen не найден, пропуск генерации документации")
endif()
