cmake_minimum_required(VERSION 3.10)
project(lab_7)

# Использование стандарта C++20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Установить режим сборки
set(CMAKE_BUILD_TYPE Debug)

# Установить глобальные флаги компиляции для отладки
set(CMAKE_CXX_FLAGS_DEBUG "-g -O0")

# Указание пути к заголовочным файлам
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

# Список исходных файлов
set(SOURCES
     src/BattleArena.cpp
     src/ConsoleObserver.cpp
     src/druids.cpp
     src/extendedVisitor.cpp 
     src/FileObserver.cpp
     src/ork.cpp
     src/squirell.cpp
)

add_executable(lab_7 main.cpp ${SOURCES})

target_compile_options(lab_7 PRIVATE -g -O0)

add_subdirectory(googletest)

set(TEST_SOURCES tests/test_01.cpp ${SOURCES})

add_executable(run_tests ${TEST_SOURCES})

target_link_libraries(run_tests gtest gtest_main)

enable_testing()

add_test(NAME lab_tests COMMAND run_tests)