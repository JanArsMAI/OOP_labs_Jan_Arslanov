#pragma once
#include "../include/figure.h"
#include "../include/point.h"

class Square : public Figure
{
public:
    Square() = default;
    Square(const Point points[4]);
    Square &operator=(const Square &other);
    Square &operator=(Square &&other) noexcept;
    bool operator==(const Figure &other) const override;
    void get_data() const override;
    Point center() const override;
    operator double() const override;

    std::ostream &output(std::ostream &os) const;
    std::istream &input(std::istream &is);

private:
    Point points[4];
    bool is_valid_or_not() const;
    bool check_for_equal_points(const Point& point_1, const Point& point_2, const Point& point_3, const Point& point_4) const;
};
