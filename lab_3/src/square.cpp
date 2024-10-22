#include "../include/square.h"
#include "../include/point.h"
#include <cmath>
#include <stdexcept>
#include <iostream>

Square::Square(const Point list_of_points[4]) {
    for (size_t i = 0; i < 4; ++i) {
        this->points[i] = list_of_points[i];
    }
    if (!is_valid_or_not()) {
        throw std::invalid_argument("Invalid square: all sides and diagonals must be equal.");
    }
}
bool Square::is_valid_or_not() const {
    const Point& p1 = points[0];
    const Point& p2 = points[1];
    const Point& p3 = points[2];
    const Point& p4 = points[3];

    
    double side1 = sqrt(std::pow(p1.get_x() - p2.get_x(), 2) + std::pow(p1.get_y() - p2.get_y(), 2));
    double side2 = sqrt(std::pow(p2.get_x() - p3.get_x(), 2) + std::pow(p2.get_y() - p3.get_y(), 2));
    double side3 = sqrt(std::pow(p3.get_x() - p4.get_x(), 2) + std::pow(p3.get_y() - p4.get_y(), 2));
    double side4 = sqrt(std::pow(p4.get_x() - p1.get_x(), 2) + std::pow(p4.get_y() - p1.get_y(), 2));
    double first_diagonal = sqrt(std::pow(p1.get_x() - p3.get_x(), 2) + std::pow(p1.get_y() - p3.get_y(), 2));
    double second_diagonal = sqrt(std::pow(p2.get_x() - p4.get_x(), 2) + std::pow(p2.get_y() - p4.get_y(), 2));
    bool sides_equal = (side1 == side2) && (side2 == side3) && (side3 == side4);
    bool diagonals_equal = (first_diagonal == second_diagonal);

    return sides_equal && diagonals_equal;
}

bool Square::check_for_equal_points(const Point& point_1, const Point& point_2, const Point& point_3, const Point& point_4) const {
    Point points[4] = {point_1, point_2, point_3, point_4};
    for (size_t i = 0; i < 4; ++i) {
        for (size_t j = i + 1; j < 4; ++j) {
            if ((points[i].get_x() == points[j].get_x()) && (points[i].get_y() == points[j].get_y())) {
                throw std::invalid_argument("Square points must be distinct.");
            }
        }
    }
    return true;
}

Square& Square::operator=(const Square& other_square) {
    if (this != &other_square) {
        for (size_t i = 0; i < 4; ++i) {
            this->points[i] = other_square.points[i];
        }
    }
    return *this;
}

Square& Square::operator=(Square&& other_square) noexcept {
    if (this != &other_square) {
        for (int i = 0; i < 4; ++i) {
            points[i] = std::move(other_square.points[i]);
        }
    }
    return *this;
}

bool Square::operator==(const Figure& other) const {
    const Square* other_square = dynamic_cast<const Square*>(&other);
    if (!other_square) {
        return false;
    }
    for (size_t i = 0; i < 4; ++i) {
        if (this->points[i] != other_square->points[i]) {
            return false;
        }
    }
    return true;
}

Square::operator double() const {
    const Point& p1 = points[0];
    const Point& p2 = points[1];
    double side = sqrt(std::pow(p1.get_x() - p2.get_x(), 2) + std::pow(p1.get_y() - p2.get_y(), 2));
    return side * side;
}

std::ostream& Square::output(std::ostream& os) const {
    os << "Square: points = ";
    for (const auto& point : points) {
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

std::ostream& operator<<(std::ostream& os, const Square& object) {
    return object.output(os);
}

std::istream& operator>>(std::istream& is, Square& object) {
    return object.input(is);
}

Point Square::center() const {
    double max_x(0), min_x(100000), max_y(0), min_y(100000);
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

void Square::get_data() const {
    std::cout << *this << std::endl;
}
