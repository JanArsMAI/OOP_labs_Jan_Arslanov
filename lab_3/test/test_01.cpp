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
    ASSERT_TRUE(cent.get_y() == 0.0);
    ASSERT_TRUE(cent.get_x() == 0.0);
}

TEST(test_of_triangle, correct_triangle)
{
    Point points[3] = {{0.0, 1.0},{1.0, 0.0},{0.0, -1.0}};
    Triangle triangle_1(points);
    ASSERT_NO_THROW(triangle_1.get_data());
    Point cent = triangle_1.center();
    ASSERT_TRUE(cent.get_y() == 0.0);
}

TEST(test_of_rectangle, correct_rectangle)
{
    Point points[4] = {{-4.0, -1.0},{-4.0, 1.0},{4.0, 1.0}, {4.0, -1.0}};
    Rectangle rect_1(points);
    ASSERT_TRUE(static_cast<double>(rect_1) == 16.0);
    ASSERT_NO_THROW(rect_1.get_data());
    Point cent = rect_1.center();
    ASSERT_TRUE(cent.get_y() == 0.0);
    ASSERT_TRUE(cent.get_x() == 0.0);
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


TEST(test_of_equality_triangles, equal_triangles)
{
    Point points[3] = {{0, 1}, {1, 1}, {2, 0}};
    Point points_2[3] = {{0, 1}, {1, 1}, {2, 0}};
    Triangle t_1(points);
    Triangle t_2(points_2);
    ASSERT_TRUE(t_1 == t_2);
}

TEST(test_of_equality_square, equal_square)
{
    Point points[4] = {{-1.0, -1.0},{-1.0, 1.0},{1.0, 1.0}, {1.0, -1.0}};
    Square rect_1(points);
    Point points_2[4] = {{-1.0, -1.0},{-1.0, 1.0},{1.0, 1.0}, {1.0, -1.0}};
    Square rect_2(points_2);
    ASSERT_TRUE(rect_1 == rect_2);
}

TEST(test_of_equality_rectangles, equal_rectangles)
{
    Point points[4] = {{-4.0, -1.0},{-4.0, 1.0},{4.0, 1.0}, {4.0, -1.0}};
    Rectangle rect_1(points);
    Point points_2[4] = {{-4.0, -1.0},{-4.0, 1.0},{4.0, 1.0}, {4.0, -1.0}};
    Rectangle rect_2(points);
    ASSERT_TRUE(rect_1 == rect_2);
}


TEST(test_of_not_equality_triangles, not_equal_triangles)
{
    Point points[3] = {{0.0, 2.0},{1.0, 0.0},{0.0, -1.0}};
    Point points_2[3] = {{0.0, 1.0},{1.0, 0.0}, {0.0, -1.0}};
    Triangle t_1(points);
    Triangle t_2(points_2);
    EXPECT_FALSE(t_1 == t_2);
}

TEST(test_of_not_equality_square, not_equal_square)
{
    Point points[4] = {{-2.0, -2.0},{-2.0, 2.0},{2.0, 2.0}, {2.0, -2.0}};
    Square rect_1(points);
    Point points_2[4] = {{-1.0, -1.0},{-1.0, 1.0},{1.0, 1.0}, {1.0, -1.0}};
    Square rect_2(points_2);
    EXPECT_FALSE(rect_1 == rect_2);
}

TEST(test_of_equality_not_rectangles, not_equal_rectangles)
{
    Point points[4] = {{-3.0, -1.0},{-3.0, 1.0},{3.0, 1.0}, {3.0, -1.0}};
    Rectangle rect_1(points);
    Point points_2[4] = {{-4.0, -1.0},{-4.0, 1.0},{4.0, 1.0}, {4.0, -1.0}};
    Rectangle rect_2(points_2);
    EXPECT_FALSE(rect_1 == rect_2);
}

TEST(test_of_square_move, square_move_operator) {
    Point points[4] = {{-2.0, -2.0},{-2.0, 2.0},{2.0, 2.0}, {2.0, -2.0}};
    Rectangle rect_1(points);
    Rectangle rect_2;
    rect_2 = std::move(rect_1);
    ASSERT_NO_THROW(rect_2.get_data());
}

TEST(test_of_rectangle_move, rectangle_move_operator) {
    Point points[4] = {{-2.0, -2.0},{-2.0, 2.0},{2.0, 2.0}, {2.0, -2.0}};
    Rectangle rect_1(points);
    Rectangle rect_2;
    rect_2 = std::move(rect_1);
    ASSERT_NO_THROW(rect_2.get_data());
}

TEST(test_of_triangle_move, triangle_move_operator) {
    Point points[3] = {{-2.0, -2.0},{-2.0, 2.0},{0.0, 0.0}};
    Triangle tr_1(points);
    Triangle tr_2;
    tr_2 = std::move(tr_1);
    ASSERT_NO_THROW(tr_2.get_data());
}

TEST(test_of_triangle_copy, triangle_copy_operator) {
    Point points[3] = {{-2.0, -2.0},{-2.0, 2.0},{0.0, 0.0}};
    Triangle tr_1(points);
    Triangle tr_2 = tr_1;
    ASSERT_NO_THROW(tr_2.get_data());
}

TEST(test_of_square_copy, square_copy_operator) {
    Point points[4] = {{-2.0, -2.0},{-2.0, 2.0},{2.0, 2.0}, {2.0, -2.0}};
    Square rect_1(points);
    Square rect_2;
    rect_1 = rect_2;
    ASSERT_TRUE(rect_1 == rect_2);
}
TEST(test_of_rect_copy, rect_copy_operator) {
    Point points[4] = {{-2.0, -2.0},{-2.0, 2.0},{2.0, 2.0}, {2.0, -2.0}};
    Rectangle rect_1(points);
    Rectangle rect_2;
    rect_1 = rect_2;
    ASSERT_TRUE(rect_1 == rect_2);
}