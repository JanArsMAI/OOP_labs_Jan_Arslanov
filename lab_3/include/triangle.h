#pragma once
#include "../include/figure.h"
#include "../include/point.h"
#include <iostream>

class Triangle : public Figure
{
public:
    Triangle() = default;
    Triangle(const Point points[3]);
    Triangle &operator=(const Triangle &other);
    Triangle &operator=(Triangle &&other) noexcept;
    bool operator==(const Figure &other) const override;
    void get_data() const override;
    Point center() const override;
    operator double() const override;
    friend std::ostream &operator<<(std::ostream &os, const Triangle &another_tr);
    friend std::istream &operator>>(std::istream &is, Triangle &another_tr);

private:
    Point points[3];
    bool is_valid_or_not() const;
    bool check_for_equal_points(const Point& p1, const Point& p2, const Point& p3) const;
};