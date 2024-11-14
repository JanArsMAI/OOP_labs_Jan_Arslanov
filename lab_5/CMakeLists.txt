cmake_minimum_required(VERSION 3.10)
project(lab_5)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(include)

set(SOURCES
    src/array.cpp
    src/MemoryRes.cpp
)

add_executable(lab_5 main.cpp ${SOURCES})

add_subdirectory(googletest)

set(TEST_SOURCES tests/test_01.cpp ${SOURCES})

add_executable(run_tests ${TEST_SOURCES})

target_link_libraries(run_tests gtest gtest_main)

enable_testing()

add_test(NAME lab_tests COMMAND run_tests)