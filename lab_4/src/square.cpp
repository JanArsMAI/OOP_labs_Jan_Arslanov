#include "../include/square.h"
#include <limits>
#include <cmath>
#include <stdexcept>

template <real_number T>
Square<T>::Square(const Point<T> points[4]) {
    for (int i = 0; i < 4; ++i) {
        this->points[i] = std::make_unique<Point<T>>(points[i]);
    }
    if (!is_valid_square()) {
        throw std::invalid_argument("Points do not form a valid Square.");
    }
}

template <real_number T>
Square<T>::Square(const Square &other) {
    for (int i = 0; i < 4; ++i) {
        points[i] = std::make_unique<Point<T>>(*other.points[i]);
    }
}

template <real_number T>
Square<T>::Square(Square &&other) noexcept {
    for (int i = 0; i < 4; ++i) {
        points[i] = std::move(other.points[i]);
    }
}

template <real_number T>
Square<T> &Square<T>::operator=(const Square &other) {
    if (this != &other) {
        for (int i = 0; i < 4; ++i) {
            points[i] = std::make_unique<Point<T>>(*other.points[i]);
        }
    }
    return *this;
}

template <real_number T>
Square<T> &Square<T>::operator=(Square &&other) noexcept {
    if (this != &other) {
        for (int i = 0; i < 4; ++i) {
            points[i] = std::move(other.points[i]);
        }
    }
    return *this;
}

template <real_number T>
bool Square<T>::operator==(const Figure<T> &other) const {
    const Square *otherSquare = dynamic_cast<const Square *>(&other);
    if (!otherSquare) return false;

    for (int i = 0; i < 4; ++i) {
        if (*points[i] != *otherSquare->points[i])
            return false;
    }
    return true;
}

template <real_number T>
Point<T> Square<T>::center() const {
    double max_x = std::numeric_limits<double>::min();
    double min_x = std::numeric_limits<double>::max();
    double max_y = std::numeric_limits<double>::min();
    double min_y = std::numeric_limits<double>::max();

    for (int i = 0; i < 4; ++i) {
        max_x = std::max(max_x, points[i]->get_x());
        min_x = std::min(min_x, points[i]->get_x());
        max_y = std::max(max_y, points[i]->get_y());
        min_y = std::min(min_y, points[i]->get_y());
    }

    double x = (min_x + max_x) / 2;
    double y = (min_y + max_y) / 2;
    return Point<T>(x, y);
}

template <real_number T>
Square<T>::operator double() const {
    double width = std::hypot(points[0]->get_x() - points[1]->get_x(), points[0]->get_y() - points[1]->get_y());
    double height = std::hypot(points[1]->get_x() - points[2]->get_x(), points[1]->get_y() - points[2]->get_y());
    return width * height;
}

template <real_number T>
bool Square<T>::is_valid_square() const {
    const auto &p1 = points[0];
    const auto &p2 = points[1];
    const auto &p3 = points[2];
    const auto &p4 = points[3];

    double side1 = std::hypot(p1->get_x() - p2->get_x(), p1->get_y() - p2->get_y());
    double side2 = std::hypot(p2->get_x() - p3->get_x(), p2->get_y() - p3->get_y());
    double side3 = std::hypot(p3->get_x() - p4->get_x(), p3->get_y() - p4->get_y());
    double side4 = std::hypot(p4->get_x() - p1->get_x(), p4->get_y() - p1->get_y());
    double first_diagonal = std::hypot(p1->get_x() - p3->get_x(), p1->get_y() - p3->get_y());
    double second_diagonal = std::hypot(p2->get_x() - p4->get_x(), p2->get_y() - p4->get_y());

    bool sides_equal = std::abs(side1 - side2) < 1e-9 && 
                       std::abs(side2 - side3) < 1e-9 && 
                       std::abs(side3 - side4) < 1e-9;
    bool diagonals_equal = std::abs(first_diagonal - second_diagonal) < 1e-9;

    return sides_equal && diagonals_equal;
}

template <real_number T>
std::ostream &operator<<(std::ostream &os, const Square<T> &square) {
    os << "Square points: ";
    for (const auto &point : square.points) {
        os << *point << " ";
    }
    return os;
}

template <real_number T>
std::istream &operator>>(std::istream &is, Square<T> &square) {
    Point<T> points[4];
    for (int i = 0; i < 4; ++i) {
        is >> points[i];
    }
    for (int i = 0; i < 4; ++i) {
        square.points[i] = std::make_unique<Point<T>>(points[i]);
    }
    if (!square.is_valid_square()) {
        throw std::invalid_argument("The entered points do not form a valid Square.");
    }
    return is;
}

template <real_number T>
void Square<T>::get_data() const {
    std::cout << *this << std::endl;
}