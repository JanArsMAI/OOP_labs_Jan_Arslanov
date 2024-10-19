#include "../include/rectangle.h"
#include "../include/point.h"
#include <cmath>
#include <stdexcept>
#include <iostream>
#include <algorithm>
#include <limits>

Rectangle::Rectangle(const Point list_of_points[4]){
    for (size_t i = 0; i < 4; ++i){
        this->points[i] = list_of_points[i];
    }
    if (!is_valid_or_not()) {
        throw std::invalid_argument("Invalid rectangle, sides are not parallel.");
    }
}

bool Rectangle::is_valid_or_not() const {
    const Point& p1 = points[0];
    const Point& p2 = points[1];
    const Point& p3 = points[2];
    const Point& p4 = points[3];


    bool side1_parallel = (p1.get_x() == p2.get_x() || p1.get_y() == p2.get_y());
    bool side2_parallel = (p3.get_x() == p4.get_x() || p3.get_y() == p4.get_y());
    bool side3_parallel = (p2.get_x() == p3.get_x() || p2.get_y() == p3.get_y());
    bool side4_parallel = (p1.get_x() == p4.get_x() || p1.get_y() == p4.get_y());


    double first_diagonal = sqrt(std::pow(std::abs(p1.get_x() - p3.get_x()), 2) + std::pow(std::abs(p1.get_y() - p3.get_y()), 2));
    double second_diagonal = sqrt(std::pow(std::abs(p2.get_x() - p4.get_x()), 2) + std::pow(std::abs(p2.get_y() - p4.get_y()), 2));

    return side1_parallel && side2_parallel && side3_parallel && side4_parallel && (first_diagonal == second_diagonal);
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
    if (this != &other_rectangle) {
        for (int i = 0; i < 4; ++i) {
            points[i] = std::move(other_rectangle.points[i]);
        }
    }
    return *this;
}

bool Rectangle::operator==(const Figure &other) const {
    const Rectangle* other_rectangle = dynamic_cast<const Rectangle *>(&other);
    if (!other_rectangle) {
        return false;
    }
    for (size_t i = 0; i < 4; ++i){
        if ((this->points[i].get_x() != other_rectangle->points[i].get_x()) || (this->points[i].get_y() != other_rectangle->points[i].get_y())) {
            return false;
        }
    }
    return true;
}

Rectangle::operator double() const {
    const Point& p1 = points[0];
    const Point& p2 = points[1];
    const Point& p3 = points[2];

    double width = sqrt(std::pow(p1.get_x() - p2.get_x(), 2) + std::pow(p1.get_y() - p2.get_y(), 2));
    double height = sqrt(std::pow(p2.get_x() - p3.get_x(), 2) + std::pow(p2.get_y() - p3.get_y(), 2));

    return width * height;
}

std::ostream &Rectangle::output(std::ostream &os) const {
    os << "Rectangle points: ";
    for (const auto &point : points) {
        os << point << " ";
    }
    return os;
}

std::istream &Rectangle::input(std::istream &is) {
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

    if (!is_valid_or_not()) {
        throw std::invalid_argument("Invalid rectangle, not parallel or invalid diagonals.");
    }
    return is;
}

std::ostream &operator<<(std::ostream &os, const Rectangle &object) {
    return object.output(os);
}

std::istream &operator>>(std::istream &is, Rectangle &object) {
    return object.input(is);
}

Point Rectangle::center() const {
    double max_x = std::numeric_limits<double>::min();
    double min_x = std::numeric_limits<double>::max();
    double max_y = std::numeric_limits<double>::min();
    double min_y = std::numeric_limits<double>::max();

    for (size_t i = 0; i < 4; ++i) {
        max_x = std::max(max_x, points[i].get_x());
        min_x = std::min(min_x, points[i].get_x());
        max_y = std::max(max_y, points[i].get_y());
        min_y = std::min(min_y, points[i].get_y());
    }

    double x = (min_x + max_x) / 2;
    double y = (min_y + max_y) / 2;
    return Point(x, y);
}

void Rectangle::get_data() const {
    std::cout << *this << std::endl;
}
