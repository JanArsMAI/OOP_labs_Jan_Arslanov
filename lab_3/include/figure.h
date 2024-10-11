#pragma once
#include <istream>
#include <ostream>
#include "../include/point.h"
#include <math.h>

class Figure{
    public:
    //используем virtual, чтобы функции роидетльского класса могли быть переопределены у произвольных классов
    
    virtual ~Figure() noexcept = default;
    virtual void get_data() const = 0;
    virtual operator double() const = 0;
    virtual bool operator==(const Figure &other) const = 0;
    virtual Point center() const = 0;
};