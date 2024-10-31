#pragma once
#include <concepts>
#include <type_traits>
#include <memory>
#include <iostream>

template <typename T>
concept real_number = std::is_integral_v<T> || std::is_floating_point_v<T>;

template <real_number T>
class Point
{
public:
    Point(){
        x = 0;
        y = 0;
    }
    Point(T x_val, T y_val){
        x = x_val;
        y = y_val;
    }
    T get_x() const {
         return x; 
    }
    T get_y() const{
        return y; 
    }
    bool operator==(const Point &other) const
    {
        return (x == other.x && y == other.y);
    }

    friend std::ostream &operator<<(std::ostream &os, const Point &point)
    {
        os << "(" << point.x << ";" << point.y << ")";
        return os;
    }

    friend std::istream &operator>>(std::istream &is, Point &point)
    {
        is >> point.x >> point.y;
        return is;
    }

private:
    T x;
    T y;
};