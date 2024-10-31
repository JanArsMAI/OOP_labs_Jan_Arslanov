#include "../include/triangle.h"
#include <limits>
#include <cmath>
#include <stdexcept>

template <real_number T>
Triangle<T>::Triangle(const Point<T> points[3]) {
    for (int i = 0; i < 3; ++i) {
        this->points[i] = std::make_unique<Point<T>>(points[i]);
    }
    if (!is_valid_tr()) {
        throw std::invalid_argument("Points do not form a valid Triangle.");
    }
}

template <real_number T>
Triangle<T>::Triangle(const Triangle &other) {
    for (int i = 0; i < 3; ++i) {
        points[i] = std::make_unique<Point<T>>(*other.points[i]);
    }
}

template <real_number T>
Triangle<T>::Triangle(Triangle &&other) noexcept {
    for (int i = 0; i < 3; ++i) {
        points[i] = std::move(other.points[i]);
    }
}

template <real_number T>
Triangle<T> &Triangle<T>::operator=(const Triangle &other) {
    if (this != &other) {
        for (int i = 0; i < 3; ++i) {
            points[i] = std::make_unique<Point<T>>(*other.points[i]);
        }
    }
    return *this;
}

template <real_number T>
Triangle<T> &Triangle<T>::operator=(Triangle &&other) noexcept {
    if (this != &other) {
        for (int i = 0; i < 3; ++i) {
            points[i] = std::move(other.points[i]);
        }
    }
    return *this;
}

template <real_number T>
bool Triangle<T>::operator==(const Figure<T> &other) const {
    const Triangle *otherTriangle = dynamic_cast<const Triangle *>(&other);
    if (!otherTriangle) return false;

    for (int i = 0; i < 3; ++i) {
        if (*points[i] != *otherTriangle->points[i])
            return false;
    }
    return true;
}

template <real_number T>
Point<T> Triangle<T>::center() const {
    T x = 0.0;
    T y = 0.0;
    for (int i = 0; i < 3; ++i) {
        x += this->points[i]->get_x();
        y += this->points[i]->get_y();
    }
    return Point<T>(x / 3, y / 3);
}

template <real_number T>
Triangle<T>::operator double() const {
    const auto &p1 = points[0];
    const auto &p2 = points[1];
    const auto &p3 = points[2];
    
    double first_side = std::hypot(p1->get_x() - p2->get_x(), p1->get_y() - p2->get_y());
    double second_side = std::hypot(p1->get_x() - p3->get_x(), p1->get_y() - p3->get_y());
    double third_side = std::hypot(p2->get_x() - p3->get_x(), p2->get_y() - p3->get_y());

    double half_perimeter = (first_side + second_side + third_side) / 2;
    double area = sqrt(half_perimeter * (half_perimeter - first_side) *
                       (half_perimeter - second_side) * 
                       (half_perimeter - third_side));

    return area;
}

template <real_number T>
bool Triangle<T>::is_valid_tr() const {
    const auto &p1 = points[0];
    const auto &p2 = points[1];
    const auto &p3 = points[2];

    if ((p1->get_x() == p2->get_x() && p2->get_x() == p3->get_x()) ||
        (p1->get_y() == p2->get_y() && p2->get_y() == p3->get_y())) {
        return false;
    }

    double first_side = std::hypot(p1->get_x() - p2->get_x(), p1->get_y() - p2->get_y());
    double second_side = std::hypot(p1->get_x() - p3->get_x(), p1->get_y() - p3->get_y());
    double third_side = std::hypot(p2->get_x() - p3->get_x(), p2->get_y() - p3->get_y());
    return (first_side < second_side + third_side) &&
           (second_side < first_side + third_side) &&
           (third_side < first_side + second_side);
}

template <real_number T>
std::ostream &operator<<(std::ostream &os, const Triangle<T> &triangle) {
    os << "Triangle points: ";
    for (const auto &point : triangle.points) {
        os << *point << " ";
    }
    return os;
}

template <real_number T>
std::istream &operator>>(std::istream &is, Triangle<T> &triangle) {
    Point<T> points[3];
    for (int i = 0; i < 3; ++i) {
        is >> points[i];
    }
    for (int i = 0; i < 3; ++i) {
        triangle.points[i] = std::make_unique<Point<T>>(points[i]);
    }
    if (!triangle.is_valid_tr()) {
        throw std::invalid_argument("The entered points do not form a valid Triangle.");
    }
    return is;
}

template <real_number T>
void Triangle<T>::get_data() const {
    std::cout << *this << std::endl;
}