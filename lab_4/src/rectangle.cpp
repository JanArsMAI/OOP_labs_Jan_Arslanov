#include "../include/rectangle.h"
#include <limits>
#include <cmath>
#include <stdexcept>

template <real_number T>
Rectangle<T>::Rectangle(const Point<T> points[4]) {
    for (int i = 0; i < 4; ++i) {
        this->points[i] = std::make_unique<Point<T>>(points[i]);
    }
    if (!is_valid_rect()) {
        throw std::invalid_argument("Points do not form a valid rectangle.");
    }
}

template <real_number T>
Rectangle<T>::Rectangle(const Rectangle &other) {
    for (int i = 0; i < 4; ++i) {
        points[i] = std::make_unique<Point<T>>(*other.points[i]);
    }
}

template <real_number T>
Rectangle<T>::Rectangle(Rectangle &&other) noexcept{
    for (int i = 0; i < 4; ++i)
    {
        points[i] = std::move(other.points[i]);
    }
}

template <real_number T>
Rectangle<T> &Rectangle<T>::operator=(const Rectangle &other){
    if (this != &other)
    {
        for (int i = 0; i < 4; ++i)
        {
            points[i] = std::make_unique<Point<T>>(*other.points[i]);
        }
    }
    return *this;
}

template <real_number T>
Rectangle<T> &Rectangle<T>::operator=(Rectangle &&other) noexcept{
    if (this != &other)
    {
        for (int i = 0; i < 4; ++i)
        {
            points[i] = std::move(other.points[i]);
        }
    }
    return *this;
}

template <real_number T>
bool Rectangle<T>::operator==(const Figure<T> &other) const{
    const Rectangle *otherrect = dynamic_cast<const Rectangle *>(&other);
    if (!otherrect)
        return false;
    for (int i = 0; i < 4; ++i)
    {
        if (*points[i] != *otherrect->points[i])
            return false;
    }
    return true;
}

template <real_number T>
Point<T> Rectangle<T>::center() const {
    double max_x = std::numeric_limits<double>::min();
    double min_x = std::numeric_limits<double>::max();
    double max_y = std::numeric_limits<double>::min();
    double min_y = std::numeric_limits<double>::max();
    for (size_t i = 0; i < 4; ++i) {
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
Rectangle<T>::operator double() const {
    double width = sqrt(std::pow(points[0]->get_x() - points[1]->get_x(), 2) + std::pow(points[0]->get_y() - points[1]->get_y(), 2));
    double height = sqrt(std::pow(points[1]->get_x() - points[2]->get_x(), 2) + std::pow(points[1]->get_y() - points[2]->get_y(), 2));
    return width * height;
}

template <real_number T>
bool Rectangle<T>::is_valid_rect() const {
    const auto& p1 = points[0];
    const auto& p2 = points[1];
    const auto& p3 = points[2];
    const auto& p4 = points[3];
    double diag1 = sqrt(pow(p1->get_x() - p3->get_x(), 2) + pow(p1->get_y() - p3->get_y(), 2));
    double diag2 = sqrt(pow(p2->get_x() - p4->get_x(), 2) + pow(p2->get_y() - p4->get_y(), 2));
    return diag1 == diag2;
}

template <real_number T>
std::ostream &operator<<(std::ostream &os, const Rectangle<T> &rect)
{
    os << "Rectangle points :";
    for (const auto &point : rect.points)
    {
        os << *point << " ";
    }
    return os;
}

template <real_number T>
std::istream &operator>>(std::istream &is, Rectangle<T> &rect)
{
    Point<T> points[4];
    for (int i = 0; i < 4; ++i)
    {
        is >> points[i];
    }
    for (int i = 0; i < 4; ++i)
    {
        rect.points[i] = std::make_unique<Point<T>>(points[i]);
    }
    return is;
}

template <real_number T>
void Rectangle<T>::get_data() const
{
    std::cout << *this << std::endl;
}