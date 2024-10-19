#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "figure.h"
#include "point.h"
#include <iostream>

class Rectangle : public Figure {
public:
    Rectangle() = default;
    Rectangle(const Point list_of_points[4]);
    Rectangle& operator=(const Rectangle& other_rectangle);
    Rectangle& operator=(Rectangle&& other_rectangle) noexcept;
    bool operator==(const Figure& other) const override;
    operator double() const override;
    std::ostream& output(std::ostream& os) const;
    std::istream& input(std::istream& is);
    Point center() const;
    void get_data() const override;

private:
    Point points[4];
    bool is_valid_or_not() const;
    bool check_for_equal_points(const Point& point_1, const Point& point_2, const Point& point_3, const Point& point_4) const;
};

std::ostream& operator<<(std::ostream& os, const Rectangle& object);
std::istream& operator>>(std::istream& is, Rectangle& object);

#endif