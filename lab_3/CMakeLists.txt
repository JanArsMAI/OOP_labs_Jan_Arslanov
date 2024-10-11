cmake_minimum_required(VERSION 3.10)
project(lab_3)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Главный исполняемый файл
add_executable(main main.cpp)

# Указываем путь к папке с Google Test
set(GTEST_DIR "./googletest")  # Укажите правильный путь до папки с Google Test

# Включаем Google Test
add_subdirectory(${GTEST_DIR})

# Включение тестирования
enable_testing()

# Тестируемый исполняемый файл
add_executable(tests test/test_01.cpp)

# Линкуем тесты с Google Test
target_link_libraries(tests PRIVATE gtest gtest_main)

# Добавление тестов в тестовый набор
add_test(NAME MyProjectTests COMMAND tests)
