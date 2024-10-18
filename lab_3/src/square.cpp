#include "../include/square.h"
#include "../include/point.h"
#include <cmath>
#include <stdexcept>
#include <iostream>

Square::Square(const Point list_of_points[4]){
    for (size_t i = 0; i < 4; ++i){
        this->points[i] = list_of_points[i];
    }
    if (!is_valid_or_not()) {
        throw std::invalid_argument("Invalid square: all sides must be equal");
    }
}


bool Square::is_valid_or_not() const {
    const Point& p1 = points[0];
    const Point& p2 = points[1];
    const Point& p3 = points[2];
    const Point& p4 = points[3];
    double side1 = sqrt(std::pow(std::abs(p1.x - p2.x), 2) + std::pow(std::abs(p1.y - p2.y), 2));
    double side2 = sqrt(std::pow(std::abs(p2.x - p3.x), 2) + std::pow(std::abs(p2.y - p3.y), 2));
    double side3 = sqrt(std::pow(std::abs(p3.x - p4.x), 2) + std::pow(std::abs(p3.y - p4.y), 2));
    double side4 = sqrt(std::pow(std::abs(p4.x - p1.x), 2) + std::pow(std::abs(p4.y - p1.y), 2));
    bool sides_equal = (side1 == side2) && (side2 == side3) && (side3 == side4);
    double first_diagonal = sqrt(std::pow(std::abs(p1.x - p3.x), 2) + std::pow(std::abs(p1.y - p3.y), 2));
    double second_diagonal = sqrt(std::pow(std::abs(p2.x - p4.x), 2) + std::pow(std::abs(p2.y - p4.y), 2));
    bool diagonals_equal = (first_diagonal == second_diagonal);

    return sides_equal && diagonals_equal;
}

bool Square::check_for_equal_points(const Point& point_1, const Point& point_2, const Point& point_3, const Point& point_4) const {
    Point points[4] = {point_1, point_2, point_3, point_4};
    for (size_t i = 0; i < 4; ++i) {
        for (size_t j = i + 1; j < 4; ++j) {
            if ((points[i].x == points[j].x) && (points[i].y == points[j].y)) {
                throw std::invalid_argument("Square points must be different.");
            }
        }
    }
    return true;
}

Square &Square::operator=(const Square& other_square){
    if (this != &other_square){
        for (size_t i = 0; i < 4; ++i){
            this->points[i] = other_square.points[i];
        }
    }
    return *this;
}

Square &Square::operator=(Square&& other_square) noexcept {
    if (this != &other_square)
    {
        for (int i = 0; i < 4; ++i)
        {
            points[i] = std::move(other_square.points[i]);
        }
    }
    return *this;
}

bool Square::operator==(const Figure &other) const{
    const Square* other_square = dynamic_cast<const Square *>(&other);
    if (!other_square) {
        return false;
    }
    for (size_t i = 0; i < 4; ++i){
        if ((this->points[i].x != other_square->points[i].x) || (this->points[i].y != other_square->points[i].y)) {
            return false;
        }
    }
    return true;
}

Square::operator double() const {
    const Point& p1 = points[0];
    const Point& p2 = points[1];
    double side = sqrt(std::pow(std::abs(p1.x - p2.x), 2) + std::pow(std::abs(p1.y - p2.y), 2));

    return side * side;
}


std::ostream &Square::output(std::ostream &os) const {
    os << "Square: points = ";
    for (const auto &point : points) {
        os << point << " ";
    }
    return os;
}

std::istream &Square::input(std::istream &is) {
    Point temp_points[4];
    for (int i = 0; i < 4; ++i) {
        is >> temp_points[i];
    }
    if (is.fail()) {
        throw std::invalid_argument("Error. Expected 4 points.");
    }
    for (int i = 0; i < 4; ++i) {
        points[i] = temp_points[i];
    }
    return is;
}

std::ostream &operator<<(std::ostream &os, const Square &object) {
    return object.output(os);
}

std::istream &operator>>(std::istream &is, Square &object) {
    return object.input(is);
}


Point Square::center() const {
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

void Square::get_data() const
{
    std::cout << *this << std::endl;
}