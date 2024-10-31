#include <gtest/gtest.h>
#include "../src/rectangle.cpp"
#include "../src/square.cpp"
#include "../src/triangle.cpp"
#include "../src/array.cpp"
#include <memory>

TEST(SquareTest, CorrectSquare) {
    Point<double> points[4] = {Point<double>{-1.0, -1.0}, Point<double>{-1.0, 1.0}, Point<double>{1.0, 1.0}, Point<double>{1.0, -1.0}};
    Square<double> square(points);
    ASSERT_EQ(static_cast<double>(square), 4.0);
    ASSERT_NO_THROW(square.get_data());
    Point<double> center = square.center();
    ASSERT_EQ(center.get_x(), 0.0);
    ASSERT_EQ(center.get_y(), 0.0);
}

TEST(TriangleTest, CorrectTriangle) {
    Point<double> points[3] = {Point<double>{0.0, 1.0}, Point<double>{1.0, 0.0}, Point<double>{0.0, -1.0}};
    Triangle<double> triangle(points);
    ASSERT_NO_THROW(triangle.get_data());
    Point<double> center = triangle.center();
    ASSERT_EQ(center.get_y(), 0.0);
}

TEST(RectangleTest, CorrectRectangle) {
    Point<double> points[4] = {Point<double>{-4.0, -1.0}, Point<double>{-4.0, 1.0}, Point<double>{4.0, 1.0}, Point<double>{4.0, -1.0}};
    Rectangle<double> rect(points);
    ASSERT_EQ(static_cast<double>(rect), 16.0);
    ASSERT_NO_THROW(rect.get_data());
    Point<double> center = rect.center();
    ASSERT_EQ(center.get_x(), 0.0);
    ASSERT_EQ(center.get_y(), 0.0);
}

TEST(TriangleTest, InvalidTriangle) {
    Point<double> points1[3] = {Point<double>{0.0, 0.0}, Point<double>{0.0, 1.0}, Point<double>{0.0, 5.0}};
    Point<double> points2[3] = {Point<double>{0.0, 0.0}, Point<double>{0.0, 1.0}, Point<double>{0.0, 0.0}};
    EXPECT_THROW(Triangle<double> triangle(points1), std::invalid_argument);
    EXPECT_THROW(Triangle<double> triangle(points2), std::invalid_argument);
}

TEST(RectangleTest, InvalidRectangle) {
    Point<double> points1[4] = {Point<double>{0.0, 0.0}, Point<double>{0.0, 1.0}, Point<double>{0.0, 5.0}, Point<double>{0.0, 3.0}};
    Point<double> points2[4] = {Point<double>{-4.0, -1.0}, Point<double>{-4.0, 1.0}, Point<double>{4.0, 1.0}, Point<double>{4.0, -1.2}};
    EXPECT_THROW(Rectangle<double> rect1(points1), std::invalid_argument);
    EXPECT_THROW(Rectangle<double> rect2(points2), std::invalid_argument);
}

TEST(SquareTest, InvalidSquare) {
    Point<double> points1[4] = {Point<double>{0.0, 0.0}, Point<double>{0.0, 1.0}, Point<double>{0.0, 5.0}, Point<double>{0.0, 3.0}};
    Point<double> points2[4] = {Point<double>{-4.0, -1.0}, Point<double>{-4.0, 1.0}, Point<double>{4.0, 1.0}, Point<double>{4.0, -1.2}};
    Point<double> points3[4] = {Point<double>{-4.0, -1.0}, Point<double>{-4.0, -1.0}, Point<double>{4.0, 1.0}, Point<double>{4.0, -1.0}};
    EXPECT_THROW(Square<double> square1(points1), std::invalid_argument);
    EXPECT_THROW(Square<double> square2(points2), std::invalid_argument);
    EXPECT_THROW(Square<double> square3(points3), std::invalid_argument);
}

TEST(SquareTest, Equality) {
    Point<double> points1[4] = {Point<double>{-1.0, -1.0}, Point<double>{-1.0, 1.0}, Point<double>{1.0, 1.0}, Point<double>{1.0, -1.0}};
    Square<double> square1(points1);
    Square<double> square2(points1);
    ASSERT_TRUE(square1 == square2);
}

TEST(TriangleTest, Inequality) {
    Point<double> points1[3] = {Point<double>{0.0, 2.0}, Point<double>{1.0, 0.0}, Point<double>{0.0, -1.0}};
    Point<double> points2[3] = {Point<double>{0.0, 1.0}, Point<double>{1.0, 0.0}, Point<double>{0.0, -1.0}};
    Triangle<double> triangle1(points1);
    Triangle<double> triangle2(points2);
    EXPECT_FALSE(triangle1 == triangle2);
}

TEST(SquareTest, MoveOperator) {
    Point<double> points[4] = {Point<double>{-2.0, -2.0}, Point<double>{-2.0, 2.0}, Point<double>{2.0, 2.0}, Point<double>{2.0, -2.0}};
    Square<double> square1(points);
    Square<double> square2 = std::move(square1);
    ASSERT_NO_THROW(square2.get_data());
}

TEST(TriangleTest, CopyOperator) {
    Point<double> points[3] = {Point<double>{-2.0, -2.0}, Point<double>{-2.0, 2.0}, Point<double>{0.0, 0.0}};
    Triangle<double> triangle1(points);
    Triangle<double> triangle2 = triangle1;
    ASSERT_NO_THROW(triangle2.get_data());
}


TEST(TriangleTest, AreaCalculation) {
    Point<double> points[3] = {Point<double>{0.0, 0.0}, Point<double>{4.0, 0.0}, Point<double>{0.0, 3.0}};
    Triangle<double> triangle(points);
    ASSERT_DOUBLE_EQ(static_cast<double>(triangle), 6.0);
}

TEST(RectangleTest, ChangeCoordinates) {
    Point<double> points[4] = {Point<double>{0.0, 0.0}, Point<double>{4.0, 0.0}, Point<double>{4.0, 2.0}, Point<double>{0.0, 2.0}};
    Rectangle<double> rect(points);
    ASSERT_EQ(static_cast<double>(rect), 8.0); 
}

TEST(TriangleTest, ZeroCoordinates) {
    Point<double> points[3] = {Point<double>{0.0, 0.0}, Point<double>{0.0, 0.0}, Point<double>{0.0, 0.0}};
    EXPECT_THROW(Triangle<double> triangle(points), std::invalid_argument);
}


TEST(RectangleTest, NegativeCoordinates) {
    Point<double> points[4] = {Point<double>{-1.0, -1.0}, Point<double>{-1.0, -2.0}, Point<double>{-2.0, -2.0}, Point<double>{-2.0, -1.0}};
    Rectangle<double> rect(points);
    ASSERT_EQ(static_cast<double>(rect), 1.0);
}

TEST(ArrayTest, push_test) {
    Array<Figure<double>> arr;
    Point<double> points[4] = {
        Point<double>{-1.0, -1.0}, 
        Point<double>{-1.0, 1.0}, 
        Point<double>{1.0, 1.0}, 
        Point<double>{1.0, -1.0}
    };
    std::shared_ptr<Square<double>> square = std::make_shared<Square<double>>(points);
    arr.push_back(square);
    EXPECT_EQ(arr.get_size(), 1);
}

TEST(ArrayTest, remove_test) {
    Array<Figure<double>> arr;
    Point<double> points[4] = {
        Point<double>{-1.0, -1.0}, 
        Point<double>{-1.0, 1.0}, 
        Point<double>{1.0, 1.0}, 
        Point<double>{1.0, -1.0}
    };
    std::shared_ptr<Square<double>> square = std::make_shared<Square<double>>(points);
    arr.push_back(square);
    
    EXPECT_EQ(arr.get_size(), 1);
    arr.remove(0);
    EXPECT_EQ(arr.get_size(), 0); 
}

TEST(ArrayTest, remove_out_of_bounds_test) {
    Array<Figure<double>> arr;
    EXPECT_THROW(arr.remove(0), std::invalid_argument);
}

TEST(ArrayTest, multiple_push_test) {
    Array<Figure<double>> arr;
    Point<double> points1[4] = {
        Point<double>{-1.0, -1.0}, 
        Point<double>{-1.0, 1.0}, 
        Point<double>{1.0, 1.0}, 
        Point<double>{1.0, -1.0}
    };
    Point<double> points2[4] = {
        Point<double>{-2.0, -2.0}, 
        Point<double>{-2.0, 2.0}, 
        Point<double>{2.0, 2.0}, 
        Point<double>{2.0, -2.0}
    };
    std::shared_ptr<Square<double>> square1 = std::make_shared<Square<double>>(points1);
    std::shared_ptr<Square<double>> square2 = std::make_shared<Square<double>>(points2);
    
    arr.push_back(square1);
    arr.push_back(square2);
    
    EXPECT_EQ(arr.get_size(), 2);
}