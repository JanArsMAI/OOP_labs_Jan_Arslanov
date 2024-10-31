#pragma once
#include "../include/figure.h"
#include "../include/point.h"
#include <memory>
#include <iostream>
#include <cmath>

template <real_number T>
class Triangle : public Figure<T>
{
public:
    Triangle() = default;
    Triangle(const Point<T> points[3]);
    Triangle(const Triangle &other);
    Triangle(Triangle &&other) noexcept;
    Triangle &operator=(const Triangle &other);
    Triangle &operator=(Triangle &&other) noexcept;
    bool operator==(const Figure<T> &other) const override;
    void get_data() const override;
    Point<T> center() const override;
    operator double() const override;
    template <real_number P>
    friend std::ostream &operator<<(std::ostream &os, const Triangle<P> &other);
    template <real_number P>
    friend std::istream &operator>>(std::istream &is, Triangle<P> &other);

private:
    std::unique_ptr<Point<T>> points[3];
    bool is_valid_tr() const;
};