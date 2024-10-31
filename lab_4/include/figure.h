#pragma once
#include <iostream>
#include <ostream>
#include <cmath>
#include "point.h"

template <real_number T>
class Figure
{
public:
    virtual ~Figure() noexcept = default;
    virtual void get_data() const = 0;
    virtual operator double() const = 0;
    virtual bool operator==(const Figure &other) const = 0;
    virtual Point<T> center() const = 0;
};