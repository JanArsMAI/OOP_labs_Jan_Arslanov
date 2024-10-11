#include "../include/rectangle.h"
#include "../include/point.h"
#include <cmath>
#include <stdexcept>
#include <iostream>

Rectangle::Rectangle(const Point list_of_points[4]){
    for (size_t i = 0; i < 4; ++i){
        this->points[i] = list_of_points[i];
    }
    if (!is_valid_or_not()) {
        throw std::invalid_argument("Invalid rectangle, not parralel");
    }
}

bool Rectangle::is_valid_or_not() const {
    const Point& p1 = points[0];
    const Point& p2 = points[1];
    const Point& p3 = points[2];
    const Point& p4 = points[3];

    bool side1_parallel = (p1.x == p2.x) || (p1.y == p2.y);
    bool side2_parallel = (p3.x == p4.x) || (p3.y == p4.y);
    double first_diagonal = sqrt(std::pow(std::abs(p1.x - p3.x), 2) + std::pow(std::abs(p1.y - p3.y), 2));
    double second_diagonal = sqrt(std::pow(std::abs(p2.x - p4.x), 2) + std::pow(std::abs(p2.y - p4.y), 2));
    bool diagonal_equal = (first_diagonal == second_diagonal);

    return side1_parallel && side2_parallel && diagonal_equal;
}


bool Rectangle::check_for_equal_points(const Point& point_1, const Point& point_2, const Point& point_3, const Point& point_4) const {
    Point points[4] = {point_1, point_2, point_3, point_4};
    for (size_t i = 0; i < 4; ++i) {
        for (size_t j = i + 1; j < 4; ++j) {
            if ((points[i].x == points[j].x) && (points[i].y == points[j].y)) {
                throw std::invalid_argument("Rectangle points must be different");
            }
        }
    }
    return true;
}

Rectangle &Rectangle::operator=(const Rectangle& other_rectangle){
    if (this != &other_rectangle){
        for (size_t i = 0; i < 4; ++i){
            this->points[i] = other_rectangle.points[i];
        }
    }
    return *this;
}

Rectangle &Rectangle::operator=(Rectangle&& other_rectangle) noexcept {
    if (this != &other_rectangle)
    {
        for (int i = 0; i < 4; ++i)
        {
            points[i] = std::move(other_rectangle.points[i]);
        }
    }
    return *this;
}

bool Rectangle::operator==(const Figure &other) const{
    const Rectangle* other_rectangle = dynamic_cast<const Rectangle *>(&other);
    if (!other_rectangle) {
        return false;
    }
    for (size_t i = 0; i < 4; ++i){
        if ((this->points[i].x != other_rectangle->points[i].x) || (this->points[i].y != other_rectangle->points[i].y)) {
            return false;
        }
    }
    return true;
}


Rectangle::operator double() const {
    const Point& p1 = points[0];
    const Point& p2 = points[1];
    const Point& p3 = points[2];
    const Point& p4 = points[3];

    double width = sqrt(std::pow(std::abs(p1.x - p2.x), 2) + std::pow(std::abs(p1.y - p2.y), 2));
    double height = sqrt(std::pow(std::abs(p2.x - p3.x), 2) + std::pow(std::abs(p2.y - p3.y), 2));
    double square = width * height;
    return square;
}


std::ostream &operator<<(std::ostream &os, const Rectangle &object) {
    os << "Rectangle: points = ";
    for (const auto &point : object.points) {
        os << point << " ";
    }
    return os;
}

std::istream &operator>>(std::istream &is, Rectangle &object) {
    Point points[4];
    for (int i = 0; i < 4; ++i) {
        is >> points[i];
    }
    if (is.fail()) {
        throw std::invalid_argument("Error. Expected 4 points.");
    }
    for (int i = 0; i < 4; ++i) {
        object.points[i] = points[i];
    }
    return is;
}

Point Rectangle::center() const{
    double x(0), y(0);
    double max_x(0), min_x(100000), max_y(0), min_y(100000);
    for (size_t i = 0; i < 4; ++i){
        max_x = std::max(max_x, points[i].x);
        min_x = std::min(min_x, points[i].x);
        max_y = std::max(max_y, points[i].y);
        min_y = std::min(min_y, points[i].y);
    }
    x = (min_x + max_x) / 2;
    y = (min_y + max_y) / 2;
    Point answer_point = Point(x, y);
    return answer_point;
}

void Rectangle::get_data() const
{
    std::cout << *this << std::endl;
}