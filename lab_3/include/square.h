#ifndef SQUARE_H
#define SQUARE_H

#include "figure.h"
#include "point.h"
#include <iostream>

class Square : public Figure {
public:

    Square() = default;
    Square(const Point list_of_points[4]);
    Square (const Square &other);
    Square& operator=(const Square& other_square);
    Square& operator=(Square&& other_square) noexcept;
    bool operator==(const Figure &other) const override;
    explicit operator double() const override;
    Point center() const;
    void get_data() const override;
    friend std::ostream& operator<<(std::ostream& os, const Square& object);
    friend std::istream& operator>>(std::istream& is, Square& object);

private:
    Point points[4];
    bool is_valid_or_not() const;
    bool check_for_equal_points(const Point& point_1, const Point& point_2, const Point& point_3, const Point& point_4) const;
    std::ostream& output(std::ostream& os) const;
    std::istream& input(std::istream& is);
};

#endif
