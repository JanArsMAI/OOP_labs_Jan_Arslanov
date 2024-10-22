cmake_minimum_required(VERSION 3.10)
project(lab_3)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wuninitialized -Wall")

add_executable(${CMAKE_PROJECT_NAME}_exe main.cpp)

add_library(${CMAKE_PROJECT_NAME}_lib_point src/point.cpp)
add_library(${CMAKE_PROJECT_NAME}_lib_figure src/figure.cpp)
add_library(${CMAKE_PROJECT_NAME}_lib_triangle src/triangle.cpp)
add_library(${CMAKE_PROJECT_NAME}_lib_rectangle src/rectangle.cpp)
add_library(${CMAKE_PROJECT_NAME}_lib_square src/square.cpp)

target_link_libraries(${CMAKE_PROJECT_NAME}_exe PRIVATE 
    ${CMAKE_PROJECT_NAME}_lib_point
    ${CMAKE_PROJECT_NAME}_lib_figure
    ${CMAKE_PROJECT_NAME}_lib_triangle
    ${CMAKE_PROJECT_NAME}_lib_rectangle
    ${CMAKE_PROJECT_NAME}_lib_square
)


target_link_libraries(${CMAKE_PROJECT_NAME}_lib_triangle PRIVATE ${CMAKE_PROJECT_NAME}_lib_point)
target_link_libraries(${CMAKE_PROJECT_NAME}_lib_rectangle PRIVATE ${CMAKE_PROJECT_NAME}_lib_point)
target_link_libraries(${CMAKE_PROJECT_NAME}_lib_square PRIVATE ${CMAKE_PROJECT_NAME}_lib_point)

set(GTEST_DIR "./googletest")
add_subdirectory(${GTEST_DIR})


enable_testing()

add_executable(tests test/test_01.cpp)


target_link_libraries(tests PRIVATE
    ${CMAKE_PROJECT_NAME}_lib_point
    ${CMAKE_PROJECT_NAME}_lib_figure
    ${CMAKE_PROJECT_NAME}_lib_triangle
    ${CMAKE_PROJECT_NAME}_lib_rectangle
    ${CMAKE_PROJECT_NAME}_lib_square
    gtest
    gtest_main
)

add_test(NAME MyProjectTests COMMAND tests)
