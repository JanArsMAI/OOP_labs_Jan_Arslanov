#pragma once
#include "../include/figure.h"
#include "../include/point.h"
#include <memory>
#include <iostream>
#include <cmath>

template <real_number T>
class Square : public Figure<T>
{
public:
    Square() = default;
    Square(const Point<T> points[4]);
    Square(const Square &other);
    Square(Square &&other) noexcept;
    Square &operator=(const Square &other);
    Square &operator=(Square &&other) noexcept;
    bool operator==(const Figure<T> &other) const override;
    void get_data() const override;
    Point<T> center() const override;
    operator double() const override;

    template <real_number P>
    friend std::ostream &operator<<(std::ostream &os, const Square<P> &other);

    template <real_number P>
    friend std::istream &operator>>(std::istream &is, Square<P> &other);

private:
    std::unique_ptr<Point<T>> points[4];
    bool is_valid_square() const;
};