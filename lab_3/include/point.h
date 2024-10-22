#pragma once
#include <iostream>
#include <fstream>
#include <math.h>

class Point {
    private:
        double x;
        double y;

    public:
        Point() = default;
        Point (double xValue, double yValue);
        Point (const Point &other);
        Point (Point &&other);
        Point& operator= (const Point &other);
        Point& operator= (Point &&other);
        bool operator== (const Point &other) const;
        double get_x () const;
        double get_y () const;

        friend std::ostream& operator<< (std::ostream& os, const Point &point);
        friend std::istream& operator>> (std::istream& is, Point &point);
};

std::ostream& operator<< (std::ostream& os, const Point &point);
std::istream& operator>> (std::istream& is, Point &point);