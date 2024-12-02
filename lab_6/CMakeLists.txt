cmake_minimum_required(VERSION 3.10)
project(lab_6)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)

set(SOURCES
     src/BattleArena.cpp
     src/ConsoleObserver.cpp
     src/druids.cpp
     src/extendedVisitor.cpp 
     src/FileObserver.cpp
     src/ork.cpp
     src/squirell.cpp
)

add_executable(lab_6 main.cpp ${SOURCES})

target_include_directories(lab_6 PRIVATE ${INCLUDE_DIR})

add_subdirectory(googletest)

set(TEST_SOURCES tests/test_01.cpp ${SOURCES})

add_executable(run_tests ${TEST_SOURCES})

target_link_libraries(run_tests gtest gtest_main)

enable_testing()

add_test(NAME lab_tests COMMAND run_tests)