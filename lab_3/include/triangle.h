#pragma once
#include "figure.h"
#include "point.h"
#include <iostream>

class Triangle : public Figure {
public:
    Triangle() = default;
    Triangle(const Point list_of_points[3]);
    Triangle& operator=(const Triangle& other_triangle);
    Triangle& operator=(Triangle&& other_triangle) noexcept;
    bool operator==(const Figure& other) const override;
    operator double() const override;
    std::ostream& output(std::ostream& os) const override;
    std::istream& input(std::istream& is) override;
    Point center() const override;
    void get_data() const override;

private:
    Point points[3];
    bool is_valid_or_not() const;
    bool check_for_equal_points(const Point& point_1, const Point& point_2, const Point& point_3) const;
};
