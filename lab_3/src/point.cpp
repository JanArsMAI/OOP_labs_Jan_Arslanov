#include "../include/point.h"


Point::Point(double x_1, double y_1) {
    this->x = x_1; 
    this->y = y_1;
}

Point::Point(const Point &other) {
    this->x = other.x; 
    this->y = other.y;
}

Point::Point(Point &&other) {
    std::swap(this->x, other.x);
    std::swap(this->y, other.y);
}

Point& Point::operator=(const Point &other) {
    if (this == &other) return *this;
    this->x = other.x;
    this->y = other.y;
    return *this;
}

Point& Point::operator=(Point &&other) {
    std::swap(this->x, other.x);
    std::swap(this->y, other.y);
    return *this;
}


bool Point::operator==(const Point &other) const {
    return (x == other.x && y == other.y);
}


double Point::get_x() const {
    return x;
}


double Point::get_y() const {
    return y;
}


std::ostream& operator<<(std::ostream& os, const Point &point) {
    os << "(" << point.x << ", " << point.y << ")";
    return os;
}

std::istream& operator>>(std::istream& is, Point &point) {
    double x, y;

    std::cout << "(" << std::endl << "\tInput x for point: ";
    is >> x;
    std::cout << "\tInput y for point: ";
    is >> y;
    std::cout << ")" << std::endl;

    point.x = x;
    point.y = y;

    return is;
}
