#pragma once
#include "../include/figure.h"
#include "../include/point.h"
#include <memory>
#include <iostream>
#include <cmath>

template <real_number T>
class Rectangle : public Figure<T>
{
public:
    Rectangle() = default;
    Rectangle(const Point<T> points[4]);
    Rectangle(const Rectangle &other);
    Rectangle(Rectangle &&other) noexcept;
    Rectangle &operator=(const Rectangle &other);
    Rectangle &operator=(Rectangle &&other) noexcept;
    bool operator==(const Figure<T> &other) const override;
    void get_data() const override;
    Point<T> center() const override;
    operator double() const override;

    template <real_number P>
    friend std::ostream &operator<<(std::ostream &os, const Rectangle<P> &other);

    template <real_number P>
    friend std::istream &operator>>(std::istream &is, Rectangle<P> &other);

private:
    std::unique_ptr<Point<T>> points[4];
    bool is_valid_rect() const;
};