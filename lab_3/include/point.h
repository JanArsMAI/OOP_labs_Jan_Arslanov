#pragma once 
#include <ostream>
#include <istream>

struct Point
{
    double x, y; //координаты точки
    Point(): x(0), y(0) {}
    Point(double x, double y): x(x), y(y) {}
    friend std::ostream &operator<<(std::ostream& output, const Point& cur_point){
        output << "coordinate x: " << cur_point.x << " " << "coordinate y: " << cur_point.y;
        return output;
    }
    friend std::istream &operator>>(std::istream& input, Point& cur_point){
        input >> cur_point.x >> cur_point.y;
        return input;
    }
};
