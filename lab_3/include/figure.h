#pragma once
#include <iostream>
#include <fstream>
#include "point.h"

class Figure {
public:
    virtual Point center() const = 0;  // Добавлен const
    virtual operator double() const = 0;
    virtual bool operator==(const Figure& other) const = 0;
    virtual void get_data() const = 0;
    virtual ~Figure () = default;

protected:
    virtual std::ostream& output(std::ostream& os) const = 0;
    virtual std::istream& input(std::istream& is) = 0;

    friend std::ostream& operator<< (std::ostream& os, const Figure &figure);
    friend std::istream& operator>> (std::istream& is, Figure &figure);
};

std::ostream& operator<< (std::ostream& os, const Figure &figure);
std::istream& operator>> (std::istream& is, Figure &figure);
