#include "../include/triangle.h"
#include <iostream>
#include <cmath>
#include <stdexcept>

Triangle::Triangle(const Point list_of_points[3]) {
    for (size_t i = 0; i < 3; ++i) {
        this->points[i] = list_of_points[i];
    }
    is_valid_or_not();
}

bool Triangle::is_valid_or_not() const {
    const Point first_point = this->points[0];
    const Point second_point = this->points[1];
    const Point third_point = this->points[2];

    if ((first_point.get_x() == second_point.get_x() && second_point.get_x() == third_point.get_x()) ||
        (first_point.get_y() == second_point.get_y() && second_point.get_y() == third_point.get_y())) {
        throw std::invalid_argument("All points are on the same line. Impossible to form a triangle.");
    }

    check_for_equal_points(first_point, second_point, third_point);

    double first_side = sqrt(pow(abs(first_point.get_x() - second_point.get_x()), 2) + pow(abs(first_point.get_y() - second_point.get_y()), 2));
    double second_side = sqrt(pow(abs(first_point.get_x() - third_point.get_x()), 2) + pow(abs(first_point.get_y() - third_point.get_y()), 2));
    double third_side = sqrt(pow(abs(second_point.get_x() - third_point.get_x()), 2) + pow(abs(second_point.get_y() - third_point.get_y()), 2));

    if ((first_side >= second_side + third_side) || 
        (second_side >= first_side + third_side) || 
        (third_side >= first_side + second_side)) {
        throw std::invalid_argument("Impossible to form a triangle with the given points.");
    }
    return true;
}

bool Triangle::check_for_equal_points(const Point& point_1, const Point& point_2, const Point& point_3) const {
    if ((point_1.get_x() == point_2.get_x() && point_1.get_y() == point_2.get_y()) || 
        (point_1.get_x() == point_3.get_x() && point_1.get_y() == point_3.get_y()) || 
        (point_2.get_x() == point_3.get_x() && point_2.get_y() == point_3.get_y())) {
        throw std::invalid_argument("Some points are the same. Impossible to form a triangle.");
    }
    return true;
}

Triangle& Triangle::operator=(const Triangle& other_triangle) {
    if (this != &other_triangle) {
        for (size_t i = 0; i < 3; ++i) {
            this->points[i] = other_triangle.points[i];
        }
    }
    return *this;
}

Triangle& Triangle::operator=(Triangle&& other_triangle) noexcept {
    if (this != &other_triangle) {
        for (int i = 0; i < 3; ++i) {
            points[i] = std::move(other_triangle.points[i]);
        }
    }
    return *this;
}

bool Triangle::operator==(const Figure& other) const {
    const Triangle* other_triangle = dynamic_cast<const Triangle*>(&other);
    if (!other_triangle) {
        return false;
    }
    for (size_t i = 0; i < 3; ++i) {
        if (this->points[i] != other_triangle->points[i]) {
            return false;
        }
    }
    return true;
}

Point Triangle::center() const {
    double x = 0.0;
    double y = 0.0;
    for (size_t i = 0; i < 3; ++i) {
        x += this->points[i].get_x();
        y += this->points[i].get_y();
    }
    return Point(x / 3, y / 3);
}


void Triangle::get_data() const {
    std::cout << *this << std::endl;
}

Triangle::operator double() const {
    const Point& first_point = this->points[0];
    const Point& second_point = this->points[1];
    const Point& third_point = this->points[2];

    double first_side = sqrt(pow(first_point.get_x() - second_point.get_x(), 2) + pow(first_point.get_y() - second_point.get_y(), 2));
    double second_side = sqrt(pow(first_point.get_x() - third_point.get_x(), 2) + pow(first_point.get_y() - third_point.get_y(), 2));
    double third_side = sqrt(pow(second_point.get_x() - third_point.get_x(), 2) + pow(second_point.get_y() - third_point.get_y(), 2));

    double half_perimeter = (first_side + second_side + third_side) / 2;
    double area = sqrt(half_perimeter * (half_perimeter - first_side) *
                       (half_perimeter - second_side) * 
                       (half_perimeter - third_side));

    return area;
}

std::ostream& Triangle::output(std::ostream& os) const {
    os << "Triangle points: ";
    for (const auto& point : points) {
        os << point << " ";
    }
    return os;
}

std::istream& Triangle::input(std::istream& is) {
    Point temp_points[3];
    for (int i = 0; i < 3; ++i) {
        is >> temp_points[i];
    }
    if (is.fail()) {
        throw std::invalid_argument("Error. Expected 3 points.");
    }
    for (int i = 0; i < 3; ++i) {
        points[i] = temp_points[i];
    }
    return is;
}

std::ostream& operator<<(std::ostream& os, const Triangle& object) {
    return object.output(os);
}

std::istream& operator>>(std::istream& is, Triangle& object) {
    return object.input(is);
}
