#include <gtest/gtest.h>
#include "../src/rectangle.cpp"
#include "../src/square.cpp"
#include "../src/triangle.cpp"

TEST(test_of_square, correct_square)
{
    Point points[4] = {{-1.0, -1.0},{-1.0, 1.0},{1.0, 1.0}, {1.0, -1.0}};
    Square rect_1(points);
    ASSERT_TRUE(static_cast<double>(rect_1) == 4.0);
    ASSERT_NO_THROW(rect_1.get_data());
    Point cent = rect_1.center();
    ASSERT_TRUE(cent.y == 0.0);
    ASSERT_TRUE(cent.x == 0.0);
}

TEST(test_of_triangle, correct_triangle)
{
    Point points[3] = {{0.0, 1.0},{1.0, 0.0},{0.0, -1.0}};
    Triangle triangle_1(points);
    ASSERT_NO_THROW(triangle_1.get_data());
    Point cent = triangle_1.center();
    ASSERT_TRUE(cent.y == 0.0);
}

TEST(test_of_rectangle, correct_rectangle)
{
    Point points[4] = {{-4.0, -1.0},{-4.0, 1.0},{4.0, 1.0}, {4.0, -1.0}};
    Rectangle rect_1(points);
    ASSERT_TRUE(static_cast<double>(rect_1) == 16.0);
    ASSERT_NO_THROW(rect_1.get_data());
    Point cent = rect_1.center();
    ASSERT_TRUE(cent.y == 0.0);
    ASSERT_TRUE(cent.x == 0.0);
}

TEST(test_of_triangle, wrong_triangle)
{
    Point points[3] = {{0, 0}, {0, 1}, {0, 5}};
    Point points_2[3] = {{0, 0}, {0, 1}, {0, 0}};
    EXPECT_THROW(Triangle triangle_1(points), std::invalid_argument);
    EXPECT_THROW(Triangle triangle_1(points_2), std::invalid_argument);
}


TEST(test_of_rectangle, wrong_rectangle)
{
    Point points[4] = {{0, 0}, {0, 1}, {0, 5}, {0, 3}};
    Point points_2[4] = {{-4.0, -1.0},{-4.0, 1.0},{4.0, 1.0}, {4.0, -1.2}};
    Point points_3[4] = {{-4.0, -1.0},{-4.0, -1.0},{4.0, 1.0}, {4.0, -1.0}};
    EXPECT_THROW(Rectangle rect_1(points), std::invalid_argument);
    EXPECT_THROW(Rectangle rect_2(points_2), std::invalid_argument);
    EXPECT_THROW(Rectangle rect_3(points_3), std::invalid_argument);
}


TEST(test_of_square, wrong_square)
{
    Point points[4] = {{0, 0}, {0, 1}, {0, 5}, {0, 3}};
    Point points_2[4] = {{-4.0, -1.0},{-4.0, 1.0},{4.0, 1.0}, {4.0, -1.2}};
    Point points_3[4] = {{-4.0, -1.0},{-4.0, -1.0},{4.0, 1.0}, {4.0, -1.0}};
    Point points_4[4] = {{-4.0, -1.0},{-4.0, 1.0},{4.0, 1.0}, {4.0, -1.0}};
    EXPECT_THROW(Square rect_1(points), std::invalid_argument);
    EXPECT_THROW(Square rect_2(points_2), std::invalid_argument);
    EXPECT_THROW(Square rect_3(points_3), std::invalid_argument);
    EXPECT_THROW(Square rect_3(points_4), std::invalid_argument);
}